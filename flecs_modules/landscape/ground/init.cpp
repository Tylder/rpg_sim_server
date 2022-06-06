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

static flecs::entity groundTileBase_Prefab;
static flecs::query<const GroundTile, const Tile::Index, const Tile::Index2> groundTilesBasicQuery;

std::vector<flecs::entity_view> createGroundTiles(flecs::world &ecsWorld, size_t width, size_t height) {
  auto f = ecsWorld.filter<const LandscapeTile, const Tile::Neighbours8>();
  std::vector<flecs::entity_view> landscapeTiles{};

  f.iter([&](flecs::iter &it, const LandscapeTile *t, const Tile::Neighbours8 *n8) {
    for (auto i : it) {
      auto tile = it.entity(i);
      tile.add(granite_Entity);
      std::cout << "Landscape: " << tile.name() << ", type: " << tile.type() << std::endl;
      landscapeTiles.emplace_back(tile);
    }
  });

  std::vector<flecs::entity_view> groundTiles {};

  for (auto tile : landscapeTiles) {
    auto index2 = tile.get<Tile::Index2>();

    std::string name = "Ground - x: " + std::to_string(index2->x) + ", y: " + std::to_string(index2->y);

    auto g = ecsWorld.entity(name.c_str()).is_a(groundTileBase_Prefab).child_of(tile);

    groundTiles.emplace_back(g);

    std::cout << "Ground: " << g.name() << ", type: " << g.type() << std::endl;
    std::cout << "#######" << std::endl;
  }

  return Tile::addNeighbourNodes(std::move(groundTiles), width, height);
}

void init(flecs::world &ecsWorld) {
  ecsWorld.import <Landscape::Components>();
  Landscape::init(ecsWorld);

  groundTileBase_Prefab = ecsWorld.prefab()
                              .add<GroundTile>();

  granite_Entity = ecsWorld.entity("Granite").is_a(groundTileBase_Prefab);
  slate_Entity = ecsWorld.entity("Slate").is_a(groundTileBase_Prefab);
  sandstone_Entity = ecsWorld.entity("Sandstone").is_a(groundTileBase_Prefab);
}

}// namespace Landscape::Ground

#endif// RPG_SIM_SERVER_LANDSCAPE_GROUND_INITS_H