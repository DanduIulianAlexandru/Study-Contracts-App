#pragma once

#include "../service/Service.h"
#include "../domain/Discipline.h"

class Console {
    Service& srv;
    //Basics
    void add_ui();
    void dlt_ui();
    void modify_ui();
    void find_uI();
    void print_ui(const vector<Discipline>& disciplines);
    void add_10();

    //filter and sort
    void filter_hours_ui();
    void filter_techar_ui();
    void sorting_sys_ui();

    //contract
    void add_c_ui();
    void generate_ui();
    void empty_ui();


    void undo();

public:
    Console(Service& srv) noexcept : srv{ srv } {};
    //nu permitem copierea obiectelor
    Console(const Console& co) = delete;

    void start();
};