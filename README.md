# Philosophers

Welcome to the Philosophers project, an implementation of the classic Dining Philosophers problem using multithreading and mutexes in C. This project was completed as part of the curriculum at 42 Beirut.

## Overview

The Dining Philosophers problem is a classic synchronization problem that illustrates challenges in concurrent programming. It involves philosophers who perform three actions:

- **Eating**
- **Sleeping**
- **Thinking**

The goal is to simulate these actions while preventing deadlocks and ensuring that no philosopher starves to death.

## Features

- Simulates multiple philosophers sharing forks (resources) without causing deadlocks.
- Uses mutexes and threads to manage synchronization between philosophers.
- Provides command-line arguments to customize the simulation parameters.

## Repository

The project is hosted on GitHub:

[GitHub Repository](https://github.com/Mohamadaliibrahim/philosophers.git)

## Cloning the Repository

To clone the repository to your local machine, use the following command:

```bash
git clone https://github.com/Mohamadaliibrahim/philosophers.git
```

## Usage

### Prerequisites

- **GCC Compiler**: Ensure you have `gcc` installed.
- **Make**: You'll need `make` to build the project.

### Building the Project

Navigate to the cloned repository directory:

```bash
cd philosophers
```

Compile the project using the `make` command:

```bash
make
```

This will generate an executable called `philo`.

### Running the Simulation

The `philo` executable accepts the following command-line arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- **number_of_philosophers**: The number of philosophers and forks.
- **time_to_die** (in milliseconds): If a philosopher doesn't start eating within this time after starting their last meal or the simulation, they die.
- **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat. During this time, they hold both forks.
- **time_to_sleep** (in milliseconds): The time a philosopher spends sleeping.
- **number_of_times_each_philosopher_must_eat** (optional): If all philosophers have eaten this number of times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

### Example Commands

- **Basic Simulation with 5 Philosophers:**

  ```bash
  ./philo 5 800 200 200
  ```

- **Simulation with Philosophers Eating a Certain Number of Times:**

  ```bash
  ./philo 5 800 200 200 7
  ```

### Understanding the Output

The program outputs events as they occur, with timestamps and philosopher IDs:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

- The first number is the timestamp in milliseconds since the simulation started.
- The second number is the philosopher's ID.
- The message describes the action.

### Exiting the Simulation

- The simulation will stop when a philosopher dies or when all philosophers have eaten the specified number of times.
- Press `Ctrl+C` to forcefully exit the simulation if needed.

## Project Structure

- **src/**: Contains the source code files.
- **includes/**: Contains the header files.
- **Makefile**: Used to build the project.

## Technical Details

- **Threads**: Each philosopher is represented by a thread.
- **Mutexes**: Forks are represented by mutexes to prevent simultaneous access.
- **Synchronization**: Proper locking mechanisms are implemented to avoid data races and deadlocks.

## How It Works

1. **Initialization**: The program initializes philosophers and forks based on the input parameters.
2. **Simulation Start**: Philosophers begin their routines in separate threads.
3. **Philosopher Routine**:
   - **Thinking**: The philosopher thinks for a brief moment.
   - **Eating**:
     - Tries to pick up the left and right forks (mutexes).
     - Eats for `time_to_eat` milliseconds.
     - Updates the time of the last meal.
   - **Sleeping**: Sleeps for `time_to_sleep` milliseconds.
4. **Monitoring**: A separate thread monitors the philosophers to check if any have died or if they've all eaten the required number of times.
5. **Termination**: The simulation ends based on the specified conditions.

## Important Notes

- **Even Number of Philosophers**: Be cautious with even numbers, as it may lead to deadlocks if not handled properly. This implementation addresses deadlocks by ensuring consistent fork-picking order.
- **Time Accuracy**: The simulation uses `usleep` and timestamp calculations to manage timing accurately.

## Contact

For any questions or issues, feel free to open an issue on the GitHub repository or contact the project author.

---

Enjoy experimenting with the Dining Philosophers simulation!
