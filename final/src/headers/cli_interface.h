#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include <string>
#include <utility>

using namespace std;

/**
 * @brief CLI interface functions for user interaction
 */
namespace CLIInterface {
    
    /**
     * @brief Display the welcome banner
     */
    void displayWelcomeBanner();
    
    /**
     * @brief Display the Pokémon selection menu
     */
    void displayPokemonMenu();
    
    /**
     * @brief Get user's Pokémon selection
     * @return pair<mask_file, pokemon_name>
     */
    pair<string, string> getPokemonSelection();
    
    /**
     * @brief Test MongoDB connection and display result
     * @param connection_string MongoDB connection string
     * @return true if connection successful
     */
    bool testMongoDBConnection(const string& connection_string);
    
    /**
     * @brief Display application instructions
     */
    void displayInstructions();
    
    /**
     * @brief Display goodbye message
     * @param pokemon_name Name of the selected Pokémon
     */
    void displayGoodbye(const string& pokemon_name);
}

#endif // CLI_INTERFACE_H
