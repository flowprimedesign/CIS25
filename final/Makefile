# Pokémon Face Mesh Adventure - Makefile
# Pokémon Face Mesh Adventure - C++ Application with OpenCV and MongoDB

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR = src
HEADERS_DIR = $(SRC_DIR)/headers
PARTICLES_DIR = $(SRC_DIR)/particles
CORE_DIR = $(SRC_DIR)/core
DATABASE_DIR = $(SRC_DIR)/database
INTERFACE_DIR = $(SRC_DIR)/interface
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# MongoDB driver paths
MONGO_DIR = mongo-cxx-driver-r4.1.0
MONGO_BUILD_DIR = $(MONGO_DIR)/build
MONGO_INCLUDE_DIRS = -I$(MONGO_DIR)/src/mongocxx/include/mongocxx/v_noabi \
                     -I$(MONGO_DIR)/src/bsoncxx/include/bsoncxx/v_noabi
MONGO_LIB_DIRS = -L$(MONGO_BUILD_DIR)/src/mongocxx \
                 -L$(MONGO_BUILD_DIR)/src/bsoncxx
MONGO_LIBS = -lmongocxx._noabi -lbsoncxx._noabi

# OpenCV settings
OPENCV_INCLUDE = -I/usr/local/include -I/usr/local/include/opencv4
OPENCV_LIB_DIR = -L/usr/local/lib
OPENCV_LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui \
              -lopencv_objdetect -lopencv_imgcodecs -lopencv_dnn -lopencv_videoio

# Include paths
INCLUDES = $(OPENCV_INCLUDE) $(MONGO_INCLUDE_DIRS) -I$(HEADERS_DIR)

# Library paths
LIB_DIRS = $(OPENCV_LIB_DIR) $(MONGO_LIB_DIRS)

# All libraries
LIBS = $(OPENCV_LIBS) $(MONGO_LIBS)

# Target executable
TARGET = facemesh_app_pokemon

