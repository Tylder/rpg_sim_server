//
// Created by Anon on 5/27/2022.
//

#ifndef RPG_SIM_SERVER_TRANSFORM_SYSTEMS_H
#define RPG_SIM_SERVER_TRANSFORM_SYSTEMS_H

#include <string>
#include "flecs.h"
#include "flecs_modules/transform/components.cpp"

namespace Transform {

//template<typename T  = double>
//void move2(const flecs::iter &it) {
//
//  auto p = it.term<Position2<T>>(1); //
//  auto v = it.term<Velocity2<T>>(2); //
//
//  for (auto row : it) {
//    p[row].x += v[row].x;
//    p[row].y += v[row].y;
//  }
//}
//
template<typename T  = double>
void move2(const flecs::iter &it, Position2<T> *p, const Velocity2<T> *v) {
  for (auto row : it) {
    p[row].x += v[row].x;
    p[row].y += v[row].y;
  }
}

template<typename TP = double, typename TV = double>
void move2(const flecs::iter &it, Position2<TP> *p, const Velocity3<TV> *v) {
  for (auto row : it) {
    p[row].x += static_cast<TV>(v[row].x);
    p[row].y += static_cast<TV>(v[row].y);
  }
}

template<typename T  = double>
void move3(const flecs::iter &it, Position3<T> *p, const Velocity3<T> *v) {
  for (auto row : it) {
    p[row].x += v[row].x;
    p[row].y += v[row].y;
    p[row].z += v[row].z;
  }
}

template<typename TP = double, typename TV = double>
void move3(const flecs::iter &it, Position3<TP> *p, const Velocity2<TV> *v) {
  for (auto row : it) {
    p[row].x += static_cast<TV>(v[row].x);
    p[row].y += static_cast<TV>(v[row].y);
  }
}

template<typename T  = double>
void applyTransform2(ecs_iter_t *it) {
  if (!ecs_query_changed(NULL, it)) {
    ecs_query_skip(it);
    return;
  }

//  EcsTransform3 *m = ecs_term(it, EcsTransform3, 1);
//  EcsTransform3 *m_parent = ecs_term(it, EcsTransform3, 2);
  Position2<T> *p = ecs_term(it, Position2<T>, 1);
  Rotation1<T> *r = ecs_term(it, Rotation1<T>, 2);
  Scale2<T> *s = ecs_term(it, Scale2<T>, 5);
  int i;
//
//  if (!m_parent) {
//    if (ecs_term_is_owned(it, 3)) {
//      for (i = 0; i < it->count; i ++) {
//        glm_translate_make(m[i].value, *(vec3*)&p[i]);
//      }
//    } else {
//      for (i = 0; i < it->count; i ++) {
//        glm_translate_make(m[i].value, *(vec3*)p);
//      }
//    }
//  } else {
//    if (ecs_term_is_owned(it, 3)) {
//      for (i = 0; i < it->count; i ++) {
//        glm_translate_to(m_parent[0].value, *(vec3*)&p[i], m[i].value);
//      }
//    } else {
//      for (i = 0; i < it->count; i ++) {
//        glm_translate_to(m_parent[0].value, *(vec3*)p, m[i].value);
//      }
//    }
//  }
//
//  if (r) {
//    if (ecs_term_is_owned(it, 4)) {
//      for (i = 0; i < it->count; i ++) {
//        glm_rotate(m[i].value, r[i].x, (vec3){1.0, 0.0, 0.0});
//        glm_rotate(m[i].value, r[i].y, (vec3){0.0, 1.0, 0.0});
//        glm_rotate(m[i].value, r[i].z, (vec3){0.0, 0.0, 1.0});
//      }
//    } else {
//      for (i = 0; i < it->count; i ++) {
//        glm_rotate(m[i].value, r->x, (vec3){1.0, 0.0, 0.0});
//        glm_rotate(m[i].value, r->y, (vec3){0.0, 1.0, 0.0});
//        glm_rotate(m[i].value, r->z, (vec3){0.0, 0.0, 1.0});
//      }
//    }
//  }
//
//  if (s) {
//    for (i = 0; i < it->count; i ++) {
//      glm_scale(m[i].value, *(vec3*)&s[i]);
//    }
//  }
}

struct Systems {
  Systems(flecs::world &ecsWorld) {
    ecsWorld.module<Transform::Systems>();

    ecsWorld.system<Position2<>, const Velocity2<>>()
        .multi_threaded(true)
        .iter([](const flecs::iter &it, Position2<> *p, const Velocity2<> *v) {
          move2(it, p, v);
        });

//    ecsWorld.system<Position2<float>, const Velocity2<float>>()
//        .multi_threaded(true)
//        .iter([](const flecs::iter &it, Position2<float> *p, const Velocity2<float> *v) {
//          move2(it, p, v);
//        });
//
//    ecsWorld.system<Position2<uint32_t>, const Velocity2<uint32_t>>()
//        .multi_threaded(true)
//        .iter([](const flecs::iter &it, Position2<uint32_t> *p, const Velocity2<uint32_t> *v) {
//          move2(it, p, v);
//        });
//
//    ecsWorld.system<Position2<uint64_t>, const Velocity2<uint64_t>>()
//        .multi_threaded(true)
//        .iter([](const flecs::iter &it, Position2<uint64_t> *p, const Velocity2<uint64_t> *v) {
//          move2(it, p, v);
//        });

    ecsWorld.system<Position2<>, const Velocity3<>>()
        .multi_threaded(true)
        .iter([](const flecs::iter &it, Position2<> *p, const Velocity3<> *v) {
          move2(it, p, v);
        });

    ecsWorld.system<Position3<>, const Velocity3<>>()
        .multi_threaded(true)
        .iter([](const flecs::iter &it, Position3<> *p, const Velocity3<> *v) {
          move3(it, p, v);
        });

    ecsWorld.system<Position3<>, const Velocity2<>>()
        .multi_threaded(true)
        .iter([](const flecs::iter &it, Position3<> *p, const Velocity2<> *v) {
          move3(it, p, v);
        });

  }
};
}

#endif //RPG_SIM_SERVER_TRANSFORM_SYSTEMS_H
