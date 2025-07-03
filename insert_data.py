import os
import sqlite3
import time
import re
import threading

NUM_VEHICLES = 10
DATA_FOLDER = r"C:\Users\h\Downloads\System-management-mini_project-main 1\System-management-mini_project-main\build\Debug"
DB_FILE = "fleetdata.db"

def setup_database():
    conn = sqlite3.connect(DB_FILE)
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS drivers (
            driver_id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            license_number TEXT,
            phone TEXT
        )
    """)
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS vehicle_data (
            id INTEGER,
            driver_id INTEGER,
            timestamp TEXT,
            speed REAL,
            rpm INTEGER,
            battery REAL,
            fuel REAL,
            tire1 REAL,
            tire2 REAL,
            tire3 REAL,
            tire4 REAL,
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
    cursor.execute("DELETE FROM vehicle_data")
    cursor.execute("DELETE FROM drivers")
    for i in range(NUM_VEHICLES):
        cursor.execute("""
            INSERT INTO drivers (driver_id, name, license_number, phone)
            VALUES (?, ?, ?, ?)
        """, (i, f"Driver {i}", f"LX-{1000 + i}", f"+21261234{i:03}"))
    conn.commit()
    conn.close()

def parse_line(line):
    try:
        timestamp, data = line.strip().split(" | ", 1)
        regex = (
            r"ID: (\d+), Speed: ([\d.]+) km/h, RPM: (\d+), Battery: ([\d.]+) V, "
            r"Fuel: ([\d.]+)%, Tires: \[([\d.]+), ([\d.]+), ([\d.]+), ([\d.]+)\] psi, "
            r"Oil: ([\d.]+)%, BrakeWear: ([\d.]+)%, BrakeFluidTemp: ([\d.]+) C, "
            r"BrakeFluidLevel: ([\d.]+)%, Lights: (ON|OFF), DTC: (\w+), "
            r"ExtTemp: ([\d.-]+) C, Smoke: (YES|NO), Vibration: ([\d.]+) g"
        )
        match = re.search(regex, data)
        if match:
            values = match.groups()
            return (
                int(values[0]),      # vehicle_id
                int(values[0]),      # driver_id (associé 1:1)
                timestamp,
                float(values[1]),    # speed
                int(values[2]),      # rpm
                float(values[3]),    # battery
                float(values[4]),    # fuel
                float(values[5]),    # tire1
                float(values[6]),    # tire2
                float(values[7]),    # tire3
                float(values[8]),    # tire4
                float(values[9]),    # oil
                float(values[10]),   # brake_wear
                float(values[11]),   # brake_fluid_temp
                float(values[12]),   # brake_fluid_level
                values[13],          # lights
                values[14],          # dtc
                float(values[15]),   # external_temp
                values[16],          # smoke
                float(values[17])    # vibration
            )
    except Exception as e:
        print("Erreur parsing :", e)
    return None

def monitor_file(vehicle_id):
    filepath = os.path.join(DATA_FOLDER, f"vehicle_{vehicle_id}.txt")
    print(f"Surveillance de {filepath}")
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
                                id, driver_id, timestamp, speed, rpm, battery, fuel,
                                tire1, tire2, tire3, tire4, oil, brake_wear,
                                brake_fluid_temp, brake_fluid_level, lights,
                                dtc, external_temp, smoke, vibration
                            ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                        """, parsed)
                        conn.commit()
                        print(f"Insertion véhicule {vehicle_id} réussie.")
                except Exception as e:
                    print(f"Erreur DB véhicule {vehicle_id} :", e)

def start_monitoring():
    threads = []
    for vid in range(NUM_VEHICLES):
        t = threading.Thread(target=monitor_file, args=(vid,))
        t.daemon = True
        t.start()
        threads.append(t)
    print("Insertion en temps réel activée. CTRL+C pour arrêter.")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nArrêt demandé. Fin du script.")

if __name__ == "__main__":
    setup_database()
    start_monitoring()
