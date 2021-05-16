#pragma once
#include "SDL.h"
#include "HL_Vector2D.h"

class HL_GameObject;
class CircleCollider;
class SquareCollider;

class HL_Collider
{
	public:

	HL_Collider(HL_GameObject* parent);

	HL_GameObject* parent = nullptr;

	virtual bool findCollision(HL_Collider* otherCollider) = 0;

	virtual bool hasCollided(HL_Collider* otherCollider) = 0;
   virtual bool hasCollided(CircleCollider* otherCollider) = 0;
   virtual bool hasCollided(SquareCollider* otherCollider) = 0;
   virtual void Move() = 0;
	

};


class CircleCollider: public HL_Collider
{
public:
	CircleCollider(HL_GameObject*, double x, double y, double radius);
	CircleCollider(HL_GameObject*, HL_Vector2D* point, double radius);
	~CircleCollider();

	// Inherited via HL_Collider

	virtual bool findCollision(HL_Collider* otherCollider);
	
	bool hasCollided(HL_Collider* otherCollider) override;
	 bool hasCollided(CircleCollider* otherCollider) override;
	 bool hasCollided(SquareCollider* othercollider) override;

	void Move() override;

	HL_Vector2D* Center();


	HL_Vector2D* pointOnObject = nullptr;

	double radius = 0;

private:
	HL_Vector2D* _center= nullptr;
};

class SquareCollider : public HL_Collider
{
public: 
	SquareCollider(HL_GameObject* parent, double x, double y, double w, double h);
	SquareCollider(HL_GameObject*);
	~SquareCollider();

	// Inherited via HL_Collider
	virtual bool findCollision(HL_Collider* otherCollider);
	bool hasCollided(HL_Collider* otherCollider) override;
	 bool hasCollided(CircleCollider* otherCollider) override;
	bool hasCollided(SquareCollider* otherCollider) override;

	//returns true if a circle intersects the square
	bool intersects(CircleCollider* circle);

	void Move();
	SDL_Rect* realRect;
	SDL_Rect* relativeRect;
};

