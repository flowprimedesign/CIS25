#ifndef ENV_LOADER_H
#define ENV_LOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

class EnvLoader {
public:
    static std::unordered_map<std::string, std::string> loadEnv(const std::string& filename = ".env") {
        std::unordered_map<std::string, std::string> env;
        std::ifstream file(filename);
        std::string line;
        
        while (std::getline(file, line)) {
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') continue;
            
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                env[key] = value;
            }
        }
        
        return env;
    }
    
    static std::string getEnv(const std::string& key, const std::string& defaultValue = "") {
        const char* env_val = std::getenv(key.c_str());
        return env_val ? std::string(env_val) : defaultValue;
    }
};

#endif // ENV_LOADER_H
