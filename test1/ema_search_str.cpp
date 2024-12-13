#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

vector<int> preprocessPattern(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = lps[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        lps[i] = j;
    }
    return lps;
}

vector<int> kmpSearch(const string& text, const string& pattern, int repetitions) {
    int n = text.size();
    int m = pattern.size();

    vector<int> matches;
    vector<int> lps = preprocessPattern(pattern);

    for (int rep = 0; rep < repetitions; ++rep) {
        int i = 0;
        int j = 0;

        while (i < n) {
            if (text[i] == pattern[j]) {
                ++i;
                ++j;

                if (j == m) {
                    matches.push_back(i - j);
                    j = lps[j - 1];
                }
            } else {
                if (j > 0) {
                    j = lps[j - 1];
                } else {
                    ++i;
                }
            }
        }
    }
    return matches;
}

string readFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + fileName);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Using: " << argv[0] << " <filename> <pattern> <repetitions>" << endl;
        return 1;
    }

    string fileName = argv[1];
    string pattern = argv[2];
    int repetitions = stoi(argv[3]);

    try {
        string text = readFile(fileName);

        auto start = chrono::high_resolution_clock::now();
        vector<int> result = kmpSearch(text, pattern, repetitions);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed = end - start;
        cout << "Time elapsed: " << elapsed.count() << " seconds" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
