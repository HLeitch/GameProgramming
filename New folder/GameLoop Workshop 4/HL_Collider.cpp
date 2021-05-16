#include "HL_Collider.h"
#include "HL_GameObject.h"
#include <algorithm>


HL_Collider::HL_Collider(HL_GameObject* parent)
{
    this->parent = parent;

}

CircleCollider::CircleCollider(HL_GameObject* parent, double x, double y, double radius) :HL_Collider(parent)
{
    pointOnObject = new HL_Vector2D;
    pointOnObject->X = x;
    pointOnObject->Y = y;

    this->radius = radius;
}

/// <summary>
/// takes a vector relative to the top right corner of the object
/// </summary>
/// <param name="parent"></param>
/// <param name="point"></param>
/// <param name="radius"></param>
CircleCollider::CircleCollider(HL_GameObject* parent, HL_Vector2D* point, double radius):HL_Collider(parent)
{
   
    pointOnObject = point;
    this->radius = radius;
}

CircleCollider::~CircleCollider()
{

    delete pointOnObject;
    
    pointOnObject = nullptr;
}

bool CircleCollider::findCollision(HL_Collider* otherCollider)
{
    if ((parent->Active) && (otherCollider->parent->Active)) {
        return otherCollider->hasCollided(this);
    }

    else return false;
    
}

bool CircleCollider::hasCollided(HL_Collider* otherCollider)
{
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "CircleCollider collided with default collider. This should not happen. (%p)", this);
    return false;
}

bool CircleCollider::hasCollided(CircleCollider* otherCollider)
{

    if((this->Center()->distance(otherCollider->Center())) < (this->radius + otherCollider->radius))
    {


        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"COLLISION OCCOURED! %p and %p. Object Type %i and %i",this,otherCollider,this->parent->_objectType,otherCollider->parent->_objectType);
        return true;
    }

    return false;
}
bool CircleCollider::hasCollided(SquareCollider* othercollider)
{
    return othercollider->intersects(this);
}
void CircleCollider::Move()
{
    if (!_center)
    {
        _center = new HL_Vector2D((this->parent->realPosition.X+ pointOnObject->X), (this->parent->realPosition.Y + pointOnObject->Y));
    }
    else
    {
        _center->X = (this->parent->myRect->x + pointOnObject->X);
        _center->Y = (this->parent->myRect->y + pointOnObject->Y);
    }

}

HL_Vector2D* CircleCollider::Center()
{
   

    return _center;
}

SquareCollider::SquareCollider(HL_GameObject* parent, double x, double y, double w, double h):HL_Collider(parent)
{
    this->parent = parent;

    realRect = new SDL_Rect;

    relativeRect = new SDL_Rect;

    relativeRect->x = x;
    relativeRect->y = y;
    relativeRect->w = w;
    relativeRect->h = h;



}
/// <summary>
/// Takes the rect of the parent.
/// Lovely and simple
/// </summary>
/// <param name="parent"></param>
SquareCollider::SquareCollider(HL_GameObject* parent):HL_Collider(parent)
{
    realRect = parent->myRect;
}

SquareCollider::~SquareCollider()
{
    delete realRect;
    delete relativeRect;

}

bool SquareCollider::findCollision(HL_Collider* otherCollider)
{
    if ((parent->Active) && (otherCollider->parent->Active)) {
        return otherCollider->hasCollided(this);
    }

    else return false;
}

bool SquareCollider::hasCollided(HL_Collider* otherCollider)
{

    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Default collider collision called in SquareCollider %p", this);
    return false;
}

bool SquareCollider::hasCollided(CircleCollider* otherCollider)
{
    return intersects(otherCollider);
}

bool SquareCollider::hasCollided(SquareCollider* otherCollider)
{
    SDL_Rect* otherRect = otherCollider->realRect;
    bool xintersect = false;
    bool yintersect = false;

    //does the sphere intersect with the square collider
       if ((realRect->x > otherRect->x + otherRect->w)){ xintersect = true;}
       else if ((realRect->x + realRect->w) < otherRect->x) { xintersect = true;}
       else if ((realRect->y > otherRect->y) + otherRect->h) { yintersect = true; }
       else if ((realRect->y + realRect->h) < otherRect->y){yintersect = true; }

    if (xintersect || yintersect)
    {
 return false;
    }
    else
    {
        return true;
    }
}

bool SquareCollider::intersects(CircleCollider* circle)
{
    if (circle->parent->_objectType == 1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_ASSERT, "SquareCollider checked against a PLAYER. Colp = %p. Colname = %s (%p). otherColp = %p", this, this->parent->_objectName.c_str
        (), this->parent, circle->parent);
    }
    

    //find the closest point between the circle and the rectangle
    double closestX = std::clamp((int)circle->Center()->X, realRect->x, realRect->x + realRect->w);
    double closestY = std::clamp((int)circle->Center()->Y, realRect->y, realRect->y + realRect->h);

    //find the distance from the center of the circle to this closest point
    double distanceX = circle->Center()->X - closestX;
    double distanceY = circle->Center()->Y - closestY;

    ///return whether distance between is smaller than radius
    bool val = ((distanceX * distanceX) + (distanceY * distanceY)) < (circle->radius * circle->radius);
    if (val) 
    
   { SDL_LogInfo(SDL_LOG_CATEGORY_ASSERT, "Wall involved in collision %p, Other Collider %p", this->parent, circle->parent); }
    return(val);
}

void SquareCollider::Move()
{
    SDL_Rect* pr = parent->myRect;

    realRect->x =relativeRect->x;
    realRect->y = relativeRect->y;
    realRect->w = relativeRect->w;
    realRect->h = relativeRect->h;
}