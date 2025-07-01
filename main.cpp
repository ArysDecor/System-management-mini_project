#include "Vehicle.h"
#include <vector>
#include <thread>
#include <memory>
#include <iostream>
#include <cstdlib> // pour std::system
#include <windows.h> // pour ShellExecute si besoin

// Nombre de véhicules simulés
const int NUM_VEHICLES = 10;

// Chemin absolu vers le script Python
const std::string PYTHON_SCRIPT_PATH = R"(C:\Users\h\Downloads\System-management-mini_project-main 1\System-management-mini_project-main\insert_data.py)";

int main() {
    std::cout << "=== Lancement de la simulation de flotte ===" << std::endl;
    std::cout << "Nombre de véhicules simulés : " << NUM_VEHICLES << std::endl;

    //  Lancer le script Python en parallèle
    std::string pythonCmd = "start \"PythonInsert\" python \"" + PYTHON_SCRIPT_PATH + "\"";
    int result = std::system(pythonCmd.c_str());
    if (result != 0) {
        std::cerr << "[Erreur] Le script Python n'a pas pu être lancé !" << std::endl;
    } else {
        std::cout << "[✓] Script Python lancé avec succès." << std::endl;
    }

    //  Initialisation des véhicules
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    std::vector<std::thread> vehicleThreads;

    for (int i = 0; i < NUM_VEHICLES; ++i) {
        vehicles.push_back(std::make_unique<Vehicle>(i));
    }

    //  Lancer les boucles de simulation dans des threads
    for (int i = 0; i < NUM_VEHICLES; ++i) {
        vehicleThreads.emplace_back(&Vehicle::runSimulationLoop, vehicles[i].get());
        std::cout << " Thread lancé pour le véhicule ID: " << vehicles[i]->getId() << std::endl;
    }

    std::cout << "\n[Simulation en cours...] Données enregistrées dans vehicle_<ID>.txt à chaque seconde." << std::endl;
    std::cout << "[Appuyez sur Ctrl+C pour arrêter.]" << std::endl;

    //  Join (pas obligatoire dans ce cas sauf si on veut bloquer le main thread)
    for (auto& th : vehicleThreads) {
        if (th.joinable()) {
            th.join();
        }
    }

    return 0;
}
