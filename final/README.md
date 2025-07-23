# Pokémon Face Mesh Adventure 🎮

An interactive C++ application that combines real-time face detection, Pokémon-themed mask overlays, and particle effects with MongoDB data storage. Built with a clean, organized architecture for easy maintenance and debugging. Choose your favorite Pokémon companion and watch magical particles appear when you open your mouth!

<img src='demo.gif' title='Demo' width='' alt='Demo' />

## Features

🎭 **Interactive CLI Interface**: Choose from 5 different Pokémon masks
📹 **Real-time Face Detection**: Uses OpenCV for live camera face tracking  
🎪 **Dynamic Mask Overlays**: Pokémon-themed masks that adapt to your face
✨ **Mouth-activated Particles**: Unique particle effects for each Pokémon
💾 **MongoDB Integration**: Automatic saving of photos and face analysis data
🎨 **Adjustable Controls**: Fine-tune mask positioning in real-time
🏗️ **Clean Architecture**: Well-organized, maintainable code structure

## Pokémon Selection

1. 🌊 **Mudkip** - Water droplet effects
2. 🪙 **Meowth** - Spinning coin effects
3. 💎 **Eevee** - Multicolored gem effects
4. 💖 **Sylveon** - Heart particle effects
5. ⚡ **Pikachu** - Lightning bolt effects

## Prerequisites

- macOS with Xcode command line tools
- Homebrew package manager
- Webcam for real-time face detection
- MongoDB Atlas account (or local MongoDB installation)

## Installation

### 1. Install OpenCV

```bash
brew install opencv
```

Verify the installation:

```bash
brew list | grep opencv
pkg-config --cflags --libs opencv4
```

### 2. MongoDB C++ Driver

The MongoDB C++ driver is included in this project:

- `mongo-cxx-driver-r4.1.0/` - Source code and built libraries
- Pre-compiled and ready to use

### 3. Build the Application

```bash
# Navigate to project directory
cd /path/to/BCC/cis25/final

# Compile the Pokémon Face Mesh app
make

# Or use the pokemon target for compatibility
make pokemon

# Clean build files if needed
make clean
```

### Manual Compilation (Alternative)

If you prefer to compile manually:

```bash
g++ -std=c++17 -I/usr/local/include -I/usr/local/include/opencv4 \
  -I./mongo-cxx-driver-r4.1.0/src/mongocxx/include/mongocxx/v_noabi \
  -I./mongo-cxx-driver-r4.1.0/src/bsoncxx/include/bsoncxx/v_noabi \
  -L/usr/local/lib -L./mongo-cxx-driver-r4.1.0/build/src/mongocxx \
  -L./mongo-cxx-driver-r4.1.0/build/src/bsoncxx \
  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect \
  -lopencv_imgcodecs -lopencv_dnn -lopencv_videoio \
  -lmongocxx._noabi -lbsoncxx._noabi \
  main.cpp src/core/*.cpp src/particles/*.cpp src/database/*.cpp src/interface/*.cpp \
  -o facemesh_app_pokemon
```

## Project Structure

```txt
├── main.cpp                   # Main entry point
├── facemesh_app_pokemon       # Compiled executable
├── Makefile                   # Build automation system
├── src/                       # Modular source code
│   ├── headers/              # Header files
│   │   ├── face_types.h      # Face detection structures
│   │   ├── particle_system.h # Particle system declarations
│   │   ├── cli_interface.h   # CLI interface
│   │   ├── mongodb_handler.h # Database operations
│   │   └── face_mesh_app.h   # Main application class
│   ├── core/                 # Core application logic
│   │   ├── face_mesh_app.cpp # Main face mesh implementation
│   │   └── particle_system.cpp # Particle system logic
│   ├── particles/            # Particle type implementations
│   │   ├── base_particle.cpp # Base particle class
│   │   ├── water_particle.cpp # Mudkip water effects
│   │   ├── coin_particle.cpp  # Meowth coin effects
│   │   ├── gem_particle.cpp   # Eevee gem effects
│   │   ├── heart_particle.cpp # Sylveon heart effects
│   │   └── lightning_particle.cpp # Pikachu lightning effects
│   ├── database/             # Database operations
│   │   └── mongodb_handler.cpp # MongoDB connection and operations
│   └── interface/            # User interface
│       └── cli_interface.cpp # Command line interface implementation
├── images/                    # Pokémon mask image files
│   ├── mudkip_mask.png       # Mudkip mask
│   ├── meowth_mask.png       # Meowth mask
│   ├── eevee_mask.png        # Eevee mask
│   ├── sylveon_mask.png      # Sylveon mask
│   ├── pikachu_mask.png      # Pikachu mask
│   ├── pokeball.png          # Pokeball icon
│   ├── pokeballOpen.png      # Open pokeball icon
│   └── pokeballSide.png      # Side pokeball icon
├── Makefile                   # Build automation
├── run_pokemon.sh            # Run script with library paths
├── README.md                  # This documentation
├── mongo-cxx-driver-r4.1.0/  # MongoDB C++ driver
└── facemesh_*.jpg            # Captured photos with analysis
```

