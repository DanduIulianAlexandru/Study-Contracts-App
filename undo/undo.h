#pragma once

#include "../repository/Repo.h"
#include "../domain/Discipline.h"

class ActionUndo{
public:
    virtual void Undo() = 0;
    virtual ~ActionUndo() = default;
};

class UndoAdd : public ActionUndo{
private:
    Discipline d;
    Repo& repo;
public:
    UndoAdd(Repo& repo, Discipline& d) : repo { repo }, d { d }{}
    void Undo() override{
        repo.dlt(d.get_name());
    }
};

class UndoDelete : public ActionUndo{
private:
    Discipline d;
    Repo& repo;
public:
    UndoDelete(Repo& repo, Discipline& d) : repo { repo }, d { d }{}
    void Undo() override{
        repo.add(d);
    }
};

class UndoModify : public ActionUndo{
private:
    string name;
    Discipline d;
    Repo& repo;
public:
    UndoModify(string name, Discipline& d, Repo& repo) : name { name }, d { d }, repo { repo }{}
    void Undo() override{
        repo.modify(d, name);
    }
};
