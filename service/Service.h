#pragma once
#include <memory>
#include "../undo/undo.h"
#include "../domain/Discipline.h"
#include "../repository/Repo.h"
#include <string>
#include <vector>
#include <functional>
#include "../validate/Validate.h"

using std::function;
using std::unique_ptr;

class Service {
    Repo& repo;
    Validate& val;

    std::vector<unique_ptr<ActionUndo>> ActionsUndo;
public:
    Service(Repo& repo, Validate& val) noexcept : repo{ repo }, val{ val }{};
    Service(const Service& srv) = delete;


    const vector<Discipline>& get_all() noexcept {
        return repo.get_all();
    }
    // append discipline to the list service function
    void add_s(const string& name, int hours, const string& type, const string& teacher);

    //delete discipline from the list service function
    void dlt_s(string name);


    //find discipline by the name in the list
    const Discipline& find_s(string name) const;

    //modify a discipline 
    void modify_s(const Discipline& d, string mark);

    void modificare(string name, int hours, string type, string teacher);

    const vector<Discipline> filter_hours(const int& hours);

    const vector<Discipline> filter_teacher(const string& teacher);

    vector<Discipline> sorting_sys(int);

    //CONTRACT
    void add_c_srv(string name);
    void generate_srv(int nr);
    void empty();
    vector<Discipline> show_c();


    void Undo();

    static int stringToInt(const std::string &str);

};

void tests_service();