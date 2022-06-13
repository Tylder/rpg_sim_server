//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_TILE_INITS_H
#define RPG_SIM_SERVER_TILE_INITS_H

#include "flecs.h"
#include "flecs_modules/tile/components.cpp"
#include "flecs_modules/transform/components.cpp"
#include <cassert>
#include <iostream>
#include <vector>

#define assertm(exp, msg) assert(((void) msg, exp))

namespace Tile {

void setNeighbourNode(flecs::entity &node, NeighbourTypeEnum type, flecs::entity_view neighbourNode, Neighbours8 &neighbours) {

  node.add<ConnectsToNode>(neighbourNode);

  switch (type) {
    case (Top): {
      node.add(NeighbourTypeEnum::Top, neighbourNode);
      node.add<ConnectsToTopNode>(neighbourNode);
      neighbours.top = neighbourNode;
      break;
    }
    case TopRight: {
      node.add(NeighbourTypeEnum::TopRight, neighbourNode);
      node.add<ConnectsToTopRightNode>(neighbourNode);
      neighbours.topRight = neighbourNode;
      break;
    }
    case Right: {
      node.add(NeighbourTypeEnum::Right, neighbourNode);
      node.add<ConnectsToRightNode>(neighbourNode);
      neighbours.right = neighbourNode;
      break;
    }
    case BottomRight: {
      node.add(NeighbourTypeEnum::BottomRight, neighbourNode);
      node.add<ConnectsToBottomRightNode>(neighbourNode);
      neighbours.bottomRight = neighbourNode;
      break;
    }
    case Bottom: {
      node.add(NeighbourTypeEnum::Bottom, neighbourNode);
      node.add<ConnectsToBottomNode>(neighbourNode);
      neighbours.bottom = neighbourNode;
      break;
    }
    case BottomLeft: {
      node.add(NeighbourTypeEnum::BottomLeft, neighbourNode);
      node.add<ConnectsToBottomLeftNode>(neighbourNode);
      node.set<NeighbourNode, NeighbourTypeEnum::BottomLeft>({neighbourNode});
      neighbours.bottomLeft = neighbourNode;
      break;
    }
    case Left: {
      node.add(NeighbourTypeEnum::Left, neighbourNode);
      node.add<ConnectsToLeftNode>(neighbourNode);
      neighbours.left = neighbourNode;
      break;
    }
    case TopLeft: {
      node.add(NeighbourTypeEnum::TopLeft, neighbourNode);
      node.add<ConnectsToTopLeftNode>(neighbourNode);
      neighbours.topLeft = neighbourNode;
      break;
    }
  }
}

std::vector<flecs::entity_view> addNeighbourNodes(std::vector<flecs::entity_view> &&tiles, size_t width, size_t height) {
  for (int32_t i = 0; i < tiles.size(); i++) {
    const auto x = i % (width);
    const auto y = i / width;

    //    auto tile = ecsWorld.entity(landscapeTiles[i]);
    auto tile = tiles[i].entity();

    //    Neighbours8 neighbours{-1, -1, -1, -1, -1, -1, -1, -1};
    Neighbours8 neighbours{};

    // start in the top left
    if (x < width - 1) {// not all the way to the right
      setNeighbourNode(tile, NeighbourTypeEnum::Right, tiles[i + 1], neighbours);

      if (y < height - 1) {// not all the way at the bottom
        setNeighbourNode(tile, NeighbourTypeEnum::Bottom, tiles[i + width], neighbours);
        setNeighbourNode(tile, NeighbourTypeEnum::BottomRight, tiles[i + width + 1], neighbours);
      }

      if (y > 0) {// not the top row
        setNeighbourNode(tile, NeighbourTypeEnum::Top, tiles[i - width], neighbours);
        setNeighbourNode(tile, NeighbourTypeEnum::TopRight, tiles[i - width + 1], neighbours);
      }
    }

    if (x > 0) {// not all the way to the left
      setNeighbourNode(tile, NeighbourTypeEnum::Left, tiles[i - 1], neighbours);

      if (y < height - 1) {// not all the way at the bottom
        setNeighbourNode(tile, NeighbourTypeEnum::Bottom, tiles[i + width], neighbours);
        setNeighbourNode(tile, NeighbourTypeEnum::BottomLeft, tiles[i + width - 1], neighbours);
      }

      if (y > 0) {// not the top row
        setNeighbourNode(tile, NeighbourTypeEnum::Top, tiles[i - width], neighbours);
        setNeighbourNode(tile, NeighbourTypeEnum::TopLeft, tiles[i - width - 1], neighbours);
      }
    }

    tile.set<Neighbours8>(neighbours);

    //    flecs::entity_to_json_desc_t descEnt = {};
    //    descEnt.serialize_values = true;
    //    //    descEnt.serialize_base = true;
    //    //    descEnt.serialize_brief = true;
    //    //    descEnt.serialize_hidden = true;
    //    //    descEnt.serialize_label = true;
    //    //    descEnt.serialize_link = true;
    //    //    descEnt.serialize_path = true;
    //    //    descEnt.serialize_type_info = true;
    //    //    auto j = std::string(tile.to_json(&descEnt).c_str());
    //
    //    auto jsonE = std::string(tile.to_json(&descEnt).c_str());
    //
    //    std::cout << jsonE << std::endl;
  }

  return tiles;
}

std::vector<flecs::entity_view> createTilesWith8Neighbours(flecs::world &ecsWorld, const flecs::entity &prefab,
                                                           const std::string &baseName, size_t width, size_t height) {

  // 0  1  2
  // 3  4  5
  // 6  7  9

  std::vector<flecs::entity_view> tiles{};
  tiles.reserve(height * width);

  auto size = prefab.get<Transform::Size2<>>();// prefab should have size set

  assertm(size != nullptr, "No Transform::Size2<> set on Tile prefab");

  int32_t index{0};

  for (int32_t y = 0; y < height; y++) {
    for (int32_t x = 0; x < width; x++) {

      std::string name = baseName + " - x: " + std::to_string(x) + ", y: " + std::to_string(y);

      auto e = ecsWorld.entity(name.c_str())
                   .is_a(prefab)
                   .set<Index>({index++})
                   .set<Index2>({x, y})
                   .set<Transform::Position2<int32_t>>({static_cast<int>(x * size->x), static_cast<int>(y * size->y)});
      tiles.emplace_back(e);
    }
  }

  return addNeighbourNodes(std::move(tiles), width, height);
}

struct Inits {
  //  static flecs::entity neighbourTileE;
  //  static flecs::entity neighbourTileRightE;

  Inits(flecs::world &ecsWorld) {
    //    ecsWorld.module<Inits>();

    //    auto landscapeTileBase = ecsWorld.entity()
    //        .add<Tile>()
    //        .set<Transform::Size2<>>({1.0, 1.0});
  }
};
}// namespace Tile

#endif// RPG_SIM_SERVER_TILE_INITS_H