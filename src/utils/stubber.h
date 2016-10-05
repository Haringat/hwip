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

#ifndef HWIP_STUBBER_H
#define HWIP_STUBBER_H

#include <stdio.h>
#include <stdlib.h>

/**
 * defines a stubbed version of a function which will make the linker happy and give the programmer feedback which
 * functions are still missing an implementation.
 */
#define STUB(RETURNVALUE, NAME, ...) RETURNVALUE NAME(__VA_ARGS__) {\
    fprintf(stderr, "STUB: %s(%s) is not implemented yet.\n", #NAME, #__VA_ARGS__);\
    if(strcmp(#RETURNVALUE, "void") == 0) {\
        return;\
    } else {\
        return ((RETURNVALUE) NULL);\
    }\
}

#endif //HWIP_STUBBER_H
