#include <iostream>
#include "FastNoise/FastNoise.h"
#include "flecs.h"
#include <chrono>

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


    flecs::world ecs;

    #ifdef FLECS_DEBUG
    flecs::log::set_level(10);
    #endif

    ecs.set_threads(4);

    ecs.system<Position, const Velocity>()
//        .interval(1)
        .multi_threaded(true)
        .iter([](const flecs::iter& it,Position *p,const Velocity *v){
            for (auto row : it) {
                    p[row].x += v[row].x;
                    p[row].y += v[row].y;
                }
//            std::cout << 'end of system 1' << std::endl;
        });

//    ecs.system<Position>()
//            .iter([](const flecs::iter& it,Position *p){
//                for (auto row : it) {
//                    p[row].x += 1;
//                    p[row].y += 1;
//                }
////                std::cout << 'end of system 2' << std::endl;
//            });

    auto entity = ecs.entity("myEntity")
            .set<Position>({0, 0})
            .set<Velocity>({1, 1});



    for (int i = 0; i < 100000; ++i) {
        ecs.entity()
                .set<Position>({0, 0})
                .set<Velocity>({1, 1})
                .set<Crap>({0});

    }
//
//
//
////    ecs.set_target_fps(1);

    std::cout << "Application move_system is running, press CTRL-C to exit..." << std::endl;

    /* Run systems */
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();

    for (int i = 0; i < 100000; ++i) {
        ecs.progress();
    }

//    while (ecs.progress()) {
//        std::cout << "Delta time: " << ecs.get_world().delta_time() << std::endl;
////        std::cout << "Moved " << entity.name() << " to {" <<
////                  entity.get<Position>()->x << ", " << entity.get<Position>()->y << "} threads: " << ecs.get_threads()  <<     std::endl;
//    }

    auto t2 = Clock::now();
    std::cout << t2-t1 << '\n';

    return 0;
}
