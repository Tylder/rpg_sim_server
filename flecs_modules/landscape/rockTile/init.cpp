//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H

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

std::vector<flecs::entity_view> createTiles(flecs::world &ecsWorld) {
  //  auto f = ecsWorld.filter<const LandscapeTile>();
  std::vector<flecs::entity_view> landscapeTiles{};
//  Landscape::landscapeTileQuery.iter([&](flecs::iter &it, const LandscapeTile *t) {
  ecsWorld.filter<LandscapeTile>().iter([&](flecs::iter &it, LandscapeTile *t) {
    for (auto i : it) {
      landscapeTiles.emplace_back(it.entity(i));
    }
  });

  auto map = Map::map.get<Map::Map>();

  const auto map2 = ecsWorld.get<Map::Map>();

  std::vector<float> noiseOutput(map->width *map->height);

  for (auto tile : landscapeTiles) {
    std::string name = "GroundTile - x: " + std::to_string(tile.get<Tile::Index2>()->x) + ", y: " + std::to_string(tile.get<Tile::Index2>()->y);
    //    tile.entity().add<Granite>(ecsWorld.entity());
    auto e = ecsWorld.entity().is_a(graniteTile_prefab).child_of(tile);
    auto json_string = e.to_json();
    auto json = nlohmann::json::parse(json_string.c_str());
    std::cout << json.dump(2) << std::endl;
    std::cout << "Landscape: " << tile.name() << ", type: " << tile.type() << std::endl;
  }

  return landscapeTiles;
}

}// namespace Landscape::Rock

#endif// RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H