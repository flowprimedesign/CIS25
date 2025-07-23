#include "../headers/face_mesh_app.h"
#include "../headers/cli_interface.h"
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

FaceMeshApp::FaceMeshApp(const string& connection_string, 
                         const string& mask_file, 
                         const string& pokemon) 
    : selected_mask_file(mask_file),
      pokemon_name(pokemon),
      photo_counter(1),
      use_real_camera(false),
      face_detection_enabled(false),
      mask_loaded(false),
      mask_vertical_offset(0.0f),
      mask_horizontal_offset(0.0f) {
    
    // Initialize MongoDB handler
    mongo_handler = make_unique<MongoDBHandler>(connection_string);
    
    initializeLandmarkNames();
    loadFaceDetectionModels();
    loadMaskImage();
    initializeCamera();
    setupParticleSystem();
    
    cout << "📊 MongoDB connection established!" << endl;
    cout << "🎭 Selected Pokémon: " << pokemon_name << endl;
    cout << "🖼️  Using mask: " << selected_mask_file << endl;
}

FaceMeshApp::~FaceMeshApp() {
    if (camera.isOpened()) {
        camera.release();
    }
    destroyAllWindows();
}

void FaceMeshApp::initializeLandmarkNames() {
    landmark_names = {
        // Jaw line (17 points: 0-16)
        "jaw_1", "jaw_2", "jaw_3", "jaw_4", "jaw_5", "jaw_6", "jaw_7", "jaw_8", "jaw_9",
        "jaw_10", "jaw_11", "jaw_12", "jaw_13", "jaw_14", "jaw_15", "jaw_16", "jaw_17",
        
        // Right eyebrow (5 points: 17-21)
        "right_eyebrow_1", "right_eyebrow_2", "right_eyebrow_3", "right_eyebrow_4", "right_eyebrow_5",
        
        // Left eyebrow (5 points: 22-26)
        "left_eyebrow_1", "left_eyebrow_2", "left_eyebrow_3", "left_eyebrow_4", "left_eyebrow_5",
        
        // Nose (9 points: 27-35)
        "nose_1", "nose_2", "nose_3", "nose_4", "nose_5", "nose_6", "nose_7", "nose_8", "nose_9",
        
        // Right eye (6 points: 36-41)
        "right_eye_center", "right_eye_1", "right_eye_2", "right_eye_3", "right_eye_4", "right_eye_5",
        
        // Left eye (6 points: 42-47)
        "left_eye_center", "left_eye_1", "left_eye_2", "left_eye_3", "left_eye_4", "left_eye_5",
        
        // Mouth (20 points: 48-67)
        "mouth_center", "mouth_outer_1", "mouth_outer_2", "mouth_outer_3", "mouth_outer_4", "mouth_outer_5",
        "mouth_outer_6", "mouth_outer_7", "mouth_outer_8", "mouth_outer_9", "mouth_outer_10",
        "mouth_outer_11", "mouth_inner_1", "mouth_inner_2", "mouth_inner_3", "mouth_inner_4", 
        "mouth_inner_5", "mouth_inner_6", "mouth_inner_7", "mouth_inner_8"
    };
}

void FaceMeshApp::loadFaceDetectionModels() {
    cout << "🔍 Loading face detection models..." << endl;
    
    vector<string> cascade_paths = {
        "/usr/local/opt/opencv/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml",
        "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml",
        "/opt/homebrew/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml",
        "haarcascade_frontalface_alt.xml"
    };
    
    for (const auto& path : cascade_paths) {
        if (face_cascade.load(path)) {
            face_detection_enabled = true;
            cout << "✅ Face detection model loaded: " << path << endl;
            break;
        }
    }
    
    if (!face_detection_enabled) {
        cout << "❌ Face detection model not found!" << endl;
    }
}

void FaceMeshApp::initializeCamera() {
    cout << "🔍 Checking for camera..." << endl;
    camera.open(0);
    if (camera.isOpened()) {
        use_real_camera = true;
        camera.set(CAP_PROP_FRAME_WIDTH, 1280);
        camera.set(CAP_PROP_FRAME_HEIGHT, 720);
        camera.set(CAP_PROP_FPS, 30);
        cout << "🎥 Real camera initialized successfully!" << endl;
    } else {
        cout << "❌ No camera detected. Camera is required for this application." << endl;
    }
}

