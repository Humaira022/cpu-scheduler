/**
 * CPU Scheduling Algorithm Simulator - Console Version (Backup)
 * Author: GitHub Copilot
 * Date: August 22, 2025
 * 
 * This is a console-based version of the CPU scheduler for compatibility.
 * Use this if the GUI version has any issues.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int remainingTime;
    
    Process(int i, int at, int bt, int p = 0) 
        : id(i), arrivalTime(at), burstTime(bt), priority(p),
          waitingTime(0), turnaroundTime(0), completionTime(0), remainingTime(bt) {}
};

class CPUScheduler {
public:
    static vector<Process> fcfs(vector<Process> processes) {
        sort(processes.begin(), processes.end(), 
             [](const Process& a, const Process& b) {
                 return a.arrivalTime < b.arrivalTime;
             });
        
        int currentTime = 0;
        
        for (auto& process : processes) {
            if (currentTime < process.arrivalTime) {
                currentTime = process.arrivalTime;
            }
            
            process.waitingTime = currentTime - process.arrivalTime;
            process.completionTime = currentTime + process.burstTime;
            process.turnaroundTime = process.completionTime - process.arrivalTime;
            
            currentTime = process.completionTime;
        }
        
        return processes;
    }
    
    static vector<Process> sjf(vector<Process> processes) {
        vector<bool> isCompleted(processes.size(), false);
        int currentTime = 0;
        int completedCount = 0;
        
        while (completedCount < processes.size()) {
            int shortestIdx = -1;
            int shortestBurst = INT_MAX;
            
            for (int i = 0; i < processes.size(); i++) {
                if (!isCompleted[i] && processes[i].arrivalTime <= currentTime &&
                    processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    shortestIdx = i;
                }
            }
            
            if (shortestIdx == -1) {
                currentTime++;
            } else {
                Process& process = processes[shortestIdx];
                process.waitingTime = currentTime - process.arrivalTime;
                process.completionTime = currentTime + process.burstTime;
                process.turnaroundTime = process.completionTime - process.arrivalTime;
                
                currentTime = process.completionTime;
                isCompleted[shortestIdx] = true;
                completedCount++;
            }
        }
        
        return processes;
    }
    
    static vector<Process> roundRobin(vector<Process> processes, int timeQuantum) {
        queue<int> readyQueue;
        vector<bool> inQueue(processes.size(), false);
        
        for (auto& process : processes) {
            process.remainingTime = process.burstTime;
        }
        
        int currentTime = 0;
        int completedCount = 0;
        
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrivalTime <= currentTime) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }
        
        while (completedCount < processes.size()) {
            if (readyQueue.empty()) {
                currentTime++;
                for (int i = 0; i < processes.size(); i++) {
                    if (!inQueue[i] && processes[i].arrivalTime <= currentTime) {
                        readyQueue.push(i);
                        inQueue[i] = true;
                    }
                }
                continue;
            }
            
            int currentIdx = readyQueue.front();
            readyQueue.pop();
            Process& currentProcess = processes[currentIdx];
            
            int execTime = min(timeQuantum, currentProcess.remainingTime);
            currentTime += execTime;
            currentProcess.remainingTime -= execTime;
            
            for (int i = 0; i < processes.size(); i++) {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime && 
                    processes[i].remainingTime > 0) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            
            if (currentProcess.remainingTime == 0) {
                currentProcess.completionTime = currentTime;
                currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
                completedCount++;
            } else {
                readyQueue.push(currentIdx);
            }
        }
        
        return processes;
    }
    
    static vector<Process> priority(vector<Process> processes) {
        vector<bool> isCompleted(processes.size(), false);
        int currentTime = 0;
        int completedCount = 0;
        
        while (completedCount < processes.size()) {
            int highestPriorityIdx = -1;
            int highestPriority = INT_MAX;
            
            for (int i = 0; i < processes.size(); i++) {
                if (!isCompleted[i] && processes[i].arrivalTime <= currentTime &&
                    processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIdx = i;
                }
            }
            
            if (highestPriorityIdx == -1) {
                currentTime++;
            } else {
                Process& process = processes[highestPriorityIdx];
                process.waitingTime = currentTime - process.arrivalTime;
                process.completionTime = currentTime + process.burstTime;
                process.turnaroundTime = process.completionTime - process.arrivalTime;
                
                currentTime = process.completionTime;
                isCompleted[highestPriorityIdx] = true;
                completedCount++;
            }
        }
        
        return processes;
    }
    
    static double calculateAverageWaitingTime(const vector<Process>& processes) {
        double total = 0;
        for (const auto& process : processes) {
            total += process.waitingTime;
        }
        return total / processes.size();
    }
    
    static double calculateAverageTurnaroundTime(const vector<Process>& processes) {
        double total = 0;
        for (const auto& process : processes) {
            total += process.turnaroundTime;
        }
        return total / processes.size();
    }
};

void printResults(const vector<Process>& processes, const string& algorithm) {
    cout << "\n" << algorithm << " Scheduling Results:\n";
    cout << string(70, '=') << "\n";
    cout << setw(8) << "Process" << setw(10) << "Arrival" << setw(8) << "Burst" 
         << setw(12) << "Completion" << setw(10) << "Waiting" << setw(12) << "Turnaround" << "\n";
    cout << string(70, '-') << "\n";
    
    for (const auto& process : processes) {
        cout << setw(8) << ("P" + to_string(process.id))
             << setw(10) << process.arrivalTime
             << setw(8) << process.burstTime
             << setw(12) << process.completionTime
             << setw(10) << process.waitingTime
             << setw(12) << process.turnaroundTime << "\n";
    }
    
    cout << string(70, '-') << "\n";
    cout << "Average Waiting Time: " << fixed << setprecision(2) 
         << CPUScheduler::calculateAverageWaitingTime(processes) << " ms\n";
    cout << "Average Turnaround Time: " << fixed << setprecision(2) 
         << CPUScheduler::calculateAverageTurnaroundTime(processes) << " ms\n";
}

int main() {
    cout << "CPU Scheduling Algorithm Simulator - Console Version\n";
    cout << string(55, '=') << "\n\n";
    
    vector<Process> processes;
    
    cout << "Enter number of processes: ";
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int arrival, burst, priority;
        cout << "\nProcess " << (i + 1) << ":\n";
        cout << "Arrival Time: ";
        cin >> arrival;
        cout << "Burst Time: ";
        cin >> burst;
        cout << "Priority (lower number = higher priority): ";
        cin >> priority;
        
        processes.emplace_back(i + 1, arrival, burst, priority);
    }
    
    while (true) {
        cout << "\n" << string(50, '=') << "\n";
        cout << "Choose Scheduling Algorithm:\n";
        cout << "1. First Come First Serve (FCFS)\n";
        cout << "2. Shortest Job First (SJF)\n";
        cout << "3. Round Robin (RR)\n";
        cout << "4. Priority Scheduling\n";
        cout << "5. Compare All Algorithms\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {
                auto result = CPUScheduler::fcfs(processes);
                printResults(result, "FCFS");
                break;
            }
            case 2: {
                auto result = CPUScheduler::sjf(processes);
                printResults(result, "SJF");
                break;
            }
            case 3: {
                int quantum;
                cout << "Enter time quantum: ";
                cin >> quantum;
                auto result = CPUScheduler::roundRobin(processes, quantum);
                printResults(result, "Round Robin (q=" + to_string(quantum) + ")");
                break;
            }
            case 4: {
                auto result = CPUScheduler::priority(processes);
                printResults(result, "Priority");
                break;
            }
            case 5: {
                cout << "\nAlgorithm Comparison:\n";
                cout << string(50, '=') << "\n";
                
                auto fcfsResult = CPUScheduler::fcfs(processes);
                auto sjfResult = CPUScheduler::sjf(processes);
                auto rrResult = CPUScheduler::roundRobin(processes, 2);
                auto priorityResult = CPUScheduler::priority(processes);
                
                cout << setw(20) << "Algorithm" << setw(15) << "Avg Waiting" << setw(15) << "Avg Turnaround" << "\n";
                cout << string(50, '-') << "\n";
                cout << setw(20) << "FCFS" << setw(15) << fixed << setprecision(2) 
                     << CPUScheduler::calculateAverageWaitingTime(fcfsResult) << setw(15) 
                     << CPUScheduler::calculateAverageTurnaroundTime(fcfsResult) << "\n";
                cout << setw(20) << "SJF" << setw(15) << fixed << setprecision(2) 
                     << CPUScheduler::calculateAverageWaitingTime(sjfResult) << setw(15) 
                     << CPUScheduler::calculateAverageTurnaroundTime(sjfResult) << "\n";
                cout << setw(20) << "Round Robin (q=2)" << setw(15) << fixed << setprecision(2) 
                     << CPUScheduler::calculateAverageWaitingTime(rrResult) << setw(15) 
                     << CPUScheduler::calculateAverageTurnaroundTime(rrResult) << "\n";
                cout << setw(20) << "Priority" << setw(15) << fixed << setprecision(2) 
                     << CPUScheduler::calculateAverageWaitingTime(priorityResult) << setw(15) 
                     << CPUScheduler::calculateAverageTurnaroundTime(priorityResult) << "\n";
                break;
            }
            case 6:
                cout << "Thank you for using CPU Scheduler Simulator!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
