//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_TILE_COMPONENTS_H
#define RPG_SIM_SERVER_TILE_COMPONENTS_H
#include "flecs_modules/transform/components.cpp"

#include "flecs.h"

namespace Tile {

enum NeighbourTypeEnum {
  Top = 1,
  TopRight = 2,
  Right = 3,
  BottomRight = 4,
  Bottom = 5,
  BottomLeft = 6,
  Left = 7,
  TopLeft = 8,
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

struct ConnectsToNode {
  std::string type;
};// links to other tiles that are connected somehow;

struct ConnectsToTopNode : ConnectsToNode {};
struct ConnectsToTopRightNode : ConnectsToNode {};
struct ConnectsToRightNode : ConnectsToNode {};
struct ConnectsToBottomRightNode : ConnectsToNode {};
struct ConnectsToBottomNode : ConnectsToNode {};
struct ConnectsToBottomLeftNode : ConnectsToNode {};
struct ConnectsToLeftNode : ConnectsToNode {};
struct ConnectsToTopLeftNode : ConnectsToNode {};

struct NeighbourNode {
  //  NeighbourTypeEnum type;
  flecs::entity_t node;
};

//struct TileType {};// relation

struct Index {
  int32_t value;
};

struct Index2 {
  int32_t x, y;
};

struct Tile {};
struct Tile2 : Tile {};

[[maybe_unused]] static flecs::entity tile_prefab;
[[maybe_unused]] static flecs::entity tile2_prefab;

struct Components {

  Components(flecs::world &ecsWorld) {
    ecsWorld.module<Components>();
    ecsWorld.import <Transform::Componets>();

    // https://flecs.docsforge.com/master/query-manual/#transitivity
    //    ecsWorld.component<TileType>().add(flecs::Transitive);// if 'x' is 'y' and 'y' is 'a' then 'x' == 'a'

    ecsWorld.component<Tile>().add(flecs::Tag);
    ecsWorld.component<Tile2>().is_a<Tile>();

    ecsWorld.component<Index>()
        .member(flecs::I32, "value");

    ecsWorld.component<Index2>()
        .member(flecs::I32, "x")
        .member(flecs::I32, "y");

    ecsWorld.component<Neighbours8>()
        .member(flecs::Entity, "top")
        .member(flecs::Entity, "topRight")
        .member(flecs::Entity, "right")
        .member(flecs::Entity, "bottomRight")
        .member(flecs::Entity, "bottom")
        .member(flecs::Entity, "bottomLeft")
        .member(flecs::Entity, "left")
        .member(flecs::Entity, "topLeft");

    ecsWorld.component<ConnectsToNode>();
    ecsWorld.component<ConnectsToTopNode>().is_a<ConnectsToNode>();
    ecsWorld.component<ConnectsToTopRightNode>().is_a<ConnectsToNode>();
    ecsWorld.component<ConnectsToRightNode>().is_a<ConnectsToNode>();
    ecsWorld.component<ConnectsToBottomRightNode>().is_a<ConnectsToNode>();
    ecsWorld.component<ConnectsToBottomNode>().is_a<ConnectsToNode>();
    ecsWorld.component<ConnectsToBottomLeftNode>().is_a<ConnectsToNode>();
    ecsWorld.component<ConnectsToLeftNode>().is_a<ConnectsToNode>();
    ecsWorld.component<ConnectsToTopLeftNode>().is_a<ConnectsToNode>();

//        ecsWorld.component<NeighbourTypeEnum>()
//            .constant("Top", Top)
//            .constant("TopRight", TopRight)
//            .constant("Right", Right)
//            .constant("BottomRight", BottomRight)
//            .constant("Bottom", Bottom)
//            .constant("BottomLeft", BottomLeft)
//            .constant("Left", Left)
//            .constant("TopLeft", TopLeft);

    ecsWorld.component<NeighbourNode>()
        //        .member<NeighbourTypeEnum>("type")
        .member(flecs::Entity, "node")
        .is_a<ConnectsToNode>();

    //    ecsWorld.component<NeighbourRight>("NeighbourRight")
    //        .is_a<NeighbourTile>()
    //        .add(flecs::Exclusive);

    //    auto landscapeTileBase = ecsWorld.entity()
    //        .add<Tile>()
    //        .set<Transform::Size2<>>({1.0, 1.0});

    tile_prefab = ecsWorld.prefab("tile")
                      .is_a<Tile>();

    tile2_prefab = ecsWorld.prefab("tile2")
                       .is_a<Tile2>()
                       .override<Transform::Position2<>>()
                       .override<Index>()
                       .override<Index2>();
  }
};
}// namespace Tile

#endif// RPG_SIM_SERVER_TILE_COMPONENTS_H