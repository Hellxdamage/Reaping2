#ifndef INCLUDED_CORE_DAMAGE_TAKEN_EVENT_H
#define INCLUDED_CORE_DAMAGE_TAKEN_EVENT_H
#include "platform/i_platform.h"

namespace core {
struct DamageTakenEvent : public Event
{
    enum Type
    {
        Health = 0,
        Armor
    };
    glm::vec2 const Pos;
    int32_t Damage;
    Type type;
    int32_t ActorGUID;
    DamageTakenEvent( double x, double y ): Pos( x, y ), Damage( 0 ), type( Health ), ActorGUID( -1 ) {}
    DamageTakenEvent( glm::vec2 const& p ): Pos( p ), Damage( 0 ), type( Health ), ActorGUID( -1 ) {}
};
}
#endif//INCLUDED_CORE_DAMAGE_TAKEN_EVENT_H
