#include <iostream>
#include <chrono>

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include "flecs_modules/landscape/components.cpp"
#include "flecs_modules/landscape/systems.cpp"
#include "flecs_modules/transform/components.cpp"
#include "flecs_modules/transform/systems.cpp"

struct Position {
  float x;
  float y;
};

int main() {
  std::cout << "Hello, World!" << std::endl;
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
  ecs.import<Landscape::Components>();
  ecs.import<Landscape::Systems>();
  ecs.import<Transform::Componets>();
  ecs.import<Transform::Systems>();
//    ecs.app().enable_rest().run();


  ecs.set_threads(4);

  Landscape::addLandscapeTile(ecs, 2, 2);

  auto qTile = ecs.query<const Landscape::LandscapeTile, Transform::Position2<int32_t>, Landscape::Neighbours8>();

  flecs::iter_to_json_desc_t descIter = {};
  descIter.serialize_entities = true;
  descIter.serialize_values = true;

  std::cout << qTile.iter().to_json(&descIter).c_str() << "\n";
//
//  auto e = flecs::entity(ecs, 999)
//      .set<Transform::Position2<int32_t>>({4, 11})
//      .set<Transform::Position2<>>({4, 11})
//      .set<Transform::Position3<>>({2.1, 3.3, 5.5})
//      .set<Transform::Velocity2<>>({1, 1})
//      .set<Transform::Velocity3<>>({3, 3});
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