# Source files
PARTICLE_SOURCES = $(wildcard $(PARTICLES_DIR)/*.cpp)
CORE_SOURCES = $(wildcard $(CORE_DIR)/*.cpp)
DATABASE_SOURCES = $(wildcard $(DATABASE_DIR)/*.cpp)
INTERFACE_SOURCES = $(wildcard $(INTERFACE_DIR)/*.cpp)
MAIN_SOURCE = main.cpp

# Object files
PARTICLE_OBJECTS = $(PARTICLE_SOURCES:$(PARTICLES_DIR)/%.cpp=$(OBJ_DIR)/particles/%.o)
CORE_OBJECTS = $(CORE_SOURCES:$(CORE_DIR)/%.cpp=$(OBJ_DIR)/core/%.o)
DATABASE_OBJECTS = $(DATABASE_SOURCES:$(DATABASE_DIR)/%.cpp=$(OBJ_DIR)/database/%.o)
INTERFACE_OBJECTS = $(INTERFACE_SOURCES:$(INTERFACE_DIR)/%.cpp=$(OBJ_DIR)/interface/%.o)
MAIN_OBJECT = $(OBJ_DIR)/main.o

ALL_OBJECTS = $(PARTICLE_OBJECTS) $(CORE_OBJECTS) $(DATABASE_OBJECTS) $(INTERFACE_OBJECTS) $(MAIN_OBJECT)

# Default target
# Add pokemon alias target for backward compatibility
.PHONY: pokemon
pokemon: $(TARGET)

.PHONY: all
all: $(TARGET)

# Build target
$(TARGET): $(BUILD_DIR) $(ALL_OBJECTS)
	@echo "🔗 Linking final executable..."
	$(CXX) $(CXXFLAGS) $(ALL_OBJECTS) $(LIB_DIRS) $(LIBS) -o $(TARGET)
	@echo "✅ Build complete: $(TARGET)"
	@echo ""
	@echo "🚀 To run the app:"
	@echo "   ./$(TARGET)"
	@echo ""
	@echo "🎮 Or use the run script:"
	@echo "   ./run_pokemon.sh"

# Create build directories
$(BUILD_DIR):
	@mkdir -p $(OBJ_DIR)/particles
	@mkdir -p $(OBJ_DIR)/core
	@mkdir -p $(OBJ_DIR)/database
	@mkdir -p $(OBJ_DIR)/interface

# Compile particle objects
$(OBJ_DIR)/particles/%.o: $(PARTICLES_DIR)/%.cpp
	@echo "🔷 Compiling particle: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile core objects
$(OBJ_DIR)/core/%.o: $(CORE_DIR)/%.cpp
	@echo "🔶 Compiling core: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile database objects
$(OBJ_DIR)/database/%.o: $(DATABASE_DIR)/%.cpp
	@echo "🔸 Compiling database: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile interface objects
$(OBJ_DIR)/interface/%.o: $(INTERFACE_DIR)/%.cpp
	@echo "🔹 Compiling interface: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile main object
$(OBJ_DIR)/main.o: $(MAIN_SOURCE)
	@echo "🔺 Compiling main: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
.PHONY: clean
clean:
	@echo "🧹 Cleaning build files..."
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
	@echo "✅ Clean complete"

# Clean everything including old binaries
.PHONY: clean-all
clean-all: clean
	@echo "🧹 Cleaning all binaries..."
	rm -f facemesh_app_pokemon
	rm -f facemesh_app
	@echo "✅ Deep clean complete"

# Run the application with proper library paths
.PHONY: run
run: $(TARGET)
	@echo "🚀 Starting Pokémon Face Mesh Adventure..."
	export DYLD_LIBRARY_PATH="$(MONGO_BUILD_DIR)/src/mongocxx:$(MONGO_BUILD_DIR)/src/bsoncxx:$$DYLD_LIBRARY_PATH" && ./$(TARGET)

# Development build with debug symbols
.PHONY: debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)
	@echo "🐛 Debug build complete"

# Show build information
.PHONY: info
info:
	@echo "📋 Build Information:"
	@echo "   Compiler: $(CXX)"
	@echo "   Flags: $(CXXFLAGS)"
	@echo "   Target: $(TARGET)"
	@echo "   Source directories:"
	@echo "     • Particles: $(PARTICLES_DIR)"
	@echo "     • Core: $(CORE_DIR)"
	@echo "     • Database: $(DATABASE_DIR)"
	@echo "     • Interface: $(INTERFACE_DIR)"
	@echo "   Object files: $(words $(ALL_OBJECTS)) files"
	@echo ""
	@echo "🔗 Library Information:"
	@echo "   OpenCV: $(OPENCV_LIBS)"
	@echo "   MongoDB: $(MONGO_LIBS)"

# Help target
.PHONY: help
help:
	@echo "🎮 Pokémon Face Mesh Adventure - Build System"
	@echo ""
	@echo "📋 Available targets:"
	@echo "   all (default) - Build the complete application"
	@echo "   clean         - Remove build files"
	@echo "   clean-all     - Remove all build files and binaries"
	@echo "   run           - Build and run the application"
	@echo "   debug         - Build with debug symbols"
	@echo "   info          - Show build configuration"
	@echo "   help          - Show this help message"
	@echo ""
	@echo "🏗️  Project Structure:"
	@echo "   • Headers in: $(HEADERS_DIR)/"
	@echo "   • Particles in: $(PARTICLES_DIR)/"
	@echo "   • Core logic in: $(CORE_DIR)/"
	@echo "   • Database in: $(DATABASE_DIR)/"
	@echo "   • Interface in: $(INTERFACE_DIR)/"
	@echo ""
	@echo "🚀 Quick start:"
	@echo "   make && ./$(TARGET)"

# Show particle system info
.PHONY: particles
particles:
	@echo "✨ Particle System Modules:"
	@echo "   🌊 WaterParticle (Mudkip)"
	@echo "   🪙 CoinParticle (Meowth)"
	@echo "   💎 GemParticle (Eevee)"
	@echo "   💖 HeartParticle (Sylveon)"
	@echo "   ⚡ LightningParticle (Pikachu)"
	@echo ""
	@echo "📁 Particle files:"
	@for file in $(PARTICLE_SOURCES); do echo "   • $$file"; done
