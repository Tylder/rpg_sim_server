//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_INITS_H
#define RPG_SIM_SERVER_LANDSCAPE_INITS_H

#include "flecs_modules/tile/inits.cpp"
#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/tile/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include <vector>

namespace Landscape {

//static flecs::entity map;
//static flecs::entity landscapeTileBase_Prefab;
//static flecs::query<const LandscapeTile> landscapeTilesBasic_Query;
//static flecs::query<const LandscapeTile, const Tile::Index, const Tile::Index2> landscapeTiles_Query;

std::vector<flecs::entity_view> getTiles(flecs::world &ecsWorld) {
  std::vector<flecs::entity_view> landscapeTiles{};
  Landscape::landscapeTileQuery.iter([&](flecs::iter &it, const LandscapeTile *t) {
    for (auto i : it) {
      landscapeTiles.emplace_back(it.entity(i));
    }
  });
}

std::vector<flecs::entity_view> createTiles(flecs::world &ecsWorld, size_t width, size_t height) {
//  assert(landscapeTileBase_Prefab);

  return Tile::createTilesWith8Neighbours(ecsWorld, Landscape::landscapeTile_prefab, "landscapeTile", width, height);
}

void init(flecs::world &ecsWorld) {

//  map = ecsWorld.entity<Map>();
//
//  landscapeTileBase_Prefab = ecsWorld.prefab()
//                                 .add<Tile::Tile>()
//                                 .add<LandscapeTile>()
//                                 .set<Transform::Size2<>>({1.0, 1.0})// hard coded size
//                                 .override<Tile::Neighbours8>()
//                                 .override<Transform::Position2<>>()
//                                 .override<Tile::Index>()
//                                 .override<Tile::Index2>();
//
//  landscapeTileBase_Prefab.child_of(map);// deletes all landscape tiles on delete of map

//  landscapeTilesBasic_Query = ecsWorld.query<const LandscapeTile>();
}

}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_INITS_H