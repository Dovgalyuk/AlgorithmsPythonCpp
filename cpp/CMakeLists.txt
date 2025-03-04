cmake_minimum_required(VERSION 3.0)
project(AlgorithmsPythonCpp)

add_executable(dice dice.cpp)
add_executable(guessnumber guessnumber.cpp)

add_executable(23matches 23matches.cpp)

add_executable(hammurabi hammurabi.cpp)

add_executable(sendmoremoney sendmoremoney.cpp)

add_executable(bullcowComputer bullcowComputer.cpp)

add_executable(bullcowHuman bullcowHuman.cpp)

add_executable(queen queen.cpp)

add_executable(mugwump mugwump.cpp)

add_executable(tictactoe tictactoe.cpp)

add_executable(blackjack blackjack.cpp)
set_property(TARGET blackjack PROPERTY CXX_STANDARD 20)

# heuristic

add_executable(battleship battleship.cpp)

add_executable(reversi reversi.cpp)

# recursive

add_executable(8queens 8queens.cpp)
add_executable(8queensLoop 8queensLoop.cpp)
add_executable(tictactoe4 tictactoe4.cpp)

# bfs

add_executable(labyrinth labyrinth.cpp)
add_executable(8 8.cpp)
set_property(TARGET 8 PROPERTY CXX_STANDARD 20)
add_executable(solitaire solitaire.cpp)
set_property(TARGET solitaire PROPERTY CXX_STANDARD 20)

# alpha-beta

add_executable(kalah kalah.cpp)
add_executable(minichess minichess.cpp)

# self-learning

add_executable(animal animal.cpp)
add_executable(hexapawn hexapawn.cpp)
set_property(TARGET hexapawn PROPERTY CXX_STANDARD 20)
