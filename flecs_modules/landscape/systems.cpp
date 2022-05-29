//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H
#define RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include <iostream>
#include <vector>
#include "flecs_modules/transform/components.cpp"
#include "flecs_modules/landscape/components.cpp"

namespace Landscape {

struct Systems {
  Systems(flecs::world &ecsWorld) {
    ecsWorld.module<Systems>();

//    auto landscapeTileBase = ecsWorld.entity()
//        .add<Tile>()
//        .set<Transform::Size2<>>({1.0, 1.0});

  }
};
}

#endif // RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H