#include <iostream>
#include "FastNoise/FastNoise.h"
#include "flecs.h"

/* Component types */
struct Position {
    double x, y;
};

struct Velocity {
    double x, y;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
//    std::vector<float> noiseOutput(16 * 16 * 16);
//
//    auto fnSimplex = FastNoise::New<FastNoise::Simplex>();
//    auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();
//
//    fnFractal->SetSource( fnSimplex );
//    fnFractal->SetOctaveCount( 5 );
//
//    // Generate a 16 x 16 x 16 area of noise
//    fnSimplex->GenUniformGrid3D(noiseOutput.data(), 0, 0, 0, 16, 16, 16, 0.2f, 1337);
//

    flecs::world ecs;
    ecs.set_threads(1);

    ecs.system<Position, const Velocity>()
            .iter([](const flecs::iter& it,
                     Position *p,
                     const Velocity *v)
                  {
                      for (auto row : it) {
                          p[row].x += v[row].x;
                          p[row].y += v[row].y;

//                          std::cout << "Moved " << it.entity(row).name() << " to {" <<
//                                    p[row].x << ", " << p[row].y << "}" << std::endl;
                      }
                  });

    auto entity = ecs.entity()
            .set<Position>({0, 0})
            .set<Velocity>({1, 1});

    for (int i = 0; i < 1000000; ++i) {
        ecs.entity()
                .set<Position>({0, 0})
                .set<Velocity>({1, 1});
    }



//    ecs.set_target_fps(1);

    std::cout << "Application move_system is running, press CTRL-C to exit..." << std::endl;

    /* Run systems */
    while (ecs.progress()) {
        std::cout << "Moved " << entity.name() << " to {" <<
                  entity.get<Position>()->x << ", " << entity.get<Position>()->y << "}" << ecs.get_threads()  <<     std::endl;
    }


    return 0;
}
