# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build"

# Include any dependencies generated for this target.
include CMakeFiles/wcd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wcd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wcd.dir/flags.make

CMakeFiles/wcd.dir/wcd.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/wcd.cc.o: ../wcd.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wcd.dir/wcd.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/wcd.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/wcd.cc"

CMakeFiles/wcd.dir/wcd.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/wcd.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/wcd.cc" > CMakeFiles/wcd.dir/wcd.cc.i

CMakeFiles/wcd.dir/wcd.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/wcd.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/wcd.cc" -o CMakeFiles/wcd.dir/wcd.cc.s

CMakeFiles/wcd.dir/src/ActionInitialization.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/ActionInitialization.cc.o: ../src/ActionInitialization.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wcd.dir/src/ActionInitialization.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/ActionInitialization.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/ActionInitialization.cc"

CMakeFiles/wcd.dir/src/ActionInitialization.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/ActionInitialization.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/ActionInitialization.cc" > CMakeFiles/wcd.dir/src/ActionInitialization.cc.i

CMakeFiles/wcd.dir/src/ActionInitialization.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/ActionInitialization.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/ActionInitialization.cc" -o CMakeFiles/wcd.dir/src/ActionInitialization.cc.s

CMakeFiles/wcd.dir/src/DetectorConstruction.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/DetectorConstruction.cc.o: ../src/DetectorConstruction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wcd.dir/src/DetectorConstruction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/DetectorConstruction.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/DetectorConstruction.cc"

CMakeFiles/wcd.dir/src/DetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/DetectorConstruction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/DetectorConstruction.cc" > CMakeFiles/wcd.dir/src/DetectorConstruction.cc.i

CMakeFiles/wcd.dir/src/DetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/DetectorConstruction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/DetectorConstruction.cc" -o CMakeFiles/wcd.dir/src/DetectorConstruction.cc.s

CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.o: ../src/HEPEvtInterface.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/HEPEvtInterface.cc"

CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/HEPEvtInterface.cc" > CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.i

CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/HEPEvtInterface.cc" -o CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.s

CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.o: ../src/HEPEvtParticle.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/HEPEvtParticle.cc"

CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/HEPEvtParticle.cc" > CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.i

CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/HEPEvtParticle.cc" -o CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.s

CMakeFiles/wcd.dir/src/PMTSD.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/PMTSD.cc.o: ../src/PMTSD.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/wcd.dir/src/PMTSD.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/PMTSD.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PMTSD.cc"

CMakeFiles/wcd.dir/src/PMTSD.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/PMTSD.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PMTSD.cc" > CMakeFiles/wcd.dir/src/PMTSD.cc.i

CMakeFiles/wcd.dir/src/PMTSD.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/PMTSD.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PMTSD.cc" -o CMakeFiles/wcd.dir/src/PMTSD.cc.s

CMakeFiles/wcd.dir/src/ParticleSource.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/ParticleSource.cc.o: ../src/ParticleSource.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/wcd.dir/src/ParticleSource.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/ParticleSource.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/ParticleSource.cc"

CMakeFiles/wcd.dir/src/ParticleSource.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/ParticleSource.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/ParticleSource.cc" > CMakeFiles/wcd.dir/src/ParticleSource.cc.i

CMakeFiles/wcd.dir/src/ParticleSource.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/ParticleSource.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/ParticleSource.cc" -o CMakeFiles/wcd.dir/src/ParticleSource.cc.s

CMakeFiles/wcd.dir/src/PhysicsList.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/PhysicsList.cc.o: ../src/PhysicsList.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/wcd.dir/src/PhysicsList.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/PhysicsList.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PhysicsList.cc"

CMakeFiles/wcd.dir/src/PhysicsList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/PhysicsList.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PhysicsList.cc" > CMakeFiles/wcd.dir/src/PhysicsList.cc.i

CMakeFiles/wcd.dir/src/PhysicsList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/PhysicsList.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PhysicsList.cc" -o CMakeFiles/wcd.dir/src/PhysicsList.cc.s

CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.o: ../src/PhysicsListMessenger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PhysicsListMessenger.cc"

CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PhysicsListMessenger.cc" > CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.i

CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PhysicsListMessenger.cc" -o CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.s

CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.o: ../src/PrimarySpectrum.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PrimarySpectrum.cc"

CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PrimarySpectrum.cc" > CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.i

CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/PrimarySpectrum.cc" -o CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.s

