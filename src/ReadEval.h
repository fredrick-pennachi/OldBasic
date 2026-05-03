/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <string>

class ReadEval
{
public:
	
	void readFile(std::string& filename);
	void evalLine(std::string& line);

};

extern ReadEval readEval;
