#include <assert.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include <iostream>
#include "Service.h"
#include <memory>
#include "../fake_repo.h"
using std::ostream;
using std::stringstream;
using namespace std;

//ADD DELETE FIND MODIFY
void Service::add_s(const string& name, int hours, const string& type, const string& teacher) {
    Discipline d{ name, hours, type, teacher };
    val.validate(d);
    repo.add(d);
//    ActionsUndo.push_back(std::make_unique<UndoAdd>(repo, d));
}

void Service::dlt_s(string name) {
    Discipline d = find_s(name);
    repo.dlt(name);
 //   ActionsUndo.push_back(std::make_unique<UndoDelete>(repo, d));
}

const Discipline& Service::find_s(string name) const
{
    return repo.find(name);
}

void Service::modify_s(const Discipline& d, string name)
{
    Discipline discipline = find_s(name);
    repo.modify(d, name);
//    ActionsUndo.push_back(std::make_unique<UndoModify>(name, discipline, repo));
}

//FILTRARI
const vector<Discipline> Service::filter_hours(const int& hours) {
    vector<Discipline> rez;
    const vector<Discipline>& dsp = repo.get_all();
    for(const auto& discipline : dsp)
        if (discipline.get_hours() == hours)
            rez.push_back(discipline);
    return rez;
}

const vector<Discipline> Service::filter_teacher(const string& teacher) {
    vector<Discipline> rez;
    const vector<Discipline>& dsp = repo.get_all();
    for(const auto& discipline : dsp)
        if(discipline.get_teacher() == teacher)
            rez.push_back(discipline);
    return rez;
}


//SORT
vector<Discipline> Service::sorting_sys(int choose) {
    vector<Discipline> rez = repo.get_all();
    if(choose == 1)
        std::sort(rez.begin(), rez.end(),[](Discipline d1, Discipline d2){ return d1.get_name() < d2.get_name();});
    if(choose == 2)
        std::sort(rez.begin(), rez.end(),[](Discipline d1, Discipline d2){ return d1.get_hours() < d2.get_hours();});
    if(choose == 1)
        std::sort(rez.begin(), rez.end(),[](Discipline d1, Discipline d2){
            if(d1.get_teacher() < d2.get_teacher())
                return true;
            if(d1.get_teacher() > d2.get_teacher())
                return false;
            if(d1.get_type() < d2.get_type())
                return true;
            if(d1.get_type() > d2.get_type())
                return false;
            return false;
        });
    return rez;
}


//CONTRACT
void Service::add_c_srv(string name) {
    repo.add_c(name);
}

void Service::generate_srv(int nr) {
    repo.generate(nr);
}

void Service::empty() {
    repo.empty();
}

vector<Discipline> Service::show_c() {
    return repo.show_cr();
}

void Service::Undo() {
    if(ActionsUndo.size() == 0) throw RepoException("Nu se mai pot face operatii de undo");
    ActionsUndo.back()->Undo();
    ActionsUndo.pop_back();
}

size_t FakeRepo::generate_number() noexcept {
    std::mt19937 mt{ std::random_device{}() };
    const std::uniform_int_distribution<size_t> dist(1, 6);
//    const size_t numarGenerat = dist(mt);// numar aleator intre [0,size-1]

 //   return numarGenerat;
}

bool FakeRepo::decide(size_t nr) {
    string numar = std::to_string(nr);
    if(nr % 2)
        throw RepoException("Nu s-a putut face operatia avand numarul generat impar: " + numar);
    return true;
}

int Service::stringToInt(const std::string &str) {
    int num = 0;
    for (char c: str) {
        if (c < '0' || c > '9')
            throw RepoException("trebuie introdus un numar!");
        num = num * 10 + (c - '0');
    }
    return num;
}

void Service::modificare(string name, int hours, string type, string teacher) {
    const vector<Discipline>& dsp = repo.get_all();
    for(const auto& discipline : dsp){
        if(discipline.get_name() == name){
            Discipline d {name, hours, type, teacher};
            repo.modify(d, name);
        }
    }
}

//TESTS

void add_s_test() {
    Repo repo;
    Validate val;
    Service srv{ repo, val};

    srv.add_s("a", 2, "a", "a");
    assert(srv.get_all().size() == 1);
    assert(srv.find_s("a").get_hours() == 2);
    srv.add_s("b", 2, "b", "b");
    assert(srv.get_all().size() == 2);
    try {
        srv.add_s("", -2, "", "");
        assert(false);
    }
    catch (const ValidateException& e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void dlt_s_test() {
    Repo repo;
    Validate val;
    Service srv{ repo, val };

    srv.add_s("a", 2, "a", "a");
    srv.add_s("b", 2, "b", "b");
    srv.dlt_s("a");
    assert(srv.get_all().size() == 1);
    srv.dlt_s("b");
    assert(srv.get_all().size() == 0);
}

void find_s_test() {
    Repo repo;
    Validate val;
    Service srv{ repo, val };

    srv.add_s("a", 2, "okfrt", "c");
    srv.add_s("b", 2, "b", "b");
    assert(srv.find_s("a").get_hours() == 2);
    assert(srv.find_s("a").get_teacher() == "c");
    assert(srv.find_s("a").get_type() == "okfrt");
}

void modify_s_test() {
    Repo repo;
    Validate val;
    Service srv{ repo, val };

    srv.add_s("a", 2, "a", "a");
    srv.add_s("b", 3, "b", "b");
    Discipline d{ "c", 4, "c", "ac" };
    srv.modify_s(d, "a");
    assert(srv.get_all().at(0).get_hours() == 4);
}

void filter_hours_test() {
    Repo repo;
    Validate val;
    Service srv{ repo, val };

    srv.add_s("a", 2, "okfrt", "c");
    srv.add_s("b", 3, "b", "b");
    srv.add_s("c", 4, "okfrt", "c");
    srv.add_s("d", 2, "b", "b");
    const vector<Discipline> &dd = srv.filter_hours(2);
    assert(dd.size() == 2);
}

void teacher_hours_test() {
    Repo repo;
    Validate val;
    Service srv{ repo, val };

    srv.add_s("a", 2, "okfrt", "c");
    srv.add_s("b", 3, "b", "b");
    srv.add_s("c", 4, "okfrt", "a");
    srv.add_s("d", 2, "b", "b");
    const vector<Discipline>& dd = srv.filter_teacher("c");
    assert(dd.size() == 1);
}

void tests_service()
{
//    sort_type_teacher_test();
//    sort_hours_test();
//    sort_name_test();
    filter_hours_test();
    teacher_hours_test();
    add_s_test();
    dlt_s_test();
    find_s_test();
    modify_s_test();
}