#pragma once
#include <QtWidgets>
#include <QListWidget>
#include <QPushButton>
#include "../service/Service.h"
#include <vector>
#include "../domain/Discipline.h"

class ContractsGUI : public QWidget{
public:
    explicit ContractsGUI(Service& service): service{service}{
        initGUIcamps();
        reloadList(service.get_all());
        connectSignalsSlots();
    }
private:
    Service& service;

    QHBoxLayout* main_layout = new QHBoxLayout;
    QListWidget* list;
    QListWidget* ItemSelection;


    QLineEdit* txtName = new QLineEdit;
    QLineEdit* txtHours = new QLineEdit;
    QLineEdit* txtType = new QLineEdit;
    QLineEdit* txtTeacher = new QLineEdit;

    QPushButton* adaugareButton;
    QPushButton* stergereButton;
    QPushButton* modifyButton;


    void initGUIcamps();
    void connectSignalsSlots();
    void reloadList(const vector<Discipline>& disciplines);
};