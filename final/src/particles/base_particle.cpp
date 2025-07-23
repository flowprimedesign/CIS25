#include "../headers/particle_system.h"

bool BaseParticle::isAlive() const {
    return life > 0;
}
