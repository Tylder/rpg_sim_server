#include "flecs.h"
#include <iostream>
//#include "SpeedTable/SpeedTable.h"

struct Requires {
  double amount;
};

struct Gigawatts {};

// Type used for Eats relation
struct Eats {};

struct Direction {};
struct DirectionUp : Direction {};
struct DirectionDown : Direction {};

enum class DirectionEnum {
  Up = 0,
  Down = 1,
  Right = 2,
  Left = 3
};

int main() {

  flecs::world ecs;

  // https://github.com/SanderMertens/flecs/blob/master/examples/cpp/relations/relation_component/src/main.cpp

  // When one element of a pair is a component and the other element is a tag,
  // the pair assumes the type of the component.
  auto e1 = ecs.entity().set<Requires, Gigawatts>({1.21});
  const Requires *r = e1.get<Requires, Gigawatts>();
  std::cout << "requires: " << r->amount << std::endl;

  // When querying for a relationship component, add the pair type as template
  // argument to the builder:
  auto q1 = ecs.query_builder<Requires>()
                .arg(1)
                .obj<Gigawatts>()// set second part of pair for first term
                .build();

  // When iterating, always use the pair type:
  q1.each([](Requires &rq) {
    std::cout << "requires " << rq.amount << " gigawatts\n";
  });

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Entity used for Grows relation
  auto grows = ecs.entity("Grows");

  // Relation objects
  auto apples = ecs.entity("Apples");
  auto pears = ecs.entity("Pears");

  // Create an entity with 3 relations. Relations are like regular components,
  // but combine two types/identifiers into an (relation, object) pair.
  auto bob = ecs.entity("Bob")
                 // Pairs can be constructed from a type and entity
                 .add<Eats>(apples)
                 .add<Eats>(pears)
                 // Pairs can also be constructed from two entity ids
                 .add(grows, pears);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ecs.component<DirectionUp>().is_a<Direction>();
  ecs.component<DirectionDown>().is_a<Direction>();

  auto eToSave = ecs.entity("eToSave");
  auto e2 = ecs.entity()
                .add<DirectionUp>(eToSave)
                .add<DirectionDown>(eToSave);

  std::cout << "e2's type: [" << e2.type().str() << "]\n";

//  auto pair = ecs.pair<flecs::IsA | Direction>(flecs::Wildcard);

  std::cout << "e2 type: " << e2.type().str() << std::endl;

//  auto q2 = ecs.query_builder().term<DirectionUp>(flecs::Wildcard).build();
  auto q2 = ecs.query_builder<>()
                .term<DirectionUp>().obj(flecs::Wildcard)
                .build();


  // Create a rule to find all ranged units
//  auto rule1 = ecs.rule<>();
//
//  // Iterate the rule
//  rule1.each([](flecs::entity e, Direction) {
//    std::cout << "Rule " << e.name() << " found\n";
//  });

  q2.iter([](flecs::iter &it){

    auto pair1 = it.pair(1).first().type().str();
    auto pair2 = it.pair(1).second().type().str();

    std::cout << "pair1: " << pair1 << ", pair2: " << pair2 << std::endl;
  });

  // Relations can be iterated for an entity. This iterates (Eats, *):
  e2.each<DirectionUp>([](flecs::entity second) {
    std::cout << "e2 direction " << second.name() << "\n";
  });

  std::cout << "node: " << std::endl;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  auto NeighbourDirectionE = ecs.entity();
  auto NeighbourUpE = ecs.entity("NeighbourUpE").is_a(NeighbourDirectionE);
  auto NeighbourDownE = ecs.entity("NeighbourDownE").is_a(NeighbourDirectionE);

  auto eToSave2 = ecs.entity("eToSave2");
  auto e3 = ecs.entity()
                .add(NeighbourUpE, eToSave2)
                .add(NeighbourDownE, eToSave2);

  std::cout << "e3's type: [" << e3.type().str() << "]\n";

  auto q3 = ecs.query_builder().term(NeighbourUpE).set(flecs::Wildcard).build();

  q3.iter([](flecs::iter &it){

    auto pair1 = it.pair(1).first().type().str();
    auto pair2 = it.pair(1).second().type().str();

    std::cout << "pair1: " << pair1 << ", pair2: " << pair2 << std::endl;
  });

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
