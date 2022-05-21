#include "repository/Repo.h"
#include "domain/Discipline.h"
#include "validate/Validate.h"
#include "user_interface/Console.h"
#include "service/Service.h"
#include "fake_repo.h"
#include "repository/file_repo.h"
#include <QApplication>
#include "GUI/ContractsGUI.h"
int main(int argc, char** argv) {
    //repo_tests();
    //domain_tests();
    //validate_tests();
    //tests_service();
    //FakeRepo repo;
    Repo repo;
    //RepoFile repo { "fisier.cvs" };
    Validate val;
    Service srv{ repo, val };

    srv.add_s("OOP", 23, "obligatorie", "Istvan");
    srv.add_s("OS", 22, "obligatorie", "Boian");

    QApplication a{argc, argv};
    ContractsGUI g{srv};

    g.show();
    a.exec();
    //Console ui{ srv };
    //ui.start();
    return 0;
}
