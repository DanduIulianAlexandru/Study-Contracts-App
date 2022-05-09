#include "file_repo.h"
#include <fstream>

using std::string;

void RepoFile::read() {
    std::ifstream in(file_name);

    if(!in.is_open())
        throw RepoException("Nu se poate deschide: " + file_name);

    while(!in.eof()){
        string name;
        in >> name;
        int hours;
        in >> hours;
        string type;
        in >> type;
        string teacher;
        in >> teacher;

        if(in.eof())
            break;

        Discipline discipline{name, hours, type, teacher};
        Repo::add(discipline);
    }
    in.close();
}

void RepoFile::write() {
    std::ofstream out (file_name);
    if(!out.is_open())
        throw RepoException("Nu se poate deschide fisierul: " + file_name);
    vector<Discipline> list_copy = get_all();

    for(const auto& d : list_copy){
        const Discipline* pointer = &d;
        if(pointer != nullptr)
            out << d.get_name() << " " << d.get_hours() << " " << d.get_type() << " " << d.get_teacher() << "\n";
    }
    out.close();
}
