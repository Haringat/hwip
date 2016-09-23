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
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <regex>

namespace clp {

    using namespace std;

    Parser *Parser::addArgument(string *name, string *description, string *defaultValue) {
        this->arguments->push_back(new Argument(name, description, defaultValue, false));
        return this;
    }

    Parser::Parser(string *projectName, string *version) {
        this->projectName = projectName;
        this->version = version;
        this->arguments = new list<Argument*>();
        this->parsed = false;
    }

    void Parser::parse(std::list<string*> *args) {
        if(this->parsed) {
            return;
        } else {
            this->parsed = true;
        }
        for (typename list<string*>::iterator argIterator = args->begin(); argIterator != args->end(); argIterator++) {
            for (typename list<Argument*>::iterator i = this->arguments->begin(); i != this->arguments->end(); i++) {
                Argument *arg = *i;
                string *argName = new string();
                *argName = (arg->getName()->find(' ')) ? arg->getName()->substr(0, arg->getName()->find(' ')) : *arg->getName();
                if (arg->getValue() == nullptr) {
                    arg->setValue(*argIterator);
                } else {
                    cerr << "Error: Argument \"" << arg->getName() << "\" was redefined." << endl;
                    exit(-1);
                }
            }
        }
    }

    bool Parser::isGiven(string *flagName) {
        if (!this->parsed) {
            return false;
        }
        for (typename list<Argument*>::iterator i = this->arguments->begin(); i != this->arguments->end(); i++) {
            if((*i)->getName()->compare(*flagName)) {
                cout << (*i)->isSet() << endl;
                return (*i)->isSet();
            }
        }
        return false;
    }

}

