#ifndef MONGODB_HANDLER_H
#define MONGODB_HANDLER_H

#include <string>
#include <vector>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/collection.hpp>
#include "face_types.h"

using namespace std;
using namespace mongocxx;

/**
 * @brief Handles all MongoDB operations for the face mesh app
 */
class MongoDBHandler {
private:
    client db_client;           // MongoDB client instance
    database db;                // Face mesh database
    collection face_collection; // Face analysis collection
    
public:
    /**
     * @brief Constructor - connects to MongoDB
     * @param connection_string MongoDB connection string
     */
    explicit MongoDBHandler(const string& connection_string);
    
    /**
     * @brief Test the MongoDB connection
     * @return true if connection is working
     */
    bool testConnection();
    
    /**
     * @brief Save face analysis data to MongoDB
     * @param faces Vector of detected faces
     * @param filename Name of the captured image file
     * @param pokemon_name Name of the selected Pokémon
     * @param mask_file Name of the mask file used
     * @return true if save was successful
     */
    bool saveFaceData(const vector<DetectedFace>& faces, 
                      const string& filename,
                      const string& pokemon_name,
                      const string& mask_file);
    
    /**
     * @brief Display all saved face capture data
     */
    void showFaceDatabase();
    
    /**
     * @brief Get statistics about saved data
     * @return pair<total_captures, total_faces>
     */
    pair<int, int> getStatistics();
    
    /**
     * @brief Get current timestamp as string (public access)
     * @return Formatted timestamp string
     */
    string getCurrentTimestamp();
    
private:
    // Removed getCurrentTimestamp from private section since it's now public
};

#endif // MONGODB_HANDLER_H
