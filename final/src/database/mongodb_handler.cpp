#include "../headers/mongodb_handler.h"
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::make_array;

MongoDBHandler::MongoDBHandler(const string& connection_string)
    : db_client(mongocxx::uri{connection_string}),
      db(db_client["facemesh_app"]),
      face_collection(db["face_analysis"]) {
}

bool MongoDBHandler::testConnection() {
    try {
        face_collection.find_one({});
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool MongoDBHandler::saveFaceData(const vector<DetectedFace>& faces, 
                                  const string& filename,
                                  const string& pokemon_name,
                                  const string& mask_file) {
    try {
        bsoncxx::builder::basic::array faces_array;
        
        for (const auto& face : faces) {
            bsoncxx::builder::basic::array landmarks_array;
            for (const auto& landmark : face.landmarks) {
                landmarks_array.append(make_document(
                    kvp("id", landmark.landmark_id),
                    kvp("name", landmark.landmark_name),
                    kvp("x", landmark.point.x),
                    kvp("y", landmark.point.y)
                ));
            }
            
            bsoncxx::builder::basic::array mesh_array;
            for (const auto& point : face.face_mesh) {
                mesh_array.append(make_document(
                    kvp("x", point.x),
                    kvp("y", point.y)
                ));
            }
            
            faces_array.append(make_document(
                kvp("face_rect", make_document(
                    kvp("x", face.rect.x),
                    kvp("y", face.rect.y),
                    kvp("width", face.rect.width),
                    kvp("height", face.rect.height)
                )),
                kvp("confidence", face.confidence),
                kvp("center", make_document(
                    kvp("x", face.center.x),
                    kvp("y", face.center.y)
                )),
                kvp("landmarks", landmarks_array),
                kvp("face_mesh", mesh_array),
                kvp("face_angle", face.face_angle),
                kvp("mouth_open", face.mouth_open),
                kvp("landmarks_count", static_cast<int>(face.landmarks.size())),
                kvp("mesh_points_count", static_cast<int>(face.face_mesh.size()))
            ));
        }
        
        auto doc = make_document(
            kvp("filename", filename),
            kvp("pokemon_name", pokemon_name),
            kvp("mask_file", mask_file),
            kvp("timestamp", getCurrentTimestamp()),
            kvp("capture_time", bsoncxx::types::b_date{chrono::system_clock::now()}),
            kvp("faces_detected", static_cast<int>(faces.size())),
            kvp("faces", faces_array),
            kvp("analysis_type", "pokemon_face_mesh"),
            kvp("app_version", "4.0")
        );
        
        auto result = face_collection.insert_one(doc.view());
        return result.has_value();
        
    } catch (const std::exception& e) {
        cerr << "❌ Failed to save to MongoDB: " << e.what() << endl;
        return false;
    }
}

void MongoDBHandler::showFaceDatabase() {
    cout << "\n📋 CAPTURED FACES DATABASE:" << endl;
    cout << string(50, '-') << endl;
    
    try {
        auto cursor = face_collection.find({});
        int count = 0;
        
        for (auto&& doc : cursor) {
            count++;
            cout << "\n🎭 Capture #" << count << ":" << endl;
            
            if (doc["filename"]) {
                cout << "  📸 File: " << doc["filename"].get_string().value << endl;
            }
            if (doc["pokemon_name"]) {
                cout << "  🎮 Pokémon: " << doc["pokemon_name"].get_string().value << endl;
            }
            if (doc["mask_file"]) {
                cout << "  🎭 Mask: " << doc["mask_file"].get_string().value << endl;
            }
            if (doc["timestamp"]) {
                cout << "  ⏰ Time: " << doc["timestamp"].get_string().value << endl;
            }
            if (doc["faces_detected"]) {
                cout << "  👤 Faces detected: " << doc["faces_detected"].get_int32().value << endl;
            }
            if (doc["app_version"]) {
                cout << "  📦 Version: " << doc["app_version"].get_string().value << endl;
            }
        }
        
        if (count == 0) {
            cout << "  No face captures found. Take some photos first!" << endl;
        } else {
            cout << "\n📊 Total analyses: " << count << endl;
        }
        
    } catch (const std::exception& e) {
        cout << "❌ Error reading database: " << e.what() << endl;
    }
}

pair<int, int> MongoDBHandler::getStatistics() {
    try {
        int total_captures = 0;
        int total_faces = 0;
        
        auto cursor = face_collection.find({});
        for (auto&& doc : cursor) {
            total_captures++;
            if (doc["faces_detected"]) {
                total_faces += doc["faces_detected"].get_int32().value;
            }
        }
        
        return make_pair(total_captures, total_faces);
    } catch (const std::exception& e) {
        return make_pair(0, 0);
    }
}

string MongoDBHandler::getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    auto time_t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time_t), "%Y%m%d_%H%M%S");
    return ss.str();
}
