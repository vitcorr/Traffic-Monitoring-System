#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_CAMERAS 4
#define LOG_FILE "traffic_log.csv"

// Mutex for synchronizing file writes
pthread_mutex_t log_mutex;

// Function to simulate a random traffic event
void *camera_thread(void *arg) {
    int camera_id = *(int *)arg;
    FILE *file;

    while (1) {
        sleep(rand() % 3 + 1);  // Simulate random event timing (1-3 sec)

        // Generate a random event
        int event_type = rand() % 3;
        char *event_desc;
        switch (event_type) {
            case 0: event_desc = "Car crossed red light"; break;
            case 1: event_desc = "Pedestrian took too long to cross"; break;
            case 2: event_desc = "Heavy traffic detected"; break;
        }

        // Get current timestamp
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

        // Lock the mutex before writing to the file
        pthread_mutex_lock(&log_mutex);

        file = fopen(LOG_FILE, "a");
        if (file == NULL) {
            perror("Error opening log file");
            pthread_mutex_unlock(&log_mutex);
            pthread_exit(NULL);
        }

        fprintf(file, "%s, Camera %d, %s\n", time_str, camera_id, event_desc);
        fclose(file);

        // Unlock the mutex after writing
        pthread_mutex_unlock(&log_mutex);

        printf("Camera %d logged event: %s\n", camera_id, event_desc);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_CAMERAS];
    int camera_ids[NUM_CAMERAS];

    // Initialize the mutex
    pthread_mutex_init(&log_mutex, NULL);

    // Create threads for each camera
    for (int i = 0; i < NUM_CAMERAS; i++) {
        camera_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, camera_thread, &camera_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join threads (optional, could run indefinitely)
    for (int i = 0; i < NUM_CAMERAS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&log_mutex);

    return 0;
}
