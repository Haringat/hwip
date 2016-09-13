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

namespace clp {

    #include <list>
    #include <string>

    using namespace std;

    Parser *Parser::addArgument(string *name, string *description, string *defaultValue) {
        this->arguments->push_back(new Argument(name, description, defaultValue));
        return this;
    }

    Parser *Parser::addArgument(std::list <string*> *aliases, string *description, string *defaultValue) {
        typename list<string*>::iterator it = aliases->begin();
        Argument *arg = new Argument(*it, description, defaultValue);
        this->arguments->push_back(new Argument(aliases, description, defaultValue));
        return this;
    }

    Parser::Parser(string *projectName, string *version) {
        this->projectName = projectName;
        this->version = version;
        this->arguments = new list<Argument*>();
    }

    void Parser::addAlias(string *original, string *alias)

    void Parser::parse(std::list<string*> *args) {
        for (typename list<string*>::iterator argIterator = args->begin(); argIterator != args->end(); argIterator++) {
            for (typename list<Argument*>::iterator i = this->arguments->begin(); i != this->arguments->end() ; i++) {
                Argument *arg = *i;
                std::list<string*> *aliases = arg->getAliases();
                for (typename list<string*>::iterator alias = aliases->begin(); alias != aliases->end(); alias++) {
                    if (**argIterator == **alias) {
                        cout << "found " << **alias << endl;
                    } else {
                        cout << "did not find " << **alias << " in " << **argIterator << endl;
                    }
                }
            }
        }
    }

}

