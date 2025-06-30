-- Script de création de la base de données `fleet`
CREATE DATABASE IF NOT EXISTS fleet;
USE fleet;

-- Supprimer les tables si elles existent déjà
DROP TABLE IF EXISTS maintenance;
DROP TABLE IF EXISTS affectations;
DROP TABLE IF EXISTS DonneesVehicule;
DROP TABLE IF EXISTS conducteurs;
DROP TABLE IF EXISTS vehicules;

-- Table des véhicules
CREATE TABLE vehicules (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    immatriculation VARCHAR(50) UNIQUE NOT NULL
);

-- Table des conducteurs
CREATE TABLE conducteurs (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    prenom VARCHAR(100) NOT NULL,
    permis VARCHAR(50),
    telephone VARCHAR(20)
);

-- Table des données de capteurs
CREATE TABLE DonneesVehicule (
    id INT AUTO_INCREMENT PRIMARY KEY,
    vehicule_id INT,
    timestamp DATETIME,
    vitesse FLOAT,
    temperature_moteur FLOAT,
    tension_batterie FLOAT,
    niveau_carburant FLOAT,
    pression_pneus FLOAT,
    rpm INT,
    consommation FLOAT,
    etat_freins VARCHAR(50),
    temp_liquide_frein FLOAT,
    phares VARCHAR(10),
    dtc VARCHAR(100),
    temp_exterieure FLOAT,
    fumees VARCHAR(100),
    vibrations VARCHAR(100),
    FOREIGN KEY (vehicule_id) REFERENCES vehicules(id)
);

-- Table d’affectation véhicule-conducteur
CREATE TABLE affectations (
    id INT AUTO_INCREMENT PRIMARY KEY,
    vehicule_id INT NOT NULL,
    conducteur_id INT NOT NULL,
    date_debut DATETIME NOT NULL,
    date_fin DATETIME,
    FOREIGN KEY (vehicule_id) REFERENCES vehicules(id),
    FOREIGN KEY (conducteur_id) REFERENCES conducteurs(id)
);

-- Table de maintenance
CREATE TABLE maintenance (
    id INT AUTO_INCREMENT PRIMARY KEY,
    vehicule_id INT NOT NULL,
    type VARCHAR(100) NOT NULL,
    date DATETIME NOT NULL,
    commentaire VARCHAR(255),
    FOREIGN KEY (vehicule_id) REFERENCES vehicules(id)
);

