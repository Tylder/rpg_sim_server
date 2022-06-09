//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H

#include "flecs_modules/landscape/init.cpp"
#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/rockTile/components.cpp"
#include "flecs_modules/tile/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include "nlohmann/json.hpp"
#include <chrono>
#include <iostream>
#include <vector>

namespace Landscape::Rock {

static flecs::entity granite_Prefab;
static flecs::entity slate_Prefab;
static flecs::entity sandstone_Prefab;

//static flecs::query<const GroundTile, const Tile::Index, const Tile::Index2> groundTilesBasicQuery;

void init(flecs::world &ecsWorld) {
  ecsWorld.import <Components>();
  Landscape::init(ecsWorld);

  granite_Prefab = ecsWorld.prefab()
                       //                       .add<Granite>()
                       //                       .add<GroundTile>()
                       .set<Landscape::Coverage>({55});
  //                       .add(GroundTypeEnum::Granite);

  //  slate_Prefab = ecsWorld.prefab()
  //                     .add(GroundTypeEnum::Slate);
  //
  //  sandstone_Prefab = ecsWorld.prefab()
  //                         .add(GroundTypeEnum::Sandstone);
}

std::vector<flecs::entity_view> createTiles(flecs::world &ecsWorld) {
  init(ecsWorld);
  //  auto f = ecsWorld.filter<const LandscapeTile>();
  std::vector<flecs::entity_view> landscapeTiles{};
  //
  //  f.iter([&](flecs::iter &it, const LandscapeTile *t) {
  //    for (auto i : it) {
  //      landscapeTiles.emplace_back(it.entity(i));
  //    }
  //  });
  //
  //  for (auto tile : landscapeTiles) {
  //    std::string name = "GroundTile - x: " + std::to_string(tile.get<Tile::Index2>()->x) + ", y: " + std::to_string(tile.get<Tile::Index2>()->y);
  //    //    tile.entity().add<Granite>(ecsWorld.entity());
  //    auto e = ecsWorld.entity().is_a(granite_Prefab).child_of(tile);
  //    auto json_string = e.to_json();
  //    auto json = nlohmann::json::parse(json_string.c_str());
  //    std::cout << json.dump(2) << std::endl;
  //    std::cout << "Landscape: " << tile.name() << ", type: " << tile.type() << std::endl;
  //  }

  return landscapeTiles;
}

}// namespace Landscape::Rock

#endif// RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H