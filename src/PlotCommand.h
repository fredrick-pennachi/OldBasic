/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define PLOT_COMMAND_NAME "PLOT"
#define PLOT_HELP "Plots a point at (x,y); PLOT X,Y"

class PlotCommand :
    public Command

{
public:

    PlotCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;
};
