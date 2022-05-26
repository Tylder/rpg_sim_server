#include <iostream>
#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include <chrono>
#include "csv.hpp"

/* Component types */
struct Position {
    double x, y;
};

struct Velocity {
    double x, y;
};

struct Crap {
    int foo[1000]; // meant to mess up the cache by taking up useless space
};

struct Config {
    std::size_t entity_count;
    std::size_t iteration_count;
    std::size_t thread_count;
    bool is_multi_threaded;

    Config(std::size_t entity_count, std::size_t iteration_count, std::size_t thread_count, bool is_multi_threaded)
            : entity_count{entity_count},
              iteration_count{iteration_count},
              thread_count{thread_count},
              is_multi_threaded{is_multi_threaded} {}
};

std::chrono::duration<double, std::milli> runComparison(std::size_t entity_count,
                                                        std::size_t iteration_count,
                                                        std::size_t thread_count,
                                                        bool is_multi_threaded) {
    flecs::world ecs;
    ecs.set_threads(thread_count);

    ecs.system<Position, const Velocity>()
            .multi_threaded(is_multi_threaded)
            .iter([](const flecs::iter &it, Position *p, const Velocity *v) {
                for (auto row: it) {
                    p[row].x += v[row].x;
                    p[row].y += v[row].y;
                }
            });

    for (int i = 0; i < entity_count; ++i) {
        ecs.entity()
                .set<Position>({0, 0})
                .set<Velocity>({1, 1})
                .set<Crap>({0});
    }

    std::cout << "Application is running, press CTRL-C to exit..." << std::endl;

    /* Run systems */
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();

    for (int i = 0; i < iteration_count; ++i) {
        ecs.progress();
    }
    auto t2 = Clock::now();
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

    return fp_ms;
}

std::chrono::duration<double, std::milli> runComparison(Config config) {
    return runComparison(config.entity_count,
                         config.iteration_count,
                         config.thread_count,
                         config.is_multi_threaded);
}

void saveCsv(const std::string &fileName,
             const std::vector<Config> &configs,
             const std::chrono::duration<double, std::milli> &durations) {

    std::ofstream stream(fileName);

    auto writer = csv::make_csv_writer(stream);

    writer << std::array<std::string, 4>({"Entities", "Iterations", "Threads", "is Multi Threaded"}); /// header

    for (const auto &c: configs) {
        writer << std::array<std::string, 4>({std::to_string(c.entity_count),
                                              std::to_string(c.iteration_count),
                                              std::to_string(c.thread_count),
                                              std::to_string(c.is_multi_threaded)});
    }
    stream.close();
}

int main() {
    std::cout << "Speed Comparison" << std::endl;

#ifdef FLECS_DEBUG
    flecs::log::set_level(10);
#endif

    std::vector<Config> configs;
    std::vector<std::size_t> entity_counts = {10, 100, 1000, 10000, 100000, 1000000};
    std::vector<std::size_t> iteration_counts = {10, 100, 1000, 10000, 100000, 1000000};
    std::vector<std::size_t> thread_counts = {1, 2, 6, 12};

    int maxSize{100000000}; // hundred million
    bool is_add_non_multi_threaded = true;

    for (auto entity_count: entity_counts) {
        for (auto iteration_count: iteration_counts) {
            for (auto thread_count: thread_counts) {
                if (entity_count * iteration_count < maxSize) {
                    if (is_add_non_multi_threaded) {
                        configs.emplace_back(entity_count, iteration_count, thread_count, false);
                        is_add_non_multi_threaded = false;
                    }
                    configs.emplace_back(entity_count, iteration_count, thread_count, true);
                }
            }
            is_add_non_multi_threaded = true;
        }
    }


    return 0;
}
