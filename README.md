# 🚗 Vehicle Simulation System

Ce projet simule une flotte de véhicules connectés, chacun exécuté dans un thread distinct, générant des données en temps réel sur l’état de ses capteurs. Il s’agit d’un système de base pour le prototypage de solutions de **fleet management**, **ADAS**, ou d’analyse de **données embarquées IoT**.

---

## 📌 Objectifs

- Simuler une flotte de véhicules (multithreadée)
- Générer dynamiquement des données (vitesse, température moteur, tension batterie, etc.)
- Écrire les données dans des fichiers texte (un par véhicule)
- Fournir une base extensible pour des systèmes de télémétrie, de diagnostic ou de visualisation

---

## 🧩 Fonctionnalités principales

- ✅ Multi-threading C++ (`std::thread`)
- ✅ Génération réaliste de données aléatoires
- ✅ Mise à jour des données toutes les secondes
- ✅ Écriture structurée dans des fichiers `.txt`
- ✅ Architecture modulaire (classe `Vehicle`)
- ✅ Compatible Windows / Linux

---

## 📁 Structure du projet

VehicleSimulation/
├── CMakeLists.txt # Fichier de configuration CMake
├── main.cpp # Point d’entrée de l’application
├── Vehicle.cpp # Implémentation de la classe Vehicle
├── Vehicle.h # Déclaration de la classe Vehicle
└── README.md # Ce fichier

yaml
Copier
Modifier

---

## 🛠️ Prérequis

- **CMake ≥ 3.10**
- **Compilateur C++ compatible C++17** (GCC, Clang ou MSVC) / VS code version 2022 
- **Threads POSIX ou Windows (std::thread)**

---

## 🔧 Installation et compilation

### ✅ Étapes sous Windows (MinGW ou Visual Studio)

```bash
# 1. Cloner le dépôt
git clone https://github.com/votre-utilisateur/VehicleSimulation.git
cd VehicleSimulation

# 2. Créer le dossier de build
mkdir build && cd build

# 3. Générer les fichiers du projet
cmake ..

# 4. Compiler
cmake --build .

# 5. Aller dans le dossier contenant l’exécutable
cd Debug

# 6. Lancer la simulation
VehicleSim.exe
📂 L’exécutable est généré dans build/Debug/VehicleSim.exe

👨‍💻 Utilisation
Une fois compilé, exécutez la simulation :

bash
Copier
Modifier
cd build/Debug
VehicleSim.exe
L'application lance une boucle infinie de simulation pour chaque véhicule.

Les fichiers vehicle_0.txt, vehicle_1.txt, … sont créés dans le même dossier.

Appuyez sur Ctrl+C pour arrêter la simulation manuellement.

📤 Données générées
Chaque véhicule écrit ses données dans un fichier vehicle_<ID>.txt (par exemple vehicle_3.txt).
Mise à jour : toutes les secondes.

Les informations enregistrées incluent :

🛣️ Vitesse (km/h)

🔁 Régime moteur (RPM)

🔋 Tension batterie (V)

⛽ Carburant restant (%)

🚗 Pression des pneus (4 roues)

🛢️ Niveau d’huile moteur

🧯 Température et niveau du liquide de frein

🧠 Code DTC simulé (OBD) : P0000, P0420, etc.

🌡️ Température extérieure

🚬 Présence de fumée

📳 Niveau de vibration (g)

Exemple d’une ligne de sortie :

2025-06-26 12:03:01 | ID: 0, Speed: 75.45 km/h, RPM: 3018, Battery: 13.25 V, ...

