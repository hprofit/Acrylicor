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
private:
	String m_spriteName;
	SurfaceTextureBuffer * m_texture;
	Mesh& m_mesh;
	float offsetX, offsetY;

public:
	SpriteComponent() = delete;
	SpriteComponent(GameObject& parent, String spriteName);
	SpriteComponent(const SpriteComponent& rhs) = delete;
	SpriteComponent(const SpriteComponent& rhs, GameObject& parent);
	SpriteComponent& operator= (SpriteComponent rhs) = delete;
	~SpriteComponent();

	virtual void Update(double deltaTime);
	virtual SpriteComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);

	const Mesh& GetMesh() const;
	void SetMesh(Mesh& mesh);

	String GetSpriteName() const;
	void SetSprite(String spriteName);

	GLuint GetTextureBuffer() const;
	bool TextureHasAlpha() const;
};

#endif