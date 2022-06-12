#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/rockTile/components.cpp"
#include "flecs_modules/map/components.cpp"
#include "flecs_modules/net/components.cpp"
#include "flecs_modules/tile/components.cpp"
#include "flecs_modules/transform/components.cpp"

#include "flecs_modules/landscape/init.cpp"
#include "flecs_modules/landscape/rockTile/init.cpp"

#include "flecs_modules/landscape/rockTile/systems.cpp"
#include "flecs_modules/landscape/systems.cpp"
#include "flecs_modules/tile/systems.cpp"
#include "flecs_modules/transform/systems.cpp"
#include "nlohmann/json.hpp"
#include <chrono>
#include <iostream>

struct Position {
  float x;
  float y;
};

struct Velocity {
  float x;
  float y;
};

struct Mass {
  float value;
};

int main() {
  //    std::vector<float> noiseOutput(16 * 16 * 16);

  //    auto fnSimplex = FastNoise::New<FastNoise::Simplex>();
  //    auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();
  //
  //    fnFractal->SetSource( fnSimplex );
  //    fnFractal->SetOctaveCount( 5 );
  //
  //    // Generate a 16 x 16 x 16 area of noise
  //    fnSimplex->GenUniformGrid3D(noiseOutput.data(), 0, 0, 0, 16, 16, 16, 0.2f, 1337);

#ifdef FLECS_DEBUG
  flecs::log::set_level(10);
#endif
  flecs::world ecs;
  ecs.import <Transform::Componets>();
  ecs.import <Tile::Components>();
  ecs.import <Map::Components>();
  ecs.import <Landscape::Components>();
  ecs.import <Net::Components>();
  //  ecs.import <Transform::Systems>();
  //  ecs.import <Landscape::Systems>();
  //  ecs.import <Tile::Systems>();

  //      ecs.app().enable_rest().run();

  ecs.set_threads(4);
  //
  //  Landscape::init(ecs);
  //  Landscape::Rock::init(ecs);
  //
  //  ecs.entity("Map").set<Map::Map>({3, 3});

  //  Landscape::Rock::createTiles(ecs);
  //  auto qTile = ecs.query<
  //      const Landscape::LandscapeTile,
  //      const Transform::Position2<int32_t>,
  //      Tile::NeighbourTile,
  //      Tile::Neighbours8>();
  //
  //  auto qTile = ecs.query_builder<>().term<Tile::NeighbourTypeEnum>(flecs::Wildcard).build();
  //  //                      const Tile::NeighbourNode
  //  //      const Tile::ConnectsToNode,
  //  //                      Tile::Neighbours8
  //
  //  auto connectedNode_Query = ecs.query_builder<>()
  //                                 .term<Tile::ConnectsToNode>(flecs::Wildcard)
  //                                 .build();
  //
  //  connectedNode_Query.iter([](flecs::iter &it) {
  //    auto pair1 = it.pair(1).first().name();
  //    auto pair2 = it.pair(1).second().name();
  //
  //    std::cout << "sdsd";++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ggggggggggggggggggggtttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt5tttttttt5tttttt5tttttt5t5tt5t5ttttttttttttttt5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t5t555555555g5555555555555555t5555555tt5tttttttttttt5t5tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
  //  });
  //
  //  auto neighbourNode_Query = ecs.query_builder<Tile::NeighbourNode>().build();
  //  //  auto N2Tile  = ecs.query<Tile::NeighbourTile>();
  //
  //  neighbourNode_Query.iter([](flecs::iter &it, Tile::NeighbourNode *t) {
  //    //    auto pair1 = it.pair(1).first().name();
  //    //    auto pair2 = it.pair(1).second().name();
  //
  //    std::cout << "sdsd";
  //  });
  //ttttttttttttttttttttttttttttttttttttttttttttt
  //  auto N2Tile  = ecs.query_builder<>().term<Tile::NeighbourNode>(flecs::Wildcard).build();
  ////  auto N2Tile  = ecs.query<Tile::NeighbourTile>();
  //
  //  N2Tile.iter([](flecs::iter &it) {
  //
  //    auto pair1 = it.pair(1).first().name();
  //    auto pair2 = it.pair(1).second().name();
  //
  //
  //    std::cout << "sdsd";
  //  });

  //  flecs::iter_to_json_desc_t descIter = {};
  //  descIter.serialize_entities = true;
  //  descIter.serialize_values = true;
  //  //
  //  //  auto json_query = ecs.query<const Landscape::LandscapeTile>().iter().to_json(&descIter).c_str();
  //  auto json_query = connectedNode_Query.iter().to_json(&descIter).c_str();
  //
  //  auto queryJson = nlohmann::json::parse(json_query);
  //  std::cout << queryJson.dump(2) << std::endl;
  //  std::cout << "" << std::endl;

  //  auto e = flecs::entity(ecs, 999)
  //               .set<Transform::Position2<int32_t>>({4, 11})
  //               .set<Transform::Position2<>>({4, 11})
  //               .set<Transform::Position3<>>({2.1, 3.3, 5.5})
  //               .set<Transform::Velocity2<>>({1, 1})
  //               .set<Transform::Velocity3<>>({3, 3});

  // Register components with reflection data

  // Query for components
  //  auto q = ecs.query<Position, const Velocity>();
  //  auto q = ecs.query_builder<Landscape::Ground::GroundTile, Landscape::Coverage>().term(flecs::ChildOf, flecs::Wildcard).build();
  //  auto q = ecs.query_builder<Landscape::Ground::GroundTile, Landscape::Coverage, Tile::Neighbours8>()
  //               .term(flecs::ChildOf, flecs::Wildcard)
  //               .term<>(flecs::Parent, )
  //               .build();
  //  auto q = ecs.query_builder<Landscape::Coverage>()
  //               .term("Tile.Index2(parent)")// same as super(ChildOf)
  //               .term("Tile.Neighbours8(super(ChildOf))")
  //               .term<Tile::Index>()
  //               .super(flecs::ChildOf)// same as super(ChildOf)
  //               //               .term<Tile::Index>(flecs::Parent)// same as super(ChildOf)
  //               //               .term(Tile::NeighbourTypeEnum::Right, flecs::Parent)
  //               .build();
  //
  //  auto q = ecs.query_builder<Tile::Index2>()
  //
  //               .build();

  //  auto q = ecs.query_builder<Tile::Index2, Tile::Index2, Tile::Neighbours8>()
  ////                .term(flecs::IsA).obj(Tile::tile2_prefab)
  ////                .term(flecs::IsA, Tile::tile2_prefab)
  //               .term(flecs::IsA, Landscape::landscapeTile_prefab)
  //               .arg(2)
  //                  .subj<Tile::ConnectsToRightNode>()
  //                  .obj(flecs::Wildcard).oper(flecs::Optional)
  //               .build();

  //  auto r = ecs.rule_builder()
  //           .term<Tile::ConnectsToLeftNode>().obj().var("nodeVar")
  //           .term<Tile::ConnectsToRightNode>().obj().var("nodeVar")
  //           .build();

  //  auto r = ecs.rule_builder<Tile::Index2>()
  ////      .term<Tile::Index2>()
  ////      .term<Tile::Index>()
  //      .term<Tile::ConnectsToRightNode>().obj().var("X")
  //      .build();

  //  int var = r.find_var("X");
  //  auto q = ecs.query_builder<Tile::Index2, Tile::Index2, Tile::Neighbours8>()
  //               //               .term("(Tile.Components.ConnectsToRightNode, $NodeVar)")
  //               //               .term("(Tile.Components.ConnectsToLeftNode, $NodeVar)")
  //               .term(flecs::IsA, Tile::tile2_prefab)
  //               .arg(2).subj<Tile::ConnectsToLeftNode>().obj(flecs::Wildcard)
  //               //                .term(flecs::IsA, Tile::tile2_prefab)
  //               //           .term("(Tile.Components.ConnectsToRightNode, *)")
  //               .build();

  auto q = ecs.query_builder<Tile::Index2, Tile::Index2>()
               .build();

  // Serialize query to JSON. Note that this works for any iterable object,
  // including filters & rules.
  flecs::iter_to_json_desc_t descIter = {};
  descIter.serialize_entities = true;
  descIter.serialize_type_info = true;
  descIter.serialize_values = true;
  descIter.measure_eval_duration = true;
  descIter.serialize_type_info = true;
  auto json_query = q.iter().to_json();
  //  auto json_query = q.iter().to_json(&descIter);
  std::cout << json_query << "\n";
  std::cout << q.iter().to_json().c_str() << "\n";

  auto queryJson = nlohmann::json::parse(json_query.c_str());
  std::cout << queryJson.dump(2) << std::endl;

  // Iterate the rule
  //  r.each([&](flecs::iter& it, size_t index, Tile::Index2 index2) {
  //    auto name = it.entity(index).name().c_str();
  //    auto varName = it.get_var(var).name().c_str();
  //    std::cout
  //        << it.entity(index).name()
  //        << " lives in " << it.get_var(var).name()
  //        << "\n";
  //  });

  std::cout << "" << std::endl;
  //  flecs::iter_to_json_desc_t descIter = {};
  //  //  descIter.serialize_entities = true;
  //  //  descIter.serialize_values = true;
  //
  //  auto json_query = ecs.query<const Transform::Position2<>>().iter().to_json(&descIter).c_str();
  //
  //  auto queryJson = nlohmann::json::parse(json_query);
  //  std::cout << queryJson.dump(2) << std::endl;
  //  std::cout << "" << std::endl;
  //
  //  const auto *ptr = e.get<Transform::Position2<int32_t>>();
  //  const auto *ptr2 = e.get<Transform::Position2<>>();
  //  const auto exp = std::string(ecs.to_expr(ptr).c_str());
  //  const auto exp2 = std::string(ecs.to_expr(ptr2).c_str());
  ////  const auto json = std::string(ecs.to_json(ptr).c_str());
  ////  const auto json2 = std::string(ecs.to_json(ptr2).c_str());
  ////  const auto jsonE = std::string(e.to_json().c_str());
  //
  ////  auto q = ecs.query<Transform::Position2<>, const Transform::Position3<>>();
  //
  //  // Serialize query to JSON. Customize serializer to only serialize entity
  //  // names and component values.
  //
  //
  //  const auto json = std::string(ecs.to_json(ptr).c_str());
  //  const auto json2 = std::string(ecs.to_json(ptr2).c_str());
  //
  //  flecs::entity_to_json_desc_t descEnt = {};
  //  descEnt.serialize_values = true;
  //  descEnt.serialize_base = true;
  //  descEnt.serialize_brief = true;
  //  descEnt.serialize_hidden = true;
  //  descEnt.serialize_label = true;
  //  descEnt.serialize_link = true;
  //  descEnt.serialize_path = true;
  //  descEnt.serialize_values = true;
  //  descEnt.serialize_type_info = true;
  //
  //  auto jsonE = std::string(e.to_json(&descEnt).c_str());
  //  std::cout << jsonE << std::endl;

  //

  //

  //
  //    ecs.system<Position2, const Velocity2>()
  ////        .interval(1)
  //        .multi_threaded(false)
  //        .iter([](const flecs::iter& it,Position2 *p,const Velocity2 *v){
  //            for (auto row : it) {
  //                    p[row].x += v[row].x;
  //                    p[row].y += v[row].y;
  //                }
  ////            std::cout << 'end of system 1' << std::endl;
  //        });
  //
  ////    ecs.system<Position>()
  ////            .iter([](const flecs::iter& it,Position *p){
  ////                for (auto row : it) {
  ////                    p[row].x += 1;
  ////                    p[row].y += 1;
  ////                }
  //////                std::cout << 'end of system 2' << std::endl;
  ////            });
  //
  //    auto entity = ecs.entity("myEntity")
  //            .set<Position2>({0, 0})
  //            .set<Velocity2>({1, 1});
  //
  //
  //
  //  for (int i = 0; i < 2; ++i) {
  //    ecs.entity()
  //        .set<Transform::Position2<>>({0, 0})
  //        .set<Transform::Velocity2<>>({1, 1});
  //  }
  //
  //
  //
  ////    ecs.set_target_fps(1);

  std::cout << "Application move_system is running, press CTRL-C to exit..." << std::endl;

  /* Run systems */
  typedef std::chrono::high_resolution_clock Clock;
  auto t1 = Clock::now();

  //    while (ecs.progress()) {
  //
  //    }

  for (int i = 0; i < 1; ++i) {
    ecs.progress();
  }

  //    while (ecs.progress()) {
  //        std::cout << "Delta time: " << ecs.get_world().delta_time() << std::endl;
  ////        std::cout << "Moved " << entity.name() << " to {" <<
  ////                  entity.get<Position>()->x << ", " << entity.get<Position>()->y << "} threads: " << ecs.get_threads()  <<     std::endl;
  //    }

  auto t2 = Clock::now();
  std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
  std::cout << fp_ms.count() << '\n';

  //  auto jsonE2 = std::string(e.to_json(&descEnt).c_str());
  //  std::cout << jsonE2 << std::endl;

  return 0;
}