void FaceMeshApp::setupParticleSystem() {
    if (pokemon_name == "Mudkip") {
        particle_system.setParticleType("water");
    } else if (pokemon_name == "Meowth") {
        particle_system.setParticleType("coin");
    } else if (pokemon_name == "Eevee") {
        particle_system.setParticleType("gem");
    } else if (pokemon_name == "Sylveon") {
        particle_system.setParticleType("heart");
    } else if (pokemon_name == "Pikachu") {
        particle_system.setParticleType("lightning");
    } else {
        particle_system.setParticleType("water");
    }
    
    cout << "✨ Particle system set to: " << particle_system.getParticleType() << endl;
}

void FaceMeshApp::loadMaskImage() {
    cout << "🎭 Loading mask image: " << selected_mask_file << endl;
    
    vector<string> mask_paths = {
        "images/" + selected_mask_file,
        selected_mask_file,
        "./images/" + selected_mask_file
    };
    
    for (const auto& path : mask_paths) {
        mask_image = imread(path, IMREAD_UNCHANGED);
        if (!mask_image.empty()) {
            mask_loaded = true;
            cout << "✅ Mask loaded: " << path << endl;
            cout << "   📏 Mask size: " << mask_image.cols << "x" << mask_image.rows 
                      << " (channels: " << mask_image.channels() << ")" << endl;
            break;
        }
    }
    
    if (!mask_loaded) {
        cout << "⚠️  Mask file not found: " << selected_mask_file << endl;
        cout << "   💡 Using default overlay instead" << endl;
    }
}

void FaceMeshApp::run() {
    displayInstructions();
    
    if (use_real_camera) {
        namedWindow("Pokemon Face Mesh", WINDOW_AUTOSIZE);
        cout << "\n🎥 Camera window is open!" << endl;
    } else {
        cout << "\n📷 No camera detected. Please connect a camera to take photos." << endl;
        return;
    }
    
    Mat frame;
    
    while (true) {
        camera >> frame;
        if (frame.empty()) continue;
        
        // Detect faces and apply effects
        auto faces = detectFacesWithMesh(frame);
        Mat display_frame = drawFaceWithMouthEmoji(frame, faces);
        
        // Add version indicator
        putText(display_frame, "SPACE: Photo | Q: Quit", 
                   Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, 
                   Scalar(0, 255, 0), 2);
        
        putText(display_frame, "w/s: mask up/down | a/d: left/right", 
                   Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.5, 
                   Scalar(0, 255, 255), 2);
        
        imshow("Pokemon Face Mesh", display_frame);
        
        int key = waitKey(1) & 0xFF;
        // adjust mask position
        if (key == ' ' || key == 13) { // SPACE or ENTER
            processFrame(frame, "camera");
        } else if (key == 'w' || key == 'W') {
            mask_vertical_offset -= 0.05f;
            cout << "📏 Mask moved up. Vertical offset: " << mask_vertical_offset << endl;
        } else if (key == 's' || key == 'S') {
            mask_vertical_offset += 0.05f;
            cout << "📏 Mask moved down. Vertical offset: " << mask_vertical_offset << endl;
        } else if (key == 'a' || key == 'A') {
            mask_horizontal_offset -= 0.05f;
            cout << "📏 Mask moved left. Horizontal offset: " << mask_horizontal_offset << endl;
        } else if (key == 'd' || key == 'D') {
            mask_horizontal_offset += 0.05f;
            cout << "📏 Mask moved right. Horizontal offset: " << mask_horizontal_offset << endl;
        } else if (key == 'r' || key == 'R') {
            mask_vertical_offset = 0.0f;
            mask_horizontal_offset = 0.0f;
            cout << "📏 Mask position reset." << endl;
        } else if (key == 'i' || key == 'I') {
            mongo_handler->showFaceDatabase();
        } else if (key == 'q' || key == 27) { // q or ESC
            break;
        }
    }
}

