# 🚗 Vehicle Simulation System

Ce projet simule une flotte de véhicules connectés, chacun exécuté dans un thread distinct, générant des données en temps réel sur l’état de ses capteurs. Il sert de base pour le prototypage de solutions de fleet management, ADAS, ou d’analyse de données embarquées IoT.

---

## 📌 Objectifs

* Simuler une flotte de véhicules (multi-threading)
* Générer dynamiquement des données (vitesse, température moteur, tension batterie, etc.)
* Écrire les données dans des fichiers texte (`vehicle_<ID>.txt`)
* Insérer les données en temps réel dans une base SQLite
* Interroger et manipuler la base depuis Java
* Fournir une base extensible pour la télémétrie, le diagnostic ou la visualisation

---

## 🧹 Fonctionnalités principales

* ✅ Multi-threading C++ (`std::thread`)
* ✅ Génération réaliste de données aléatoires
* ✅ Écriture structurée dans des fichiers `.txt`
* ✅ Stockage automatique dans une base **SQLite** (`fleetdata.db`)
* ✅ Lancement automatique du script Python d’insertion depuis `main.cpp`
* ✅ Ajout du champ `total_mileage` (kilométrage total)
* ✅ Structure relationnelle avec table `drivers`
* ✅ Connexion Java ↔ SQLite via JDBC (`sqlite-jdbc`)
* ✅ Compatible Windows / Linux

---

## 📁 Structure du projet

```
VehicleSimulation/
├── CMakeLists.txt        # Configuration CMake
├── main.cpp              # Entrée de l’application C++
├── Vehicle.cpp/h         # Classe Vehicle simulée
├── insert_data.py        # Script Python : insertion en temps réel
├── ReadFleetData.java    # Exemple Java : lecture base SQLite
└── README.md             # Ce fichier
```

---

## 🛠️ Prérequis

* CMake ≥ 3.10
* Compilateur C++ compatible C++17
* Python 3.7+ avec `sqlite3` (et `watchdog` pour surveillance)
* Java ≥ 8
* JDBC driver : `sqlite-jdbc`
* SQLite intégré

---

## ⚙️ Compilation & Simulation

```bash
git clone https://github.com/ArysDecor/System-management-mini_project
cd System-management-mini_project
mkdir build && cd build
cmake ..
cmake --build .
cd Debug
VehicleSim.exe
```

---

## 💻 Utilisation

* Chaque véhicule génère un fichier `vehicle_<ID>.txt`
* Les données sont mises à jour toutes les secondes
* Le script Python insère les données en temps réel dans `fleetdata.db`
* Les données sont disponibles pour consultation via Java ou autres langages

---

## 🤺 Exemple de données générées

```
2025-07-01 10:22:10 | ID: 3, Speed: 92.3 km/h, RPM: 3250, Battery: 13.1 V,
Fuel: 47.2%, Tires: [2.31, 2.29, 2.28, 2.30] psi, Oil: 80.5%,
BrakeWear: 5.2%, BrakeFluidTemp: 90.0 C, BrakeFluidLevel: 96.3%,
Lights: ON, DTC: P0420, ExtTemp: 27.5 C, Smoke: NO, Vibration: 0.45 g,
Mileage: 15342.8
```

---

## 📃 Base de données SQLite

Nom du fichier : `fleetdata.db`

### Tables :

#### 🔹 drivers

| Colonne         | Type    | Description             |
| --------------- | ------- | ----------------------- |
| driver\_id      | INTEGER | ID du conducteur        |
| name            | TEXT    | Nom du conducteur       |
| license\_number | TEXT    | Numéro de permis        |
| phone           | TEXT    | Téléphone du conducteur |

#### 🔹 vehicle\_data

| Colonne             | Type    | Description                    |
| ------------------- | ------- | ------------------------------ |
| id                  | INTEGER | ID du véhicule                 |
| driver\_id          | INTEGER | Clé étrangère vers drivers     |
| timestamp           | TEXT    | Date et heure                  |
| speed               | REAL    | Vitesse (km/h)                 |
| rpm                 | INTEGER | Régime moteur                  |
| battery             | REAL    | Tension batterie (V)           |
| fuel                | REAL    | Carburant (%)                  |
| tire1 à tire4       | REAL    | Pression pneus (psi)           |
| oil                 | REAL    | Niveau d’huile moteur (%)      |
| brake\_wear         | REAL    | Usure des freins (%)           |
| brake\_fluid\_temp  | REAL    | Température liquide frein (°C) |
| brake\_fluid\_level | REAL    | Niveau liquide frein (%)       |
| lights              | TEXT    | ON / OFF                       |
| dtc                 | TEXT    | Code défaut (ex: P0420)        |
| external\_temp      | REAL    | Température extérieure (°C)    |
| smoke               | TEXT    | YES / NO                       |
| vibration           | REAL    | Vibration (g)                  |
| total\_mileage      | REAL    | Kilométrage total (km)         |

---

## ☕ Connexion à SQLite depuis Java

### 🔧 Prérequis Java

* Ajouter la dépendance JDBC SQLite :

#### Si Maven :

```xml
<dependency>
  <groupId>org.xerial</groupId>
  <artifactId>sqlite-jdbc</artifactId>
  <version>3.44.1.0</version>
</dependency>
```

#### Si sans Maven :

* Télécharger : [https://github.com/xerial/sqlite-jdbc/releases](https://github.com/xerial/sqlite-jdbc/releases)
* Ajouter le `.jar` à votre classpath

### 🧪 Exemple Java minimal

```java
import java.sql.*;

public class ReadFleetData {
    public static void main(String[] args) {
        String url = "jdbc:sqlite:C:/chemin/vers/fleetdata.db";

        try (Connection conn = DriverManager.getConnection(url)) {
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM vehicle_data LIMIT 5");

            while (rs.next()) {
                System.out.println("Vehicule " + rs.getInt("id") +
                    " à " + rs.getString("timestamp") +
                    " => vitesse : " + rs.getDouble("speed") + " km/h");
            }
        } catch (SQLException e) {
            System.out.println("Erreur : " + e.getMessage());
        }
    }
}
```

---

## 📦 Bonus

* Script Python modulaire pour exporter vers CSV
* Support de visualisation possible via pandas, matplotlib, JavaFX ou Grafana

---

## 🔐 Avertissements

* SQLite gère un accès **concurrent en lecture**, mais les écritures simultanées doivent être évitées.
* Toujours fermer proprement la base (`conn.close()` ou `with`).
