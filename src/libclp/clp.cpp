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

#include "Parser.hpp"
#include "config.h"
#include "clp.h"
#include <string>
#include <list>
#include <stdlib.h>
#include <iostream>

using namespace clp;
using namespace std;

static Parser *parser = nullptr;

void clpAddArgument(const char *name, const char *description) {
    parser->addArgument(new string(name), new string(description), new string(""));
}

void clpInit(const char *name, const char *version) {
    if (parser == nullptr) {
        parser = new Parser(new string(name), new string(version));
    }
}

void clpParse(int argc, char **argv) {
    std::list<string*> *argList = new list<string*>();
    for (int i = 1; i < argc; i++) {
        argList->push_back(new string(argv[i]));
    }
    parser->parse(argList);
}

void clpAddArgumentWithDefaultValue(const char *name, const char *description, const char *defaultValue) {
    parser->addArgument(new string(name), new string(description), new string(defaultValue));
}

bool clpGetFlag(const char *flagName) {
    return parser->isGiven(new string(flagName));
}
