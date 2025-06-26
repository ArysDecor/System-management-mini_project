#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib> // pour rand()
#include <ctime>   // pour std::time_t

Vehicle::Vehicle(int id) : id_(id) {
    dataFileName_ = "vehicle_" + std::to_string(id_) + ".txt";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() + id;
    randomEngine_.seed(seed);
    initializeState();
}

void Vehicle::initializeState() {
    speed_ = generateRandomDouble(0.0, 100.0);
    engineTemp_ = generateRandomDouble(60.0, 100.0);
    batteryVoltage_ = generateRandomDouble(12.0, 14.5);
    fuelLevel_ = generateRandomDouble(30.0, 100.0);
    for (int i = 0; i < 4; ++i)
        tirePressure_[i] = generateRandomDouble(30.0, 35.0);
    engineRPM_ = static_cast<int>(generateRandomDouble(800, 4000));
    totalMileage_ = generateRandomDouble(1000, 200000);
    avgConsumption_ = generateRandomDouble(5.0, 12.0);
    oilLevel_ = generateRandomDouble(60.0, 100.0);
    brakeWear_ = generateRandomDouble(0.0, 80.0);
    brakeFluidTemp_ = generateRandomDouble(30.0, 90.0);
    brakeFluidLevel_ = generateRandomDouble(60.0, 100.0);
    headlightsOn_ = (rand() % 2 == 0);
    dtcCode_ = "P0000";
    externalTemp_ = generateRandomDouble(-10.0, 40.0);
    smokeDetected_ = (rand() % 10 == 0);
    vibrationLevel_ = generateRandomDouble(0.1, 1.5);
}

double Vehicle::generateRandomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(randomEngine_);
}

void Vehicle::updateData() {
    speed_ = generateRandomDouble(0.0, 120.0);
    engineTemp_ = generateRandomDouble(70.0, 110.0);
    batteryVoltage_ = generateRandomDouble(11.5, 14.8);
    fuelLevel_ = std::max(0.0, fuelLevel_ - generateRandomDouble(0.01, 0.05));
    for (int i = 0; i < 4; ++i)
        tirePressure_[i] += generateRandomDouble(-0.1, 0.1);
    engineRPM_ = static_cast<int>(speed_ * 40);
    totalMileage_ += speed_ / 3600.0;
    avgConsumption_ += generateRandomDouble(-0.05, 0.05);
    oilLevel_ -= generateRandomDouble(0.001, 0.01);
    brakeWear_ += generateRandomDouble(0.01, 0.1);
    brakeFluidTemp_ += generateRandomDouble(-1.0, 1.0);
    brakeFluidLevel_ -= generateRandomDouble(0.01, 0.05);
    headlightsOn_ = (rand() % 100 < 50);
    dtcCode_ = (rand() % 100 < 5) ? "P0420" : "P0000";
    externalTemp_ += generateRandomDouble(-0.2, 0.2);
    smokeDetected_ = (rand() % 100 < 2);
    vibrationLevel_ = generateRandomDouble(0.1, 2.0);
}

void Vehicle::writeDataToFile() const {
    std::ofstream outFile(dataFileName_, std::ios::app);
    if (outFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        outFile << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << " | "
                << "ID: " << id_ << ", "
                << "Speed: " << std::fixed << std::setprecision(2) << speed_ << " km/h, "
                << "RPM: " << engineRPM_ << ", "
                << "Battery: " << batteryVoltage_ << " V, "
                << "Fuel: " << fuelLevel_ << "%, "
                << "Tires: [" << tirePressure_[0] << ", " << tirePressure_[1] << ", "
                << tirePressure_[2] << ", " << tirePressure_[3] << "] psi, "
                << "Oil: " << oilLevel_ << "%, "
                << "BrakeWear: " << brakeWear_ << "%, "
                << "BrakeFluidTemp: " << brakeFluidTemp_ << " C, "
                << "BrakeFluidLevel: " << brakeFluidLevel_ << "%, "
                << "Lights: " << (headlightsOn_ ? "ON" : "OFF") << ", "
                << "DTC: " << dtcCode_ << ", "
                << "ExtTemp: " << externalTemp_ << " C, "
                << "Smoke: " << (smokeDetected_ ? "YES" : "NO") << ", "
                << "Vibration: " << vibrationLevel_ << " g"
                << std::endl;
        outFile.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour le véhicule " << id_ << std::endl;
    }
}

void Vehicle::runSimulationLoop() {
    // Efface le fichier au démarrage
    std::ofstream outFile(dataFileName_, std::ios::trunc);
    outFile.close();

    while (true) {
        updateData();
        writeDataToFile();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int Vehicle::getId() const {
    return id_;
}
