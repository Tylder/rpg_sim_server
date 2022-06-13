//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_MAP_SYSTEMS_H
#define RPG_SIM_SERVER_MAP_SYSTEMS_H

#include "flecs.h"
#include "flecs_modules/map/components.cpp"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/rockTile/components.cpp"
#include "flecs_modules/landscape/rockTile/init.cpp"
#include "flecs_modules/landscape/init.cpp"

namespace Map {

struct Systems {
  Systems(flecs::world &ecsWorld) {
    ecsWorld.module<Systems>();

    ecsWorld.observer<Map>()
        .event(flecs::OnSet)
        .each([&](flecs::entity, Map &map) {
          Landscape::createTiles(ecsWorld, map.width, map.height);
          Landscape::Rock::createTiles(ecsWorld);
          //        Landscape::createTiles(ecsWorld, map.width, map.height);
        });
  }
};
}// namespace Map

#endif// RPG_SIM_SERVER_MAP_SYSTEMS_H