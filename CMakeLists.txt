# SPDX-FileCopyrightText: 2026 Fredrick Pennachi
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(OldBasic VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(oldbasic
	src/Array.cpp
	src/ArrayNode.cpp
	src/ClsCommand.cpp
	src/Command.cpp
	src/DataCommand.cpp
	src/DimCommand.cpp
	src/DrawCommand.cpp
	src/ExpressionNode.cpp
	src/ForCommand.cpp
	src/FunctionNode.cpp
	src/GosubCommand.cpp
	src/GotoCommand.cpp
	src/IfCommand.cpp
	src/InputCommand.cpp
	src/LetCommand.cpp
	src/Lexeme.cpp
	src/ListCommand.cpp
	src/MultiCommand.cpp
	src/NewCommand.cpp
	src/NextCommand.cpp
	src/NoOpCommand.cpp
	src/NullNode.cpp
	src/OldBasic.cpp
	src/OnCommand.cpp
	src/OperatorNode.cpp
	src/Parser.cpp
	src/PlotCommand.cpp
	src/PrintCommand.cpp
	src/ReadCommand.cpp
	src/ReturnCommand.cpp
	src/RunCommand.cpp
	src/SleepCommand.cpp
	src/StopCommand.cpp
	src/Test.cpp
	src/Tokenizer.cpp
	src/Value.cpp
	src/ValueNode.cpp
	src/Variable.cpp
	src/VariableNode.cpp
)

if (WIN32)
	message("Platform is Windows")
	target_sources(oldbasic PUBLIC "src/windows/Runtime.cpp")
endif()

if (LINUX)
	message("Platform is Linux")
	target_sources(oldbasic PUBLIC "src/linux/Runtime.cpp")
endif()
