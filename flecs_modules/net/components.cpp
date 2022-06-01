//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_NET_COMPONENTS_H
#define RPG_SIM_SERVER_NET_COMPONENTS_H

#include "flecs.h"

namespace Net {

struct Serializable {}; // tag, not used
struct Replicated {}; // tag used to specify whether the component should be replicated from server

/* if of the machine responsible to update value, could be same as owner or it could be a client
 * if it's a client then the client runs the update and pushes the data to listeners but the server might
 * also run the update to check the calculation
 */
struct Responsibility {};

struct Owner {};

struct Client {
  int32_t id;
};

struct Server {};

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    ecsWorld.component<Serializable>()
        .add(flecs::Tag);

    ecsWorld.component<Replicated>()
        .add(flecs::Tag);

    ecsWorld.component<Responsibility>();
    ecsWorld.component<Owner>();

    ecsWorld.component<Client>()
        .member(flecs::I32, "id");

    ecsWorld.component<Server>().is_a<Client>();  // Server is a superset of Client

//    auto landscapeTileBase = ecsWorld.entity()
//        .add<Tile>()
//        .set<Transform::Size2<>>({1.0, 1.0});

  }
};
}

#endif // RPG_SIM_SERVER_NET_COMPONENTS_H