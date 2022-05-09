cmake_minimum_required(VERSION 3.22)
project(StudyContractsApp)

set(CMAKE_CXX_STANDARD 11)

add_executable(StudyContractsApp main.cpp domain/Discipline.cpp domain/Discipline.h repository/Repo.cpp repository/Repo.h repository/VectorDinamicTemplate.h service/Service.cpp service/Service.h validate/Validate.cpp validate/Validate.h user_interface/Console.cpp user_interface/Console.h undo/undo.h fake_repo.h repository/file_repo.cpp repository/file_repo.h)
