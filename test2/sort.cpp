#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

vector<int> generateRandomArray(int size, int maxValue = 10000) {
    vector<int> arr(size);
    for (int& x : arr) {
        x = rand() % (maxValue + 1);
    }
    return arr;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Using: " << argv[0] << " <repetitions> <array_size>" << endl;
        return 1;
    }

    int repetitions = stoi(argv[1]);
    int arraySize = stoi(argv[2]);

    srand(static_cast<unsigned>(time(nullptr)));

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < repetitions; ++i) {
        vector<int> arr = generateRandomArray(arraySize);

        quicksort(arr, 0, arraySize - 1);
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    cout << "Sorted time: " << elapsed.count() << " seconds" << endl;

    return 0;
}
