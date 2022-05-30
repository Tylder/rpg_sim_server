//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H

#include "flecs.h"
#include "flecs_modules/tile/components.cpp"

namespace Landscape {

struct Map {};
struct LandscapeTile {}; // base type
struct GroundTile {}; //

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    ecsWorld.component<Map>().add<Map>(); //  singleton
//    map = ecsWorld.entity<Map>();

    ecsWorld.component<LandscapeTile>().is_a<Tile::Tile>();
    ecsWorld.component<GroundTile>().is_a<Tile::Tile>();

  }
};
}

#endif // RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H