void FaceMeshApp::processFrame(const Mat& image, const string& source_type) {
    string filename = "facemesh_" + pokemon_name + "_" + 
                         mongo_handler->getCurrentTimestamp() + "_" + 
                         to_string(photo_counter) + ".jpg";
    
    auto faces = detectFacesWithMesh(image);
    Mat result_image = drawFaceMeshOverlay(image, faces);
    
    if (imwrite(filename, result_image)) {
        cout << "\n🎭 Face capture saved: " << filename << endl;
        cout << "   📊 Faces detected: " << faces.size() << endl;
        
        // Save to MongoDB with additional info
        if (mongo_handler->saveFaceData(faces, filename, pokemon_name, selected_mask_file)) {
            cout << "   💾 Data saved to MongoDB" << endl;
        }
        
        photo_counter++;
    } else {
        cout << "❌ Failed to save image: " << filename << endl;
    }
}

void FaceMeshApp::showAppStats() {
    cout << "\n📊 APP STATISTICS:" << endl;
    cout << "  Camera available: " << (use_real_camera ? "Yes" : "No") << endl;
    cout << "  Face detection: " << (face_detection_enabled ? "Enabled" : "Disabled") << endl;
    cout << "  Pokémon: " << pokemon_name << endl;
    cout << "  Mask file: " << selected_mask_file << endl;
    cout << "  Analyses performed: " << (photo_counter - 1) << endl;
    cout << "  Particles active: " << particle_system.getParticleCount() << endl;
    
    auto stats = mongo_handler->getStatistics();
    cout << "  MongoDB captures: " << stats.first << endl;
    cout << "  Total faces saved: " << stats.second << endl;
}

void FaceMeshApp::displayInstructions() {
    CLIInterface::displayInstructions();
}
// Draw face mesh overlay on the image
vector<DetectedFace> FaceMeshApp::detectFacesWithMesh(const Mat& image) {
    vector<DetectedFace> detected_faces;
    
    if (!face_detection_enabled) {
        return detected_faces;
    }
    
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, gray);
    
    vector<Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));
    
    if (!faces.empty()) {
        // Find the largest face
        Rect largest_face = faces[0];
        for (const auto& face_rect : faces) {
            if (face_rect.area() > largest_face.area()) {
                largest_face = face_rect;
            }
        }
        
        DetectedFace face;
        face.rect = largest_face;
        face.center = Point2f(largest_face.x + largest_face.width/2.0f, 
                                 largest_face.y + largest_face.height/2.0f);
        face.confidence = 1.0;
        face.landmarks = generateFacialLandmarks(largest_face);
        face.face_mesh = createFaceMesh(face.landmarks);
        face.face_angle = calculateFaceAngle(face.landmarks);
        
        Mat face_roi = image(largest_face);
        face.mouth_open = detectMouthOpenSimple(face_roi);
        face.mouth_center = getMouthCenter(face.landmarks);
        
        detected_faces.push_back(face);
    }
    
    return detected_faces;
}

