#ifndef INCLUDED_CORE_COLLISION_COMPONENT_H
#define INCLUDED_CORE_COLLISION_COMPONENT_H
#include "i_collision_component.h"


class Actor;
class CollisionComponent : public ICollisionComponent
{
public:
    virtual CollisionClass::Type GetCollisionClass()const;
    virtual void SetCollisionClass( CollisionClass::Type CollisionClassType );
    virtual void Collide( Actor& Other );
    virtual void ClipScene(); //TODO: i don't really like this concept. This might be simply just a collision with scene edges, later maybe.
    virtual double GetRadius()const;
    virtual void SetRadius( double Radius);

protected:
    CollisionComponent();
    friend class ComponentFactory;
    CollisionClass::Type mCollisionClassType;
    double mRadius;
};

#endif//INCLUDED_CORE_COLLISION_COMPONENT_H