#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>

class Vehicle {
public:
    Vehicle(int id);

    void updateData();
    void writeDataToFile() const;
    void runSimulationLoop();

    // Getters
    int getId() const;

private:
    int id_;
    std::string dataFileName_;
    std::mt19937 randomEngine_;

    // Données simulées
    double speed_;               // a. Vitesse (km/h)
    double engineTemp_;          // b. Température moteur (°C)
    double batteryVoltage_;      // c. Tension batterie (V)
    double fuelLevel_;           // d. Niveau de carburant (%)
    double tirePressure_[4];     // e. Pression des pneus (psi) par roue
    int engineRPM_;              // f. Régime moteur (tr/min)
    double totalMileage_;        // g. Kilométrage total (km)
    double avgConsumption_;      // h. Consommation moyenne (L/100km)
    double oilLevel_;            // i. Niveau d’huile moteur (%)
    double brakeWear_;           // j. Usure des freins (%)
    double brakeFluidTemp_;      // k. Température liquide frein (°C)
    double brakeFluidLevel_;     // l. Niveau liquide frein (%)
    bool headlightsOn_;          // m. État des phares/clignotants (ON/OFF)
    std::string dtcCode_;        // n. Code défaut moteur (OBD simulé)
    double externalTemp_;        // o. Température extérieure (°C)
    bool smokeDetected_;         // p. Présence de fumée
    double vibrationLevel_;      // q. Niveau de vibrations (indice/g)

    void initializeState();
    double generateRandomDouble(double min, double max);
};

#endif // VEHICLE_H