#ifndef FACE_MESH_APP_H
#define FACE_MESH_APP_H

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include <vector>
#include "face_types.h"
#include "particle_system.h"
#include "mongodb_handler.h"

using namespace cv;
using namespace std;

/**
 * @brief Main application class for Pokémon Face Mesh Adventure
 */
class FaceMeshApp {
private:
    // Core components
    VideoCapture camera;                    // Camera for video capture
    CascadeClassifier face_cascade;         // Face detection classifier
    Mat mask_image;                         // Current Pokémon mask image
    ParticleSystem particle_system;         // Particle effects system
    unique_ptr<MongoDBHandler> mongo_handler; // MongoDB handler
    
    // App state
    string selected_mask_file;              // Current mask file (e.g., "mudkip_mask.png")
    string pokemon_name;                    // Current Pokémon name
    int photo_counter;                      // Counter for photo naming
    bool use_real_camera;                   // Whether real camera is available
    bool face_detection_enabled;            // Whether face detection is working
    bool mask_loaded;                       // Whether mask image is loaded
    
    // Mask positioning
    float mask_vertical_offset;             // Adjustable vertical offset
    float mask_horizontal_offset;           // Adjustable horizontal offset
    
    // Landmark names
    vector<string> landmark_names;          // Names for the 68 facial landmarks
    
public:
    /**
     * @brief Constructor
     * @param connection_string MongoDB connection string
     * @param mask_file Pokémon mask file to use
     * @param pokemon Pokémon name
     */
    FaceMeshApp(const string& connection_string, 
                const string& mask_file, 
                const string& pokemon);
    
    /**
     * @brief Destructor - cleanup resources
     */
    ~FaceMeshApp();
    
    /**
     * @brief Main application loop
     */
    void run();
    
    /**
     * @brief Process a single frame (detect faces, apply effects)
     * @param image Input image to process
     * @param source_type Description of image source
     */
    void processFrame(const Mat& image, const string& source_type);
    
    /**
     * @brief Show application statistics
     */
    void showAppStats();
    
private:
    // Initialization methods
    void initializeLandmarkNames();
    void loadFaceDetectionModels();
    void initializeCamera();
    void setupParticleSystem();
    void loadMaskImage();
    void downloadFaceModel();
    
    // Face detection and analysis
    vector<DetectedFace> detectFacesWithMesh(const Mat& image);
    vector<FaceLandmark> generateFacialLandmarks(const Rect& face_rect);
    vector<Point2f> createFaceMesh(const vector<FaceLandmark>& landmarks);
    double calculateFaceAngle(const vector<FaceLandmark>& landmarks);
    
    // Mouth detection
    bool detectMouthOpen(const vector<FaceLandmark>& landmarks);
    bool detectMouthOpenSimple(const Mat& face_roi);
    Point2f getMouthCenter(const vector<FaceLandmark>& landmarks);
    Point2f calculateRealMouthCenter(const Rect& face_rect);
    
    // Mask and particle effects
    Mat createMaskOverlay(const Mat& image, const DetectedFace& face);
    Mat applyCustomMask(const Mat& image, const DetectedFace& face);
    Mat createDefaultMask(const Mat& image, const DetectedFace& face);
    Mat updateWaterParticles(const Mat& image, const Point2f& mouth_center, bool mouth_open);
    
    // Drawing and visualization
    Mat drawFaceMeshOverlay(const Mat& image, const vector<DetectedFace>& faces);
    Mat drawFaceWithMouthEmoji(const Mat& image, const vector<DetectedFace>& faces);
    
    // UI and interaction
    void displayInstructions();
};

#endif // FACE_MESH_APP_H
