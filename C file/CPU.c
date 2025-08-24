#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

// Global variables
struct Process *processes = NULL;
int n = 0;

// Function to input processes
void enterProcesses() {
    int i;

    // Free previous memory if allocated
    if (processes != NULL) {
        free(processes);
        processes = NULL;
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of processes!\n");
        n = 0;
        return;
    }

    // Allocate memory dynamically
    processes = (struct Process*)malloc(n * sizeof(struct Process));
    if (processes == NULL) {
        printf("Memory allocation failed!\n");
        n = 0;
        return;
    }

    printf("\nEnter process details:\n");
    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d:\n", i + 1);
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("  Priority (for Priority Scheduling): ");
        scanf("%d", &processes[i].priority);
        printf("\n");
    }
    printf("Processes entered successfully!\n");
}

// Function to calculate FCFS
void fcfs() {
    int i;
    if (n == 0) {
        printf("Please enter processes first!\n");
        return;
    }

    // Sort by arrival time
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate times
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    for (i = 1; i < n; i++) {
        if (processes[i].arrival_time > processes[i-1].completion_time) {
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
        } else {
            processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
        }
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

// Function to calculate SJF
void sjf() {
    int i;
    if (n == 0) {
        printf("Please enter processes first!\n");
        return;
    }

    // Sort by burst time
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate times (similar to FCFS after sorting)
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    for (i = 1; i < n; i++) {
        processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

// Function to calculate Priority Scheduling
void priorityScheduling() {
    int i;
    if (n == 0) {
        printf("Please enter processes first!\n");
        return;
    }

    // Sort by priority (lower number = higher priority)
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate times
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    for (i = 1; i < n; i++) {
        processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

// Function to calculate Round Robin
void roundRobin() {
    int time_quantum, time = 0, completed = 0, i;
    int *remaining_time;

    if (n == 0) {
        printf("Please enter processes first!\n");
        return;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    if (time_quantum <= 0) {
        printf("Invalid time quantum!\n");
        return;
    }

    // Allocate memory for remaining times
    remaining_time = (int*)malloc(n * sizeof(int));
    if (remaining_time == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Initialize remaining times
    for (i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        processes[i].completion_time = 0;
    }

    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] > time_quantum) {
                    time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    time += remaining_time[i];
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }
    }

    // Free allocated memory
    free(remaining_time);
}

// Function to display results
void displayResults() {
    int i;
    float avg_waiting = 0, avg_turnaround = 0;

    printf("\n=== CPU Scheduling Results ===\n");
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n");
    printf("------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].completion_time);

        avg_waiting += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
    }

    avg_waiting /= n;
    avg_turnaround /= n;

    printf("------------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);
}

// Function to calculate average times
void calculateAverages(float *avg_waiting, float *avg_turnaround) {
    int i;
    *avg_waiting = 0;
    *avg_turnaround = 0;

    for (i = 0; i < n; i++) {
        *avg_waiting += processes[i].waiting_time;
        *avg_turnaround += processes[i].turnaround_time;
    }

    *avg_waiting /= n;
    *avg_turnaround /= n;
}

// Function to compare all algorithms
void compareAll() {
    struct Process *original;
    int i;
    float fcfs_waiting, fcfs_turnaround;
    float sjf_waiting, sjf_turnaround;
    float priority_waiting, priority_turnaround;
    float rr_waiting, rr_turnaround;
    int time_quantum = 2; // Default time quantum

    if (n == 0) {
        printf("Please enter processes first!\n");
        return;
    }

    printf("\n=== ALGORITHM COMPARISON ===\n");
    printf("Using default time quantum = 2 for Round Robin\n");

    // Allocate memory for original data backup
    original = (struct Process*)malloc(n * sizeof(struct Process));
    if (original == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Save original data
    for (i = 0; i < n; i++) {
        original[i] = processes[i];
    }

    // FCFS
    printf("\n--- FCFS ---\n");
    fcfs();
    displayResults();
    calculateAverages(&fcfs_waiting, &fcfs_turnaround);

    // Restore original data
    for (i = 0; i < n; i++) {
        processes[i] = original[i];
    }

    // SJF
    printf("\n--- SJF ---\n");
    sjf();
    displayResults();
    calculateAverages(&sjf_waiting, &sjf_turnaround);

    // Restore original data
    for (i = 0; i < n; i++) {
        processes[i] = original[i];
    }

    // Priority
    printf("\n--- Priority Scheduling ---\n");
    priorityScheduling();
    displayResults();
    calculateAverages(&priority_waiting, &priority_turnaround);

    // Restore original data
    for (i = 0; i < n; i++) {
        processes[i] = original[i];
    }

    // Round Robin (simplified - use default quantum)
    printf("\n--- Round Robin (Time Quantum = %d) ---\n", time_quantum);

    // Simple Round Robin calculation for comparison
    int time = 0, completed = 0;
    int *remaining_time = (int*)malloc(n * sizeof(int));

    // Initialize remaining times
    for (i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        processes[i].completion_time = 0;
    }

    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] > time_quantum) {
                    time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    time += remaining_time[i];
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }
    }

    free(remaining_time);
    displayResults();
    calculateAverages(&rr_waiting, &rr_turnaround);

    // Performance Summary
    printf("\n");
    printf("========================================================\n");
    printf("                 PERFORMANCE SUMMARY                   \n");
    printf("========================================================\n");
    printf("Algorithm\t\tAvg Waiting Time\tAvg Turnaround Time\n");
    printf("--------------------------------------------------------\n");
    printf("FCFS\t\t\t%.2f\t\t\t%.2f\n", fcfs_waiting, fcfs_turnaround);
    printf("SJF\t\t\t%.2f\t\t\t%.2f\n", sjf_waiting, sjf_turnaround);
    printf("Priority\t\t%.2f\t\t\t%.2f\n", priority_waiting, priority_turnaround);
    printf("Round Robin (q=%d)\t%.2f\t\t\t%.2f\n", time_quantum, rr_waiting, rr_turnaround);
    printf("--------------------------------------------------------\n");

    // Determine best algorithm
    float min_waiting = fcfs_waiting;
    float min_turnaround = fcfs_turnaround;
    char best_waiting[20] = "FCFS";
    char best_turnaround[20] = "FCFS";
    char best_overall[20] = "FCFS";

    // Check SJF
    if (sjf_waiting < min_waiting) {
        min_waiting = sjf_waiting;
        strcpy(best_waiting, "SJF");
    }
    if (sjf_turnaround < min_turnaround) {
        min_turnaround = sjf_turnaround;
        strcpy(best_turnaround, "SJF");
    }

    // Check Priority
    if (priority_waiting < min_waiting) {
        min_waiting = priority_waiting;
        strcpy(best_waiting, "Priority");
    }
    if (priority_turnaround < min_turnaround) {
        min_turnaround = priority_turnaround;
        strcpy(best_turnaround, "Priority");
    }

    // Check Round Robin
    if (rr_waiting < min_waiting) {
        min_waiting = rr_waiting;
        strcpy(best_waiting, "Round Robin");
    }
    if (rr_turnaround < min_turnaround) {
        min_turnaround = rr_turnaround;
        strcpy(best_turnaround, "Round Robin");
    }

    // Determine overall best (weighted average of both metrics)
    float fcfs_score = (fcfs_waiting + fcfs_turnaround) / 2;
    float sjf_score = (sjf_waiting + sjf_turnaround) / 2;
    float priority_score = (priority_waiting + priority_turnaround) / 2;
    float rr_score = (rr_waiting + rr_turnaround) / 2;

    float min_score = fcfs_score;
    strcpy(best_overall, "FCFS");

    if (sjf_score < min_score) {
        min_score = sjf_score;
        strcpy(best_overall, "SJF");
    }
    if (priority_score < min_score) {
        min_score = priority_score;
        strcpy(best_overall, "Priority");
    }
    if (rr_score < min_score) {
        min_score = rr_score;
        strcpy(best_overall, "Round Robin");
    }

    // Display recommendations
    printf("\n");
    printf("========================================================\n");
    printf("                    RECOMMENDATIONS                    \n");
    printf("========================================================\n");
    printf("Best for Waiting Time: %s (%.2f)\n", best_waiting, min_waiting);
    printf("Best for Turnaround Time: %s (%.2f)\n", best_turnaround, min_turnaround);
    printf("Overall Best Algorithm: %s (Score: %.2f)\n", best_overall, min_score);
    printf("========================================================\n");

    // Additional insights
    printf("\nPerformance Insights:\n");
    if (strcmp(best_overall, "SJF") == 0) {
        printf("SJF provides optimal results for non-preemptive scheduling.\n");
        printf("Note: SJF may cause starvation for longer processes.\n");
    } else if (strcmp(best_overall, "FCFS") == 0) {
        printf("FCFS is simple and fair with no starvation.\n");
        printf("Note: May not be optimal for varying burst times.\n");
    } else if (strcmp(best_overall, "Priority") == 0) {
        printf("Priority scheduling handles important processes first.\n");
        printf("Note: May cause starvation for low-priority processes.\n");
    } else if (strcmp(best_overall, "Round Robin") == 0) {
        printf("Round Robin provides good response time and fairness.\n");
        printf("Note: Performance depends on time quantum selection.\n");
    }

    // Free allocated memory
    free(original);
}

// Function to display menu
void displayMenu() {
    printf("\n");
    printf("========================================================\n");
    printf("    CPU SCHEDULING ALGORITHM SIMULATOR & EVALUATOR    \n");
    printf("========================================================\n");
    printf("\n");
    printf("============= MAIN MENU =============\n");
    printf("1. Enter Processes\n");
    printf("2. First-Come, First-Served (FCFS)\n");
    printf("3. Shortest Job First (SJF)\n");
    printf("4. Round Robin (RR)\n");
    printf("5. Priority Scheduling\n");
    printf("6. Compare All Algorithms\n");
    printf("7. Exit\n");
    printf("====================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterProcesses();
                break;
            case 2:
                printf("\n--- First-Come, First-Served (FCFS) ---\n");
                fcfs();
                displayResults();
                break;
            case 3:
                printf("\n--- Shortest Job First (SJF) ---\n");
                sjf();
                displayResults();
                break;
            case 4:
                printf("\n--- Round Robin (RR) ---\n");
                roundRobin();
                displayResults();
                break;
            case 5:
                printf("\n--- Priority Scheduling ---\n");
                priorityScheduling();
                displayResults();
                break;
            case 6:
                compareAll();
                break;
            case 7:
                printf("\nThank you for using CPU Scheduler!\n");
                // Free memory before exit
                if (processes != NULL) {
                    free(processes);
                }
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }

    return 0;
}
