CREATE TABLE IF NOT EXISTS vehicules (
    id INTEGER PRIMARY KEY,
    nom TEXT NOT NULL,
    immatriculation TEXT UNIQUE NOT NULL
);

-- Création de la table des données capteurs
CREATE TABLE DonneesVehicule (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicule_id TEXT,
    timestamp TEXT,
    vitesse REAL,
    temperature_moteur REAL,
    tension_batterie REAL,
    niveau_carburant REAL,
    pression_pneus REAL,
    rpm INTEGER,
    consommation REAL,
    etat_freins TEXT,
    temp_liquide_frein REAL,
    phares TEXT,
    dtc TEXT,
    temp_exterieure REAL,
    fumees TEXT,
    vibrations TEXT
);


-- Création de la table des conducteurs
CREATE TABLE IF NOT EXISTS conducteurs (
    id INTEGER PRIMARY KEY,
    nom TEXT NOT NULL,
    prenom TEXT NOT NULL,
    permis TEXT,
    telephone TEXT
);

-- Table pour l’affectation véhicule - conducteur
CREATE TABLE IF NOT EXISTS affectations (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicule_id INTEGER NOT NULL,
    conducteur_id INTEGER NOT NULL,
    date_debut TEXT NOT NULL,
    date_fin TEXT,
    FOREIGN KEY (vehicule_id) REFERENCES vehicules(id),
    FOREIGN KEY (conducteur_id) REFERENCES conducteurs(id)
);

-- Historique de maintenance
CREATE TABLE IF NOT EXISTS maintenance (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicule_id INTEGER NOT NULL,
    type TEXT NOT NULL,
    date TEXT NOT NULL,
    commentaire TEXT,
    FOREIGN KEY (vehicule_id) REFERENCES vehicules(id)
);
