//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_ROCK_SYSTEMS
#define RPG_SIM_SERVER_LANDSCAPE_ROCK_SYSTEMS

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/rockTile/components.cpp"
#include "flecs_modules/landscape/rockTile/init.cpp"
#include <vector>
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/rockTile/init.cpp"


namespace Landscape::Rock {

struct Systems {
  Systems(flecs::world &ecsWorld) {
    ecsWorld.module<Systems>();
    ecsWorld.import <Landscape::Components>();
    ecsWorld.import <Landscape::Rock::Components>();

    /* Create tiles */
    ecsWorld.observer<const Landscape::LandscapeTile>()
        .event(flecs::OnSet)
        .iter([&](flecs::iter &it, const Landscape::LandscapeTile *tile) {
          createTiles(ecsWorld);
        });

    ecsWorld.observer<LandscapeTile>()
        .event(flecs::OnSet)
        .iter([&](flecs::iter &it, LandscapeTile*) {
          createTiles(ecsWorld);
        });
  }
};
}// namespace Landscape::Rock

#endif// RPG_SIM_SERVER_LANDSCAPE_ROCK_SYSTEMS