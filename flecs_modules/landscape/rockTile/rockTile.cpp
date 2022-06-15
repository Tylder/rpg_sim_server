//
// Created by Administrator on 15/06/2022.
//

#include "rockTile.h"
#include <iostream>

namespace Landscape::Rock {
RockTile::RockTile(flecs::world &ecsWorld) : ecsWorld{&ecsWorld} {
  ecsWorld.import <Landscape::Components>();
}
void RockTile::handleMapSet() {
}

float *RockTile::updateAndGetNoise() {
  auto map = this->ecsWorld->get<Map::Map>();
  float noiseData[map->width * map->height];

  auto fnSimplex = FastNoise::New<FastNoise::Simplex>();
  auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();

  fnFractal->SetSource(fnSimplex);
  fnFractal->SetOctaveCount(5);

  std::vector<float> noiseData2 {};

  fnFractal->GenUniformGrid2D(noiseData2.data(), 0, 0, map->width, map->height, 0.02f, map->seed);

  for (int i = 0; i < sizeof(noiseData) / sizeof(float); i++) {
    std::cout << noise[i] << ", ";
  }
  return noiseData;
}

}// namespace Landscape::Rock