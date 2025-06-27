CREATE TABLE IF NOT EXISTS vehicules (
    id INTEGER PRIMARY KEY,
    nom TEXT NOT NULL,
    immatriculation TEXT UNIQUE NOT NULL
);

-- Création de la table des données capteurs
CREATE TABLE IF NOT EXISTS donnees_capteurs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicule_id INTEGER NOT NULL,
    timestamp TEXT NOT NULL,
    vitesse INTEGER,
    niveau_carburant INTEGER,
    temperature_moteur INTEGER,
    kilometrage INTEGER,
    FOREIGN KEY (vehicule_id) REFERENCES vehicules(id)
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
