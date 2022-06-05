//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H

#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/ground/components.cpp"
#include "flecs_modules/landscape/init.cpp"
#include "flecs_modules/tile/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include <vector>

namespace Landscape::Ground {

void createGroundTiles(flecs::world &ecsWorld) {
  auto landscapeTileFilter = ecsWorld.filter<LandscapeTile>();

  landscapeTileFilter.iter([](flecs::iter &it, LandscapeTile *t) {

  });

  //  Tile::createTilesWith8Neighbours(ecsWorld, prefab, baseName, width, height);
}

struct Inits {

  static flecs::entity groundTileBase_Prefab;

  static  flecs::query<const GroundTile, const Tile::Index, const Tile::Index2> groundTilesBasicQuery;
  static flecs::world ecsWorld;

  Inits(flecs::world &ecsWorld) {
//    ecsWorld.module<Inits>();
    ecsWorld.import <Landscape::Components>();
    Landscape::Init(ecsWorld);
//    ecsWorld.import <Landscape::Inits>();

    groundTileBase_Prefab = ecsWorld.prefab()
                                .add<GroundTile>()
                                .child_of<LandscapeTile>();

    groundTileBase_Prefab.child_of(Landscape::landscapeTileBase_Prefab);// deletes all ground Tiles on delete of map
  }
};
}// namespace Landscape::Ground

#endif// RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H