/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextComponent.h
Purpose: Text Component class - renders a string as sprites
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "SpriteComponent.h"

class TextComponent :
	public SpriteComponent
{
protected:
	std::vector< std::vector<TexCoords> > m_textureOffsets; // collection of UV coordinates for each letter
	std::vector< std::pair<int, int> > m_letters; // indecies into m_textureOffsets
	std::vector<Vector3D *> m_colors;
	String m_text;

	std::pair<int, int> _GetTextureOffsetForLetter(const char letter);
	void _SetLettersFromString();
	void _InitFontOffsets();
public:
	TextComponent() = delete;
	TextComponent(GameObject& parent, String fontName, String text, String shader);
	TextComponent(const TextComponent& rhs) = delete;
	TextComponent(const TextComponent& rhs, GameObject& parent);
	TextComponent& operator= (TextComponent rhs) = delete;
	~TextComponent();

	virtual void Update(double deltaTime);
	virtual TextComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};

	virtual void SetSprite(String fontName);
	void SetText(String newText);
	String Text() const;

	std::vector< std::vector<TexCoords> > GetTextureOffsets() const;
	std::pair< std::vector< std::pair<int, int> >, std::vector<Vector3D *> > GetLetterData() const;
};

#endif