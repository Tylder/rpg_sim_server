//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_MAP_COMPONENTS_H
#define RPG_SIM_SERVER_MAP_COMPONENTS_H

#include "flecs.h"

namespace Map {

struct RockTileConfig {
  uint8_t granitePriority; /* the higher, the more prominent, 0-255, 0 means not used */
  uint8_t slatePriority;
  uint8_t sandstonePriority;
};

struct Map {
  int seed;
  uint16_t width, height;
  RockTileConfig rockTileConfig;
};

static flecs::entity map;// singleton

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    ecsWorld.component<Map>().add<Map>();//  singleton
    map = ecsWorld.entity<Map>("map");
  }
};
}// namespace Map

#endif// RPG_SIM_SERVER_MAP_COMPONENTS_H