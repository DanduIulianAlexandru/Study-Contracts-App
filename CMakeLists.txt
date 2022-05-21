cmake_minimum_required(VERSION 3.22)
project(StudyContractsApp)

set(CMAKE_CXX_STANDARD 11)

add_executable(StudyContractsApp main.cpp domain/Discipline.cpp domain/Discipline.h repository/Repo.cpp repository/Repo.h repository/VectorDinamicTemplate.h service/Service.cpp service/Service.h validate/Validate.cpp validate/Validate.h user_interface/Console.cpp user_interface/Console.h undo/undo.h fake_repo.h repository/file_repo.cpp repository/file_repo.h GUI/ContractsGUI.cpp GUI/ContractsGUI.h)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.4\\mingw_64\\lib\\cmake")
find_package(Qt6Widgets REQUIRED)
target_link_libraries(StudyContractsApp Qt6::Widgets)