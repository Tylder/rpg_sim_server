#include <iostream>
#include <chrono>
#include <vector>
#include <array>

/* Component types */
struct Position {
    double x, y;
};

struct Velocity {
    double x, y;
};

struct Crap {
    int foo[1000] = {0}; // meant to mess up the cache by taking up useless space
};

struct Entity {
    Position pos;
    Velocity vel;
//    Crap crap;
};

void move_system(std::vector<Entity>& ents) {
    for(Entity& ent : ents) {
        ent.pos.x += ent.vel.x;
        ent.pos.y += ent.vel.y;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<Entity> entities;

    for (int i = 0; i < 100000; ++i) {
        Position pos {0, 0};
        Velocity vel {1, 1};
//        Crap crap;
        Entity ent {pos, vel};
        entities.emplace_back(ent);
    }


    std::cout << "Application move_system is running, press CTRL-C to exit..." << std::endl;

    /* Run systems */
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();

    for (int i = 0; i < 100000; ++i) {
        move_system(entities);
    }

    auto t2 = Clock::now();
    std::cout << t2-t1 << '\n';

    return 0;
}
