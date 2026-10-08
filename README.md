# 🍝 Philosophers

> **Dining Philosophers Problem** — *A classic synchronization and concurrency problem.*

## 📖 Description

**Philosophers** is a project from the 42 curriculum designed to introduce the basics of threading a process and managing concurrency. It is an implementation of the famous "Dining Philosophers" problem formulated by Edsger Dijkstra.

### 🎯 Goal
The main objective of this project is to learn how to create and synchronize **threads** in C. It introduces the concept of **mutexes** (mutual exclusions) to prevent data races and deadlocks when multiple threads share the same resources (memory).

### 🧠 Overview
- **The Setup:** A given number of philosophers sit at a round table with a large bowl of spaghetti in the middle.
- **The Forks:** There is one fork placed between each pair of philosophers. To eat, a philosopher must hold two forks (the one on their left and the one on their right).
- **The Routine:** Philosophers continuously alternate between three states: **Eating**, **Sleeping**, and **Thinking**. 
- **The Catch:** A philosopher will starve to death if they don't start eating within a specified time limit. The simulation stops if a philosopher dies or if everyone has eaten a specific amount of times.

---

## 🚀 Instructions

### 🛠️ Compilation

The project comes with a `Makefile`. To compile the program, simply run the following command at the root of the repository:

```bash
make
```

This will generate the `philo` executable.

**Other available rules:**
- `make clean`: Removes the generated object files (`.o`).
- `make fclean`: Removes the object files and the `philo` executable.
- `make re`: Cleans the directory and recompiles the entire project.

### ⚙️ Execution

Run the compiled executable by providing the required arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### 📌 Arguments details:

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | The number of philosophers (and forks) at the table. |
| `time_to_die` | Time in milliseconds before a philosopher dies of starvation. |
| `time_to_eat` | Time in milliseconds it takes for a philosopher to eat. |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping. |
| `[number_of_times...]` | *(Optional)* The simulation stops if all philosophers have eaten at least this many times. If omitted, the simulation runs until a philosopher dies. |

#### 💡 Examples

**Infinite simulation (nobody dies):**
```bash
./philo 5 800 200 200
```
*(5 philosophers, die if they don't eat for 800ms, take 200ms to eat, take 200ms to sleep)*

**Simulation with an end goal:**
```bash
./philo 4 410 200 200 5
```
*(4 philosophers, die at 410ms, eat for 200ms, sleep for 200ms, stops when every philosopher has eaten 5 times)*
