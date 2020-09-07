# CMakeList.txt: projeto de CMake para CommandLine_RPG, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

project ("CommandLine_RPG")
set (CMAKE_CXX_STANDARD 17)

#include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(source)

set_property(TARGET CommandLine_RPG PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/resources")
# TODO: Adicione testes e instale destinos, se necessário.
install(TARGETS CommandLine_RPG DESTINATION bin)
