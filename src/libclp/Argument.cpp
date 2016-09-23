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

#include "Argument.hpp"

namespace clp {

    Argument::Argument(string *name, string *description, string *defaultValue, bool hasValue) {
        this->name = name;
        this->hasValue = hasValue;
        this->description = description;
        this->defaultValue = defaultValue;
        this->set = false;
    }

    void Argument::setValue(string *value) {
        this->value = value;
        this->set = true;
    }

    string *Argument::getValue() {
        return this->value;
    }

    void Argument::setDefaultValue(string *value) {
        this->defaultValue = value;
    }

    string *Argument::getName() {
        return this->name;
    }

    bool Argument::isSet() {
        return this->set;
    }

}