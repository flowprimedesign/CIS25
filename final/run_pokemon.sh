#!/bin/bash
# Pokémon Face Mesh Adventure Runner
# Sets up proper library paths and runs the application

echo "🚀 Starting Pokémon Face Mesh Adventure..."
echo "Setting up MongoDB library paths..."

# Set complete library path including C driver dependencies
export DYLD_LIBRARY_PATH="./mongo-cxx-driver-r4.1.0/build/src/mongocxx:./mongo-cxx-driver-r4.1.0/build/src/bsoncxx:./mongo-cxx-driver-r4.1.0/build/_deps/mongo-c-driver-build/src/libmongoc:./mongo-cxx-driver-r4.1.0/build/_deps/mongo-c-driver-build/src/libbson:$DYLD_LIBRARY_PATH"

# Check if application exists
if [ ! -f "facemesh_app_pokemon" ]; then
    echo "❌ Application not found! Building first..."
    make pokemon
fi

# Run the application
./facemesh_app_pokemon
