#include "Validate.h"
#include <cassert>
#include <sstream>

ostream& operator<<(ostream& out, const ValidateException& ex) {
    for (const auto& msg : ex.msgs) {
        const auto* p = &msg;
        if(p != nullptr)
            out << msg << " ";
    }
    return out;
}

void Validate::validate(const Discipline& d) {
    vector<string> msgs;
    if (d.get_type().empty())
        msgs.emplace_back("Invalid type!");
    if (d.get_teacher().empty())
        msgs.emplace_back("Invalid teacher");
    if (d.get_hours() <= 0)
        msgs.emplace_back("Invalid hours!");
    if (d.get_name().empty())
        msgs.emplace_back("Invalid name!");
    if (!msgs.empty())
        throw ValidateException(msgs);
}

void validate_tests() {
    Validate v;
    Discipline d{ "", -1, "", "" };
    try {
        v.validate(d);
    }
    catch (const ValidateException& ex) {
        std::stringstream sout;
        sout << ex;
        const auto mesaj = sout.str();
        assert(mesaj.find("type") >= 0);
        assert(mesaj.find("Invalid") >= 0);
        assert(mesaj.find("teacher") >= 0);
        assert(mesaj.find("hours") >= 0);
        assert(mesaj.find("name") >= 0);

    }
}
