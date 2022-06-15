//
// Created by Administrator on 15/06/2022.
//

#ifndef RPG_SIM_SERVER_FLECS_MODULES_LANDSCAPE_ROCKTILE_ROCKTILE_H_
#define RPG_SIM_SERVER_FLECS_MODULES_LANDSCAPE_ROCKTILE_ROCKTILE_H_

#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include <array>
#include <string>
#include <vector>

#include "flecs_modules/landscape/rockTile/components.cpp"

namespace Landscape::Rock {

class RockTile {
 public:
  RockTile(flecs::world &ecsWorld);
  void handleMapSet();

 private:
  float *updateAndGetNoise();

 public:
  flecs::world *ecsWorld;
  std::vector<float> noise;// holds vector of noise data, same size as map
};

}// namespace Landscape::Rock

#endif//RPG_SIM_SERVER_FLECS_MODULES_LANDSCAPE_ROCKTILE_ROCKTILE_H_
