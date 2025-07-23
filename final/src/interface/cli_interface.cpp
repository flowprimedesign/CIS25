#include "../headers/cli_interface.h"
#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using namespace std;

namespace CLIInterface {

    void displayWelcomeBanner() {
        cout << string(60, '=') << endl;
        cout << "🎮 POKÉMON FACE MESH ADVENTURE 🎮" << endl;
        cout << string(60, '=') << endl;
        cout << "Welcome, Trainer! Ready to catch some facial features?" << endl;
        cout << "Choose your Pokémon companion for a magical mask experience!" << endl;
        cout << string(60, '-') << endl;
    }

    void displayPokemonMenu() {
        cout << "\n🎭 SELECT YOUR POKÉMON MASK:" << endl;
        cout << string(40, '-') << endl;
        cout << "1. 🌊 Mudkip    - Water droplet effects" << endl;
        cout << "2. 🪙 Meowth    - Coin shower effects" << endl;
        cout << "3. 💎 Eevee     - Multicolored gem effects" << endl;
        cout << "4. 💖 Sylveon   - Heart particle effects" << endl;
        cout << "5. ⚡ Pikachu   - Lightning bolt effects" << endl;
        cout << string(40, '-') << endl;
        cout << "Enter your choice (1-5): ";
    }

    pair<string, string> getPokemonSelection() {
        int choice = 0;
        
        while (true) {
            displayPokemonMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                    cout << "\n🎉 Great choice! Mudkip is ready for action!" << endl;
                    cout << "🎬 Starting face detection with Mudkip mask..." << endl;
                    cout << string(60, '=') << endl;
                    return make_pair("mudkip_mask.png", "Mudkip");
                    
                case 2:
                    cout << "\n🎉 Great choice! Meowth is ready for action!" << endl;
                    cout << "🎬 Starting face detection with Meowth mask..." << endl;
                    cout << string(60, '=') << endl;
                    return make_pair("meowth_mask.png", "Meowth");
                    
                case 3:
                    cout << "\n🎉 Great choice! Eevee is ready for action!" << endl;
                    cout << "🎬 Starting face detection with Eevee mask..." << endl;
                    cout << string(60, '=') << endl;
                    return make_pair("eevee_mask.png", "Eevee");
                    
                case 4:
                    cout << "\n🎉 Great choice! Sylveon is ready for action!" << endl;
                    cout << "🎬 Starting face detection with Sylveon mask..." << endl;
                    cout << string(60, '=') << endl;
                    return make_pair("sylveon_mask.png", "Sylveon");
                    
                case 5:
                    cout << "\n🎉 Great choice! Pikachu is ready for action!" << endl;
                    cout << "🎬 Starting face detection with Pikachu mask..." << endl;
                    cout << string(60, '=') << endl;
                    return make_pair("pikachu_mask.png", "Pikachu");
                    
                default:
                    cout << "\n❌ Invalid choice! Please select 1-5." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
            }
        }
    }

    bool testMongoDBConnection(const string& connection_string) {
        cout << "\n🔌 Testing MongoDB connection..." << endl;
        
        try {
            mongocxx::client client{mongocxx::uri{connection_string}};
            client["test"]["test"].find_one({});
            cout << "✅ MongoDB connection successful!" << endl;
            return true;
        } catch (const std::exception& e) {
            cout << "❌ MongoDB connection failed: " << e.what() << endl;
            cout << "⚠️  The app will continue but photos won't be saved to database." << endl;
            return false;
        }
    }

    void displayInstructions() {
        cout << "\n" << string(60, '=') << endl;
        cout << "🎭 FACE MESH & MASK OVERLAY APP" << endl;
        cout << string(60, '=') << endl;
        cout << "🎥 REAL CAMERA MODE:" << endl;
        cout << "   SPACE or ENTER - Take photo with mask overlay" << endl;
        cout << "📋 INFO:" << endl;
        cout << "   'i' or 'I' - Show captured faces database" << endl;
        cout << "   'S' - Show app statistics" << endl;
        cout << "🎭 MASK CONTROLS:" << endl;
        cout << "   w/s - Move mask up/down" << endl;
        cout << "   a/d - Move mask left/right" << endl;
        cout << "   r - Reset mask position" << endl;
        cout << "😮 MOUTH DETECTION:" << endl;
        cout << "   Open/close mouth to see emoji changes" << endl;
        cout << "❌ EXIT:" << endl;
        cout << "   'q' or ESC - Quit application" << endl;
        cout << string(60, '=') << endl;
    }

    void displayGoodbye(const string& pokemon_name) {
        cout << "\n👋 Exiting face mesh app..." << endl;
        cout << "\n🎉 Face mesh adventure completed successfully!" << endl;
        cout << "Thanks for playing with " << pokemon_name << "! 🎮" << endl;
    }

} // namespace CLIInterface
