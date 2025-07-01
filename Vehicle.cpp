#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Constructeur
Vehicle::Vehicle(int id) : id_(id) {
    dataFileName_ = "vehicle_" + std::to_string(id_) + ".txt";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() + id;
    randomEngine_.seed(seed);
    initializeState();
}

// Initialisation réaliste des états initiaux
void Vehicle::initializeState() {
    speed_ = generateRandomDouble(0.0, 100.0);
    engineTemp_ = generateRandomDouble(70.0, 90.0);
    batteryVoltage_ = generateRandomDouble(12.5, 14.2);
    fuelLevel_ = generateRandomDouble(40.0, 100.0);
    for (int i = 0; i < 4; ++i)
        tirePressure_[i] = generateRandomDouble(30.5, 34.5);
    engineRPM_ = static_cast<int>(speed_ * 40);
    totalMileage_ = generateRandomDouble(1000, 200000);
    avgConsumption_ = generateRandomDouble(5.0, 10.0);
    oilLevel_ = generateRandomDouble(60.0, 100.0);
    brakeWear_ = generateRandomDouble(0.0, 40.0);
    brakeFluidTemp_ = generateRandomDouble(30.0, 60.0);
    brakeFluidLevel_ = generateRandomDouble(70.0, 100.0);
    headlightsOn_ = (rand() % 2 == 0);
    dtcCode_ = "P0000";
    externalTemp_ = generateRandomDouble(5.0, 35.0);
    smokeDetected_ = false;
    vibrationLevel_ = generateRandomDouble(0.1, 1.0);
}

// Génération réaliste et progressive
void Vehicle::updateData() {
    double targetSpeed = generateRandomDouble(0.0, 120.0);
    speed_ = approach(speed_, targetSpeed, 5.0);

    engineRPM_ = static_cast<int>(speed_ * 40 + generateRandomDouble(-100, 100));

    double targetEngineTemp = 70.0 + (engineRPM_ / 100.0);
    engineTemp_ = approach(engineTemp_, targetEngineTemp, 0.5);

    double targetVoltage = generateRandomDouble(12.0, 14.5);
    batteryVoltage_ = approach(batteryVoltage_, targetVoltage, 0.05);

    fuelLevel_ = std::max(0.0, fuelLevel_ - generateRandomDouble(0.01, 0.05));

    for (int i = 0; i < 4; ++i) {
        tirePressure_[i] = approach(tirePressure_[i], tirePressure_[i] + generateRandomDouble(-0.02, 0.02), 0.02);
    }

    totalMileage_ += speed_ / 3600.0;

    avgConsumption_ = std::max(3.0, approach(avgConsumption_, avgConsumption_ + generateRandomDouble(-0.05, 0.05), 0.05));

    oilLevel_ = std::max(0.0, oilLevel_ - generateRandomDouble(0.001, 0.005));

    brakeWear_ = std::min(100.0, brakeWear_ + generateRandomDouble(0.01, 0.1));

    double targetBrakeTemp = 30.0 + (speed_ / 3.0);
    brakeFluidTemp_ = approach(brakeFluidTemp_, targetBrakeTemp, 0.3);

    brakeFluidLevel_ = std::max(0.0, brakeFluidLevel_ - generateRandomDouble(0.005, 0.02));

    headlightsOn_ = (rand() % 100 < 50);

    if (engineTemp_ > 105.0 || oilLevel_ < 30.0 || brakeFluidLevel_ < 40.0 || batteryVoltage_ < 11.8) {
        dtcCode_ = "P0420";
    } else {
        dtcCode_ = "P0000";
    }

    externalTemp_ = approach(externalTemp_, externalTemp_ + generateRandomDouble(-0.2, 0.2), 0.2);

    smokeDetected_ = (engineTemp_ > 110.0 && brakeWear_ > 70.0) || (rand() % 100 < 2);

    double baseVibration = 0.1 + (brakeWear_ / 100.0) + generateRandomDouble(0.0, 0.2);
    vibrationLevel_ = std::min(3.0, baseVibration);
}

// Sauvegarde dans le fichier
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

// Boucle de simulation
void Vehicle::runSimulationLoop() {
    std::ofstream outFile(dataFileName_, std::ios::trunc);
    outFile.close();

    while (true) {
        updateData();
        writeDataToFile();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Générateur aléatoire
double Vehicle::generateRandomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(randomEngine_);
}

// Transition progressive
double Vehicle::approach(double current, double target, double maxChange) {
    if (std::abs(current - target) <= maxChange)
        return target;
    return current + (target > current ? maxChange : -maxChange);
}

// Getter ID
int Vehicle::getId() const {
    return id_;
}
