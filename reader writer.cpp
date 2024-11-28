#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared data and synchronization variables
int shared_data = 0;
int read_count = 0;
pthread_mutex_t mutex;
sem_t write_lock;

// Reader function
void* reader(void* arg) {
    int reader_id = *(int*)arg;

    // Entry section
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&write_lock);  // First reader locks writers
    }
    pthread_mutex_unlock(&mutex);

    // Critical section (reading)
    printf("Reader %d: Read shared_data = %d\n", reader_id, shared_data);
    sleep(1);  // Simulate reading time

    // Exit section
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&write_lock);  // Last reader unlocks writers
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer function
void* writer(void* arg) {
    int writer_id = *(int*)arg;

    // Entry section (writing)
    sem_wait(&write_lock);  // Lock writers

    // Critical section (writing)
    shared_data++;
    printf("Writer %d: Updated shared_data to %d\n", writer_id, shared_data);
    sleep(2);  // Simulate writing time

    // Exit section
    sem_post(&write_lock);  // Unlock writers

    return NULL;
}

int main() {
    int num_readers, num_writers;

    // User input for number of readers and writers
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    // Thread arrays and ids
    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    // Initialize synchronization primitives
    pthread_mutex_init(&mutex, NULL);
    sem_init(&write_lock, 0, 1);

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for threads to complete (not necessary for infinite loops in this case)
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
/*
Enter the number of readers: 2
Enter the number of writers: 1

Reader 1: Read shared_data = 0
Reader 2: Read shared_data = 0
Writer 1: Updated shared_data to 1

*/