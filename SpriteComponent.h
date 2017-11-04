/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpriteComponent.h
Purpose: Sprite Component class - contains a mesh for 2D rendering
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Component.h"
#include "Mesh.h"
#include "AcrylicorTypedefs.h"
#include "STBSurface.h"

class SpriteComponent :
	public Component
{
protected:
	String m_spriteName;
	SurfaceTextureBuffer * m_texture;
	Mesh& m_mesh;
	int m_frameX, m_frameY;
	float m_tileX, m_tileY;
	String m_shader;

	SpriteComponent(COMPONENT_TYPE type, GameObject& parent, String spriteName, int frameX, int frameY, String shader, float tileX = 1.f, float tileY = 1.f);
	SpriteComponent(COMPONENT_TYPE type, const SpriteComponent& rhs, GameObject& parent);
public:
	SpriteComponent() = delete;
	SpriteComponent(GameObject& parent, String spriteName);
	SpriteComponent(GameObject& parent, String spriteName, int frameX, int frameY, String shader, float tileX = 1.f, float tileY = 1.f);
	SpriteComponent(const SpriteComponent& rhs) = delete;
	SpriteComponent(const SpriteComponent& rhs, GameObject& parent);
	SpriteComponent& operator= (SpriteComponent rhs) = delete;
	~SpriteComponent();

	virtual void Update(double deltaTime);
	virtual SpriteComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};

	const Mesh& GetMesh() const;
	void SetMesh(Mesh& mesh);

	String GetSpriteName() const;
	void SetSprite(String spriteName);

	GLuint GetTextureBuffer() const;
	bool TextureHasAlpha() const;

	void SetFrame(int frameNum);
	void SetFrame(int x, int y);
	void NextFrame();
	void PrevFrame();
	int GetFrame() const;
	void GetFrame(int &x, int &y) const;
	float GetFrameUOffset() const;
	float GetFrameVOffset() const;

	float FrameHeight() const;
	float FrameWidth() const;

	float TileX() const;
	float TileY() const;

	String Shader() const;

	SurfaceTextureBuffer * GetTexture() const;
};

#endif