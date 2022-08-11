#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;

void cpu_gpu(vector<string> n){
    string s;
    int value = 0;
    for (int i = 0; i < 2; ++i) {
        ifstream file(n[i]);
        if (!file.is_open()) {
            throw std::invalid_argument("There is no such file");
        }
        getline(file, s);
        value = stoi(s);
        file.close();
        value /= 1000;
        if (i == 0)
            cout << "CPU: " << value << endl;
        else cout << "GPU: " << value << endl;
    }
}

void load(string ss, int count_cores){
    vector<int> strs1;
    vector<int> strs2;
    string s;

    for (int j = 0; j < 2; ++j) {
        ifstream file(ss);
        getline(file, s);
        auto pos2 = 4;
        for (int i = 0; i < 4; ++i) {
            auto pos1 = s.find( ' ', pos2);
            pos2 = s.find(' ', pos1 + 1);
            if(j == 0)
                strs1.push_back(stoi(s.substr(pos1, pos2)));
            else strs2.push_back(stoi(s.substr(pos1, pos2)));
        }
        sleep(1);
        file.close();
    }

    vector<int> razn_strs;
    for (int i = 0; i < 4; ++i) {
        razn_strs.push_back(strs2[i] - strs1[i]);
    }
    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        sum += razn_strs[i];
    }
    int avr_load = ((razn_strs[0] + razn_strs[1] + razn_strs[2]) * 100 / sum);
    cout << "Load: " << avr_load << '%';
}

int main() {
    int count_cores = 8;
    vector<string> n = {"/sys/class/hwmon/hwmon4/temp1_input", // cpu
                        "/sys/class/hwmon/hwmon7/temp1_input"}; // gpu
    string ss = "/proc/stat"; // load
    cpu_gpu(n);
    load(ss, count_cores);
}