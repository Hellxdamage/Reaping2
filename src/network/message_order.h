#ifndef INCLUDED_NETWORK_MESSAGE_ORDER_H
#define INCLUDED_NETWORK_MESSAGE_ORDER_H
#include "boost/serialization/export.hpp"
#include "network/my_name_message.h"
#include "network/client_id_message.h"
#include "network/lifecycle_message.h"
#include "create_actor_message.h"
#include "set_ownership_message.h"
#include "position_message.h"
#include "platform/auto_id.h"
#include "move_message.h"
#include "player_controller_message.h"
#include "orientation_message.h"
#include "heading_message.h"
#include "pickup_message.h"
#include "ping_message.h"
#include "revive_message.h"


    struct message_order
    {
        message_order()
        {
            int32_t type;
            type=network::ClientIdMessage::GetType_static();
            type=network::MyNameMessage::GetType_static();
            type=network::LifecycleMessage::GetType_static();
            type=network::CreateActorMessage::GetType_static();
            type=network::SetOwnershipMessage::GetType_static();
            type=network::PositionMessage::GetType_static();
            type=network::MoveMessage::GetType_static();
            type=network::PlayerControllerMessage::GetType_static();
            type=network::DamageTakenMessage::GetType_static();
            type=network::OrientationMessage::GetType_static();
            type=network::HeadingMessage::GetType_static();
            type=network::PickupMessage::GetType_static();
            type=network::SetPickupContentMessage::GetType_static();
            type=network::PingMessage::GetType_static();
            type=network::ReviveMessage::GetType_static();

            type=platform::AutoId("player");
            type=platform::AutoId("plasma_gun");
            type=platform::AutoId("plasma_shot");
            type=platform::AutoId("spider1");
            type=platform::AutoId("pickup");
            type=platform::AutoId("pistol");
            type=platform::AutoId("pistol_shot");
            type=platform::AutoId("rocket_launcher");
            type=platform::AutoId("rocket_launcher_primary");
            type=platform::AutoId("rocket_launcher_secondary");
            type=platform::AutoId("rocket_launcher_projectile");
            type=platform::AutoId("grenade_projectile");
            type=platform::AutoId("pow_projectile");
            type=platform::AutoId("rocket_pow_projectile");
        }
    } _msg_order;

    BOOST_CLASS_EXPORT_GUID(network::MyNameMessage,"my_name")
    BOOST_CLASS_EXPORT_GUID(network::ClientIdMessage, "client_id")
    BOOST_CLASS_EXPORT_GUID(network::LifecycleMessage, "lifecycle")
    BOOST_CLASS_EXPORT_GUID(network::CreateActorMessage, "create_actor")
    BOOST_CLASS_EXPORT_GUID(network::SetOwnershipMessage, "set_ownership")
    BOOST_CLASS_EXPORT_GUID(network::PositionMessage, "position")
    BOOST_CLASS_EXPORT_GUID(network::MoveMessage, "move")
    BOOST_CLASS_EXPORT_GUID(network::PlayerControllerMessage, "player_c")
    BOOST_CLASS_EXPORT_GUID(network::DamageTakenMessage, "damage_taken")
    BOOST_CLASS_EXPORT_GUID(network::OrientationMessage, "orientation")
    BOOST_CLASS_EXPORT_GUID(network::HeadingMessage, "heading")
    BOOST_CLASS_EXPORT_GUID(network::PickupMessage, "pickup")
    BOOST_CLASS_EXPORT_GUID(network::SetPickupContentMessage, "set_pickup")
    BOOST_CLASS_EXPORT_GUID(network::PingMessage, "ping")
    BOOST_CLASS_EXPORT_GUID(network::ReviveMessage, "revive")
    


#endif//INCLUDED_NETWORK_MESSAGE_ORDER_H