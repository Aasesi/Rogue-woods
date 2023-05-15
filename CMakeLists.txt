cmake_minimum_required(VERSION 3.0)
project(Therogueswoods)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall)

set(SFML_DIR "C:/Sfmlvscode/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories("C:/Sfmlvscode/SFML-2.5.1/include" "include")

add_executable(Therogueswoods src/main.cpp src/utils.cpp include/statemanager.hpp
src/game.cpp src/statemanager.cpp include/state.hpp src/button.cpp include/configs.hpp include/interface_element.hpp src/game_state.cpp src/console.cpp src/player_input.cpp
src/map.cpp src/node.cpp include/node.hpp src/quest.cpp)
target_link_libraries(Therogueswoods sfml-system sfml-window sfml-graphics sfml-network sfml-audio)