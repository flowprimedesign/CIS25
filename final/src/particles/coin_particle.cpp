#include "../headers/particle_system.h"
#include <cstdlib>

CoinParticle::CoinParticle(Point2f start_pos) {
    position = start_pos;
    velocity.x = (rand() % 40 - 20) / 10.0f;    // -2 to 2 horizontal speed
    velocity.y = (rand() % 20 - 40) / 10.0f;    // -4 to -2 (upward)
    life = 1.0f;
    size = 6 + (rand() % 3);  // Size 6-8
    color = Scalar(0, 215, 255); // Gold color
    rotation = 0;
}

void CoinParticle::update() {
    velocity.y += 0.5f;  // Gravity
    position.x += velocity.x;
    position.y += velocity.y;
    rotation += 0.2f;
    life -= 0.012f;
    if (life < 0) life = 0;
}

void CoinParticle::draw(Mat& image) {
    if (isAlive()) {
        // Draw spinning coin as ellipse
        ellipse(image, position, Size(size, size * 0.7), rotation * 57.3, 0, 360, color, -1);
        ellipse(image, position, Size(size * 0.6, size * 0.4), rotation * 57.3, 0, 360, Scalar(0, 255, 255), 2);
    }
}
