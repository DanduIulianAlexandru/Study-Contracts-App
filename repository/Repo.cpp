#include "Repo.h"
#include <algorithm>
#include "assert.h"
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>

using std::ostream;
using std::stringstream;

ostream& operator<<(ostream& out, const RepoException& ex) {
    out << ex.msg;
    return out;
}

bool Repo::exist(const Discipline& d) const {
    try {
        string name = d.get_name();
        for(const auto& discipline : disciplines){
            if(discipline.get_name() == name)
                return true;
        }
        throw RepoException("The discipline doesn t exist!");
    }
    catch (RepoException&) {
        return false;
    }
}

bool Repo::find2(string name) const{
    try {
        for(const auto& discipline : disciplines){
            if(discipline.get_name() == name)
                return true;
        }
        throw RepoException("The discipline doesn t exist!");
    }
    catch (RepoException&) {
        return false;
    }
}

void Repo::add(const Discipline& d) {
    if (exist(d)) {
        throw RepoException("The discipline already exists");
    }
    disciplines.push_back(d);
}

const vector<Discipline>& Repo::get_all() const noexcept {
    return disciplines;
}

const Discipline& Repo::find(string name) const {

    auto CorrectName = [name](Discipline discipline){ return discipline.get_name() == name; };
    /*
    for(const auto& discipline : disciplines){
        if(discipline.get_name() == name)
            return discipline;
    }
    throw RepoException("The discipline doesn t exist!");
    */
    auto it = std::find_if(disciplines.begin(), disciplines.end(), CorrectName);
    if(!find2(name))
        throw RepoException("The discipline doesn t exist!");
    else
        return *it;
}

void Repo::dlt(string name) {
    int i = 0;
    while (i < disciplines.size() && disciplines.at(i).get_name() != name) {
        i++;
    }
    if (i < disciplines.size()) disciplines.erase(disciplines.begin() + i);
    else throw RepoException("Discipline doesn t exist!\n");
}

void Repo::modify(const Discipline& d, string name) {
    int ok = 1;
    for(auto& discipline : disciplines){
        if(discipline.get_name() == name){
            discipline = d;
            ok = 0;
        }
    }
    if (ok == 1)
        throw RepoException("The discipline doesn t exist!");
}

void Repo::generate(int nr) {
    for(int i = 0; i < nr; i ++){
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, disciplines.size()-1);
        int rndNr = dist(mt);
        contract.push_back(disciplines.at(rndNr));
    }
}

void Repo::empty() {
    contract.clear();
}

void Repo::add_c(string name) {
    int ok;
    for(auto const dis : disciplines)
        if(name == dis.get_name())
            ok = 1;
    if(ok == 0)
        throw RepoException("This discipline is not in the discipline list");
    Discipline d = find(name);
    contract.push_back(d);
}

vector<Discipline> Repo::show_cr() {
    return contract;
}


//TESTS
void test_add() {
    Repo repo;
    repo.add(Discipline{ "a", 2, "a", "a" });
    assert(repo.get_all().size() == 1);
    assert(repo.find("a").get_hours() == 2);
    repo.add(Discipline("b", 4, "b", "b"));
    assert(repo.get_all().size() == 2);

    //discipline already exists
    try {
        repo.add(Discipline{ "b", 4, "b", "b" });
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
    //discipline doesn t exist
    try {
        repo.find("c");
        assert(false);
    }
    catch (const RepoException& e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}
void test_find() {
    Repo repo;
    repo.add(Discipline{ "a", 2, "a", "a" });
    repo.add(Discipline{ "b", 3, "b", "b" });

    auto d = repo.find("a");
    assert(d.get_hours() == 2);
    assert(d.get_teacher() == "a");
    assert(d.get_type() == "a");

    try {
        repo.find("c");
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }

}
void test_delete() {
    Repo repo;
    repo.add(Discipline{ "a", 2, "a", "a" });
    repo.dlt("a");
    repo.add(Discipline{ "a", 2, "a", "a" });
    repo.add(Discipline{ "b", 2, "b", "b" });
    repo.dlt("b");
    assert(repo.get_all().size() == 1);
    assert(repo.get_all().at(0).get_teacher() == "a");
    repo.add(Discipline{ "b", 2, "b", "b" });
    repo.add(Discipline{ "c", 5, "c", "c" });
    repo.dlt("b");
    assert(repo.get_all().at(1).get_hours() == 5);
}

void test_modify() {
    Repo repo;
    repo.add(Discipline{ "a", 3, "a", "a" });
    repo.add(Discipline{ "b", 2, "b", "b" });
    repo.add(Discipline{ "c", 5, "c", "c" });
    Discipline d{ "v", 32, "v", "v" };
    repo.modify(d, "b");
    assert(repo.get_all().at(1).get_hours() == 32);
    assert(repo.get_all().at(1).get_teacher() == "v");
}
void repo_tests() {
    test_delete();
    test_find();
    test_add();
    test_modify();
}