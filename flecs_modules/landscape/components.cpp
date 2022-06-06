//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H

#include "flecs_modules/tile/components.cpp"
#include "flecs.h"

namespace Landscape {

struct Map {};
struct LandscapeTile {};// base type
//struct RockGroundTile {};//
//struct DirtTile {};      //
//struct GrassTile {};     //
//struct WaterTile {};     //

struct LandscapeTileType {};

// in meters, applies to both dirt and water
struct Depth {
  uint8_t value;
};
// 0 - 100, applies to both dirt and water
struct Coverage {
  uint8_t value;
};

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    ecsWorld.component<Map>().add<Map>();//  singleton
    ecsWorld.component<LandscapeTile>().is_a<Tile::Tile>();

    ecsWorld.component<Depth>("Depth")
        .member(flecs::U8, "value");

    ecsWorld.component<Coverage>("Coverage")
        .member(flecs::U8, "value");

    ecsWorld.component<LandscapeTileType>()
        .add(flecs::Exclusive);
  }
};
}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H