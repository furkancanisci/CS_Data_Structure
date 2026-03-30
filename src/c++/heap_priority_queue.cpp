#include <iostream>
#include <string>
#include <queue>
#include <vector>

class HeapPriorityQueue {
private:
    struct Patient {
        int severity;
        int arrival_order;
        std::string name;
        std::string complaint;

        // C++ priority_queue puts the "largest" element at top.
        // We want: 1. Higher severity first. 2. Earlier arrival first.
        bool operator<(const Patient& other) const {
            if (severity != other.severity) {
                // Higher severity is "greater", so it should be at the top.
                return severity < other.severity; 
            }
            // If severities are equal, the one that arrived LATER is "less",
            // so it goes to the back. This ensures FIFO.
            return arrival_order > other.arrival_order;
        }
    };

    std::priority_queue<Patient> q;
    int global_counter = 0; // Tracks the arrival sequence automatically

public:
    // Pass by const reference to avoid unnecessary string copies
    void push(const std::string& name, int severity, const std::string& complaint) {
        q.push({severity, global_counter++, name, complaint});
    }

    void pop() {
        if (!q.empty()) q.pop();
    }

    void peek() const {
        if (!q.empty()) {
            const auto& top = q.top();
            std::cout << "[Next] " << top.name << " | Severity: " << top.severity 
                      << " | Order: " << top.arrival_order << std::endl;
        } else {
            std::cout << "No patients in queue." << std::endl;
        }
    }
};

int main() {
    HeapPriorityQueue hpq;
    hpq.push("Alice", 4, "Headache");
    hpq.push("Bob", 3, "Fever");
    hpq.push("Charlie", 5, "Chest Pain"); // Same severity as Alice but arrived later

    hpq.peek(); // Shows Alice (First arrival among severity 5)
    hpq.pop();
    hpq.peek(); // Shows Charlie (Second arrival among severity 5)
    
    return 0;
}