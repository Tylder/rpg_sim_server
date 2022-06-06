//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H

#include "flecs_modules/landscape/components.cpp"
#include "flecs.h"

namespace Landscape::Ground {

//enum GroundTypeEnum {
//  Granite,
//  Slate,
//  Sandstone
//};

struct GroundTile {};// Relation

struct Granite {};
struct Slate {};
struct Sandstone {};

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    //    ecsWorld.component<GroundTypeEnum>("GroundTypeEnum")
    //        .constant("Granite", Granite)
    //        .constant("Slate", Slate)
    //        .constant("Sandstone", Sandstone);

    ecsWorld.component<GroundTile>("GroundTile");
    ecsWorld.component<Granite>("Granite").is_a<GroundTile>();
    ecsWorld.component<Granite>("Slate").is_a<GroundTile>();
    ecsWorld.component<Granite>("Sandstone").is_a<GroundTile>();

    //
    //    ecsWorld.component<GroundTypeEnum>("GroundTypeEnum")
    //        .constant("Granite", Granite)
    //        .constant("Slate", Slate)
    //        .constant("Sandstone", Sandstone)
    //        .is_a<LandscapeTile>();
  }
};
}// namespace Landscape::Ground

#endif// RPG_SIM_SERVER_LANDSCAPE_GROUND_COMPONENTS_H