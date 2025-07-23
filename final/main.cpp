/**
 * @file main.cpp
 * @brief Main entry point for Pokémon Face Mesh Adventure
 * @author Luis Ibarra
 * @date 2025
 * 
 * A C++ application that combines real-time face detection,
 * Pokémon-themed mask overlays, and particle effects with MongoDB data storage.
 */

#include <mongocxx/instance.hpp>
#include "src/headers/cli_interface.h"
#include "src/headers/face_mesh_app.h"
#include "src/headers/env_loader.h"

using namespace std;

int main() {
    try {
        // Display welcome banner
        CLIInterface::displayWelcomeBanner();
        
        // Initialize MongoDB instance once (required for MongoDB C++ driver)
        mongocxx::instance instance{};
        
        // Load environment variables
        auto env = EnvLoader::loadEnv();
        
        // MongoDB connection string from environment or fallback
        string connection_string;
        if (env.find("MONGODB_CONNECTION_STRING") != env.end()) {
            connection_string = env["MONGODB_CONNECTION_STRING"];
        } else {
            // Fallback for development (still not recommended)
            cerr << "⚠️  WARNING: No .env file found. Using fallback connection." << endl;
            cerr << "   Create a .env file with MONGODB_CONNECTION_STRING for security." << endl;
            connection_string = "mongodb+srv://luisibarradesign:Microm14%21@camerapp.bpkgdqw.mongodb.net/";
        }
        
        // Test MongoDB connection
        bool mongo_connected = CLIInterface::testMongoDBConnection(connection_string);
        
        // Get user's Pokémon selection
        auto pokemon_selection = CLIInterface::getPokemonSelection();
        string mask_file = pokemon_selection.first;
        string pokemon_name = pokemon_selection.second;
        
        // Create and run the face mesh application
        FaceMeshApp app(connection_string, mask_file, pokemon_name);
        app.run();
        
        // Display goodbye message
        CLIInterface::displayGoodbye(pokemon_name);
        
        return 0;
        
    } catch (const std::exception& e) {
        cerr << "\n❌ Application error: " << e.what() << endl;
        cerr << "Please check your system configuration and try again." << endl;
        return 1;
    }
}
