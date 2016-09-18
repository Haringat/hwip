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



#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "hwip.spec.h"
#include "../hwip.h"

int main(int argc, char **argv) {
    printf("testing hwipCreateSchoolModePacket...");
    if (test_hwipCreateSchoolModePacket()) {
        printf("success\n");
    } else {
        printf("failure\n");
    }
    /*printf("testing hwipCreateSchoolModePacket...");
    if (test_hwipCreateSchoolModePacket()) {
        printf("success\n");
    } else {
        printf("failure\n");
    }
    printf("testing hwipCreateSchoolModePacket...");
    if (test_hwipCreateSchoolModePacket()) {
        printf("success\n");
    } else {
        printf("failure\n");
    }
    printf("testing hwipCreateSchoolModePacket...");
    if (test_hwipCreateSchoolModePacket()) {
        printf("success\n");
    } else {
        printf("failure\n");
    }
    printf("testing hwipCreateSchoolModePacket...");
    if (test_hwipCreateSchoolModePacket()) {
        printf("success\n");
    } else {
        printf("failure\n");
    }*/
}

bool test_hwipCreateSchoolModePacket() {
    IPV4_PACKET *actual = hwipCreateSchoolModePacket("");
    IPV4_PACKET *expected = malloc(sizeof(IPV4_PACKET));
    expected->header = malloc(sizeof(IPV4_HEADER));
    IPV4_HEADER *header = expected->header;
    memset(header, '\0', sizeof(IPV4_HEADER));
    header->version = 4;
    header->ihl = 5;
    header->tos = 24;
    header->totalLength = 5;
    header->identification = 0;
    header->flags = 0;
    header->fragmentOffset = 0;
    header->ttl = 32;
    header->protocol = 0;
    header->checksum = 0xA659;
    header->source = 0xC3A80166;
    header->destination = 0xC3A80166;

    if (memcmp(actual->header, expected->header, sizeof(IPV4_HEADER)) == 0) {
        return true;
    } else {
        printf("got:\n");
        //dumpIPv4Header(actual->header);
        //dumpIPv4HeaderSchoolMode(actual->header);
        dumpIPv4HeaderSchoolModeBinary(actual->header);
        printf("expected:\n");
        //dumpIPv4Header(expected->header);
        //dumpIPv4HeaderSchoolMode(expected->header);
        dumpIPv4HeaderSchoolModeBinary(expected->header);
        return false;
    }
}
