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

int AcryJson::ParseInt(const json j, String first)
{
	if (j.find(first) != j.end())
		return j[first];
	return 0;
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

String AcryJson::ParseString(const json j, String first)
{
	if (j.find(first) != j.end())
		return j[first];
	return "";
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

bool AcryJson::ParseBool(const json j, String first)
{
	if (j.find(first) != j.end())
		return j[first];
	return false;
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

Vector2D AcryJson::ParseVector2D(const json j, String first, String second)
{
	if (j[first].find(second) != j[first].end()) {
		return Vector2D(
			ParseFloat(j, first, second, "x"),
			ParseFloat(j, first, second, "y"),
			ParseFloat(j, first, second, "w")
		);
	}
	return Vector2D();
}

Vector3D AcryJson::ParseVector3D(const json j, String first, String second)
{
	if (j[first].find(second) != j[first].end()) {
		return Vector3D(
			ParseFloat(j, first, second, "x"),
			ParseFloat(j, first, second, "y"),
			ParseFloat(j, first, second, "z"),
			ParseFloat(j, first, second, "w")
		);
	}
	return Vector3D();
}

Vector3D AcryJson::ParseColor(const json j, String first, String second)
{
	if (j[first].find(second) != j[first].end()) {
		return Vector3D(
			ValueExists(j, first, second) ? ParseFloat(j, first, second, "r") : 1.0f,
			ValueExists(j, first, second) ? ParseFloat(j, first, second, "g") : 1.0f,
			ValueExists(j, first, second) ? ParseFloat(j, first, second, "b") : 1.0f,
			ValueExists(j, first, second) ? ParseFloat(j, first, second, "a") : 1.0f
		);
	}
	return Vector3D(1,1,1,1);
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