CMakeFiles/wcd.dir/src/RunAction.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/RunAction.cc.o: ../src/RunAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/wcd.dir/src/RunAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/RunAction.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/RunAction.cc"

CMakeFiles/wcd.dir/src/RunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/RunAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/RunAction.cc" > CMakeFiles/wcd.dir/src/RunAction.cc.i

CMakeFiles/wcd.dir/src/RunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/RunAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/RunAction.cc" -o CMakeFiles/wcd.dir/src/RunAction.cc.s

CMakeFiles/wcd.dir/src/StackingAction.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/StackingAction.cc.o: ../src/StackingAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/wcd.dir/src/StackingAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/StackingAction.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/StackingAction.cc"

CMakeFiles/wcd.dir/src/StackingAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/StackingAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/StackingAction.cc" > CMakeFiles/wcd.dir/src/StackingAction.cc.i

CMakeFiles/wcd.dir/src/StackingAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/StackingAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/StackingAction.cc" -o CMakeFiles/wcd.dir/src/StackingAction.cc.s

CMakeFiles/wcd.dir/src/SteppingAction.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/SteppingAction.cc.o: ../src/SteppingAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/wcd.dir/src/SteppingAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/SteppingAction.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/SteppingAction.cc"

CMakeFiles/wcd.dir/src/SteppingAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/SteppingAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/SteppingAction.cc" > CMakeFiles/wcd.dir/src/SteppingAction.cc.i

CMakeFiles/wcd.dir/src/SteppingAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/SteppingAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/SteppingAction.cc" -o CMakeFiles/wcd.dir/src/SteppingAction.cc.s

CMakeFiles/wcd.dir/src/SteppingVerbose.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/SteppingVerbose.cc.o: ../src/SteppingVerbose.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/wcd.dir/src/SteppingVerbose.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/SteppingVerbose.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/SteppingVerbose.cc"

CMakeFiles/wcd.dir/src/SteppingVerbose.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/SteppingVerbose.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/SteppingVerbose.cc" > CMakeFiles/wcd.dir/src/SteppingVerbose.cc.i

CMakeFiles/wcd.dir/src/SteppingVerbose.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/SteppingVerbose.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/SteppingVerbose.cc" -o CMakeFiles/wcd.dir/src/SteppingVerbose.cc.s

CMakeFiles/wcd.dir/src/TrackingAction.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/TrackingAction.cc.o: ../src/TrackingAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/wcd.dir/src/TrackingAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/TrackingAction.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/TrackingAction.cc"

CMakeFiles/wcd.dir/src/TrackingAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/TrackingAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/TrackingAction.cc" > CMakeFiles/wcd.dir/src/TrackingAction.cc.i

CMakeFiles/wcd.dir/src/TrackingAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/TrackingAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/TrackingAction.cc" -o CMakeFiles/wcd.dir/src/TrackingAction.cc.s

CMakeFiles/wcd.dir/src/UserEventAction.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/UserEventAction.cc.o: ../src/UserEventAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/wcd.dir/src/UserEventAction.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/UserEventAction.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/UserEventAction.cc"

CMakeFiles/wcd.dir/src/UserEventAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/UserEventAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/UserEventAction.cc" > CMakeFiles/wcd.dir/src/UserEventAction.cc.i

CMakeFiles/wcd.dir/src/UserEventAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/UserEventAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/UserEventAction.cc" -o CMakeFiles/wcd.dir/src/UserEventAction.cc.s

CMakeFiles/wcd.dir/src/photonCounter.cc.o: CMakeFiles/wcd.dir/flags.make
CMakeFiles/wcd.dir/src/photonCounter.cc.o: ../src/photonCounter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/wcd.dir/src/photonCounter.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wcd.dir/src/photonCounter.cc.o -c "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/photonCounter.cc"

CMakeFiles/wcd.dir/src/photonCounter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wcd.dir/src/photonCounter.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/photonCounter.cc" > CMakeFiles/wcd.dir/src/photonCounter.cc.i

CMakeFiles/wcd.dir/src/photonCounter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wcd.dir/src/photonCounter.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/src/photonCounter.cc" -o CMakeFiles/wcd.dir/src/photonCounter.cc.s

