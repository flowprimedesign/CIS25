#include "../headers/particle_system.h"
#include <algorithm>
#include <cstdlib>

ParticleSystem::ParticleSystem() 
    : is_emitting(false), emission_counter(0), particle_type("water") {
}

void ParticleSystem::setParticleType(const string& type) {
    particle_type = type;
}

void ParticleSystem::setEmitPosition(Point2f pos) {
    emit_position = pos;
}

void ParticleSystem::startEmission() {
    is_emitting = true;
}

void ParticleSystem::stopEmission() {
    is_emitting = false;
}

void ParticleSystem::update() {
    // Emit new particles if mouth is open
    if (is_emitting) {
        emission_counter++;
        int emit_frequency = (particle_type == "lightning") ? 6 : 4;  // Lightning less frequent
        
        if (emission_counter % emit_frequency == 0) {
            Point2f emit_pos = emit_position;
            emit_pos.x += (rand() % 4 - 2);   // ±2 pixels horizontal
            emit_pos.y += (rand() % 4 - 2);   // ±2 pixels vertical
            
            // Create appropriate particle type
            if (particle_type == "water") {
                particles.push_back(make_unique<WaterParticle>(emit_pos));
            } else if (particle_type == "coin") {
                particles.push_back(make_unique<CoinParticle>(emit_pos));
            } else if (particle_type == "gem") {
                particles.push_back(make_unique<GemParticle>(emit_pos));
            } else if (particle_type == "heart") {
                particles.push_back(make_unique<HeartParticle>(emit_pos));
            } else if (particle_type == "lightning") {
                particles.push_back(make_unique<LightningParticle>(emit_pos));
            }
        }
    }
    
    // Update all particles
    for (auto& particle : particles) {
        particle->update();
    }
    
    // Remove dead particles
    particles.erase(
        remove_if(particles.begin(), particles.end(),
            [](const unique_ptr<BaseParticle>& p) { return !p->isAlive(); }),
        particles.end()
    );
}

void ParticleSystem::draw(Mat& image) {
    for (const auto& particle : particles) {
        if (particle->isAlive()) {
            particle->draw(image);
        }
    }
}

void ParticleSystem::clear() {
    particles.clear();
}

size_t ParticleSystem::getParticleCount() const {
    return particles.size();
}

string ParticleSystem::getParticleType() const {
    return particle_type;
}
