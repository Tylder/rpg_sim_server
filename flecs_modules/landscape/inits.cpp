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

void createLandscapeTiles(flecs::world &ecsWorld, const flecs::entity &prefab, const std::string &baseName, size_t width, size_t height) {
  Tile::createTilesWith8Neighbours(ecsWorld, prefab, baseName, width, height);
}

void createGroundTiles(flecs::world &ecsWorld, const flecs::entity &prefab, const std::string &baseName, size_t width, size_t height) {
  Tile::createTilesWith8Neighbours(ecsWorld, prefab, baseName, width, height);
}

struct Inits {

  flecs::entity map;
  flecs::entity landscapeTileBase;
  flecs::entity groundTileBase;

  Inits(flecs::world &ecsWorld) {
//    ecsWorld.module<Inits>();

      map = ecsWorld.entity<Map>();

      landscapeTileBase = ecsWorld.prefab()
          .add<Tile::Tile>()
          .add<LandscapeTile>()
          .set<Transform::Size2<>>({1.0, 1.0}) // hard coded size
          .override<Tile::Neighbours8>()
          .override<Transform::Position2<>>()
          .override<Tile::Index>()
          .override<Tile::Index2>();

      landscapeTileBase.child_of(map);// deletes all landscape tiles on delete of map

      groundTileBase = ecsWorld.prefab()
                            .add<Tile::Tile>()
                            .add<Groun  dTile>()
                            .set<Transform::Size2<>>({1.0, 1.0}) // hard coded size
                            .override<Tile::Neighbours8>()
                            .override<Transform::Position2<>>()
                            .override<Tile::Index>()
                            .override<Tile::Index2>();

      groundTileBase.child_of(map);// deletes all ground Tiles on delete of map
  }
};
}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_INITS_H