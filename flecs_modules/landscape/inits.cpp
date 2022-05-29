//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_INITS_H
#define RPG_SIM_SERVER_LANDSCAPE_INITS_H

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include <iostream>
#include <vector>

namespace Landscape {

void addLandscapeTile(flecs::world &ecsWorld, size_t width, size_t height) {

  auto landscapeTileBase = ecsWorld.entity()
                               .add<Tile>()
                               .add<LandscapeTile>()
                               .set<Transform::Size2<>>({1.0, 1.0});

  //  std::vector<flecs::entity_t> landscapeTileIds { };
  std::vector<flecs::entity_view> landscapeTiles{};
  landscapeTiles.reserve(height * width);

  for (int32_t x = 0; x < width; x++) {
    for (int32_t y = 0; y < height; y++) {

      std::string name = "x: " + std::to_string(x) + ", y: " + std::to_string(y);

      auto e = ecsWorld.entity(name.c_str())
                   //          .is_a(landscapeTileBase)
                   .add<Tile>()
                   .add<LandscapeTile>()
                   .set<Transform::Position2<int32_t>>({x, y});

      //      landscapeTiles.push_back(e.id());
      landscapeTiles.emplace_back(flecs::entity_view(ecsWorld, e.id()));

      //      landscapeTiles.push_back(
      //        &ecsWorld.entity()
      ////          .is_a(landscapeTileBase)
      //          .add<Tile>()
      //          .add<LandscapeTile>()
      //          .set<Transform::Position2<int32_t>>({x, y})
      //      );

      //        &flecs::entity(ecsWorld)
      //        .is_a(landscapeTileBase)
      //        .set<Transform::Position2<int32_t>>({x, y})
      //      auto e = flecs::entity(ecsWorld)
      //        .is_a(landscapeTileBase)
      //        .set<Transform::Position2<int32_t>>({x, y});
      //
      //      landscapeTiles.emplace_back(&e);
    }
  }
  for (int32_t i = 0; i < landscapeTiles.size(); i++) {
    const auto x = i % (width);
    const auto y = i / width;

    //    auto tile = ecsWorld.entity(landscapeTiles[i]);
    auto tile = landscapeTiles[i].entity();

    Neighbours8 neighbours{nullptr, nullptr, nullptr,
                           nullptr, nullptr, nullptr, nullptr, nullptr};

    // 0  1  2
    // 3  4  5
    // 6  7  9

    // start in the top left
    if (x < width - 1) {// not all the way to the right
      neighbours.right = &landscapeTiles[i + 1];

      if (y < height - 1) {  // not all the way at the bottom
        neighbours.bottom = &landscapeTiles[i + width];
        neighbours.bottomRight = &landscapeTiles[i + width + 1];
      }

      if (y > 0) { // not the top row
        neighbours.top = &landscapeTiles[i - width];
        neighbours.topRight = &landscapeTiles[i - width + 1];
      }
    }

    if (x > 0) {// not all the way to the left
      neighbours.left = &landscapeTiles[i - 1];

      if (y < height - 1) {// not all the way at the bottom
        neighbours.bottomLeft = &landscapeTiles[i + width - 1];
      }

      if (y > 0) { // not the top row
        neighbours.topLeft = &landscapeTiles[i - width - 1];
      }
    }

    tile.set<Neighbours8>(neighbours);
  }
  std::cout << "sdsdsd" << std::endl;

  //  return landscapeTiles;
}

struct Inits {
  Inits(flecs::world &ecsWorld) {
    ecsWorld.module<Inits>();

    //    auto landscapeTileBase = ecsWorld.entity()
    //        .add<Tile>()
    //        .set<Transform::Size2<>>({1.0, 1.0});
  }
};
}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_INITS_H