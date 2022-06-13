//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_MAP_COMPONENTS_H
#define RPG_SIM_SERVER_MAP_COMPONENTS_H

#include "flecs.h"

namespace Map {

struct Map {
  uint16_t width, height;
};

static flecs::entity map; // singleton

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    ecsWorld.component<Map>().add<Map>();//  singleton
    map = ecsWorld.entity<Map>("map");
  }
};
}// namespace Map

#endif// RPG_SIM_SERVER_MAP_COMPONENTS_H