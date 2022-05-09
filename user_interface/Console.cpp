#include "Console.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

void Console::add_ui() {
    string name, type, teacher;
    int hours;
    cout << "Introduceti numele disciplinei:";
    cin >> name;
    cout << "Introduceti numarul de ore pe saptamana:";
    cin >> hours;
    cout << "Introduceti tipul:";
    cin >> type;
    cout << "Introduceti numele profesorului:";
    cin >> teacher;
    srv.add_s(name, hours, type, teacher);
    cout << "Disciplina adaugata cu succes!\n";
}

void Console::dlt_ui()
{
    string name;
    cout << "Introduceti numele disciplinei pe care doriti sa o stergeti:";
    cin >> name;
    srv.dlt_s(name);
}

void Console::modify_ui()
{
    string name;
    cout << "Introduceti numele disciplinei pe care doriti sa o modificati:";
    cin >> name;
    string name1, type, teacher;
    int hours;
    cout << "Introduceti numele disciplinei:";
    cin >> name1;
    cout << "Introduceti numarul de ore pe saptamana:";
    cin >> hours;
    cout << "Introduceti tipul:";
    cin >> type;
    cout << "Introduceti numele profesorului:";
    cin >> teacher;
    Discipline d{ name1, hours, type, teacher };
    srv.modify_s(d, name);
}

void Console::find_uI()
{
    string name;
    cout << "Introduceti numele disciplinei pe care o cautati:";
    cin >> name;
    Discipline d = srv.find_s(name);
    cout << "|Nume: " << d.get_name() << "|Ore pe sapt: " << d.get_hours() << "|Tip: " << d.get_type() << "|Profesor: " << d.get_teacher() << " |" << '\n';
}

void Console::print_ui(const vector<Discipline>& disciplines) {
    cout << "Lista disciplinelor:\n";
    for (int i = 0; i < disciplines.size(); i ++) {
        Discipline d = disciplines.at(i);
        cout << "|Nume: " << d.get_name() << "|Ore pe sapt: " << d.get_hours() << "|Tip: " << d.get_type() << "|Profesor: " << d.get_teacher() << " |" << '\n';
    }
}


void Console::filter_hours_ui()
{
    int hours;
    cout << "Introduceti numarul de ore:";
    cin >> hours;
    const vector<Discipline>& dd = srv.filter_hours(hours);
    print_ui(dd);
}

void Console::filter_techar_ui()
{
    string teacher;
    cout << "Introduceti numele profesorului:";
    cin >> teacher;
    const vector<Discipline>& dd = srv.filter_teacher(teacher);
    print_ui(dd);
}


void Console::start() {
    const auto* p = &srv;
    while (true) {
        cout << "Meniu:\n";
        cout << "1 add\n2 print list\n3 delete discipline\n4 modify discipline\n5 find discipline\n6 filter hours\n7 filter teacher\n8 sort\n9 add in contract\n10 empty the contract\n11 generate a number of disciplines in contract\n12 print the contract\n13 add 10\n20 undo\n";
        int cmd;
        cin >> cmd;
        try {
            switch (cmd) {
                case 1:
                    add_ui();
                    break;
                case 2:
                    if (p != nullptr) {
                        print_ui(srv.get_all());
                        break;
                    }
                case 3:
                    dlt_ui();
                    break;
                case 4:
                    modify_ui();
                    break;
                case 5:
                    find_uI();
                    break;
                case 6:
                    filter_hours_ui();
                    break;
                case 7:
                    filter_techar_ui();
                    break;
                case 8:
                    sorting_sys_ui();
                    break;
                case 9:
                    add_c_ui();
                    break;
                case 10:
                    empty_ui();
                    break;
                case 11:
                    generate_ui();
                    break;
                case 12:
                    if (p != nullptr) {
                        print_ui(srv.show_c());
                        break;
                    }
                case 13:
                    add_10();
                    break;
                case 20:
                    undo();
                    break;
                case 0:
                    return;
                default:
                    cout << "Comanda invalida!\n";
            }
        }
        catch (const RepoException& ex) {
            cout << ex << '\n';
        }
        catch (const ValidateException& ex) {
            cout << ex << '\n';
        }
    }
}

void Console::add_10() {
    srv.add_s("j", 5, "ob", "n");
    srv.add_s("b", 69, "cr", "b");
    srv.add_s("k", 1, "ta", "nua");
    srv.add_s("l", 1, "ta", "dO");
    srv.add_s("f", 1, "dr", "de");
    srv.add_s("e", 10, "hh", "ok");
    srv.add_s("h", 21, "da", "ok");
    srv.add_s("a", 9, "fe", "a");
    srv.add_s("c", 2, "bu", "ok");
    srv.add_s("d", 420, "ma", "d");
}

void Console::sorting_sys_ui() {
    int choose;
    cout << "For sorting by name press 1" << endl;
    cout << "For sorting by hours press 2" << endl;
    cout << "For sorting by teachers and type press 3" << endl;
    cout << ">>>"; cin >> choose;
    vector<Discipline> ok = srv.sorting_sys(choose);
    print_ui(ok);
}

void Console::add_c_ui() {
    string name;
    cout << "Enter the discipline name which u want to add to the contract" << endl;
    cin >> name;
    srv.add_c_srv(name);
    cout << "Append went successfully" << endl;
}

void Console::generate_ui() {
    int n;
    cout << "Enter the number of random disciplines u want to add to the contract" << endl;
    cin >> n;
    srv.generate_srv(n);
    cout << "Generate random went successfully" << endl;
}

void Console::empty_ui() {
    srv.empty();
}

void Console::undo() {
    srv.Undo();
    cout << "Operatie realizata cu succes!\n";
}
