#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

// Mutex for each fork
mutex forks[5];

// Philosopher function to think and eat
void philosopher(int id) {
    int left = id;
    int right = (id + 1) % 5;

    while (true) {
        // Think
        cout << "Philosopher " << id << " is thinking.\n";
        this_thread::sleep_for(chrono::seconds(1));

        // Pick up forks (lock)
        forks[left].lock();
        forks[right].lock();
        cout << "Philosopher " << id << " picked up forks " << left << " and " << right << ".\n";

        // Eat
        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::seconds(2));

        // Put down forks (unlock)
        cout << "Philosopher " << id << " put down forks " << left << " and " << right << ".\n";
        forks[left].unlock();
        forks[right].unlock();
    }
}

int main() {
    int num_philosophers = 5;  // Set default to 5 philosophers

    // Create a vector of threads for each philosopher
    vector<thread> philosophers;

    // Create threads for philosophers
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers.push_back(thread(philosopher, i));
    }

    // Join all threads (they will run indefinitely)
    for (auto& t : philosophers) {
        t.join();
    }

    return 0;
}
/*

Philosopher 0 is thinking.
Philosopher 1 is thinking.
Philosopher 0 picked up forks 0 and 1.
Philosopher 0 is eating.
Philosopher 1 picked up forks 1 and 2.
Philosopher 1 is eating.
Philosopher 0 put down forks 0 and 1.
Philosopher 2 picked up forks 2 and 3.
Philosopher 2 is eating.
Philosopher 3 picked up forks 3 and 4.
Philosopher 3 is eating.
Philosopher 4 picked up forks 4 and 0.
Philosopher 4 is eating.


*/