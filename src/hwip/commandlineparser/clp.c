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

#include "clp.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <unistd.h>

#define CLP_MAX_ARGUMENTS 40

static PARAMETERTYPE validArgs[CLP_MAX_ARGUMENTS];
static char *pkgVersion = (char *)NULL;
static int paramCount = 0;

void clp_addArg(char *argument, char *description) {
    paramCount++;
    if(paramCount == CLP_MAX_ARGUMENTS) {
        // we got more args than we can handle
        fprintf(stderr, "Too many arguments specified. The cap is at %d\n", CLP_MAX_ARGUMENTS);
        exit(-1);
    }
    char *argCommaIndex = index(argument, ',');
    if (argCommaIndex != (char *)NULL) {
        *argCommaIndex = '\0';
        argCommaIndex++;
        char shortArg = *(argument + 1); // we don't want the '-' but the character behind it
        char *spaceIndex = argCommaIndex;
        int argumentCount = 0;
        while ((spaceIndex = index(spaceIndex, ' ')) != (char *)NULL) {
            *spaceIndex = '\0';
            spaceIndex++;
            argumentCount++;
        }
        char *longArg = argCommaIndex;
        if (strlen(longArg) > sizeof(PARAMETERTYPE.longForm)) {
            fprintf(stderr, "The parameter %s is too long to be handled.\nAllowed are max. %d characters.\n", longArg, sizeof(PARAMETERTYPE.longForm));
            exit(-1);
        }
        if (strlen(description) > sizeof(PARAMETERTYPE.description)) {
            fprintf(stderr, "The description for parameter %s is too long to be handled.\nAllowed are max. %d characters.\n", longArg, sizeof(PARAMETERTYPE.description));
            exit(-1);
        }
        PARAMETERTYPE *par = (PARAMETERTYPE *) malloc(sizeof(PARAMETERTYPE));
        strcpy(par->description, description);
        strcpy(par->longForm, longArg);
        par->shorthandForm = shortArg;
        par->argumentCount = argumentCount;
        printf("shortform: %s\n", shortArg);
        printf("longform:  %s\n", longArg);
    }
}

void clp_setVersion(char *version) {
    pkgVersion = malloc(strlen(version));
    strcpy(pkgVersion, version);
}

void clp_printHelp() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("Version: %s\n", pkgVersion);
    printf("Arguments:\n");
    int maxArgWidth;
    for (int i = 0; i < sizeof(validArgs); i++) {
        int argWidth = strlen(validArgs[i].argumentCount);

    }
    printf("-h, --help\t\tprints this information");
    for (int i = 0; i < sizeof(validArgs); i++) {
        printf("")
    }
}