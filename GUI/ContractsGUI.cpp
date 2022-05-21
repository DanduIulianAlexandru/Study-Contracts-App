#include "ContractsGUI.h"
#include "../service/Service.h"
#include "../repository/Repo.h"

void ContractsGUI::initGUIcamps() {
    setLayout(main_layout);
    QWidget* listW = new QWidget;
    QVBoxLayout* vertical = new QVBoxLayout;
    listW->setLayout(vertical);
    list = new QListWidget;

    QLabel* titlu = new QLabel("Lista discipline");
    vertical->addWidget(titlu);
    vertical->addWidget(list);
    main_layout->addWidget(listW);

    adaugareButton = new QPushButton("Adauga");
    QVBoxLayout* form = new QVBoxLayout;
    QWidget* formWidget = new QWidget;
    formWidget->setLayout(form);
    QLabel* titlu1 = new QLabel("Nume");
    form->addWidget(titlu1);
    form->addWidget(txtName);
    QLabel* titlu2 = new QLabel("Hours");
    form->addWidget(titlu2);
    form->addWidget(txtHours);
    QLabel* titlu3 = new QLabel("Type");
    form->addWidget(titlu3);
    form->addWidget(txtType);
    QLabel* titlu4 = new QLabel("Teacher");
    form->addWidget(titlu4);
    form->addWidget(txtTeacher);
    form->addWidget(adaugareButton);
    stergereButton = new QPushButton("Sterge");
    modifyButton = new QPushButton("Modificare");
    form->addWidget(stergereButton);
    form->addWidget(modifyButton);
    main_layout->addWidget(formWidget);
}

void ContractsGUI::reloadList(const vector<Discipline> &disciplines) {
    list->clear();
    for(const auto& d : disciplines){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.get_name()));
        list->addItem(item);
    }
}

void ContractsGUI::connectSignalsSlots() {
    QObject::connect(adaugareButton,
                     &QPushButton::clicked,
                     [&](){
    try {
        service.add_s(txtName->text().toStdString(),
                      Service::stringToInt(txtHours->text().toStdString()),
                      txtType->text().toStdString(),
                      txtTeacher->text().toStdString()
        );
        reloadList(service.get_all());
    }catch(RepoException &e){
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(e.msg));
    }
    });
    QObject::connect(stergereButton,
                     &QPushButton::clicked,
                     [&](){
                         try {
                             service.dlt_s(txtName->text().toStdString()
                             );
                             reloadList(service.get_all());
                         }catch(RepoException &e){
                             QMessageBox::warning(this,
                                                  "Warning",
                                                  QString::fromStdString(e.msg));
                         }
                     });
    QObject::connect(modifyButton,
                     &QPushButton::clicked,
                     [&](){
                         try {
                             service.modificare(txtName->text().toStdString(),
                                           Service::stringToInt(txtHours->text().toStdString()),
                                           txtType->text().toStdString(),
                                           txtTeacher->text().toStdString()
                             );
                             reloadList(service.get_all());
                         }catch(RepoException &e){
                             QMessageBox::warning(this,
                                                  "Warning",
                                                  QString::fromStdString(e.msg));
                         }
                     });
    QObject::connect(list, &QListWidget::itemSelectionChanged, [&](){
       auto sel = list->selectedItems();
       if(sel.isEmpty()){
           txtName->setText("");
           txtHours->setText("");
           txtType->setText("");
           txtTeacher->setText("");
       }else{
           auto selItem = sel.at(0);
           auto name = selItem->text();
           auto d = service.find_s(name.toStdString());
           txtName->setText(QString::fromStdString(d.get_name()));
           txtHours->setText(QString::fromStdString(std::to_string(d.get_hours())));
           txtType->setText(QString::fromStdString(d.get_type()));
           txtTeacher->setText(QString::fromStdString(d.get_teacher()));
       }
    });
}
