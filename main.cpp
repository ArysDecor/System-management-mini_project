#include "Vehicle.h"
#include <vector>
#include <thread>
#include <memory>
#include <iostream>

const int NUM_VEHICLES = 10;

int main() {
    std::cout << "=== Lancement de la simulation de flotte ===" << std::endl;
    std::cout << "Nombre de véhicules simulés : " << NUM_VEHICLES << std::endl;

    std::vector<std::unique_ptr<Vehicle>> vehicles;
    std::vector<std::thread> vehicleThreads;

    // Création des objets Vehicle
    for (int i = 0; i < NUM_VEHICLES; ++i) {
        vehicles.push_back(std::make_unique<Vehicle>(i));
    }

    // Lancement d’un thread pour chaque véhicule
    for (int i = 0; i < NUM_VEHICLES; ++i) {
        vehicleThreads.emplace_back(&Vehicle::runSimulationLoop, vehicles[i].get());
        std::cout << " Thread lancé pour le véhicule ID: " << vehicles[i]->getId() << std::endl;
    }

    std::cout << "\nSimulation en cours. Données écrites dans vehicle_<ID>.txt toutes les secondes." << std::endl;
    std::cout << "Appuyez sur Ctrl+C pour arrêter." << std::endl;

    // Attente des threads (jamais atteinte si boucle infinie)
    for (auto& th : vehicleThreads) {
        if (th.joinable()) {
            th.join();
        }
    }

    return 0;
}