## Build System

The project uses a **Makefile** for build automation with the following features:

- ✅ **Pre-configured and ready to use** - all paths and dependencies set up
- ✅ **Handles library paths automatically** - no manual configuration needed
- ✅ **Optimized for this project structure** - works perfectly with the modular design
- ✅ **Includes helpful build targets** - `make clean`, `make run`, `make info`, `make help`
- ✅ **Academic-friendly** - standard build system expected by professors

### Available Make Targets

```bash
make          # Build the application (default)
make pokemon  # Build the application (alias)
make run      # Build and run with proper library paths
make clean    # Remove build files
make info     # Show build configuration details
make help     # Display all available commands
make particles # Show particle system information
```

## How to Run

### Quick Start

```bash
# Option 1: Use the run script (recommended)
./run_pokemon.sh

# Option 2: Use Makefile run target
make run

# Option 3: Build and run manually
make && ./facemesh_app_pokemon
```

### Step-by-Step Usage

1. **Launch the application**

   ```bash
   # Recommended: Use the run script
   ./run_pokemon.sh

   # Or use make
   make run
   ```

2. **Welcome Screen**

   - See the Pokémon adventure banner
   - MongoDB connection test runs automatically

3. **Choose Your Pokémon**

   - Select from 5 different Pokémon masks (1-5)
   - Each has unique particle effects

4. **Face Detection Starts**

   - Camera window opens automatically
   - Real-time face detection begins
   - Mask overlay appears on your face

5. **Interactive Controls**
   - **Open/Close Mouth**: Trigger particle effects
   - **SPACE**: Capture photo with analysis
   - **W/S**: Adjust mask vertical position
   - **A/D**: Adjust mask horizontal position
   - **ESC/Q**: Exit application

## Application Features

### Real-time Face Detection

- Uses OpenCV Haar Cascade classifiers
- Processes largest detected face in frame
- Adjusts mask overlay to face size and position

### Particle Effects System

Each Pokémon has unique mouth-activated particle effects:

- **Mudkip**: Blue water droplets with gravity physics
- **Meowth**: Spinning golden coins with rotation
- **Eevee**: Multi-colored gems with diamond shapes
- **Sylveon**: Pink heart particles with gentle physics
- **Pikachu**: Yellow lightning bolts with zigzag patterns

### MongoDB Data Storage

Automatically saves to database:

- Captured photos (JPG files)
- Face analysis metadata
- Landmark detection results
- Timestamp and session information

## Configuration

### Environment Setup (Required)

**Create your environment file:**

1. Copy the example environment file:

   ```bash
   cp .env.example .env
   ```

2. Edit `.env` with your actual MongoDB credentials:
   ```bash
   # MongoDB Configuration
   MONGODB_CONNECTION_STRING=mongodb+srv://yourusername:yourpassword@yourcluster.mongodb.net/
   MONGODB_DATABASE_NAME=facemesh_app
   ```

### MongoDB Atlas Setup

