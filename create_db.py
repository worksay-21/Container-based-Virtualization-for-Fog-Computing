import sqlite3

conn = sqlite3.connect("smart_parking.db")
cursor = conn.cursor()

cursor.execute("""
CREATE TABLE IF NOT EXISTS parking_events (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    slot_id INTEGER,
    distance_cm REAL,
    status TEXT,
    ts DATETIME DEFAULT CURRENT_TIMESTAMP
)
""")

cursor.execute("DELETE FROM parking_events")

sample_data = [
    (1, 10.5, "occupied"),
    (2, 45.0, "free"),
    (3, 12.3, "occupied"),
    (4, 50.2, "free")
]

cursor.executemany("""
INSERT INTO parking_events (slot_id, distance_cm, status)
VALUES (?, ?, ?)
""", sample_data)

conn.commit()
conn.close()

print("Database created and sample data inserted successfully.")