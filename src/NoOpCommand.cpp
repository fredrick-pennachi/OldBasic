// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "NoOpCommand.h"


const std::string NoOpCommand::NOOP_COMMAND_NAME = "NOOP";

NoOpCommand::NoOpCommand(const std::vector<Lexeme>& lexemes) : Command(NOOP_COMMAND_NAME, lexemes) {

}


CommandStatus NoOpCommand::invoke()
{
    return OK;
}
