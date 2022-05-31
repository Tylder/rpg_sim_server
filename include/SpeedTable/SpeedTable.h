//
// Created by Administrator on 26/05/2022.
//

#ifndef RPG_SIM_SERVER_SPEEDTABLE_H
#define RPG_SIM_SERVER_SPEEDTABLE_H

#include <vector>
#include <string>
#include <chrono>
#include "flecs.h"
#include "csv.hpp"

namespace speedTable {

const std::uint_fast32_t MAX_SIZE = 100000000; // 100 mil

/* Component types */
struct Position {
  double x, y;
};

struct Velocity {
  double x, y;
};

struct Crap {
  int foo[100]; // meant to mess up the cache by taking up useless space
};

struct Config {
  int entityCount;
  int iterationCount;
  int threadCount;
  bool isMultiThreaded;

  Config(int entityCount, int iterationCount, int threadCount, bool isMultiThreaded)
      : entityCount{entityCount},
        iterationCount{iterationCount},
        threadCount{threadCount},
        isMultiThreaded{isMultiThreaded} {}
};

typedef std::vector<std::size_t> countVec;

class SpeedTable {
 public:
  static std::vector<Config> makeConfigs(const countVec &entityCounts,
                                         const countVec &iterationCounts,
                                         const countVec &threadCounts);

  static std::vector<std::chrono::duration<double, std::milli>> runConfigs(const std::vector<Config> &configs,
                                                                           const std::string &csvFileName = "");
};

}

#endif //RPG_SIM_SERVER_SPEEDTABLE_H
