#include "../headers/particle_system.h"
#include <cstdlib>

LightningParticle::LightningParticle(Point2f start_pos) {
    position = start_pos;
    velocity.x = (rand() % 40 - 20) / 10.0f;    // -2 to 2 horizontal speed
    velocity.y = (rand() % 10 - 30) / 10.0f;    // -3 to -2 (upward)
    life = 1.0f;
    size = 3 + (rand() % 2);  // Size 3-4
    color = Scalar(0, 255, 255); // Yellow color
    
    // Generate zigzag lightning path
    lightning_path.clear();
    for (int i = 0; i < 5; i++) {
        Point2f point = start_pos;
        point.x += (rand() % 20 - 10);
        point.y += i * 8;
        lightning_path.push_back(point);
    }
}

void LightningParticle::update() {
    velocity.y += 0.6f;  // Medium gravity
    position.x += velocity.x;
    position.y += velocity.y;
    
    // Update lightning path
    for (auto& point : lightning_path) {
        point.x += velocity.x;
        point.y += velocity.y;
    }
    
    life -= 0.020f;  // Fast decay
    if (life < 0) life = 0;
}

void LightningParticle::draw(Mat& image) {
    if (isAlive()) {
        // Draw lightning bolt
        for (size_t i = 0; i < lightning_path.size() - 1; i++) {
            line(image, lightning_path[i], lightning_path[i + 1], color, size);
        }
        // Add glow effect
        for (size_t i = 0; i < lightning_path.size() - 1; i++) {
            line(image, lightning_path[i], lightning_path[i + 1], Scalar(150, 255, 255), 1);
        }
    }
}
