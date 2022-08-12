#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;

int cpu_gpu(string n) {
    string s;
    int value = 0;
    ifstream file(n);
    if (!file.is_open()) {
        throw std::invalid_argument("There is no such file");
    }
    getline(file, s);
    value = stoi(s);
    file.close();
    value /= 1000;
    return value;
}

int load(string ss) {
    int strs1[4];
    int strs2[4];
    string s;

    for (int j = 0; j < 2; ++j) {
        ifstream file(ss);
        getline(file, s);
        auto pos2 = 4;
        for (int i = 0; i < 4; ++i) {
            auto pos1 = s.find(' ', pos2);
            pos2 = s.find(' ', pos1 + 1);
            if (j == 0)
                strs1[i] = stoi(s.substr(pos1, pos2));
            else strs2[i] = stoi(s.substr(pos1, pos2));
        }
        sleep(1);
        file.close();
    }

    int razn_strs[4];
    for (int i = 0; i < 4; ++i) {
        razn_strs[i] = strs2[i] - strs1[i];
    }
    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        sum += razn_strs[i];
    }
    return ((razn_strs[0] + razn_strs[1] + razn_strs[2]) * 100 / sum);
}

int main() {
    const string n[2] = {"/sys/class/hwmon/hwmon4/temp1_input", // cpu
                   "/sys/class/hwmon/hwmon7/temp1_input"}; // gpu
    string ss = "/proc/stat"; // load
    cout << "CPU: " << cpu_gpu(n[0]) << endl;
    cout << "GPU: " << cpu_gpu(n[1]) << endl;
    cout << "Load: " << load(ss);
}