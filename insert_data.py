import os
import sqlite3
import time
import re
import threading

NUM_VEHICLES = 10
DATA_FOLDER = "."  # Dossier courant
DB_FILE = "fleetdata.db"  # Base existante

# Création de la table si elle n'existe pas et nettoyage complet à chaque lancement
def setup_database():
    conn = sqlite3.connect(DB_FILE)
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS vehicle_data (
            id INTEGER,
            timestamp TEXT,
            speed REAL,
            rpm INTEGER,
            battery REAL,
            fuel REAL,
            tire1 REAL, tire2 REAL, tire3 REAL, tire4 REAL,
            oil REAL,
            brake_wear REAL,
            brake_fluid_temp REAL,
            brake_fluid_level REAL,
            lights TEXT,
            dtc TEXT,
            external_temp REAL,
            smoke TEXT,
            vibration REAL
        )
    """)
    # Réinitialiser la table pour partir sur du vide
    cursor.execute("DELETE FROM vehicle_data")
    conn.commit()
    conn.close()

# Extraction des champs depuis la ligne brute
def parse_line(line):
    try:
        timestamp = line.split(" | ")[0]
        data = line.split(" | ")[1]
        regex = r"ID: (\d+), Speed: ([\d.]+) km/h, RPM: (\d+), Battery: ([\d.]+) V, Fuel: ([\d.]+)%, Tires: \[([\d.]+), ([\d.]+), ([\d.]+), ([\d.]+)\] psi, Oil: ([\d.]+)%, BrakeWear: ([\d.]+)%, BrakeFluidTemp: ([\d.]+) C, BrakeFluidLevel: ([\d.]+)%, Lights: (ON|OFF), DTC: (\w+), ExtTemp: ([\d.-]+) C, Smoke: (YES|NO), Vibration: ([\d.]+) g"
        match = re.search(regex, data)
        if match:
            values = match.groups()
            return (int(values[0]), timestamp, *map(float, values[1:5]), *map(float, values[5:9]), float(values[9]), float(values[10]),
                    float(values[11]), float(values[12]), values[13], values[14], float(values[15]), values[16], float(values[17]))
    except Exception as e:
        print("Erreur de parsing :", e)
    return None

# Lecture en temps réel des fichiers
def monitor_file(vehicle_id):
    filepath = os.path.join(DATA_FOLDER, f"vehicle_{vehicle_id}.txt")
    print(f" Surveillance de {filepath}...")
    while not os.path.exists(filepath):
        time.sleep(0.5)

    with open(filepath, "r") as file:
        file.seek(0, os.SEEK_END)
        while True:
            line = file.readline()
            if not line:
                time.sleep(0.5)
                continue
            parsed = parse_line(line)
            if parsed:
                try:
                    with sqlite3.connect(DB_FILE) as conn:
                        cursor = conn.cursor()
                        cursor.execute("""
                            INSERT INTO vehicle_data (
                                id, timestamp, speed, rpm, battery, fuel,
                                tire1, tire2, tire3, tire4, oil, brake_wear,
                                brake_fluid_temp, brake_fluid_level, lights,
                                dtc, external_temp, smoke, vibration
                            ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                        """, parsed)
                        conn.commit()
                        print(f" Insertion véhicule {vehicle_id} dans fleetdata.db")
                except Exception as e:
                    print(f"[!] Erreur DB pour véhicule {vehicle_id} :", e)

# Lancer la surveillance pour tous les véhicules
def start_monitoring():
    threads = []
    for vid in range(NUM_VEHICLES):
        t = threading.Thread(target=monitor_file, args=(vid,))
        t.daemon = True
        t.start()
        threads.append(t)
    print(" Insertion en temps réel activée. CTRL+C pour arrêter.")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\n Arrêt demandé. Fin du script.")

if __name__ == "__main__":
    setup_database()
    start_monitoring()
