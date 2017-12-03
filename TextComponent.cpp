#include "TextComponent.h"
#include "JsonReader.h"
#include <iostream>

std::pair<int, int> TextComponent::_GetTextureOffsetForLetter(const char letter)
{
	if (letter >= 33 && letter <= 126) {
		int letNum = letter - 32;
		int cols = m_texture->surface->columns;

		return std::make_pair(letNum / cols, letNum % cols);
	}
	return std::make_pair(0, 0);
}

void TextComponent::_SetLettersFromString()
{
	m_letters.clear();

	for (char letter : m_text)
		m_letters.push_back(_GetTextureOffsetForLetter(letter));
}

void TextComponent::_InitFontOffsets()
{
	int rows = m_texture->surface->rows;
	int cols = m_texture->surface->columns;
	float frameHeight = m_texture->surface->frameHeight;
	float frameWidth = m_texture->surface->frameWidth;

	m_textureOffsets.reserve(rows);
	for (int row = 0; row < rows; ++row) {
		m_textureOffsets.push_back(std::vector<TexCoords>());
		m_textureOffsets[row].reserve(cols);

		for (int col = 0; col < cols; ++col) {
			m_textureOffsets[row].push_back(TexCoords(
				(float)row * frameHeight,
				(float)col * frameWidth
			));
		}
	}
}

#pragma region Ctor/Dtor
TextComponent::TextComponent(GameObject & parent, String fontName, String text, String shader) :
	SpriteComponent(COMPONENT_TYPE::TEXT, parent, fontName, 0, 0, shader),
	m_text(text)
{
	_InitFontOffsets();
	_SetLettersFromString();
}

TextComponent::TextComponent(const TextComponent & rhs, GameObject & parent) :
	SpriteComponent(COMPONENT_TYPE::TEXT, rhs, parent),
	m_text(rhs.m_text) 
{
	_InitFontOffsets();
	_SetLettersFromString();
}

TextComponent::~TextComponent()
{
	for (Vector3D * color : m_colors) {
		delete color;
	}
	m_colors.clear();
}
#pragma endregion

void TextComponent::Update(double deltaTime) {}

TextComponent * TextComponent::Clone(GameObject & parent)
{
	TextComponent* comp = new TextComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * TextComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	String fontName = AcryJson::ParseString(j, "text", "font");
	String text = AcryJson::ParseString(j, "text", "text");
	String shader = AcryJson::ParseString(j, "text", "shader");
	return new TextComponent(gObject, fontName, text, shader);
}

void TextComponent::Override(nlohmann::json j)
{
	SetSprite(AcryJson::ValueExists(j, "text", "font") ? j["text"]["font"] : GetSpriteName());
	m_text = AcryJson::ValueExists(j, "text", "text") ? AcryJson::ParseString(j, "text", "text") : m_text;
	m_shader = AcryJson::ValueExists(j, "text", "shader") ? AcryJson::ParseString(j, "text", "shader") : m_shader;
}

void TextComponent::SetSprite(String fontName)
{
	SpriteComponent::SetSprite(fontName);
	_InitFontOffsets();
	_SetLettersFromString();
}

void TextComponent::SetText(String newText)
{
	m_text = newText;
	_SetLettersFromString();
}

String TextComponent::Text() const
{
	return m_text;
}

std::vector<std::vector<TexCoords>> TextComponent::GetTextureOffsets() const
{
	return m_textureOffsets;
}

std::pair<std::vector<std::pair<int, int>>, std::vector<Vector3D*>> TextComponent::GetLetterData() const
{
	return std::make_pair(
		m_letters, m_colors
	);
}