# Object files for target wcd
wcd_OBJECTS = \
"CMakeFiles/wcd.dir/wcd.cc.o" \
"CMakeFiles/wcd.dir/src/ActionInitialization.cc.o" \
"CMakeFiles/wcd.dir/src/DetectorConstruction.cc.o" \
"CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.o" \
"CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.o" \
"CMakeFiles/wcd.dir/src/PMTSD.cc.o" \
"CMakeFiles/wcd.dir/src/ParticleSource.cc.o" \
"CMakeFiles/wcd.dir/src/PhysicsList.cc.o" \
"CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.o" \
"CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.o" \
"CMakeFiles/wcd.dir/src/RunAction.cc.o" \
"CMakeFiles/wcd.dir/src/StackingAction.cc.o" \
"CMakeFiles/wcd.dir/src/SteppingAction.cc.o" \
"CMakeFiles/wcd.dir/src/SteppingVerbose.cc.o" \
"CMakeFiles/wcd.dir/src/TrackingAction.cc.o" \
"CMakeFiles/wcd.dir/src/UserEventAction.cc.o" \
"CMakeFiles/wcd.dir/src/photonCounter.cc.o"

# External object files for target wcd
wcd_EXTERNAL_OBJECTS =

wcd: CMakeFiles/wcd.dir/wcd.cc.o
wcd: CMakeFiles/wcd.dir/src/ActionInitialization.cc.o
wcd: CMakeFiles/wcd.dir/src/DetectorConstruction.cc.o
wcd: CMakeFiles/wcd.dir/src/HEPEvtInterface.cc.o
wcd: CMakeFiles/wcd.dir/src/HEPEvtParticle.cc.o
wcd: CMakeFiles/wcd.dir/src/PMTSD.cc.o
wcd: CMakeFiles/wcd.dir/src/ParticleSource.cc.o
wcd: CMakeFiles/wcd.dir/src/PhysicsList.cc.o
wcd: CMakeFiles/wcd.dir/src/PhysicsListMessenger.cc.o
wcd: CMakeFiles/wcd.dir/src/PrimarySpectrum.cc.o
wcd: CMakeFiles/wcd.dir/src/RunAction.cc.o
wcd: CMakeFiles/wcd.dir/src/StackingAction.cc.o
wcd: CMakeFiles/wcd.dir/src/SteppingAction.cc.o
wcd: CMakeFiles/wcd.dir/src/SteppingVerbose.cc.o
wcd: CMakeFiles/wcd.dir/src/TrackingAction.cc.o
wcd: CMakeFiles/wcd.dir/src/UserEventAction.cc.o
wcd: CMakeFiles/wcd.dir/src/photonCounter.cc.o
wcd: CMakeFiles/wcd.dir/build.make
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4Tree.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4FR.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4GMocren.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4visHepRep.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4RayTracer.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4VRML.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4OpenGL.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4gl2ps.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4vis_management.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4modeling.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4interfaces.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4persistency.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4error_propagation.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4readout.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4physicslists.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4tasking.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4parmodels.so
wcd: /usr/lib/x86_64-linux-gnu/libXmu.so
wcd: /usr/lib/x86_64-linux-gnu/libXext.so
wcd: /usr/lib/x86_64-linux-gnu/libXt.so
wcd: /usr/lib/x86_64-linux-gnu/libICE.so
wcd: /usr/lib/x86_64-linux-gnu/libSM.so
wcd: /usr/lib/x86_64-linux-gnu/libX11.so
wcd: /usr/lib/x86_64-linux-gnu/libGL.so
wcd: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.12.8
wcd: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.12.8
wcd: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.12.8
wcd: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.12.8
wcd: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
wcd: /usr/lib/x86_64-linux-gnu/libxerces-c.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4run.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4event.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4tracking.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4processes.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4analysis.so
wcd: /usr/lib/x86_64-linux-gnu/libexpat.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4digits_hits.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4track.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4particles.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4geometry.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4materials.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4zlib.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4graphics_reps.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4intercoms.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4global.so
wcd: /home/josue/Geant4/geant4-v10.7.4-install/lib/libG4ptl.so.0.0.2
wcd: /home/josue/CLHEP/2.4.7.1/CLHEP/CLHEP-install/lib/libCLHEP-2.4.7.1.so
wcd: CMakeFiles/wcd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable wcd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wcd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wcd.dir/build: wcd

.PHONY : CMakeFiles/wcd.dir/build

CMakeFiles/wcd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wcd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wcd.dir/clean

CMakeFiles/wcd.dir/depend:
	cd "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source" "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source" "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build" "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build" "/home/josue/Desktop/Avances simulacion/Avances/wcd_particle_source/build/CMakeFiles/wcd.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/wcd.dir/depend