vector<FaceLandmark> FaceMeshApp::generateFacialLandmarks(const Rect& face_rect) {
    vector<FaceLandmark> landmarks;
    
    // Generate 68 facial landmarks based on face rectangle
    float face_width = face_rect.width;
    float face_height = face_rect.height;
    float center_x = face_rect.x + face_width / 2.0f;
    float center_y = face_rect.y + face_height / 2.0f;
    
    // Jaw line (17 points)
    for (int i = 0; i < 17; i++) {
        float t = i / 16.0f;
        float x = face_rect.x + t * face_width;
        float y = face_rect.y + face_height * 0.8f + sin(t * M_PI) * face_height * 0.1f;
        
        FaceLandmark landmark;
        landmark.point = Point2f(x, y);
        landmark.landmark_id = i;
        landmark.landmark_name = (i < landmark_names.size()) ? landmark_names[i] : "jaw_" + to_string(i);
        landmarks.push_back(landmark);
    }
    
    // Right eyebrow (5 points)
    for (int i = 0; i < 5; i++) {
        float t = i / 4.0f;
        float x = center_x - face_width * 0.25f + t * face_width * 0.25f;
        float y = center_y - face_height * 0.25f - face_height * 0.05f * sin(t * M_PI);
        
        FaceLandmark landmark;
        landmark.point = Point2f(x, y);
        landmark.landmark_id = 17 + i;
        landmark.landmark_name = (17 + i < landmark_names.size()) ? landmark_names[17 + i] : "right_eyebrow_" + to_string(i);
        landmarks.push_back(landmark);
    }
    
    // Left eyebrow (5 points)
    for (int i = 0; i < 5; i++) {
        float t = i / 4.0f;
        float x = center_x + t * face_width * 0.25f;
        float y = center_y - face_height * 0.25f - face_height * 0.05f * sin(t * M_PI);
        
        FaceLandmark landmark;
        landmark.point = Point2f(x, y);
        landmark.landmark_id = 22 + i;
        landmark.landmark_name = (22 + i < landmark_names.size()) ? landmark_names[22 + i] : "left_eyebrow_" + to_string(i);
        landmarks.push_back(landmark);
    }
    
    // Nose (9 points)
    for (int i = 0; i < 9; i++) {
        float t = i / 8.0f;
        float x = center_x + (i % 3 - 1) * face_width * 0.05f;
        float y = center_y - face_height * 0.1f + t * face_height * 0.2f;
        
        FaceLandmark landmark;
        landmark.point = Point2f(x, y);
        landmark.landmark_id = 27 + i;
        landmark.landmark_name = (27 + i < landmark_names.size()) ? landmark_names[27 + i] : "nose_" + to_string(i);
        landmarks.push_back(landmark);
    }
    
    // Right eye (6 points)
    Point2f right_eye_center(center_x - face_width * 0.18f, center_y - face_height * 0.1f);
    FaceLandmark right_eye_center_landmark;
    right_eye_center_landmark.point = right_eye_center;
    right_eye_center_landmark.landmark_id = 36;
    right_eye_center_landmark.landmark_name = (36 < landmark_names.size()) ? landmark_names[36] : "right_eye_center";
    landmarks.push_back(right_eye_center_landmark);
    
    for (int i = 1; i < 6; i++) {
        float angle = i * 2 * M_PI / 6;
        float x = right_eye_center.x + cos(angle) * face_width * 0.06f;
        float y = right_eye_center.y + sin(angle) * face_height * 0.03f;
        
        FaceLandmark landmark;
        landmark.point = Point2f(x, y);
        landmark.landmark_id = 36 + i;
        landmark.landmark_name = (36 + i < landmark_names.size()) ? landmark_names[36 + i] : "right_eye_" + to_string(i);
        landmarks.push_back(landmark);
    }
    
    // Left eye (6 points)
    Point2f left_eye_center(center_x + face_width * 0.18f, center_y - face_height * 0.1f);
    FaceLandmark left_eye_center_landmark;
    left_eye_center_landmark.point = left_eye_center;
    left_eye_center_landmark.landmark_id = 42;
    left_eye_center_landmark.landmark_name = (42 < landmark_names.size()) ? landmark_names[42] : "left_eye_center";
    landmarks.push_back(left_eye_center_landmark);
    
    for (int i = 1; i < 6; i++) {
        float angle = i * 2 * M_PI / 6;
        float x = left_eye_center.x + cos(angle) * face_width * 0.06f;
        float y = left_eye_center.y + sin(angle) * face_height * 0.03f;
        
        FaceLandmark landmark;
        landmark.point = Point2f(x, y);
        landmark.landmark_id = 42 + i;
        landmark.landmark_name = (42 + i < landmark_names.size()) ? landmark_names[42 + i] : "left_eye_" + to_string(i);
        landmarks.push_back(landmark);
    }
    
    // Mouth (20 points)
    Point2f mouth_center(center_x, center_y + face_height * 0.42f);
    FaceLandmark mouth_center_landmark;
    mouth_center_landmark.point = mouth_center;
    mouth_center_landmark.landmark_id = 48;
    mouth_center_landmark.landmark_name = (48 < landmark_names.size()) ? landmark_names[48] : "mouth_center";
    landmarks.push_back(mouth_center_landmark);
    
    for (int i = 1; i < 20; i++) {
        float angle = i * 2 * M_PI / 20;
        float radius = (i < 12) ? face_width * 0.15f : face_width * 0.1f;
        float x = mouth_center.x + cos(angle) * radius;
        float y = mouth_center.y + sin(angle) * face_height * 0.08f;
        
        FaceLandmark landmark;
        landmark.point = Point2f(x, y);
        landmark.landmark_id = 48 + i;
        landmark.landmark_name = (48 + i < landmark_names.size()) ? landmark_names[48 + i] : "mouth_" + to_string(i);
        landmarks.push_back(landmark);
    }
    
    return landmarks;
}

