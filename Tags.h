/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tags.h
Purpose: Manages a list of tags.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef TAGS_H
#define TAGS_H

#include "AcrylicorTypedefs.h"
#include <list>

class Tags
{
protected:
	std::list<String> m_tags;
public:
	Tags();
	Tags(const Tags& rhs);
	Tags& operator=(const Tags& rhs);
	~Tags();

	void AddTag(String tag);
	bool HasTag(String tag) const;
	void RemoveTag(String tag);
	void SetTags(std::list<String> tags);
	std::list<String> GetTags() const;
};

#endif