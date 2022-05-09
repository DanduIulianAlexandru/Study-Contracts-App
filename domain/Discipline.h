#pragma once
#include <string>
#include <iostream>
#include <utility>

using std::string;
using std::cout;

class Discipline {
private:
    string name;
    int hours{};
    string type;
    string teacher;
public:
    //constructor:
    Discipline(string  name, const int hours, string  type, string  teacher) : name{std::move( name )}, hours{ hours }, type{std::move( type )}, teacher{std::move( teacher )}{}
    Discipline() = default;
    //getteri:
    int get_hours() const noexcept{
        return hours;
    }
    string get_name() const {
        return name;
    }
    string get_type() const {
        return type;
    }
    string get_teacher() const {
        return teacher;
    }
};

//name compare: True- <    False- >
bool cmp_name(const Discipline& d1, const Discipline& d2);


//teacher compare: True- <    False- >
bool cmp_teacher(const Discipline& d1, const Discipline& d2);

void domain_tests();