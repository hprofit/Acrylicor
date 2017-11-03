#include "JsonReader.h"
#include <fstream>

float AcryJson::ParseFloat(const json j, String comp, String prop)
{
	if (j[comp].find(prop) != j[comp].end())
		return j[comp][prop];
	return 0.0f;
}

float AcryJson::ParseFloat(const json j, String comp, String prop, String coord)
{
	if (j[comp].find(prop) != j[comp].end()) {
		if (j[comp][prop].find(coord) != j[comp][prop].end())
			return j[comp][prop][coord];
	}
	return 0.0f;
}

int AcryJson::ParseInt(const json j, String comp, String prop)
{
	if (j[comp].find(prop) != j[comp].end())
		return j[comp][prop];
	return 0;
}

int AcryJson::ParseInt(const json j, String comp, String prop, String coord)
{
	if (j[comp].find(prop) != j[comp].end()) {
		if (j[comp][prop].find(coord) != j[comp][prop].end())
			return j[comp][prop][coord];
	}
	return 0;
}

String AcryJson::ParseString(const json j, String comp, String prop)
{
	if (j[comp].find(prop) != j[comp].end())
		return j[comp][prop];
	return "";
}

String AcryJson::ParseString(const json j, String comp, String prop, String coord)
{
	if (j[comp].find(prop) != j[comp].end()) {
		if (j[comp][prop].find(coord) != j[comp][prop].end())
			return j[comp][prop][coord];
	}
	return "";
}

bool AcryJson::ParseBool(const json j, String comp, String prop)
{
	if (j[comp].find(prop) != j[comp].end())
		return j[comp][prop];
	return false;
}

bool AcryJson::ParseBool(const json j, String comp, String prop, String coord)
{
	if (j[comp].find(prop) != j[comp].end()) {
		if (j[comp][prop].find(coord) != j[comp][prop].end())
			return j[comp][prop][coord];
	}
	return false;
}

bool AcryJson::ValueExists(const json j, String comp, String prop)
{
	return j[comp].find(prop) != j[comp].end();
}

bool AcryJson::ValueExists(const json j, String comp, String prop, String coord)
{
	if (j[comp].find(prop) != j[comp].end()) {
		if (j[comp][prop].find(coord) != j[comp][prop].end())
			return true;
	}
	return false;
}

json AcryJson::OpenJsonFile(String fileName)
{
	std::ifstream i(fileName);
	json j;
	i >> j;
	i.close();
	return j;
}

bool AcryJson::KeyIs(json::iterator it, String key)
{
	return it.key().compare(key) == 0;
}
