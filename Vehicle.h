#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>

class Vehicle {
public:
    Vehicle(int id);                 // Constructeur avec ID

    void updateData();              // Met à jour les données de simulation
    void writeDataToFile() const;   // Écrit les données dans un fichier
    void runSimulationLoop();       // Boucle infinie de simulation

    int getId() const;              // Récupère l'ID du véhicule

private:
    int id_;                        // Identifiant du véhicule
    std::string dataFileName_;      // Nom du fichier de sortie
    std::mt19937 randomEngine_;     // Générateur de nombres aléatoires

    // Données simulées
    double speed_;                  // Vitesse (km/h)
    double engineTemp_;             // Température moteur
    double batteryVoltage_;         // Tension batterie
    double fuelLevel_;              // Carburant (%)
    double tirePressure_[4];        // Pression pneus (4 roues)
    int engineRPM_;                 // Régime moteur
    double totalMileage_;           // Kilométrage
    double avgConsumption_;         // Consommation moyenne
    double oilLevel_;               // Niveau d'huile
    double brakeWear_;              // Usure des freins
    double brakeFluidTemp_;         // Température liquide de frein
    double brakeFluidLevel_;        // Niveau liquide de frein
    bool headlightsOn_;             // État des phares
    std::string dtcCode_;           // Code défaut moteur
    double externalTemp_;           // Température extérieure
    bool smokeDetected_;            // Détection de fumée
    double vibrationLevel_;         // Niveau de vibration

    void initializeState();                             // Initialise les valeurs aléatoires
    double generateRandomDouble(double min, double max); // Générateur de doubles aléatoires
};

#endif // VEHICLE_H
