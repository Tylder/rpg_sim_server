//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H

#include "flecs_modules/landscape/components.cpp"
#include "flecs.h"
#include <string>

namespace Landscape::Rock {

struct GraniteTile : RockTile {};
struct SlateTile : RockTile {};
struct SandstoneTile : RockTile {};

[[maybe_unused]] static flecs::entity graniteTile_prefab;
[[maybe_unused]] static flecs::entity slateTile_prefab;
[[maybe_unused]] static flecs::entity sandstoneTile_prefab;

struct Components {

  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();
    ecsWorld.import <Map::Components>();
    ecsWorld.import <Landscape::Components>();

    ecsWorld.component<GraniteTile>("GraniteTile");
    ecsWorld.component<SlateTile>("SlateTile");
    ecsWorld.component<SandstoneTile>("SandstoneTile");

    graniteTile_prefab = ecsWorld.prefab("graniteTile").is_a(Landscape::rockTile_prefab).is_a<GraniteTile>().add<GraniteTile>();
    slateTile_prefab = ecsWorld.prefab("slateTile").is_a(Landscape::rockTile_prefab).is_a<SlateTile>().add<SlateTile>();
    sandstoneTile_prefab = ecsWorld.prefab("sandstoneTile").is_a(Landscape::rockTile_prefab).is_a<SandstoneTile>().add<SandstoneTile>();

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