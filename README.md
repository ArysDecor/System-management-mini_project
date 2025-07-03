
```markdown
# Vehicle Simulation System

Ce projet simule une flotte de véhicules connectés, chacun exécuté dans un thread distinct, générant des données en temps réel sur l’état de ses capteurs. Il s’agit d’un système de base pour le prototypage de solutions de fleet management, ADAS, ou d’analyse de données embarquées IoT.

---

##  Objectifs

- Simuler une flotte de véhicules (multi-threading)
- Générer dynamiquement des données (vitesse, température moteur, tension batterie, etc.)
- Écrire les données dans des fichiers texte (`vehicle_<ID>.txt`)
- Insérer les données en temps réel dans une base SQLite
- Fournir une base extensible pour des systèmes de télémétrie, diagnostic ou visualisation

---

##  Fonctionnalités principales

-  Multi-threading C++ (`std::thread`)
-  Génération réaliste de données aléatoires
-  Mise à jour des données toutes les secondes
-  Écriture structurée dans des fichiers `.txt`
-  Stockage automatique dans une base **SQLite** (`fleetdata.db`)
-  Architecture modulaire (classe `Vehicle`)
-  Simulation de DTC, fumée, vibrations, pression des pneus, etc.
-  Lancement automatique du script Python d’insertion depuis `main.cpp`
-  Champ `total_mileage` (kilométrage total) disponible dans la simulation

---

##  Structure du projet

```

VehicleSimulation/
├── CMakeLists.txt            # Fichier de configuration CMake
├── main.cpp                  # Point d’entrée de l’application
├── Vehicle.cpp               # Implémentation de la classe Vehicle
├── Vehicle.h                 # Déclaration de la classe Vehicle
├── insert\_data.py            # Script Python d’insertion dans SQLite
└── README.md                 # Ce fichier

````

---

##  Prérequis

- CMake ≥ 3.10
- Compilateur C++ compatible C++17 (GCC, Clang, MSVC)
- Python 3.7+ avec module `sqlite3`
- Threads POSIX ou Windows (`std::thread`)
- SQLite intégré (pas besoin d’installation supplémentaire)

---

##  Compilation (Windows)

```bash
# Cloner le dépôt
git clone https://github.com/ArysDecor/System-management-mini_project
cd System-management-mini_project

# Créer le dossier de build
mkdir build && cd build

# Générer le projet avec CMake
cmake ..

# Compiler
cmake --build .

# Lancer le simulateur (dans le dossier Debug ou Release)
cd Debug
VehicleSim.exe
````

---

## ▶ Utilisation

* L’application simule 10 véhicules avec un thread chacun.
* Chaque véhicule écrit dans `vehicle_<ID>.txt` dans `build/Debug/`
* Les données sont mises à jour toutes les **secondes**
* Le script Python `insert_data.py` est lancé automatiquement en parallèle depuis le C++
* Appuyez sur `Ctrl + C` pour interrompre proprement

---

##  Exemple de ligne de données générée

```
2025-07-01 10:22:10 | ID: 3, Speed: 92.3 km/h, RPM: 3250, Battery: 13.1 V, Fuel: 47.2%, Tires: [2.31, 2.29, 2.28, 2.30] psi, Oil: 80.5%, BrakeWear: 5.2%, BrakeFluidTemp: 90.0 C, BrakeFluidLevel: 96.3%, Lights: ON, DTC: P0420, ExtTemp: 27.5 C, Smoke: NO, Vibration: 0.45 g
```

---

##  Base de données SQLite

* Fichier : `fleetdata.db`
* Gérée automatiquement par `insert_data.py`

### Tables :

#### `drivers`

| Colonne         | Type    | Description       |
| --------------- | ------- | ----------------- |
| driver\_id      | INTEGER | ID du conducteur  |
| name            | TEXT    | Nom du conducteur |
| license\_number | TEXT    | Numéro de permis  |
| phone           | TEXT    | Téléphone         |

#### `vehicle_data`

| Colonne                    | Type    | Description                    |
| -------------------------- | ------- | ------------------------------ |
| id                         | INTEGER | ID du véhicule                 |
| driver\_id                 | INTEGER | ID du conducteur associé       |
| timestamp                  | TEXT    | Date et heure                  |
| speed                      | REAL    | Vitesse (km/h)                 |
| rpm                        | INTEGER | Régime moteur (RPM)            |
| battery                    | REAL    | Tension batterie (V)           |
| fuel                       | REAL    | Niveau de carburant (%)        |
| tire1, tire2, tire3, tire4 | REAL    | Pression pneus (psi)           |
| oil                        | REAL    | Niveau d’huile moteur (%)      |
| brake\_wear                | REAL    | Usure des freins (%)           |
| brake\_fluid\_temp         | REAL    | Température liquide frein (°C) |
| brake\_fluid\_level        | REAL    | Niveau liquide frein (%)       |
| lights                     | TEXT    | État des phares (ON/OFF)       |
| dtc                        | TEXT    | Code défaut OBD (DTC)          |
| external\_temp             | REAL    | Température extérieure (°C)    |
| smoke                      | TEXT    | Présence de fumée (YES/NO)     |
| vibration                  | REAL    | Niveau de vibration (g)        |

