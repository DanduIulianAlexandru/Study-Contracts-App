#include "Discipline.h"
#include <cassert>

bool cmp_name(const Discipline& d1, const Discipline& d2) {
    return d1.get_name() < d2.get_name();
}

bool cmp_teacher(const Discipline& d1, const Discipline& d2) {
    return d1.get_teacher() < d2.get_teacher();
}

void domain_tests() {
    Discipline d1{ "a", 2, "a", "a" };
    Discipline d2{ "b", 3, "b", "b" };
    assert(cmp_name(d1, d2));
    assert(cmp_teacher(d1, d2));
}