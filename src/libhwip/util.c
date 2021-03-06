/*
 * Copyright (c) 2016 Marcel Mundl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "hwip.h"
#include "../utils/utils.h"

IPV4_PACKET *hwipCreateSchoolModePacket(const char *options) {
    IPV4_PACKET *ret = malloc(sizeof(IPV4_PACKET));
    memset(ret, '\0', sizeof(IPV4_PACKET));
    IPV4_HEADER *header = malloc(sizeof(IPV4_HEADER));
    ret->header = header;
    header->version = 4;
    header->tos = 24;
    header->ECN = 0;
    header->source = (unsigned int) ((195 << 24) | (168 << 16) | (1 << 8) | 102);
    header->destination = (unsigned int) ((223 << 24) | (168 << 16) | (1 << 8) | 102);
    header->checksum = 0;
    header->identification = 0;
    header->ttl = 32;
    header->fragmentOffset = 0;
    header->protocol = 0;
    ret->payload = (char *)NULL;
    memset(header->options, '\0', 11 * sizeof(uint32_t));
    strcpy((char *) header->options, options);

    hwipCalculateIHL(header);
    header->totalLength = header->ihl;
    hwipCalculateChecksum(header);

    return ret;
}

void hwipCalculateIHL(IPV4_HEADER *header) {
    size_t optionsSize = strlen((char *)header->options);
    header->ihl = (uint8_t) ((uint8_t) 5 + (unsigned long int) ceil(optionsSize / 4.0));
}

void hwipCalculateChecksum(IPV4_HEADER *header) {
    header->checksum = 0;
    uint32_t sum = 0;
    uint16_t *runner = (uint16_t *)header;
    for (int i = 0; i < header->ihl * 2; i++) {
        sum += *runner;
        runner += 1;
    }
    uint16_t *carry;
    // TODO: support big endian
    while (*(carry = (uint16_t *) (&sum) + 2) != 0) {
        uint16_t carryBuffer = *(carry);
        *carry = 0;
        sum += carryBuffer;
    }
    header->checksum = (uint16_t) (sum ^ 0xffff);
}

bool hwipVerifyChecksum(IPV4_HEADER *header) {
    uint32_t sum = 0;
    uint16_t *runner = (uint16_t *)header;
    for (int i = 0; i < header->ihl / 2; i++) {
        sum += *runner;
        runner += 2;
    }
    uint16_t *carry;
    while (*(carry = (uint16_t *) &sum) != 0) {
        int carryBuffer = *carry;
        *carry = 0;
        sum += carryBuffer;
    }
    return sum == 0xffff;
}

void dumpIPv4Header(IPV4_HEADER *header) {
    printf("version: %u\nheader length: %u\ntype of service: %x\ntotal packet length: %u\nidentification: %u\nflags:\n  (reserved): %u\n  don't fragment: %u\n  more fragments: %u\nfragment offset: %u\ntime to live: %u\nnext protocol: %s\nchecksum: %x\nsource address: %u.%u.%u.%u\ndestination address: %u.%u.%u.%u\noptions: \"%s\"",
           header->version,
           header->ihl,
           header->tos,
           header->totalLength,
           header->identification,
           header->flags >> 2,
           (header->flags >> 1) & 0x1,
           header->flags & 0x1,
           header->fragmentOffset,
           header->ttl,
           (header->protocol < sizeof(hwipProtocols) ? hwipProtocols[header->protocol] : "UNKNOWN PROTOCOL"),
           header->checksum,
           (header->source >> 24) & 0xff,
           (header->source >> 16) & 0xff,
           (header->source >> 8) & 0xff,
           header->source & 0xff,
           (header->destination >> 24) & 0xff,
           (header->destination >> 16) & 0xff,
           (header->destination >> 8) & 0xff,
           header->destination & 0xff,
           header->options ? (char *) header->options : ""
    );
}

void readIPv4Packet(IPV4_PACKET *packet) {
    IPV4_HEADER *header = packet->header;
    char buffer[100];
    printf("version: ");
    fflush(stdout);
    header->version = (uint8_t) atoi(fgets(buffer, 3, stdin));
    memset(buffer, '\0', 100);
    if (header->version == 6) {
        error("IPV6 is not supported yet");
        exit(1);
    } else if (header->version != 4) {
        error("unknown or invalid ip version specified");
        exit(-1);
    }
    printf("type of service: ");
    fflush(stdout);
    header->tos = (uint8_t) atoi(fgets(buffer, 4, stdin));
    memset(buffer, '\0', 100);
    printf("Explicit Congestion Notification(ECN): ");
    fflush(stdout);
    header->ECN = (uint8_t) atoi(fgets(buffer, 3, stdin));
    memset(buffer, '\0', 100);
    printf("identification: ");
    fflush(stdout);
    header->identification = (uint16_t) atoi(fgets(buffer, 7, stdin));
    memset(buffer, '\0', 100);
    printf("Don't fragment(0 or 1): ");
    fflush(stdout);
    uint_fast8_t dontFragment = (uint8_t) atoi(fgets(buffer, 3, stdin));
    memset(buffer, '\0', 100);
    if (dontFragment > 1) {
        error("Flag can only contain 0 or 1");
        exit(-1);
    }
    printf("More fragments(0 or 1): ");
    fflush(stdout);
    uint_fast8_t moreFragments = (uint8_t) atoi(fgets(buffer, 3, stdin));
    memset(buffer, '\0', 100);
    if (moreFragments > 1) {
        error("Flag can only contain 0 or 1");
        exit(-1);
    }
    header->flags = (dontFragment << 1) | moreFragments;
    printf("fragment offset: ");
    fflush(stdout);
    header->fragmentOffset = (uint16_t) atoi(fgets(buffer, 7, stdin));
    memset(buffer, '\0', 100);
    printf("time to live: ");
    fflush(stdout);
    header->ttl = (uint8_t) atoi(fgets(buffer, 5, stdin));
    memset(buffer, '\0', 100);
    printf("protocol: ");
    fflush(stdout);
    fgets(buffer, 100, stdin);
    strrep(buffer, '\n', '\0');
    bool foundProtocol = false;
    for (int i = 0; i < hwipProtocolCount; i++) {
        if (strcmp(hwipProtocols[i], buffer) == 0) {
            header->protocol = (uint8_t) i;
            foundProtocol = true;
            break;
        }
    }
    if (!foundProtocol) {
        error("invalid or unknown protocol specified.");
        exit(-1);
    }
    memset(buffer, '\0', 100);
    printf("source address:");
    fgets(buffer, 16, stdin);
    header->source = (uint_fast8_t) atoi(strtok(buffer, ".")) << 24;
    header->source += (uint_fast8_t) atoi(strtok(NULL, ".")) << 16;
    header->source += (uint_fast8_t) atoi(strtok(NULL, ".")) << 8;
    header->source += (uint_fast8_t) atoi(strtok(NULL, "."));
    memset(buffer, '\0', 100);
    printf("destination address:");
    fgets(buffer, 16, stdin);
    header->destination = (uint_fast8_t) atoi(strtok(buffer, ".")) << 24;
    header->destination += (uint_fast8_t) atoi(strtok(NULL, ".")) << 16;
    header->destination += (uint_fast8_t) atoi(strtok(NULL, ".")) << 8;
    header->destination += (uint_fast8_t) atoi(strtok(NULL, "."));
    memset(buffer, '\0', 100);

    hwipCalculateIHL(header);

    header->totalLength = header->ihl;

    hwipCalculateChecksum(header);
}

void dumpIPv4HeaderSchoolMode(IPV4_HEADER *header) {
    printf("%u-%u-%u-%u-%u-%u%u%u-%u-%u-%u-%u-%u.%u.%u.%u-%u.%u.%u.%u\n",
           header->version,
           header->ihl,
           header->tos,
           header->totalLength,
           header->identification,
           header->flags >> 2,
           (header->flags >> 1) & 0x1,
           header->flags & 0x1,
           header->fragmentOffset,
           header->ttl,
           header->protocol,
           header->checksum,
           (header->source >> 24) & 0xff,
           (header->source >> 16) & 0xff,
           (header->source >> 8) & 0xff,
           header->source & 0xff,
           (header->destination >> 24) & 0xff,
           (header->destination >> 16) & 0xff,
           (header->destination >> 8) & 0xff,
           header->destination & 0xff);
}

char *strrep(char *string, char needle, char token) {
    for(char *runner = string; *runner != '\0'; runner++) {
        if (*runner == needle) {
            *runner = token;
            return runner + 1;
        }
    }
}

void dumpIPv4HeaderSchoolModeBinary(IPV4_HEADER *header) {
    // buffer the values because the fields in a bitfield do not have adresses for pointers
    int8_t version = header->version;
    int8_t ihl = header->ihl;
    int8_t tos = header->tos;
    int16_t totalLength = toBE16(header->totalLength);
    int16_t identification = toBE16(header->identification);
    int8_t flags = header->flags;
    int16_t fragmentOffset = toBE16(header->fragmentOffset);
    int8_t ttl = header->ttl;
    int8_t protocol = header->protocol;
    int16_t checksum = toBE16(header->checksum);
    int32_t source = toBE32(header->source);
    int32_t destination = toBE32(header->destination);
    printBits(4, &version);
    putchar(' ');
    printBits(4, &ihl);
    putchar(' ');
    printBits(8, &tos);
    putchar(' ');
    printBits(16, &totalLength);
    putchar(' ');
    printBits(16, &identification);
    putchar(' ');
    printBits(3, &flags);
    putchar(' ');
    printBits(13, &fragmentOffset);
    putchar(' ');
    printBits(8, &ttl);
    putchar(' ');
    printBits(8, &protocol);
    putchar(' ');
    printBits(16, &checksum);
    putchar(' ');
    printBits(32, &source);
    putchar(' ');
    printBits(32, &destination);
}

// based on user295190's answer on http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format#112956
void printBits(const size_t bitSize, const void *ptr) {

    size_t byteCount = (size_t) (ceil((double) bitSize / 8.0));
    void *workCopy = malloc(byteCount);
    memcpy(workCopy, ptr, byteCount);

    size_t border = (size_t) floor((double) bitSize / 8.0);
    // convert to BE

    uint8_t *b = (uint8_t *) workCopy;
    uint8_t byte;

    for (size_t j = 0; j <= border; j++) {
        int byteLimit = (j == border ? bitSize % 8 : 8) - 1;
        for (int_fast8_t i = (int_fast8_t) byteLimit;i>=0;i--) {
            byte = (uint8_t) ((*b >> i) & 1);
            printf("%u", byte);
        }
        b++;
    }
}

uint32_t toBE32(uint32_t le) {
    return (u_int32_t) (((le & 0xff000000) >> 24) |
                        ((le & 0x00ff0000) >>  8) |
                        ((le & 0x0000ff00) <<  8) |
                        ((le & 0x000000ff) << 24));
}

uint16_t toBE16(uint16_t le) {
    return (uint16_t) (((le & 0xff00) >> 8) |
                       ((le & 0x00ff) << 8));
}