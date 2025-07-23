#include "../headers/particle_system.h"
#include <cstdlib>

WaterParticle::WaterParticle(Point2f start_pos) {
    position = start_pos;
    velocity.x = (rand() % 60 - 30) / 10.0f;    // -3 to 3 horizontal speed
    velocity.y = (rand() % 20 - 30) / 10.0f;    // -3 to -1 (slight upward)
    life = 1.0f;
    size = 5 + (rand() % 4);  // Size 5-8
    color = Scalar(255, 150 + rand() % 50, 0); // Blue variations
}

void WaterParticle::update() {
    velocity.y += 0.7f;  // Gravity
    position.x += velocity.x;
    position.y += velocity.y;
    life -= 0.015f;
    if (life < 0) life = 0;
    color = Scalar(255, 150 + (int)(life * 50), 0);
}

void WaterParticle::draw(Mat& image) {
    if (isAlive()) {
        circle(image, position, size, color, -1);
        circle(image, Point(position.x - 1, position.y - 1), 
               max(1, (int)(size * 0.5)), Scalar(255, 255, 200), -1);
    }
}
