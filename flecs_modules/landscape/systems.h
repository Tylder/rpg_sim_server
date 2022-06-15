//
// Created by Administrator on 15/06/2022.
//

#ifndef RPG_SIM_SERVER_FLECS_MODULES_LANDSCAPE_SYSTEMS_H_
#define RPG_SIM_SERVER_FLECS_MODULES_LANDSCAPE_SYSTEMS_H_

#ifndef RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H
#define RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include "flecs_modules/landscape/init.cpp"
#include "flecs_modules/map/components.cpp"
#include <vector>

namespace Landscape {

struct Systems {
  Systems(flecs::world &ecsWorld) {
    ecsWorld.module<Systems>();
    ecsWorld.import <Map::Components>();

    ecsWorld.observer<Map::Map>()
        .event(flecs::OnSet)
        .each([&](flecs::entity, Map::Map &map) {
          createTiles(ecsWorld, map.width, map.height);
        });
  }
};
}// namespace Landscape

#endif// RPG_SIM_SERVER_LANDSCAPE_SYSTEMS_H

#endif//RPG_SIM_SERVER_FLECS_MODULES_LANDSCAPE_SYSTEMS_H_
