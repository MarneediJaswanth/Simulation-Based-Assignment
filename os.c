#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct {
    int process_id;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

// Function to sort the processes based on priority
void sort(Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to execute processes in Queue 1 (Fixed Priority Preemptive)
void execute_queue1(Process *processes, int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].priority == 0 && processes[i].remaining_time > 0) {
            printf("Executing process %d from Queue 1\n", processes[i].process_id);
            // Ensure that the process time is strictly in multiples of 2
            int time_quantum1 = 2;
            if (processes[i].remaining_time <= time_quantum1) {
                time += processes[i].remaining_time;
                processes[i].remaining_time = 0;
            } else {
                time += time_quantum1;
                processes[i].remaining_time -= time_quantum1;
            }
        }
    }
}

// Function to execute processes in Queue 2 (Round Robin)
void execute_queue2(Process *processes, int n, int time_quantum2) {
    int time = 0;
    int remaining_processes = n;
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].priority == 1 && processes[i].remaining_time > 0) {
                printf("Executing process %d from Queue 2\n", processes[i].process_id);
                if (processes[i].remaining_time <= time_quantum2) {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    remaining_processes--;
                } else {
                    time += time_quantum2;
                    processes[i].remaining_time -= time_quantum2;
                }
            }
        }
    }
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &processes[i].process_id);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority (0 for Queue 1, 1 for Queue 2): ");
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort the processes based on priority
    sort(processes, n);

    // Implement multilevel scheduling
    printf("Executing Queue 1 (Fixed Priority Preemptive):\n");
    execute_queue1(processes, n);

    printf("\nExecuting Queue 2 (Round Robin):\n");
    int time_quantum2 = 3; // You can adjust the time quantum for Queue 2
    execute_queue2(processes, n, time_quantum2);

    // Print the turnaround time and burst time for each process
    printf("\nTurnaround Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        int turnaround_time = processes[i].burst_time;
        printf("Process %d - Turnaround Time: %d, Burst Time: %d\n", processes[i].process_id, turnaround_time, processes[i].burst_time);
    }

    free(processes);

    return 0;
}
