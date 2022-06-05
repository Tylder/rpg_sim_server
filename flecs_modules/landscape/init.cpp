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

flecs::entity map;
flecs::entity landscapeTileBase_Prefab;
flecs::query<const LandscapeTile, const Tile::Index, const Tile::Index2> landscapeTilesBasicQuery;

void createLandscapeTiles(flecs::world &ecsWorld, const flecs::entity &prefab, const std::string &baseName, size_t width, size_t height) {
  Tile::createTilesWith8Neighbours(ecsWorld, prefab, baseName, width, height);
}

void createGroundTiles(flecs::world &ecsWorld) {
  auto landscapeTileFilter = ecsWorld.filter<LandscapeTile>();

  landscapeTileFilter.iter([](flecs::iter &it, LandscapeTile *t) {

  });

  //  Tile::createTilesWith8Neighbours(ecsWorld, prefab, baseName, width, height);
}

void Init(flecs::world &ecsWorld) {

  map = ecsWorld.entity<Map>();

  landscapeTileBase_Prefab = ecsWorld.prefab()
                                 .add<Tile::Tile>()
                                 .add<LandscapeTile>()
                                 .set<Transform::Size2<>>({1.0, 1.0})// hard coded size
                                 .override<Tile::Neighbours8>()
                                 .override<Transform::Position2<>>()
                                 .override<Tile::Index>()
                                 .override<Tile::Index2>();

  landscapeTileBase_Prefab.child_of(map);// deletes all landscape tiles on delete of map
}

}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_INITS_H