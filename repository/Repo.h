#pragma once
#include "../domain/Discipline.h"
#include "VectorDinamicTemplate.h"
#include <string>
#include <vector>
#include "ostream"

using std::vector;
using std::string;
using std::ostream;

class Repo {
    //vector<Discipline> disciplines;
    vector<Discipline> disciplines;
    bool exist(const Discipline& d) const;
    vector<Discipline> contract;
public:
    //DISCIPLINES
    Repo() = default;
    Repo(const Repo& r) = delete;

    //append to the list;throw exception if discipline already exists
     virtual void add(const Discipline& d);

    //deletes the discipline from the list if it exists; throw exception if not
    virtual void dlt(string name);

    //
    virtual void modify(const Discipline& d, string name);

    //search a discipline and throw exception if the discipline doesn t exist
    const Discipline& find(string name) const;

    //returns all disciplines
    const vector<Discipline>& get_all() const noexcept;

    bool find2(string name) const;

    //study contract
    vector<Discipline>show_cr();
    void empty();
    void add_c(string);
    void generate(int);
};

class RepoException {
public:
    RepoException(string m) :msg{ m } {}
    friend ostream& operator<<(ostream& out, const RepoException& ex);

    string msg;
};

void repo_tests();