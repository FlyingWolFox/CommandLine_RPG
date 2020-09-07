add_subdirectory(pugixml)

# Adicione a origem ao executável deste projeto.
add_executable (CommandLine_RPG "CommandLine_RPG.cpp" "ansi_escapes.c" "graphics.cpp" "loader.cpp" "Player.cpp")
target_link_libraries(CommandLine_RPG pugixml)
