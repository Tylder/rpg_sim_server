//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H

#include "flecs.h"
#include "flecs_modules/tile/components.cpp"

namespace Landscape::Ground {

struct GroundTile {};   //

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();
        ecsWorld.component<GroundTile>().is_a<Tile::Tile>();
  }
};
} // Landscape::Ground namespace

#endif // RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H