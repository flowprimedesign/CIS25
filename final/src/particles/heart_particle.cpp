#include "../headers/particle_system.h"
#include <cstdlib>

HeartParticle::HeartParticle(Point2f start_pos) {
    position = start_pos;
    velocity.x = (rand() % 30 - 15) / 10.0f;    // -1.5 to 1.5 horizontal speed
    velocity.y = (rand() % 20 - 35) / 10.0f;    // -3.5 to -1.5 (upward)
    life = 1.0f;
    size = 5 + (rand() % 3);  // Size 5-7
    color = Scalar(180, 20, 255); // Pink color
}

void HeartParticle::update() {
    velocity.y += 0.3f;  // Very light gravity
    position.x += velocity.x;
    position.y += velocity.y;
    life -= 0.008f;  // Longer life
    if (life < 0) life = 0;
}

void HeartParticle::draw(Mat& image) {
    if (isAlive()) {
        // Draw heart shape
        int heart_size = size;
        Point center = position;
        
        // Draw two circles for top of heart
        circle(image, Point(center.x - heart_size/2, center.y - heart_size/3), 
               heart_size/2, color, -1);
        circle(image, Point(center.x + heart_size/2, center.y - heart_size/3), 
               heart_size/2, color, -1);
        
        // Draw triangle for bottom of heart
        vector<Point> triangle = {
            Point(center.x - heart_size, center.y),
            Point(center.x + heart_size, center.y),
            Point(center.x, center.y + heart_size)
        };
        fillPoly(image, vector<vector<Point>>{triangle}, color);
    }
}
