Vehicle Simulation System

Ce projet simule une flotte de véhicules connectés, chacun exécuté dans un thread distinct, générant des données en temps réel sur l’état de ses capteurs. Il s’agit d’un système de base pour le prototypage de solutions de fleet management, ADAS, ou d’analyse de données embarquées IoT.
Objectifs

    Simuler une flotte de véhicules (multithreadée)

    Générer dynamiquement des données (vitesse, température moteur, tension batterie, etc.)

    Écrire les données dans des fichiers texte (un par véhicule)

    Stocker les données dans une base SQLite en temps réel

    Fournir une base extensible pour des systèmes de télémétrie, de diagnostic ou de visualisation

Fonctionnalités principales

    ✅ Multi-threading C++ (std::thread)

    ✅ Génération réaliste de données aléatoires

    ✅ Mise à jour des données toutes les secondes

    ✅ Écriture structurée dans des fichiers .txt

    ✅ Stockage automatique dans une base SQLite (fleetdata.db)

    ✅ Architecture modulaire (classe Vehicle)

    ✅ Ajout du champ total_mileage (kilométrage total)

    ✅ Compatible Windows / Linux

Structure du projet

VehicleSimulation/
├── CMakeLists.txt            # Fichier de configuration CMake
├── main.cpp                  # Point d’entrée de l’application
├── Vehicle.cpp               # Implémentation de la classe Vehicle
├── Vehicle.h                 # Déclaration de la classe Vehicle
├── insert_data.py            # Script Python de lecture/insertion SQLite
└── README.md                 # Ce fichier

Prérequis

    CMake ≥ 3.10

    Compilateur C++ compatible C++17 (GCC, Clang, MSVC) ou Visual Studio 2022

    Python 3.7+ avec module sqlite3

    Threads POSIX ou Windows (std::thread)

Compilation (Windows avec CMake / Visual Studio)

# Cloner le dépôt
git clone https://github.com/ArysDecor/System-management-mini_project
cd System-management-mini_project

# Créer le dossier de build
mkdir build && cd build

# Générer les fichiers du projet
cmake ..

# Compiler
cmake --build .

# Aller dans le dossier contenant l’exécutable
cd Debug

# Lancer la simulation
VehicleSim.exe

Utilisation

    L’application lance une boucle de simulation multithreadée pour chaque véhicule.

    Les fichiers vehicle_0.txt, vehicle_1.txt, etc. sont générés dans le dossier build/Debug/

    Les données sont mises à jour chaque seconde.

    Appuyez sur Ctrl+C pour arrêter la simulation manuellement.

Données générées

Chaque véhicule écrit ses données dans un fichier vehicle_<ID>.txt (exemple : vehicle_3.txt).

Une ligne typique :

2025-07-01 10:22:10 | ID: 3, Speed: 92.3 km/h, RPM: 3250, Battery: 13.1 V, Fuel: 47.2%, Tires: [2.31, 2.29, 2.28, 2.30] psi, Oil: 80.5%, BrakeWear: 5.2%, BrakeFluidTemp: 90.0 C, BrakeFluidLevel: 96.3%, Lights: ON, DTC: P0420, ExtTemp: 27.5 C, Smoke: NO, Vibration: 0.45 g, Mileage: 15342.8

Insertion en base SQLite

Un script Python insert_data.py est fourni pour :

    Lire en temps réel tous les fichiers vehicle_<ID>.txt

    Parser chaque ligne et insérer les données dans fleetdata.db

    Gérer jusqu’à 10 véhicules en parallèle

Base SQLite : fleetdata.db
Table : vehicle_data
Colonne	Type	Description
id	INTEGER	ID du véhicule
driver_id	INTEGER	ID du conducteur associé
timestamp	TEXT	Date et heure
speed	REAL	Vitesse (km/h)
rpm	INTEGER	Régime moteur (RPM)
battery	REAL	Tension batterie (V)
fuel	REAL	Niveau de carburant (%)
tire1, tire2, tire3, tire4	REAL	Pression des pneus (psi)
oil	REAL	Niveau d’huile moteur (%)
brake_wear	REAL	Usure des freins (%)
brake_fluid_temp	REAL	Température liquide frein (°C)
brake_fluid_level	REAL	Niveau liquide frein (%)
lights	TEXT	État des phares (ON/OFF)
dtc	TEXT	Code défaut OBD (DTC)
external_temp	REAL	Température extérieure (°C)
smoke	TEXT	Présence de fumée (YES/NO)
vibration	REAL	Niveau de vibration (g)
