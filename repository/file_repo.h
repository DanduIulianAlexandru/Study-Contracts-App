#pragma once
#include "Repo.h"

using std::string;

class RepoFile : public Repo{
private:
    string file_name;

    void write();

    void read();
public:
    RepoFile(string file_name): Repo(), file_name{ file_name }{
        read();
    }

    void add(const Discipline& discipline) override{
        Repo::add(discipline);
        write();
    }

    void dlt(const string name) override{
        Repo::dlt(name);
        write();
    }

    void modify(const Discipline& d, string name) override{
        Repo::modify(d, name);
        write();
    }
};
