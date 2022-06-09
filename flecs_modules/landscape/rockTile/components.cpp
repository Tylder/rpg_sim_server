//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H

#include "flecs_modules/landscape/components.cpp"
#include "flecs.h"
#include <string>

namespace Landscape::Rock {

struct Components {

  static flecs::entity graniteTile_prefab;
  static flecs::entity slateTile_prefab;
  static flecs::entity sandstoneTile_prefab;

  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();
    ecsWorld.import <Landscape::Components>();

    graniteTile_prefab = ecsWorld.prefab("GraniteTile_prefab").is_a(Landscape::Components::rockTile_prefab);
    slateTile_prefab = ecsWorld.prefab("SlateTile_prefab").is_a(Landscape::Components::rockTile_prefab);
    sandstoneTile_prefab = ecsWorld.prefab("SandstoneTile_prefab").is_a(Landscape::Components::rockTile_prefab);

    //    ecsWorld.component<GroundTypeEnum>("GroundTypeEnum")
    //        .constant("Granite", Granite)
    //        .constant("Slate", Slate)
    //        .constant("Sandstone", Sandstone);
    //    ecsWorld.component<GroundTile>("GroundTile");
    //
    //    ecsWorld.component<Granite>("Granite").is_a<GroundTile>();
    //    ecsWorld.component<Slate>("Slate").is_a<GroundTile>();
    //    ecsWorld.component<Sandstone>("Sandstone").is_a<GroundTile>();

    //
    //        ecsWorld.component<GroundTypeEnum>("GroundTypeEnum")
    //            .constant("Granite", Granite)
    //            .constant("Slate", Slate)
    //            .constant("Sandstone", Sandstone);
  }
};
}// namespace Landscape::Rock

#endif// RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H