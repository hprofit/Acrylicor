/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: JsonReader.h
Purpose: A set of functions for opening and reading a JSON file.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef JSON_READER_H
#define JSON_READER_H

#include "json.hpp"
#include "AcrylicorTypedefs.h"

using json = nlohmann::json;

namespace AcryJson {
	float ParseFloat(const json j, String comp, String prop);
	float ParseFloat(const json j, String comp, String prop, String coord);
	json OpenJsonFile(String fileName);
	bool KeyIs(json::iterator it, String key);
}
#endif