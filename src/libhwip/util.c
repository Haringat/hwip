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
    printf("version: %u\nheader length: %u\ntype of service: %x\ntotal packet length: %u\nidentification: %u\nflags:\n  (reserved): %u\n  don't fragment: %u\n  more fragments: %u\nfragment offset: %u\ntime to live: %u\nnext protocol: %s\nchecksum: %x\nsource address: %u.%u.%u.%u\ndestination address: %u.%u.%u.%u\n",
           header->version,
           header->ihl,
           header->tos,
           header->totalLength,
           header->identification,
           header->flags & 0x4,
           header->flags & 0x2,
           header->flags & 0x1,
           header->fragmentOffset,
           header->ttl,
           hwipProtocols[header->protocol],
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

void dumpIPv4HeaderSchoolMode(IPV4_HEADER *header) {
    printf("%u-%u-%u-%u-%u-%u%u%u-%u-%u-%u-%u-%u.%u.%u.%u-%u.%u.%u.%u\n",
           header->version,
           header->ihl,
           header->tos,
           header->totalLength,
           header->identification,
           header->flags & 0x4,
           header->flags & 0x2,
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

void dumpIPv4HeaderSchoolModeBinary(IPV4_HEADER *header) {
    // buffer the values because the fields in a bitfield do not have adresses for pointers
    int8_t version = header->version;
    int8_t ihl = header->ihl;
    int8_t tos = header->tos;
    int16_t totalLength = header->totalLength;
    int16_t identification = header->identification;
    int8_t flags = header->flags;
    int16_t fragmentOffset = header->fragmentOffset;
    int8_t ttl = header->ttl;
    int8_t protocol = header->protocol;
    int16_t checksum = header->checksum;
    int32_t source = header->source;
    int32_t destination = header->destination;
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

// TODO: Modify to support Big Endian
// based on user295190's answer on http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format#112956
void printBits(const size_t bitSize, const void *ptr) {
    uint32_t *b = (uint32_t *) ptr;
    unsigned char byte;
    int i, j;

    for (i=(int) bitSize;i>=0;i--) {
        byte = (unsigned char) ((*b >> i) & 1);
        printf("%u", byte);
    }
}
