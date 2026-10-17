cmake_minimum_required(VERSION 3.16)
project(cli CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cli
        main.cpp
        src/ErrorHandler.cpp
        src/Executor.cpp
        src/Inputer.cpp
        src/Interpreter.cpp
        src/Lexer.cpp
        src/Maker.cpp
        src/Parser.cpp
        src/Pipe.cpp
        src/Reader.cpp
        src/Command.cpp
        src/CommandBatch.cpp
        src/CommandDate.cpp
        src/CommandEcho.cpp
        src/CommandHead.cpp
        src/CommandPrompt.cpp
        src/CommandRm.cpp
        src/CommandTime.cpp
        src/CommandTouch.cpp
        src/CommandTr.cpp
        src/CommandTruncate.cpp
        src/CommandWc.cpp
        src/FileHandler.cpp
        src/LexicalError.cpp
        src/NewCommand.cpp
)