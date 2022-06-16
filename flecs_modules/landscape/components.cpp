//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H

#include "flecs_modules/tile/components.cpp"
#include "flecs.h"
#include "flecs_modules/map/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include "flecs_modules/landscape/rockTile/components.cpp"
#include "flecs_modules/landscape/rockTile/systems.cpp"

namespace Landscape {

// in meters, applies to both dirt and water
struct Depth {
  uint8_t value;
};
// 0 - 100, applies to both dirt and water
struct Coverage {
  uint8_t value;
};

struct LandscapeTile : Tile::Tile2 {};
struct RockTile : LandscapeTile {};
struct DirtTile : LandscapeTile {};
struct GrassTile : LandscapeTile {};
struct WaterTile : LandscapeTile {};

static flecs::entity landscapeTile_prefab;
static flecs::entity rockTile_prefab;
static flecs::entity dirtTile_prefab;
static flecs::entity grassTile_prefab;
static flecs::entity waterTile_prefab;

// QUERIES
static flecs::query<const LandscapeTile> landscapeTileQuery;

struct Components {

  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();
    ecsWorld.import<Landscape::Rock::Components>();

    ecsWorld.component<LandscapeTile>().add(flecs::Tag);
    ecsWorld.component<RockTile>().add(flecs::Tag);
    ecsWorld.component<DirtTile>().add(flecs::Tag);
    ecsWorld.component<GrassTile>().add(flecs::Tag);
    ecsWorld.component<WaterTile>().add(flecs::Tag);

    ecsWorld.component<Depth>()
        .member(flecs::U8, "value");

    ecsWorld.component<Coverage>()
        .member(flecs::U8, "value");

    ecsWorld.component<LandscapeTile>();
    ecsWorld.component<RockTile>();
    ecsWorld.component<DirtTile>();
    ecsWorld.component<GrassTile>();
    ecsWorld.component<WaterTile>();

    landscapeTile_prefab = ecsWorld.prefab("landscapeTile")
                               .child_of(Map::map)// deletes all landscape tiles on delete of map
                               .is_a(Tile::tile2_prefab)
//                               .is_a<LandscapeTile>()
                               .add<LandscapeTile>()
                               .set<Transform::Size2<>>({1.0, 1.0})// hard coded size
                               .override<Tile::Neighbours8>();

    rockTile_prefab = ecsWorld.prefab("rockTile").is_a(landscapeTile_prefab).is_a<RockTile>().add<RockTile>();
    dirtTile_prefab = ecsWorld.prefab("dirtTile").is_a(landscapeTile_prefab).is_a<DirtTile>().add<DirtTile>();
    grassTile_prefab = ecsWorld.prefab("grassTile").is_a(landscapeTile_prefab).is_a<GrassTile>().add<GrassTile>();
    waterTile_prefab = ecsWorld.prefab("waterTile").is_a(landscapeTile_prefab).is_a<WaterTile>().add<WaterTile>();

    landscapeTileQuery = ecsWorld.query<const LandscapeTile>();
  }
};
}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H