//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_TILE_INITS_H
#define RPG_SIM_SERVER_TILE_INITS_H

#include "flecs.h"
#include "flecs_modules/tile/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include <iostream>
#include <vector>
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

namespace Tile {

void createTilesWith8Neighbours(flecs::world &ecsWorld, const flecs::entity &prefab,
                                const std::string &baseName, size_t width, size_t height) {

  std::vector<flecs::entity_view> tiles{};
  tiles.reserve(height * width);

  auto size = prefab.get<Transform::Size2<>>();  // prefab should have size set

  assertm(size != nullptr, "No Transform::Size2<> set on Tile prefab");

  for (int32_t x = 0; x < width; x++) {
    for (int32_t y = 0; y < height; y++) {

      std::string name = baseName + " - x: " + std::to_string(x) + ", y: " + std::to_string(y);

      auto e = ecsWorld.entity(name.c_str())
                   .is_a(prefab)
                   .set<Index2>({x, y})
                   .set<Transform::Position2<int32_t>>({static_cast<int>(x * size->x), static_cast<int>(y * size->y)});

      tiles.emplace_back(flecs::entity_view(ecsWorld, e.id()));
    }
  }
  for (int32_t i = 0; i < tiles.size(); i++) {
    const auto x = i % (width);
    const auto y = i / width;

    //    auto tile = ecsWorld.entity(landscapeTiles[i]);
    auto tile = tiles[i].entity();

    Neighbours8 neighbours{nullptr, nullptr, nullptr,
                           nullptr, nullptr, nullptr, nullptr, nullptr};

    // 0  1  2
    // 3  4  5
    // 6  7  9

    // start in the top left
    if (x < width - 1) {// not all the way to the right
      neighbours.right = &tiles[i + 1];

      if (y < height - 1) {// not all the way at the bottom
        neighbours.bottom = &tiles[i + width];
        neighbours.bottomRight = &tiles[i + width + 1];
      }

      if (y > 0) {// not the top row
        neighbours.top = &tiles[i - width];
        neighbours.topRight = &tiles[i - width + 1];
      }
    }

    if (x > 0) {// not all the way to the left
      neighbours.left = &tiles[i - 1];

      if (y < height - 1) {                            // not all the way at the bottom
        neighbours.bottom = &tiles[i + width];// might end up overwriting the previous set bottom
        neighbours.bottomLeft = &tiles[i + width - 1];
      }

      if (y > 0) {                                  // not the top row
        neighbours.top = &tiles[i - width];// might end up overwriting the previous set top
        neighbours.topLeft = &tiles[i - width - 1];
      }
    }

    tile.set<Neighbours8>(neighbours);
  }
  std::cout << "" << std::endl;// TODO remove - debug line

}

struct Inits {
  Inits(flecs::world &ecsWorld) {
    ecsWorld.module<Inits>();

    //    auto landscapeTileBase = ecsWorld.entity()
    //        .add<Tile>()
    //        .set<Transform::Size2<>>({1.0, 1.0});
  }
};
}// namespace Tile

#endif// RPG_SIM_SERVER_TILE_INITS_H