1. **Create MongoDB Atlas Account**: Visit [https://cloud.mongodb.com/](https://cloud.mongodb.com/)
2. **Create a New Cluster**: Choose the free tier
3. **Create Database User**:
   - Go to "Database Access"
   - Add new database user with read/write permissions
   - Remember the username and password
4. **Whitelist IP Address**:
   - Go to "Network Access"
   - Add your current IP address (or 0.0.0.0/0 for development)
5. **Get Connection String**:
   - Click "Connect" on your cluster
   - Choose "Connect your application"
   - Copy the connection string and update your `.env` file

### Security Notes

- ✅ **`.env` is gitignored** - Your credentials won't be committed
- ✅ **No hardcoded credentials** - All sensitive data in environment variables
- ✅ **Template provided** - Use `.env.example` as a starting point
- ⚠️ **URL-encode passwords** - Special characters must be encoded (e.g., `!` becomes `%21`)

### MongoDB Connection

### Camera Settings

The application automatically detects your default camera (index 0). To use a different camera:

```cpp
camera.open(1); // Use camera index 1 instead of 0
```

## Troubleshooting

### MongoDB Issues

- **Connection errors**: Check your MongoDB Atlas connection string, username, password, and network access
- **Library not found**: Ensure `DYLD_LIBRARY_PATH` includes the MongoDB build directories
- **Header not found**: Verify the include paths point to the correct MongoDB source directories

### OpenCV Issues

## Troubleshooting

### Common Issues

**Camera not detected**

- Ensure your webcam is connected and working
- Check camera permissions in System Preferences > Security & Privacy > Camera
- Try a different camera index (0, 1, 2) in the code

**MongoDB connection fails**

- Verify your connection string is correct
- Check that your IP is whitelisted in MongoDB Atlas
- Ensure username/password are properly URL-encoded

**Face detection not working**

- Ensure adequate lighting
- Face the camera directly
- Check that OpenCV Haar cascade files are installed
- Try adjusting distance from camera

**Particle effects not appearing**

- Make sure face is detected (green rectangle around face)
- Open mouth wider to trigger detection
- Check mouth detection threshold in debug output

**Compilation errors**

- Verify all include paths are correct
- Check that MongoDB C++ driver is built
- Ensure OpenCV is properly installed via Homebrew

### Build Issues

- Install Xcode command line tools: `xcode-select --install`
- Rebuild MongoDB driver: `cd mongo-cxx-driver-r4.1.0/build && make clean && make`
- Check OpenCV version: `pkg-config --modversion opencv4`
- Verify include paths are correct
- Ensure OpenCV is properly installed via Homebrew

## Technical Details

### Modular Architecture

The application uses a clean modular design for improved maintainability:

- **Headers (`src/headers/`)**: All type definitions and class declarations
- **Core Logic (`src/core/`)**: Main application and particle system implementation
- **Particle Types (`src/particles/`)**: Individual particle effect implementations
- **Database (`src/database/`)**: MongoDB connection and data operations
- **Interface (`src/interface/`)**: User interaction and CLI components

This structure provides:

- **Easy Debugging**: Issues can be isolated to specific modules
- **Code Reusability**: Components can be easily reused or swapped
- **Clear Separation**: Each module has a single responsibility
- **Better Testing**: Individual components can be tested independently

### Technologies Used

- **C++17**: Modern C++ features and standard library
- **OpenCV 4.x**: Computer vision and image processing
- **MongoDB C++ Driver**: Database connectivity and operations
- **Haar Cascade Classifiers**: Face detection algorithm
- **Real-time Particle Systems**: Custom physics simulation

### Performance

- **Face Detection**: ~30 FPS on modern hardware
- **Particle Rendering**: 100+ particles with smooth performance
- **Memory Usage**: Optimized with automatic particle cleanup
- **Database Operations**: Async operations for smooth UI

## Future Enhancements

Potential improvements for this project:

- **Additional Pokémon**: Expand to all 151 original Pokémon
- **Hand Gesture Recognition**: Control particles with hand movements
- **3D Face Mesh**: Upgrade to MediaPipe for 3D facial landmarks
- **AR Effects**: Add augmented reality features
- **Mobile Version**: Port to iOS/Android using OpenCV mobile
- **Machine Learning**: Train custom models for better face detection
- **Multiplayer Mode**: Multiple users in same session
- **Video Recording**: Save interaction sessions as video files

## Credits

- **OpenCV**: Computer vision functionality
- **MongoDB**: Database storage and management
- **Pokémon**: Character designs by The Pokémon Company
- **Haar Cascades**: Face detection algorithms by Viola-Jones

## License

This project is for educational purposes. Pokémon characters and names are trademarks of The Pokémon Company.

## Version Information

- **OpenCV**: 4.11.0+
- **MongoDB C++ Driver**: 4.1.0
- **C++ Standard**: C++17
- **macOS**: Compatible with current versions
- **Xcode**: Command line tools required
