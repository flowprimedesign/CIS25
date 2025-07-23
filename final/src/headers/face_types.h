#ifndef FACE_TYPES_H
#define FACE_TYPES_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

/**
 * @brief Represents a single facial landmark point
 */
struct FaceLandmark {
    Point2f point;           // 2D position of the landmark
    int landmark_id;         // Unique identifier for the landmark
    string landmark_name;    // Human-readable name of the landmark
};

/**
 * @brief Represents a detected face with all its features
 */
struct DetectedFace {
    Rect rect;                          // Bounding rectangle of the face
    double confidence;                  // Detection confidence score
    Point2f center;                     // Center point of the face
    vector<FaceLandmark> landmarks;     // 68 facial landmark points
    vector<Point2f> face_mesh;          // Face mesh points for overlay
    Mat mask_overlay;                   // Generated mask overlay
    double face_angle;                  // Face rotation angle
    bool mouth_open;                    // Mouth state (open/closed)
    Point2f mouth_center;               // Center point of the mouth
};

#endif // FACE_TYPES_H
