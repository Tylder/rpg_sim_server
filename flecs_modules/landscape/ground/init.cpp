//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H

#include "flecs_modules/landscape/init.cpp"
#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/ground/components.cpp"
#include "flecs_modules/tile/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include <vector>

namespace Landscape::Ground {

static flecs::entity granite_Prefab;
static flecs::entity slate_Prefab;
static flecs::entity sandstone_Prefab;

static flecs::query<const GroundTile, const Tile::Index, const Tile::Index2> groundTilesBasicQuery;

std::vector<flecs::entity_view> createGroundTiles(flecs::world &ecsWorld, size_t width, size_t height) {
  auto f = ecsWorld.filter<const LandscapeTile, const Tile::Neighbours8>();
  std::vector<flecs::entity_view> landscapeTiles{};

  f.iter([&](flecs::iter &it, const LandscapeTile *t, const Tile::Neighbours8 *n8) {
    for (auto i : it) {
      auto tile = it.entity(i);
      tile.add<Granite>();
      std::cout << "Landscape: " << tile.name() << ", type: " << tile.type() << std::endl;
      landscapeTiles.emplace_back(tile);
    }
  });

  std::vector<flecs::entity_view> groundTiles{};

  for (auto tile : landscapeTiles) {
    auto index2 = tile.get<Tile::Index2>();

    std::string name = "Ground - x: " + std::to_string(index2->x) + ", y: " + std::to_string(index2->y);

    tile.entity().add<Granite>(granite_Prefab);

    std::cout << "Ground: " << tile.name() << ", type: " << g.type() << std::endl;
    std::cout << "#######" << std::endl;
  }

  return Tile::addNeighbourNodes(std::move(groundTiles), width, height);
}

void init(flecs::world &ecsWorld) {
  ecsWorld.import <Landscape::Components>();
  Landscape::init(ecsWorld);

  granite_Prefab = ecsWorld.prefab()
                       .add<Granite>();

  slate_Prefab = ecsWorld.prefab()
                      .add<Slate>();

  sandstone_Prefab = ecsWorld.prefab()
                      .add<Sandstone>();
}

}// namespace Landscape::Ground

#endif// RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H