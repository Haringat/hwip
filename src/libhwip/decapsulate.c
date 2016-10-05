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
#include <memory.h>
#include <stdio.h>
#include "hwip.h"
#include "../utils/stubber.h"

IPV4_PACKET *hwipDecodeSchoolMode(const char *ascii) {
    IPV4_PACKET *ret = malloc(sizeof(IPV4_PACKET));
    ret->header = malloc(sizeof(IPV4_HEADER));
    IPV4_HEADER *header = ret->header;
    /*char *binstr = malloc(strlen(ascii));
    strcpy(binstr, ascii);*/
    char *binstr = (char *) ascii;
    header->version = (uint8_t) strtol(binstr, &binstr, 2);
    if (header->version == 6) {
        printf("ipv6 is not implemented yet.");
        exit(1);
    }
    if (header->version != 4) {
        printf("invalid version specified");
        exit(2);
    }
    binstr++;
    header->ihl = (uint8_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->tos = (uint8_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->totalLength = (uint16_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->identification = (uint16_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->flags = (uint8_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->fragmentOffset = (uint16_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->ttl = (uint8_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->protocol = (uint8_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->checksum = (uint16_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->source = (uint32_t) strtol(binstr, &binstr, 2);
    binstr++;
    header->destination = (uint32_t) strtol(binstr, &binstr, 2);
    return ret;
}

// 0100 00101 100011000 00000000000000101 10000000000000000 0000 00000000000000 000100000 000000000 00100000101101010 011000011101010000000000101100110 011011111101010000000000101100110