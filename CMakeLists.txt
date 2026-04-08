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
	Array.cpp
	ArrayNode.cpp
	ClsCommand.cpp
	Command.cpp
	DataCommand.cpp
	DimCommand.cpp
	DrawCommand.cpp
	ExpressionNode.cpp
	ForCommand.cpp
	FunctionNode.cpp
	GosubCommand.cpp
	GotoCommand.cpp
	IfCommand.cpp
	InputCommand.cpp
	LetCommand.cpp
	Lexeme.cpp
	ListCommand.cpp
	MultiCommand.cpp
	NewCommand.cpp
	NextCommand.cpp
	NoOpCommand.cpp
	NullNode.cpp
	OldBasic.cpp
	OnCommand.cpp
	OperatorNode.cpp
	Parser.cpp
	PlotCommand.cpp
	PrintCommand.cpp
	ReadCommand.cpp
	ReturnCommand.cpp
	RunCommand.cpp
	SleepCommand.cpp
	StopCommand.cpp
	Test.cpp
	Tokenizer.cpp
	Value.cpp
	ValueNode.cpp
	Variable.cpp
	VariableNode.cpp
)

if (WIN32)
	message("Platform is Windows")
	target_sources(oldbasic PUBLIC "windows/Runtime.cpp")
endif()

if (LINUX)
	message("Platform is Linux")
	target_sources(oldbasic PUBLIC "linux/Runtime.cpp")
endif()
