#include "../headers/particle_system.h"
#include <cstdlib>

GemParticle::GemParticle(Point2f start_pos) {
    position = start_pos;
    velocity.x = (rand() % 50 - 25) / 10.0f;    // -2.5 to 2.5 horizontal speed
    velocity.y = (rand() % 30 - 40) / 10.0f;    // -4 to -1 (upward)
    life = 1.0f;
    size = 4 + (rand() % 3);  // Size 4-6
    
    // Random gem colors (multicolored)
    int color_choice = rand() % 6;
    switch (color_choice) {
        case 0: gem_color = Scalar(255, 0, 0); break;     // Red
        case 1: gem_color = Scalar(0, 255, 0); break;     // Green  
        case 2: gem_color = Scalar(0, 0, 255); break;     // Blue
        case 3: gem_color = Scalar(255, 0, 255); break;   // Magenta
        case 4: gem_color = Scalar(255, 255, 0); break;   // Cyan
        default: gem_color = Scalar(128, 0, 255); break;  // Purple
    }
    color = gem_color;
}

void GemParticle::update() {
    velocity.y += 0.4f;  // Light gravity
    position.x += velocity.x;
    position.y += velocity.y;
    life -= 0.010f;
    if (life < 0) life = 0;
}

void GemParticle::draw(Mat& image) {
    if (isAlive()) {
        // Draw gem as diamond shape
        vector<Point> diamond = {
            Point(position.x, position.y - size),
            Point(position.x + size, position.y),
            Point(position.x, position.y + size),
            Point(position.x - size, position.y)
        };
        fillPoly(image, vector<vector<Point>>{diamond}, color);
        polylines(image, vector<vector<Point>>{diamond}, true, Scalar(255, 255, 255), 1);
    }
}