vector<Point2f> FaceMeshApp::createFaceMesh(const vector<FaceLandmark>& landmarks) {
    vector<Point2f> mesh_points;
    
    // Convert landmarks to mesh points
    for (const auto& landmark : landmarks) {
        mesh_points.push_back(landmark.point);
    }
    
    // Add additional interpolated points for smoother mesh
    if (landmarks.size() >= 17) {
        // Add points between jaw landmarks for smoother curve
        for (size_t i = 0; i < 16; i++) {
            Point2f mid_point = (landmarks[i].point + landmarks[i+1].point) * 0.5f;
            mesh_points.push_back(mid_point);
        }
    }
    
    return mesh_points;
}

double FaceMeshApp::calculateFaceAngle(const vector<FaceLandmark>& landmarks) {
    if (landmarks.size() < 42) return 0.0;
    
    // Calculate angle based on eye positions
    Point2f left_eye = landmarks[36].point;  // Right eye (left from viewer perspective)
    Point2f right_eye = landmarks[42].point; // Left eye (right from viewer perspective)
    
    Point2f eye_vector = right_eye - left_eye;
    double angle = atan2(eye_vector.y, eye_vector.x) * 180.0 / M_PI;
    
    return angle;
}

bool FaceMeshApp::detectMouthOpenSimple(const Mat& face_roi) {
    if (face_roi.empty()) return false;
    
    // Get the mouth area (center bottom of face)
    int mouth_y = face_roi.rows * 0.75;  // 75% down the face (lower than before)
    int mouth_x_start = face_roi.cols * 0.4;   // 40% from left (narrower focus)
    int mouth_x_end = face_roi.cols * 0.6;     // 60% from left
    int mouth_height = face_roi.rows * 0.08;   // 8% of face height to scan
    
    if (mouth_y >= face_roi.rows || mouth_x_start >= mouth_x_end || mouth_y + mouth_height >= face_roi.rows) {
        return false;
    }
    
    // Convert to grayscale
    Mat gray;
    if (face_roi.channels() == 3) {
        cvtColor(face_roi, gray, COLOR_BGR2GRAY);
    } else {
        gray = face_roi.clone();
    }
    
    // Apply slight blur to reduce noise
    GaussianBlur(gray, gray, Size(3, 3), 0);
    
    // Get reference brightness from cheek area (should be consistent)
    Rect cheek_area(face_roi.cols * 0.15, face_roi.rows * 0.5, face_roi.cols * 0.2, face_roi.rows * 0.15);
    if (cheek_area.x + cheek_area.width < gray.cols && cheek_area.y + cheek_area.height < gray.rows) {
        Scalar cheek_mean = mean(gray(cheek_area));
        int dynamic_threshold = (int)(cheek_mean[0] * 0.6);  // 60% of cheek brightness
        
        // Count dark pixels in mouth region (looking for mouth cavity)
        int total_pixels = 0;
        int dark_pixels = 0;
        int very_dark_pixels = 0;
        
        // Scan multiple horizontal lines in mouth region
        for (int y_offset = 0; y_offset < mouth_height; y_offset += 2) {
            int scan_y = mouth_y + y_offset;
            if (scan_y >= gray.rows) break;
            
            for (int x = mouth_x_start; x < mouth_x_end; x += 1) {
                if (x < gray.cols) {
                    uchar pixel_value = gray.at<uchar>(scan_y, x);
                    total_pixels++;
                    
                    if (pixel_value < dynamic_threshold) {
                        dark_pixels++;
                    }
                    if (pixel_value < dynamic_threshold * 0.7) {
                        very_dark_pixels++;
                    }
                }
            }
        }
        
        // Calculate ratios
        float dark_ratio = (total_pixels > 0) ? (float)dark_pixels / total_pixels : 0;
        float very_dark_ratio = (total_pixels > 0) ? (float)very_dark_pixels / total_pixels : 0;
        
        // Debug output
        // cout << "Cheek ref: " << (int)cheek_mean[0] << ", Threshold: " << dynamic_threshold 
        //      << ", Dark: " << dark_pixels << "/" << total_pixels << " (" << dark_ratio 
        //      << "), Very dark: " << very_dark_pixels << " (" << very_dark_ratio << ")" << endl;
        
        // More forgiving thresholds with better logic
        bool mouth_detected = (very_dark_ratio > 0.12f) || (dark_ratio > 0.35f && very_dark_ratio > 0.05f);
        
        if (mouth_detected) {
           // cout << "� MOUTH OPEN DETECTED! (Multi-line scan method)" << endl;
        }
        
        return mouth_detected;
    }
    
    // Fallback to original method if cheek detection fails
    return false;
}

