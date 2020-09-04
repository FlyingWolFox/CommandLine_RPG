# CMakeList.txt: projeto de CMake para CommandLine_RPG, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

project ("CommandLine_RPG")
set (CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(pugixml)

# Adicione a origem ao executável deste projeto.
add_executable (CommandLine_RPG "CommandLine_RPG.cpp" "ansi_escapes.c" "graphics.cpp" "loader.cpp" "Player.cpp")
target_link_libraries(CommandLine_RPG pugixml)

# TODO: Adicione testes e instale destinos, se necessário.
install(TARGETS CommandLine_RPG DESTINATION bin)
