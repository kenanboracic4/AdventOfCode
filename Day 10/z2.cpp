#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>
#include "input_reader.h"

using namespace std;

const long double EPSILON = 1e-8;
const int SEARCH_RANGE = 200;

struct Machine {
    vector<vector<long long>> A;
    vector<long long> b;
    int J;
    int B;
};

Machine parseMachinePartTwo(const string& line) {
    Machine machine;

    size_t joltage_start = line.find('{');
    size_t joltage_end = line.find('}');
    if (joltage_start == string::npos || joltage_end == string::npos) {
        machine.J = 0;
        return machine;
    }
    string joltage_str = line.substr(joltage_start + 1, joltage_end - joltage_start - 1);

    stringstream ss_joltage(joltage_str);
    string joltage_val;
    while (getline(ss_joltage, joltage_val, ',')) {
        try {
            machine.b.push_back(stoll(joltage_val));
        } catch (...) {}
    }
    machine.J = machine.b.size();

    size_t lights_end = line.find(']');
    size_t buttons_start = lights_end + 1;

    string buttons_str = line.substr(buttons_start, joltage_start - buttons_start);
    stringstream ss_buttons(buttons_str);
    string button_schematic;
    vector<vector<long long>> toggles;

    while (getline(ss_buttons, button_schematic, '(')) {
        if (button_schematic.empty()) continue;

        size_t end_paren = button_schematic.find(')');
        if (end_paren == string::npos) continue;

        string indices_str = button_schematic.substr(0, end_paren);

        vector<long long> current_toggles(machine.J, 0);

        stringstream ss_indices(indices_str);
        string index_str;
        while (getline(ss_indices, index_str, ',')) {
            try {
                int index = stoi(index_str);
                if (index >= 0 && index < machine.J) {
                    current_toggles[index] = 1;
                }
            } catch (...) {}
        }
        toggles.push_back(current_toggles);
    }

    machine.B = toggles.size();
    if (machine.B > 0) {
        machine.A.resize(machine.J, vector<long long>(machine.B, 0));
        for (int j = 0; j < machine.B; ++j) {
            for (int i = 0; i < machine.J; ++i) {
                machine.A[i][j] = toggles[j][i];
            }
        }
    } else {
        machine.B = 0;
    }

    return machine;
}

long long solveMachinePartTwo(Machine& m) {
    if (m.J == 0 || m.B == 0) return 0;

    vector<vector<long double>> M(m.J, vector<long double>(m.B + 1));
    for (int i = 0; i < m.J; ++i) {
        for (int j = 0; j < m.B; ++j) {
            M[i][j] = (long double)m.A[i][j];
        }
        M[i][m.B] = (long double)m.b[i];
    }
    int B_aug = m.B + 1;

    //Gaussian elimination
    int current_row = 0;
    vector<int> pivot_cols;

    for (int lead_col = 0; lead_col < m.B && current_row < m.J; ++lead_col) {
        int pivot_row_idx = current_row;
        for(int i = current_row + 1; i < m.J; ++i) {
            if (abs(M[i][lead_col]) > abs(M[pivot_row_idx][lead_col])) {
                pivot_row_idx = i;
            }
        }

        if (abs(M[pivot_row_idx][lead_col]) > EPSILON) {
            swap(M[pivot_row_idx], M[current_row]);
            pivot_cols.push_back(lead_col);

            long double pivot_val = M[current_row][lead_col];
            for (int k = lead_col; k < B_aug; ++k) {
                M[current_row][k] /= pivot_val;
            }

            for (int r = 0; r < m.J; ++r) {
                if (r != current_row) {
                    long double factor = M[r][lead_col];
                    for (int k = lead_col; k < B_aug; ++k) {
                        M[r][k] -= factor * M[current_row][k];
                    }
                }
            }

            current_row++;
        }
    }

    //check
    for (int r = current_row; r < m.J; ++r) {
        if (abs(M[r][m.B]) > EPSILON) {
            return -1;
        }
    }

    vector<int> free_cols;
    int current_pivot_row = 0;
    for (int j = 0; j < m.B; ++j) {
        if (current_pivot_row < pivot_cols.size() && j == pivot_cols[current_pivot_row]) {
            current_pivot_row++;
        } else {
            free_cols.push_back(j);
        }
    }
    int k = free_cols.size();

    long long min_total_presses = -1;
    vector<long long> current_free_vars(k);

    //recursive minimization search
    function<void(int)> search =
        [&](int index) {
        if (index == k) {
            vector<long double> current_x(m.B, 0.0);
            bool non_negative = true;
            bool all_integer = true;

            for (int i = 0; i < k; ++i) {
                current_x[free_cols[i]] = (long double)current_free_vars[i];
            }

            for (int r = 0; r < pivot_cols.size(); ++r) {
                int pivot_col = pivot_cols[r];
                long double value = M[r][m.B];

                for (int i = 0; i < k; ++i) {
                    value -= M[r][free_cols[i]] * current_x[free_cols[i]];
                }

                current_x[pivot_col] = value;

                if (value < -EPSILON) {
                    non_negative = false; break;
                }
                if (abs(value - round(value)) > EPSILON) {
                    all_integer = false; break;
                }
            }
            if (!non_negative || !all_integer) return;

            long long current_total = 0;
            for (int j = 0; j < m.B; ++j) {
                long long presses = (long long)round(current_x[j]);
                if (presses < 0) return;
                current_total += presses;
            }

            if (min_total_presses == -1 || current_total < min_total_presses) {
                min_total_presses = current_total;
            }

        } else {
            for (long long val = -SEARCH_RANGE; val <= SEARCH_RANGE; ++val) {
                current_free_vars[index] = val;
                search(index + 1);
            }
        }
    };

    search(0);

    return min_total_presses;
}

int main() {
    vector<string> lines = readLines("input.txt");

    long long total_min_presses = 0;
    int machine_count = 0;
    for (const string& line : lines) {
        if (line.empty()) continue;
        cout<<"Processing machine no. "<<machine_count+1<<endl;

        Machine machine = parseMachinePartTwo(line);
        if (machine.J == 0) continue;

        long long min_presses = solveMachinePartTwo(machine);

        if (min_presses == -1) {
            cout << "\tERROR on machine " << machine_count + 1 << endl;
        } else {
            total_min_presses += min_presses;
        }

        machine_count++;
    }

    cout << "Total min presses: " << total_min_presses << endl;

    return 0;
}