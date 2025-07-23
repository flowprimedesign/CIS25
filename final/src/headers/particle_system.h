#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include <string>

using namespace cv;
using namespace std;

/**
 * @brief Base class for all particle types
 */
class BaseParticle {
public:
    Point2f position;    // Current position of the particle
    Point2f velocity;    // Velocity vector (x, y)
    float life;          // Life value (0.0 to 1.0, 1.0 = just created)
    float size;          // Size of the particle
    Scalar color;        // Color of the particle

    virtual ~BaseParticle() = default;
    
    /**
     * @brief Update particle physics (position, velocity, life)
     */
    virtual void update() = 0;
    
    /**
     * @brief Draw the particle on the given image
     * @param image The image to draw on
     */
    virtual void draw(Mat& image) = 0;
    
    /**
     * @brief Check if particle is still alive
     * @return true if particle should continue existing
     */
    bool isAlive() const;
};

/**
 * @brief Water droplet particle for Mudkip
 */
class WaterParticle : public BaseParticle {
public:
    explicit WaterParticle(Point2f start_pos);
    void update() override;
    void draw(Mat& image) override;
};

/**
 * @brief Spinning coin particle for Meowth
 */
class CoinParticle : public BaseParticle {
private:
    float rotation;      // Current rotation angle
    
public:
    explicit CoinParticle(Point2f start_pos);
    void update() override;
    void draw(Mat& image) override;
};

/**
 * @brief Multicolored gem particle for Eevee
 */
class GemParticle : public BaseParticle {
private:
    Scalar gem_color;    // Specific gem color
    
public:
    explicit GemParticle(Point2f start_pos);
    void update() override;
    void draw(Mat& image) override;
};

/**
 * @brief Heart-shaped particle for Sylveon
 */
class HeartParticle : public BaseParticle {
public:
    explicit HeartParticle(Point2f start_pos);
    void update() override;
    void draw(Mat& image) override;
};

/**
 * @brief Lightning bolt particle for Pikachu
 */
class LightningParticle : public BaseParticle {
private:
    vector<Point2f> lightning_path;    // Zigzag path points
    
public:
    explicit LightningParticle(Point2f start_pos);
    void update() override;
    void draw(Mat& image) override;
};

/**
 * @brief Manages all particles and their emission
 */
class ParticleSystem {
private:
    vector<unique_ptr<BaseParticle>> particles;    // All active particles
    Point2f emit_position;                         // Where to emit new particles
    bool is_emitting;                              // Whether to emit new particles
    int emission_counter;                          // Frame counter for emission timing
    string particle_type;                          // Type of particles to emit
    
public:
    ParticleSystem();
    
    /**
     * @brief Set the type of particles to emit
     * @param type "water", "coin", "gem", "heart", or "lightning"
     */
    void setParticleType(const string& type);
    
    /**
     * @brief Set where new particles should be emitted
     * @param pos Position to emit particles from
     */
    void setEmitPosition(Point2f pos);
    
    /**
     * @brief Start emitting particles
     */
    void startEmission();
    
    /**
     * @brief Stop emitting particles
     */
    void stopEmission();
    
    /**
     * @brief Update all particles and handle emission
     */
    void update();
    
    /**
     * @brief Draw all active particles
     * @param image Image to draw particles on
     */
    void draw(Mat& image);
    
    /**
     * @brief Clear all particles
     */
    void clear();
    
    /**
     * @brief Get current particle count
     * @return Number of active particles
     */
    size_t getParticleCount() const;
    
    /**
     * @brief Get current particle type
     * @return Current particle type string
     */
    string getParticleType() const;
};

#endif // PARTICLE_SYSTEM_H