Point2f FaceMeshApp::getMouthCenter(const vector<FaceLandmark>& landmarks) {
    // Use the actual mouth center landmark (landmark 48)
    if (landmarks.size() > 48) {
        return landmarks[48].point;
    }
    // Fallback to old calculation if landmarks not available
    return Point2f(0, 0);
}

Mat FaceMeshApp::drawFaceWithMouthEmoji(const Mat& image, const vector<DetectedFace>& faces) {
    Mat result = image.clone();
    
    for (const auto& face : faces) {
        // Apply custom mask if loaded
        if (mask_loaded && !mask_image.empty()) {
            result = applyCustomMask(result, face);
        }
        
        // Update particle system
        if (face.mouth_center.x > 0 && face.mouth_center.y > 0) {
            result = updateWaterParticles(result, face.mouth_center, face.mouth_open);
        }
        
        // Draw face rectangle
        //rectangle(result, face.rect, Scalar(0, 255, 0), 2);
        
        // Add mouth state text
        string mouth_state = face.mouth_open ? "MOUTH OPEN" : "MOUTH CLOSED";
        Scalar text_color = face.mouth_open ? Scalar(0, 255, 0) : Scalar(0, 255, 255);
        // putText(result, mouth_state, 
        //            Point(face.rect.x, face.rect.y - 10), 
        //            FONT_HERSHEY_SIMPLEX, 0.6, text_color, 2);
    }
    
    return result;
}

Mat FaceMeshApp::drawFaceMeshOverlay(const Mat& image, const vector<DetectedFace>& faces) {
    return drawFaceWithMouthEmoji(image, faces); 
}

Mat FaceMeshApp::createMaskOverlay(const Mat& image, const DetectedFace& face) {
    Mat overlay = Mat::zeros(image.size(), CV_8UC3);
    
    if (face.landmarks.empty()) return overlay;
    
    if (mask_loaded && !mask_image.empty()) {
        // Use custom mask image
        return applyCustomMask(image, face);
    } else {
        // Use default procedural mask
        return createDefaultMask(image, face);
    }
}

Mat FaceMeshApp::createDefaultMask(const Mat& image, const DetectedFace& face) {
    Mat mask = Mat::zeros(image.size(), CV_8UC3);
    
    // Create default procedural mask
    vector<Point> mask_points;
    for (const auto& point : face.face_mesh) {
        mask_points.push_back(Point(static_cast<int>(point.x), static_cast<int>(point.y)));
    }
    
    if (mask_points.size() > 3) {
        Scalar mask_color(100, 200, 255); // Light blue mask
        fillPoly(mask, vector<vector<Point>>{mask_points}, mask_color);
        
        // Add decorative elements
        if (face.landmarks.size() > 42) {
            circle(mask, Point(face.landmarks[36].point), 5, Scalar(255, 255, 0), -1);
            circle(mask, Point(face.landmarks[42].point), 5, Scalar(255, 255, 0), -1);
        }
        
        if (face.landmarks.size() > 30) {
            circle(mask, Point(face.landmarks[30].point), 3, Scalar(0, 255, 255), -1);
        }
    }
    
    return mask;
}

