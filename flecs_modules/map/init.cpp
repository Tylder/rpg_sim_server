//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_MAP_INITS_H
#define RPG_SIM_SERVER_MAP_INITS_H

#include "flecs.h"
#include "flecs_modules/map/components.cpp"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/init.cpp"

namespace Map {

struct Inits {
  Inits(flecs::world &ecsWorld) {
    ecsWorld.module<Inits>();
  }
};
}

#endif// RPG_SIM_SERVER_MAP_INITS_H