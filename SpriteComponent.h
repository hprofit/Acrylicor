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

class SpriteComponent :
	public Component
{
private:
	std::string m_spriteName;
	Mesh& m_mesh;

public:
	SpriteComponent() = delete;
	SpriteComponent(GameObject& parent, std::string meshName);
	SpriteComponent(GameObject& parent, const char * meshName);
	SpriteComponent(SpriteComponent const& rhs) = delete;
	SpriteComponent& operator= (SpriteComponent rhs) = delete;
	~SpriteComponent();

	virtual void Update(double deltaTime);

	const Mesh& GetMesh() const { 
		return m_mesh; 
	}

	void SetMesh(Mesh& mesh) { m_mesh = mesh; }
};

#endif