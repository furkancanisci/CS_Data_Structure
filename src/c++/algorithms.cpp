#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

namespace algo {

void printVector(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": [";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << (i + 1 == arr.size() ? "" : ", ");
    }
    std::cout << "]\n";
}

// ---------- Sorting ----------
void bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        bool swapped = false;
        for (size_t j = 1; j < arr.size() - i; ++j) {
            if (arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0;
    int j = 0;
    int k = left;

    while (i < static_cast<int>(leftPart.size()) && j < static_cast<int>(rightPart.size())) {
        if (leftPart[i] <= rightPart[j]) {
            arr[k++] = leftPart[i++];
        } else {
            arr[k++] = rightPart[j++];
        }
    }

    while (i < static_cast<int>(leftPart.size())) {
        arr[k++] = leftPart[i++];
    }

    while (j < static_cast<int>(rightPart.size())) {
        arr[k++] = rightPart[j++];
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ---------- Searching ----------
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

// ---------- Graph Algorithms ----------
std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> order;
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return order;
}

void dfsImpl(const std::vector<std::vector<int>>& graph, int node, std::vector<bool>& visited, std::vector<int>& order) {
    visited[node] = true;
    order.push_back(node);

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsImpl(graph, neighbor, visited, order);
        }
    }
}

std::vector<int> dfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> order;
    std::vector<bool> visited(graph.size(), false);
    dfsImpl(graph, start, visited, order);
    return order;
}

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int source) {
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(graph.size(), INF);

    using Node = std::pair<int, int>; // (distance, vertex)
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currentDist > dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// ---------- Dynamic Programming ----------
int knapsack01(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    int n = static_cast<int>(weights.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    return dp[n][capacity];
}

int longestCommonSubsequence(const std::string& a, const std::string& b) {
    int n = static_cast<int>(a.size());
    int m = static_cast<int>(b.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

} // namespace algo

int main() {
    using namespace algo;

    std::cout << "=== C++ Algorithms Demo ===\n\n";

    std::vector<int> data = {7, 2, 9, 4, 3, 8, 1, 6, 5};
    std::vector<int> a = data;
    std::vector<int> b = data;
    std::vector<int> c = data;
    std::vector<int> d = data;

    bubbleSort(a);
    insertionSort(b);
    mergeSort(c, 0, static_cast<int>(c.size()) - 1);
    quickSort(d, 0, static_cast<int>(d.size()) - 1);

    printVector(data, "Original");
    printVector(a, "Bubble Sort");
    printVector(b, "Insertion Sort");
    printVector(c, "Merge Sort");
    printVector(d, "Quick Sort");

    int target = 6;
    std::cout << "\nBinary Search target=" << target << ", index=" << binarySearch(d, target) << "\n";

    std::vector<std::vector<int>> unweightedGraph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };

    std::vector<int> bfsOrder = bfs(unweightedGraph, 0);
    std::vector<int> dfsOrder = dfs(unweightedGraph, 0);

    printVector(bfsOrder, "\nBFS Order");
    printVector(dfsOrder, "DFS Order");

    std::vector<std::vector<std::pair<int, int>>> weightedGraph = {
        {{1, 4}, {2, 1}},
        {{3, 1}},
        {{1, 2}, {3, 5}},
        {{4, 3}},
        {}
    };

    std::vector<int> dist = dijkstra(weightedGraph, 0);
    printVector(dist, "\nDijkstra Distances from 0");

    std::vector<int> weights = {2, 3, 4, 5};
    std::vector<int> values = {3, 4, 5, 8};
    int capacity = 8;
    std::cout << "\n0/1 Knapsack max value (capacity=" << capacity << "): "
              << knapsack01(weights, values, capacity) << "\n";

    std::string s1 = "AGGTAB";
    std::string s2 = "GXTXAYB";
    std::cout << "LCS length between \"" << s1 << "\" and \"" << s2 << "\": "
              << longestCommonSubsequence(s1, s2) << "\n";

    return 0;
}
