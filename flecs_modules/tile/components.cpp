//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_TILE_COMPONENTS_H
#define RPG_SIM_SERVER_TILE_COMPONENTS_H

#include "flecs.h"

namespace Tile {

enum NeighbourTypeEnum {
  Top,
  TopRight,
  Right,
  BottomRight,
  Bottom,
  BottomLeft,
  Left,
  TopLeft,
};

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

struct ConnectedNode {};// links to other tiles that are connected somehow;
struct NeighbourNode {
  //  NeighbourTypeEnum type;
  flecs::entity_t node;
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

    ecsWorld.component<ConnectedNode>("ConnectedNode");

    //    ecsWorld.component<NeighbourTypeEnum>()
    //        .constant("Top", Top)
    //        .constant("TopRight", TopRight)
    //        .constant("Right", Right)
    //        .constant("BottomRight", BottomRight)
    //        .constant("Bottom", Bottom)
    //        .constant("BottomLeft", BottomLeft)
    //        .constant("Left", Left)
    //        .constant("TopLeft", TopLeft);

    ecsWorld.component<NeighbourNode>("NeighbourNode")
        //        .member<NeighbourTypeEnum>("type")
        .member(flecs::Entity, "node")
        .is_a<ConnectedNode>();

    //    ecsWorld.component<NeighbourRight>("NeighbourRight")
    //        .is_a<NeighbourTile>()
    //        .add(flecs::Exclusive);

    //    auto landscapeTileBase = ecsWorld.entity()
    //        .add<Tile>()
    //        .set<Transform::Size2<>>({1.0, 1.0});
  }
};
}// namespace Tile

#endif// RPG_SIM_SERVER_TILE_COMPONENTS_H