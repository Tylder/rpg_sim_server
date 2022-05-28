//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H
#define RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include <iostream>
#include "flecs_modules/transform/components.cpp"
#include "flecs_modules/landscape/components.cpp"

namespace Landscape {

void addLandscapeTile(flecs::world &ecsWorld, size_t width, size_t height) {

  auto landscapeTileBase = ecsWorld.entity()
        .add<Tile>()
        .add<LandscapeTile>()
        .set<Transform::Size2<>>({1.0, 1.0});

//  std::vector<flecs::entity_t> landscapeTileIds { };
  std::vector<flecs::entity_view> landscapeTiles { };
  landscapeTiles.reserve(height * width);

  for (int32_t x = 0; x < width; x++) {
    for (int32_t y = 0; y < height; y++) {

      std::string name = "x: " + std::to_string(x) +  ", y: " +  std::to_string(y);

      auto e = ecsWorld.entity(name.c_str())
//          .is_a(landscapeTileBase)
          .add<Tile>()
          .add<LandscapeTile>()
          .set<Transform::Position2<int32_t>>({x, y});

//      landscapeTiles.push_back(e.id());
      landscapeTiles.emplace_back(flecs::entity_view(ecsWorld,e.id()));

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
    const auto x =  i % (width);
    const auto y = i / width;

//    auto tile = ecsWorld.entity(landscapeTiles[i]);
    auto tile = landscapeTiles[i].entity();

    Neighbours8 neighbours {nullptr, nullptr, nullptr,
                            nullptr, nullptr, nullptr, nullptr,nullptr};

    if (x > 0) {
        neighbours.left = &landscapeTiles[i - 1];

        if (y > 0) {
          neighbours.topLeft = &landscapeTiles[i - 1 - width];
          neighbours.top = &landscapeTiles[i - width];
        }

        if (y < height - 2) {
          neighbours.bottomRight = &landscapeTiles[i - width + 1];
          neighbours.topRight = &landscapeTiles[i - width + 1];
        }
    }

    if (x < width - 2) {
      neighbours.right = &landscapeTiles[i + 1];

      if (y < height - 2) {
        neighbours.bottomRight = &landscapeTiles[i + width + 1];
        neighbours.bottom = &landscapeTiles[i + width];
      }
    }

    tile.set<Neighbours8>(neighbours);
  }
  std::cout << "sdsdsd" << std::endl;

//  return landscapeTiles;
}

struct Systems {
  Systems(flecs::world &ecsWorld) {
    ecsWorld.module<Systems>();

//    auto landscapeTileBase = ecsWorld.entity()
//        .add<Tile>()
//        .set<Transform::Size2<>>({1.0, 1.0});

  }
};
}

#endif RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H