//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H
#define RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include "flecs_modules/transform/components.cpp"

namespace Landscape {

struct Neighbours8 {
  const flecs::entity_view *top;
  const flecs::entity_view *topRight;
  const flecs::entity_view *right;
  const flecs::entity_view *bottomRight;
  const flecs::entity_view *bottom;
  const flecs::entity_view *bottomLeft;
  const flecs::entity_view *left;
  const flecs::entity_view *topLeft;
};

struct Tile {};
struct LandscapeTile {};

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    ecsWorld.component<Neighbours8>("Neighbours8")
        .member(flecs::Entity, "top")
        .member(flecs::Entity, "topRight")
        .member(flecs::Entity, "right")
        .member(flecs::Entity, "bottomRight")
        .member(flecs::Entity, "bottom")
        .member(flecs::Entity, "bottomLeft")
        .member(flecs::Entity, "left")
        .member(flecs::Entity, "topLeft");

//    auto landscapeTileBase = ecsWorld.entity()
//        .add<Tile>()
//        .set<Transform::Size2<>>({1.0, 1.0});

  }
};
}

#endif RPG_SIM_SERVER_LANDSCAPE_COMPONENTS_H