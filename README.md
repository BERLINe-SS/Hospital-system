# Patient Scheduling & Treatment Simulation System

This project is a C++ simulation system built for the CMPG1040 - Data Structures and Algorithms course (Spring 2025). It simulates a hospital-like environment with different types of patients, treatments, and resources, demonstrating the use of advanced data structures in a real-world scenario.

---

## 📌 Table of Contents

- [Project Description](#project-description)
- [Features](#features)
- [Data Structures Used](#data-structures-used)
- [Simulation Logic](#simulation-logic)
- [How to Run](#how-to-run)
- [Project Structure](#project-structure)
- [Credits](#credits)

---

## 📖 Project Description

This system simulates the scheduling and treatment of patients in a medical facility. Patients arrive either on time, early, or late, and are treated based on their priority and treatment requirements using available resources like medical devices or treatment rooms. The simulation runs step-by-step, processing patient arrival, device allocation, treatment completion, and reporting.

---

## 🚀 Features

- Supports different **patient types**:
  - `N` - Normal
  - `R` - Emergency
- Each patient can require **multiple therapies** (U, E, X).
- Patients may arrive **early**, **on time**, or **late**.
- Uses **devices/rooms** of types:
  - `U` - Ultra
  - `E` - Electro
  - `X` - X-ray
- Assigns patients to resources based on:
  - Priority
  - Availability
  - Treatment time
- Tracks and prints simulation data at every **time step**.
- Allows for **cancellation**, **completion**, and **status updates**.

---

## 🧠 Data Structures Used

| Data Structure       | Purpose                                   |
|----------------------|--------------------------------------------|
| `Doubly Linked List` | For managing lists like patients, history, etc. |
| `Queue`              | For scheduling waiting patients by type    |
| `Priority Queue`     | For managing Emergency patient priority     |
| `Stack`              | For history log (optional)                 |
| `Array`              | For storing available devices of each type |

Each custom DS class was implemented manually without STL.

---

## 🔄 Simulation Logic

1. **Initialization**
   - Load patients from a file or generate them randomly.
   - Initialize device pools.

2. **Time Step Loop**
   - Increment global time.
   - Check new arrivals.
   - Update waiting queues.
   - Assign patients to available resources.
   - Decrease remaining treatment times.
   - Free up resources upon treatment completion.
   - Print system status (`printConsole()`).

3. **End Conditions**
   - Simulation ends when all patients are either:
     - Treated
     - Cancelled (e.g. timeout)
     - No remaining events

---

## ⚙️ How to Run

### Requirements

- C++ Compiler (e.g. `g++`)
- Terminal or WSL (if on Windows)

### Steps

```bash
g++ main.cpp -o simulation
./simulation
