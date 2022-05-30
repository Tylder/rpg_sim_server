//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_TILE_SYSTEMS_H
#define RPG_SIM_SERVER_TILE_SYSTEMS_H

#include "flecs.h"

namespace Tile {

struct Systems {
  Systems(flecs::world &ecsWorld) {
    ecsWorld.module<Systems>();

  }
};
}

#endif // RPG_SIM_SERVER_TILE_SYSTEMS_H