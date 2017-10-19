#include "GameObject.h"

GameObject::GameObject() :
	m_compPhysicsBody(NULL),
	m_compPhysicsMovement(NULL),
	m_compSprite(NULL),
	m_compTransform(NULL)
{}

GameObject::GameObject(GameObject const & rhs)
{
}

GameObject & GameObject::operator=(GameObject rhs)
{
	return *this;
}

GameObject::~GameObject()
{
	delete m_compPhysicsBody;
	delete m_compPhysicsMovement;
	delete m_compSprite;
	delete m_compTransform;
}

void GameObject::AddPhysicsBodyComponent()
{
	m_compPhysicsBody = new PhysicsBodyComponent(*this);
}

void GameObject::AddPhysicsMovementComponent()
{
	m_compPhysicsMovement = new PhysicsMovementComponent(*this);
}

void GameObject::AddSpriteComponent(char * spriteName)
{
	m_compSprite = new SpriteComponent(*this, spriteName);
}

void GameObject::AddTransformComponent(Vector2D position, float angle, float scaleX, float scaleY)
{
	m_compTransform = new TransformComponent(*this, position, angle, scaleX, scaleY);
}
