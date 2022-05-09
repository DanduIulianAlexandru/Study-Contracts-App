#pragma once
#include "repository/Repo.h"

class FakeRepo : public Repo{
private:
    size_t generate_number() noexcept;

    bool decide(size_t nr);
public:
    FakeRepo() = default;

    void add(const Discipline& d) override{
        decide(generate_number());
        Repo::add(d);
    }

    void dlt(const string name) override{
        decide(generate_number());
        Repo::dlt(name);
    }

    void modify(const Discipline& discipline, const string name) override{
        decide(generate_number());
        Repo::modify(discipline, name);
    }
};