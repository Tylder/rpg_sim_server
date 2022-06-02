//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_TILE_COMPONENTS_H
#define RPG_SIM_SERVER_TILE_COMPONENTS_H

#include "flecs.h"

namespace Tile {

//struct Neighbours8 {
//  flecs::entity_view top{};
//  flecs::entity_view topRight{};
//  flecs::entity_view right{};
//  flecs::entity_view bottomRight{};
//  flecs::entity_view bottom{};
//  flecs::entity_view bottomLeft{};
//  flecs::entity_view left{};
//  flecs::entity_view topLeft{};
//};

struct Neighbours8 {
  flecs::entity_t top;
  flecs::entity_t topRight;
  flecs::entity_t right;
  flecs::entity_t bottomRight;
  flecs::entity_t bottom;
  flecs::entity_t bottomLeft;
  flecs::entity_t left;
  flecs::entity_t topLeft;
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
}// namespace Tile

#endif// RPG_SIM_SERVER_TILE_COMPONENTS_H