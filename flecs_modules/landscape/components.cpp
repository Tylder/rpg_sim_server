//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H

#include "flecs_modules/tile/components.cpp"
#include "flecs.h"
#include "flecs_modules/transform/components.cpp"

namespace Landscape {

struct Map {};

// in meters, applies to both dirt and water
struct Depth {
  uint8_t value;
};
// 0 - 100, applies to both dirt and water
struct Coverage {
  uint8_t value;
};

struct Components {

  static flecs::entity mapE;
  static flecs::entity landscapeTile_prefab;
  static flecs::entity rockTile_prefab;
  static flecs::entity dirtTile_prefab;
  static flecs::entity grassTile_prefab;
  static flecs::entity waterTile_prefab;

  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();
    ecsWorld.import <Tile::Components>();

    mapE = ecsWorld.entity<Map>("Map");

    landscapeTile_prefab = ecsWorld.prefab()
                               .child_of(mapE)// deletes all landscape tiles on delete of map
                               .is_a(Tile::Components::tile2_prefab)
                               .set<Transform::Size2<>>({1.0, 1.0})// hard coded size
                               .override<Tile::Neighbours8>()
                               .override<Transform::Position2<>>()
                               .override<Tile::Index>()
                               .override<Tile::Index2>();

    rockTile_prefab = ecsWorld.prefab("rockTile").is_a(landscapeTile_prefab);
    dirtTile_prefab = ecsWorld.prefab("dirtTile").is_a(landscapeTile_prefab);
    grassTile_prefab = ecsWorld.prefab("grassTile").is_a(landscapeTile_prefab);
    waterTile_prefab = ecsWorld.prefab("waterTile").is_a(landscapeTile_prefab);

    ecsWorld.component<Map>().add<Map>();//  singleton

    ecsWorld.component<Depth>("Depth")
        .member(flecs::U8, "value");

    ecsWorld.component<Coverage>("Coverage")
        .member(flecs::U8, "value");

    //    ecsWorld.component<LandscapeTileType>()
    //        .add(flecs::Exclusive);
  }
};
}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H