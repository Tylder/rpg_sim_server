//
// Created by Anon on 5/26/2022.
//

#ifndef RPG_SIM_SERVER_NET_INITS_H
#define RPG_SIM_SERVER_NET_INITS_H

#include "flecs.h"

namespace Net {

struct Inits {
  Inits(flecs::world &ecsWorld) {
    ecsWorld.module<Inits>();

  }
};
}// namespace Net

#endif// RPG_SIM_SERVER_NET_INITS_H