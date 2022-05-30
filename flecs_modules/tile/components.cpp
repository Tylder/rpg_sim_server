//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_TILE_COMPONENTS_H
#define RPG_SIM_SERVER_TILE_COMPONENTS_H

#include "flecs.h"

namespace Tile {

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

struct Index {
  int32_t value;
};
struct Index2 {
  int32_t x, y;
};

struct Components {
  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();

    ecsWorld.component<Index>("Index")
        .member(flecs::I32, "value");

    ecsWorld.component<Index2>("Index2")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y");

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

#endif // RPG_SIM_SERVER_TILE_COMPONENTS_H