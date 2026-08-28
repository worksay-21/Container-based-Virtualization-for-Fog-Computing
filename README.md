# Smart Parking System using IoT and Fog Computing

## Project Overview

This project is an IoT-based Smart Parking System designed to monitor parking slot availability in real time. The system collects live sensor data using an ESP32 and ultrasonic sensor, sends the data through MQTT, stores and processes it using Python and SQLite, and visualizes the parking status through a dashboard.

The project also includes containerization using Docker and deployment using Kubernetes as part of the container-based virtualization and fog computing implementation.

---

## System Architecture

```text
ESP32 + Ultrasonic Sensor
          ↓
     MQTT / HiveMQ
          ↓
Python Data Processing
          ↓
   SQLite Database
          ↓
Real-Time Dashboard
          ↓
 Docker Containerization
          ↓
 Kubernetes Deployment
```

---

## Features

- Real-time parking slot monitoring
- Live sensor data collection using ESP32
- Ultrasonic sensor-based vehicle detection
- MQTT communication using HiveMQ
- Parking status classification as Occupied or Free
- SQLite database for storing parking events
- Real-time data processing using Python
- Parking dashboard for visualization
- Docker containerization
- Kubernetes deployment
- Container-based virtualization for fog computing

---

## Technologies Used

### Hardware

- ESP32
- Ultrasonic Sensor
- Breadboard
- Jumper Wires

### Software and Tools

- Arduino IDE / VS Code
- Python
- Google Colab
- MQTT
- HiveMQ Cloud
- SQLite
- Streamlit
- Docker
- Kubernetes
- GitHub

---

## Project Workflow

1. The ultrasonic sensor measures the distance between the sensor and an object.
2. ESP32 processes the sensor readings.
3. Based on the configured distance threshold, the parking slot is classified as **Occupied** or **Free**.
4. ESP32 sends the parking data to HiveMQ Cloud using MQTT.
5. Python receives and processes the parking data.
6. The parking data is stored in an SQLite database.
7. The stored data is analyzed to monitor parking availability.
8. A dashboard displays the latest parking status and parking information.
9. The application is containerized using Docker.
10. Kubernetes is used for deployment and container orchestration.

---

## Repository Structure

```text
Container-based-Virtualization-for-Fog-Computing/
│
├── Smart_Parking.ino
├── Smart_Parking_processing data.ipynb
├── create_db.py
├── dashboard.py
├── Dockerfile
├── deployment.yaml
├── service.yaml
├── requirements.txt
├── README.md
├── docker-deployment.png
└── Container based virtualization for fog computing
```

---

## ESP32 Sensor Module

The ESP32 collects distance data from the ultrasonic sensor.

Based on the configured distance threshold:

- Distance below the threshold → **Occupied**
- Distance above the threshold → **Free**

The ESP32 then publishes the parking information to the MQTT broker.

---

## MQTT Communication

HiveMQ Cloud is used as the MQTT broker for communication between the ESP32 and the Python application.

The sensor data is transmitted in real time through MQTT topics and processed by the Python application.

---

## Database

SQLite is used to store parking-related data.

The stored data includes information such as:

- Parking Slot ID
- Distance
- Parking Status
- Timestamp

---

## Dashboard

The dashboard provides visualization of parking information, including:

- Current parking slot status
- Occupied and Free parking spaces
- Sensor distance readings
- Latest parking events
- Parking occupancy information

---

## Docker

The application is containerized using Docker to package the application and its dependencies into a portable container environment.

The `Dockerfile` contains the configuration required to build and run the application container.

---

## Kubernetes

Kubernetes is used to deploy and manage the containerized application.

The repository includes:

- `deployment.yaml` – Kubernetes deployment configuration
- `service.yaml` – Kubernetes service configuration

---

## How to Run

### 1. Install Python Dependencies

```bash
pip install -r requirements.txt
```

### 2. Create the Database

```bash
python create_db.py
```

### 3. Run the Dashboard

```bash
streamlit run dashboard.py
```

### 4. Run Using Docker

Build the Docker image:

```bash
docker build -t smart-parking .
```

Run the container:

```bash
docker run -p 8501:8501 smart-parking
```

### 5. Deploy Using Kubernetes

```bash
kubectl apply -f deployment.yaml
kubectl apply -f service.yaml
```

---

## Future Enhancements

- Multiple parking slot monitoring
- Parking reservation system
- Mobile application integration
- Cloud database integration
- Advanced parking analytics
- Notification system for parking availability

---

## Conclusion

This project demonstrates an IoT-based smart parking system where live sensor data is collected using an ESP32 and ultrasonic sensor, transmitted through MQTT, processed using Python, and stored in an SQLite database.

The project further demonstrates container-based deployment using Docker and Kubernetes for scalable application deployment.

---

## Author

**Sayali Rajput**

B.Tech in Artificial Intelligence and Data Science
