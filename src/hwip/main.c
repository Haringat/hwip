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
    clpInit();
    printf("assigning params\n");
    const char *schoolModeAliases[14] = {
            "--school-mode",
            "-s",
    };
    clpAddArgumentWithAlias(schoolModeAliases, 2, "Execute in school mode.");
    const char *version
    clpParse(argc, argv);
    //clpAddFlag("-s", "Execute in school mode");
    /*clpAddArg("-s, --school-mode", "Execute in school mode.");
    printf("1\n");
    clpAddArg("-i, --ip-version {version}", "The ip version to use. Currently supported is 4. (NYI: 6");
    printf("2\n");
    clpAddArg("-t, --time-to-live {ttl}", "The number of routers (or hops) which the package is allowed to pass before it should be dropped.");
    printf("3\n");
    clpAddArg("-n, --next-header PROTOCOL", "");*/

    printf("parsing command line\n");

    //GIVENPARAMETER *params = clpParseCommandLine(argc, argv);

	/*for (int i = 0; i < argc; i++) {

		// determine whether to just print version information
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
			dumpData = true;
			// we do not need any further information as we will not actually process any data so we can just skip all other arguments
			break;
		}

		// determine ip version
		if (strcmp(argv[i], "--ip-version") == 0 || strcmp(argv[i], "-i") == 0) {
			if (version != 0) {
				fprintf(stderr, "ERROR:multiple version arguments given.");
				exit(1);
			}
			version = atoi(argv[i + 1]);
			i++;
		} else if (strcmp(argv[i], "--ipv4") == 0 || strcmp(argv[i], "-4") == 0) {
			if (version != 0) {
				fprintf(stderr, "ERROR:multiple version arguments given.");
				exit(1);
			}
			version = 4;
		} else if (strcmp(argv[i], "--ipv6") == 0 || strcmp(argv[i], "-6") == 0) {
			if (version != 0) {
				fprintf(stderr, "ERROR:multiple version arguments given.");
				exit(1);
			}
			version = 6;
		}

		// determine TTL
		if (strcmp(argv[i], "--time-to-live") == 0 || strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--hop-limit") == 0) {
			if (ttl != 0) {
				fprintf(stderr, "ERROR:multiple TTL/hop limit arguments given.");
				exit(1);
			}
			if (i == argc - 1) {
				fprintf(stderr, "ERROR:argument expected after %s", argv[i]);
				exit(1);
			}
			ttl = atoi(argv[i + 1]);
		}

		// determine next header
		if (strcmp(argv[i], "--next-header") == 0 || strcmp(argv[i], "-n") == 0) {
		}
	}

	if (version != 4 && version != 6) {
		fprintf(stderr, "ERROR:unknown or no ip version provided. Please specify either version 4 or 6.");
	}

	if (version == 6) {
		fprintf(stderr, "ERROR:not implemented yet.");
	}*/

}
