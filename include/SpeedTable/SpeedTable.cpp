//
// Created by Administrator on 26/05/2022.
//

#include "SpeedTable.h"

using namespace speedTable;

std::vector<Config> SpeedTable::makeConfigs(const countVec &entityCounts,
                                            const countVec &iterationCounts,
                                            const countVec &threadCounts) {

  std::vector<Config> configs;

  bool isAddNonMultiThreaded = true;

  for (auto entityCount : entityCounts) {
    for (auto iterationCount : iterationCounts) {
      for (auto threadCount : threadCounts) {
        if (entityCount * iterationCount < MAX_SIZE) {
          if (isAddNonMultiThreaded) {
            configs.emplace_back(entityCount, iterationCount, threadCount, false);
            isAddNonMultiThreaded = false;
          }
          configs.emplace_back(entityCount, iterationCount, threadCount, true);
        }
      }
      isAddNonMultiThreaded = true;
    }
  }

  return configs;
}

std::vector<std::chrono::duration<double, std::milli>> SpeedTable::runConfigs(const std::vector<Config> &configs,
                                                                              const std::string &csvFileName) {

  std::vector<std::chrono::duration<double, std::milli>> durations;

  for (auto config : configs) {
    flecs::world ecs;

    ecs.set_threads(config.threadCount);

    // system
    ecs.system<Position, const Velocity>()
        .multi_threaded(config.isMultiThreaded)
        .iter([](const flecs::iter &it, Position *p, const Velocity *v) {
          for (auto row : it) {
            p[row].x += v[row].x;
            p[row].y += v[row].y;
          }
        });

    // entities
    for (int i = 0; i < config.entityCount; ++i) {
      ecs.entity()
          .set<Position>({0, 0})
          .set<Velocity>({1, 1})
          .set<Crap>({0});
    }

    // Run systems
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();

    for (int i = 0; i < config.iterationCount; ++i) {
      ecs.progress();
    }

    auto t2 = Clock::now();

    std::chrono::duration<double, std::milli> durationMs = t2 - t1;

    durations.emplace_back(durationMs);
  }

  if (!csvFileName.empty()) {
    std::ofstream stream(csvFileName);

    auto writer = csv::make_csv_writer(stream);

    writer << std::array<std::string, 5>({"Entities", "Iterations", "Threads", "is Multi Threaded",
                                          "Duration"}); /// header

    for (std::size_t i = 0; i < configs.size(); i++) {

      writer << std::array<std::string, 5>({
                                               std::to_string(configs[i].entityCount),
                                               std::to_string(configs[i].iterationCount),
                                               std::to_string(configs[i].threadCount),
                                               std::to_string(configs[i].isMultiThreaded),
                                               std::to_string(durations[i].count())
                                           });
    }
//    stream.close();
  }

  return durations;
}
