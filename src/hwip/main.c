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

#include "../libclp/clp.h"
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "../libhwip/hwip.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum {
	ENCAPSULATE,
	DECAPSULATE
} MODE;

int main (int argc, char **argv) {
	MODE mode;
	bool dumpData = false;
	bool gui = false;
	int version = 0;
	int ttl = 0;

    printf("setting version\n");
    clpInit(PROJECT_NAME, PROJECT_VERSION);
    printf("assigning params\n");
    clpAddArgument("-1", "Check for grade \"1\".");
    clpAddArgument("-2", "Check for grade \"2\".");
    clpAddArgument("-3", "Check for grade \"3\".");
    printf("parsing command line\n");
    clpParse(argc, argv);
    //if (clpGetFlag("-3")) {
    if (strcmp(argv[1], "-3") == 0) {
        //IPV4_PACKET *packet = hwipCreateSchoolModePacket("");
        IPV4_PACKET *packet = malloc(sizeof(IPV4_PACKET));
        memset(packet, '\0', sizeof(IPV4_PACKET));
        packet->header = malloc(sizeof(IPV4_HEADER));
        memset(packet->header, '\0', sizeof(IPV4_HEADER));
        readIPv4Packet(packet);
        dumpIPv4HeaderSchoolMode(packet->header);
        free(packet->header);
        free(packet);
    }
    //if (clpGetFlag("-2")) {
    if (strcmp(argv[1], "-2") == 0) {
        IPV4_PACKET *packet = hwipCreateSchoolModePacket("");
        dumpIPv4HeaderSchoolModeBinary(packet->header);
        free(packet->header);
        free(packet);
    }
    //if (clpGetFlag("-1")) {
    if (strcmp(argv[1], "-1") == 0) {
        char buf[1000];
        memset(buf, '\0', 1000 * sizeof(char));
        fgets(buf, 1000, stdin);
        IPV4_PACKET *packet = hwipDecodeSchoolMode(buf);
        dumpIPv4Header(packet->header);
        free(packet->header);
        free(packet);
    }

}
