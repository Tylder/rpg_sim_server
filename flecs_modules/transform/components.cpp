//
// Created by Anon on 5/27/2022.
//

#ifndef RPG_SIM_SERVER_TRANSFORM_COMPONENTS_H
#define RPG_SIM_SERVER_TRANSFORM_COMPONENTS_H

#include <string>
#include "flecs.h"

namespace Transform {

//template<typename T = double>
//void registerTransform2Dim(flecs::world &ecsWorld, const std::string& name) {
//  ecsWorld.component<double>(name)
//      .member<T>("x")
//      .member<T>("y");
//}

template<typename T = double>
struct Tranform2Dim {
  T x, y;
};

template<typename T = double>
struct Tranform3Dim {
  T x, y, z;
};

/* Position */
template<typename T = double>
struct Size2 : Tranform2Dim<T> {};

template<typename T = double>
struct Size3 : Tranform3Dim<T> {};

/* Position */
template<typename T = double>
struct Position2 : Tranform2Dim<T> {};

template<typename T = double>
struct Position3 : Tranform3Dim<T> {};

/* Velocity */
template<typename T = double>
struct Velocity1 {
  T value;
};

template<typename T = double>
struct Velocity2 : Tranform2Dim<T> {};

template<typename T = double>
struct Velocity3 : Tranform3Dim<T> {};

template<typename T = double>
struct Rotation1 {
  T angle;
};

/* Rotation */
template<typename T = double>
struct Rotation3 : Tranform3Dim<T> {};

template<typename T = double>
struct Quaternion {
  T x, y, z, w;
};

/* Scale */
template<typename T = double>
struct Scale1 {
  T value;
};

template<typename T = double>
struct Scale2 : Tranform2Dim<T> {};

template<typename T = double>
struct Scale3 : Tranform3Dim<T> {};

struct Componets {
  Componets(flecs::world &ecsWorld) {
    ecsWorld.module<Transform::Componets>();

    /* REGISTERING COMPONENTS FOR REFLECTION */

    /* SIZE 2 */
    ecsWorld.component<Size2<double>>("Size2")
        .member<double>("x")
        .member<double>("y");

    ecsWorld.component<Size2<float>>("Size2<float>")
        .member<float>("x")
        .member<float>("y");

    // Use platform-independent type ids
    ecsWorld.component<Size2<int32_t>>("Size2<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y");

    // Use platform-independent type ids
    ecsWorld.component<Size2<int64_t>>("Size2<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y");

    /* SIZE 3 */
    ecsWorld.component<Size3<double>>("Size3")
        .member<double>("x")
        .member<double>("y")
        .member<double>("z");

    ecsWorld.component<Size3<float>>("Size3<float>")
        .member<float>("x")
        .member<float>("y")
        .member<float>("z");

    // Use platform-independent type ids
    ecsWorld.component<Size3<int32_t>>("Size3<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y")
        .member(flecs::I32, "z");

    // Use platform-independent type ids
    ecsWorld.component<Size3<int64_t>>("Size3<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y")
        .member(flecs::I64, "z");


    /* POSITION 2 */
    ecsWorld.component<Position2<double>>("Position2")
        .member<double>("x")
        .member<double>("y");

    ecsWorld.component<Position2<float>>("Position2<float>")
        .member<float>("x")
        .member<float>("y");

    // Use platform-independent type ids
    ecsWorld.component<Position2<int32_t>>("Position2<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y");

    // Use platform-independent type ids
    ecsWorld.component<Position2<int64_t>>("Position2<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y");

    /* POSITION 3 */
    ecsWorld.component<Position3<double>>("Position3")
        .member<double>("x")
        .member<double>("y")
        .member<double>("z");

    ecsWorld.component<Position3<float>>("Position3<float>")
        .member<float>("x")
        .member<float>("y")
        .member<float>("z");

    // Use platform-independent type ids
    ecsWorld.component<Position3<int32_t>>("Position3<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y")
        .member(flecs::I32, "z");

    // Use platform-independent type ids
    ecsWorld.component<Position3<int64_t>>("Position3<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y")
        .member(flecs::I64, "z");

    /* VELOCITY 1 */
    ecsWorld.component<Velocity1<double>>("Velocity1")
        .member<double>("value");

    ecsWorld.component<Velocity1<float>>("Velocity1<float>")
        .member<float>("value");

    // Use platform-independent type ids
    ecsWorld.component<Velocity1<int32_t>>("Velocity1<int32_t>")
        .member(flecs::I32, "value");

    // Use platform-independent type ids
    ecsWorld.component<Velocity1<int64_t>>("Velocity1<int64_t>")
        .member(flecs::I64, "value");

    /* VELOCITY 2 */
    ecsWorld.component<Velocity2<double>>("Velocity2")
        .member<double>("x")
        .member<double>("y");

    ecsWorld.component<Velocity2<float>>("Velocity2<float>")
        .member<float>("x")
        .member<float>("y");

    // Use platform-independent type ids
    ecsWorld.component<Velocity2<int32_t>>("Velocity2<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y");

    // Use platform-independent type ids
    ecsWorld.component<Velocity2<int64_t>>("Velocity2<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y");

    /* VELOCITY 3 */
    ecsWorld.component<Velocity3<double>>("Velocity3")
        .member<double>("x")
        .member<double>("y")
        .member<double>("z");

    ecsWorld.component<Velocity3<float>>("Velocity3<float>")
        .member<float>("x")
        .member<float>("y")
        .member<float>("z");

    // Use platform-independent type ids
    ecsWorld.component<Velocity3<int32_t>>("Velocity3<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y")
        .member(flecs::I32, "z");

    // Use platform-independent type ids
    ecsWorld.component<Velocity3<int64_t>>("Velocity3<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y")
        .member(flecs::I64, "z");

    /* ROTATION 1 */
    ecsWorld.component<Rotation1<double>>("Rotation1")
        .member<double>("value");

    ecsWorld.component<Rotation1<float>>("Rotation1<float>")
        .member<float>("value");

    // Use platform-independent type ids
    ecsWorld.component<Rotation1<int32_t>>("Rotation1<int32_t>")
        .member(flecs::I32, "value");

    // Use platform-independent type ids
    ecsWorld.component<Rotation1<int64_t>>("Rotation1<int64_t>")
        .member(flecs::I64, "value");

    /* ROTATION 3 */
    ecsWorld.component<Rotation3<double>>("Rotation3")
        .member<double>("x")
        .member<double>("y")
        .member<double>("z");

    ecsWorld.component<Rotation3<float>>("Rotation3<float>")
        .member<float>("x")
        .member<float>("y")
        .member<float>("z");

    // Use platform-independent type ids
    ecsWorld.component<Rotation3<int32_t>>("Rotation3<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y")
        .member(flecs::I32, "z");

    // Use platform-independent type ids
    ecsWorld.component<Rotation3<int64_t>>("Rotation3<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y")
        .member(flecs::I64, "z");

    /* QUATERNION */
    ecsWorld.component<Quaternion<double>>("Quaternion")
        .member<double>("x")
        .member<double>("y")
        .member<double>("z")
        .member<double>("w");

    ecsWorld.component<Quaternion<float>>("Quaternion<float>")
        .member<float>("x")
        .member<float>("y")
        .member<float>("z")
        .member<float>("w");

    // Use platform-independent type ids
    ecsWorld.component<Quaternion<int32_t>>("Quaternion<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y")
        .member(flecs::I32, "z")
        .member(flecs::I32, "w");

    // Use platform-independent type ids
    ecsWorld.component<Quaternion<int64_t>>("Quaternion<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y")
        .member(flecs::I64, "z")
        .member(flecs::I64, "w");

    /* SCALE 1 */
    ecsWorld.component<Scale1<double>>("Scale1")
        .member<double>("value");

    ecsWorld.component<Scale1<float>>("Scale1<float>")
        .member<float>("value");

    // Use platform-independent type ids
    ecsWorld.component<Scale1<int32_t>>("Scale1<int32_t>")
        .member(flecs::I32, "value");

    // Use platform-independent type ids
    ecsWorld.component<Scale1<int64_t>>("Scale1<int64_t>")
        .member(flecs::I64, "value");

    /* SCALE 2 */
    ecsWorld.component<Scale2<double>>("Scale2")
        .member<double>("x")
        .member<double>("y");

    ecsWorld.component<Scale2<float>>("Scale2<float>")
        .member<float>("x")
        .member<float>("y");

    // Use platform-independent type ids
    ecsWorld.component<Scale2<int32_t>>("Scale2<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y");

    // Use platform-independent type ids
    ecsWorld.component<Scale2<int64_t>>("Scale2<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y");

    /* SCALE 3 */
    ecsWorld.component<Scale3<double>>("Scale3")
        .member<double>("x")
        .member<double>("y")
        .member<double>("z");

    ecsWorld.component<Scale3<float>>("Scale3<float>")
        .member<float>("x")
        .member<float>("y")
        .member<float>("z");

    // Use platform-independent type ids
    ecsWorld.component<Scale3<int32_t>>("Scale3<int32_t>")
        .member(flecs::I32, "x")
        .member(flecs::I32, "y")
        .member(flecs::I32, "z");

    // Use platform-independent type ids
    ecsWorld.component<Scale3<int64_t>>("Scale3<int64_t>")
        .member(flecs::I64, "x")
        .member(flecs::I64, "y")
        .member(flecs::I64, "z");

  }
};
}

#endif //RPG_SIM_SERVER_TRANSFORM_COMPONENTS_H
