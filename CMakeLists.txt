# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Déclaration du projet
project(VehicleSimulation LANGUAGES CXX)

# Spécifie que l'on utilise le standard C++17 sans extensions spécifiques
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

# Ajout des fichiers source et en-tête à l'exécutable
add_executable(VehicleSim main.cpp Vehicle.cpp Vehicle.h)

# Recherche la bibliothèque des threads (portable entre Windows/Linux)
find_package(Threads REQUIRED)
target_link_libraries(VehicleSim PRIVATE Threads::Threads)

# Ajout des options de compilation en fonction du compilateur
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(VehicleSim PRIVATE -Wall -Wextra -Wpedantic) # Warnings utiles
elseif(MSVC)
    target_compile_options(VehicleSim PRIVATE /W4) # Niveau d’avertissement maximal sur Visual Studio
endif()

# Installe l'exécutable dans le dossier `bin`
install(TARGETS VehicleSim DESTINATION bin)

# Affichage de quelques informations utiles à la compilation
message(STATUS "Configuring VehicleSimulation project")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Pthreads library found: ${Threads_FOUND}")
