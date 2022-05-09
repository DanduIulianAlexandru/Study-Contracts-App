#pragma once
#include <string>
#include "../domain/Discipline.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
    vector<string> msgs;
public:
    explicit ValidateException(const vector<string>& errors) : msgs{ errors } {};

    friend ostream& operator<<(ostream& out, const ValidateException& ex);
};


class Validate {
public:
    static void validate(const Discipline& d);
};

void validate_tests();