Mat FaceMeshApp::applyCustomMask(const Mat& image, const DetectedFace& face) {
    Mat result = image.clone();
    
    // Calculate face dimensions and position
    Rect face_rect = face.rect;
    float face_width = face_rect.width;
    float face_height = face_rect.height;
    
    // Resize mask to fit face
    Mat resized_mask;
    float scale_factor = 1.4f; // Make mask slightly larger than face
    int mask_width = static_cast<int>(face_width * scale_factor);
    int mask_height = static_cast<int>(face_height * scale_factor);
    
    resize(mask_image, resized_mask, Size(mask_width, mask_height));
    
    // Calculate position to align mask with face features
    float vertical_offset = -0.7f + mask_vertical_offset;
    float horizontal_offset = 0.0f + mask_horizontal_offset;
    
    int mask_x = face_rect.x - (mask_width - face_width) / 2 + static_cast<int>(face_width * horizontal_offset);
    int mask_y = face_rect.y - (mask_height - face_height) / 2 + static_cast<int>(face_height * vertical_offset);
    
    // Fine-tune positioning based on eye landmarks if available
    if (face.landmarks.size() > 42) {
        Point2f left_eye = face.landmarks[36].point;
        Point2f right_eye = face.landmarks[42].point;
        
        Point2f eye_center;
        float face_center_x = face_rect.x + face_rect.width * 0.5f;
        
        eye_center.x = face_center_x;
        eye_center.y = (left_eye.y + right_eye.y) * 0.5f;
        
        float eye_offset_y = -face_height * 0.35f;
        
        mask_y = static_cast<int>(eye_center.y + eye_offset_y - mask_height * 0.3f + face_height * mask_vertical_offset);
        mask_x = static_cast<int>(eye_center.x - mask_width * 0.5f + face_width * mask_horizontal_offset);
    }
    
    // Create rotation matrix if face is angled
    Mat rotation_matrix = getRotationMatrix2D(Point2f(mask_width/2, mask_height/2), 
                                                      face.face_angle, 1.0);
    Mat rotated_mask;
    warpAffine(resized_mask, rotated_mask, rotation_matrix, Size(mask_width, mask_height));
    
    // Apply mask with proper blending
    for (int y = 0; y < rotated_mask.rows; y++) {
        for (int x = 0; x < rotated_mask.cols; x++) {
            int img_x = mask_x + x;
            int img_y = mask_y + y;
            
            // Check bounds
            if (img_x >= 0 && img_x < result.cols && img_y >= 0 && img_y < result.rows) {
                Vec3b mask_pixel = rotated_mask.at<Vec3b>(y, x);
                Vec3b img_pixel = result.at<Vec3b>(img_y, img_x);
                
                // Apply mask with transparency based on brightness
                float alpha = 1.0f; // Base transparency
                
                // If mask has 4 channels (RGBA), use alpha channel
                if (rotated_mask.channels() == 4) {
                    Vec4b mask_pixel_rgba = rotated_mask.at<Vec4b>(y, x);
                    alpha = mask_pixel_rgba[3] / 255.0f * 0.7f; // Use alpha channel
                    mask_pixel = Vec3b(mask_pixel_rgba[0], mask_pixel_rgba[1], mask_pixel_rgba[2]);
                }
                
                // Skip transparent or very dark pixels
                if (mask_pixel[0] + mask_pixel[1] + mask_pixel[2] > 30) {
                    // Blend mask with original image
                    result.at<Vec3b>(img_y, img_x) = Vec3b(
                        static_cast<uchar>(img_pixel[0] * (1 - alpha) + mask_pixel[0] * alpha),
                        static_cast<uchar>(img_pixel[1] * (1 - alpha) + mask_pixel[1] * alpha),
                        static_cast<uchar>(img_pixel[2] * (1 - alpha) + mask_pixel[2] * alpha)
                    );
                }
            }
        }
    }
    
    return result;
}

Mat FaceMeshApp::updateWaterParticles(const Mat& image, const Point2f& mouth_center, bool mouth_open) {
    Mat result = image.clone();
    
    particle_system.setEmitPosition(mouth_center);
    
    if (mouth_open) {
        particle_system.startEmission();
    } else {
        particle_system.stopEmission();
    }
    
    particle_system.update();
    particle_system.draw(result);
    
    return result;
}
