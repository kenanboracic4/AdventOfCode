#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> graph;
unordered_map<string, array<long long, 4>> memo;
unordered_map<string, bool> computed;

string trim(const string &s) {
    int i = 0, j = (int)s.size() - 1;
    while (i <= j && isspace((unsigned char)s[i])) i++;
    while (j >= i && isspace((unsigned char)s[j])) j--;
    return s.substr(i, j - i + 1);
}

array<long long, 4> dfs(const string &node) {
    if (computed[node])
        return memo[node];

    array<long long, 4> res = {0,0,0,0};

    if (node == "out") {
        res[0] = 1;
        computed[node] = true;
        memo[node] = res;
        return memo[node];
    }

    for (const string &nxt : graph[node]) {
        auto sub = dfs(nxt);

        for (int m = 0; m < 4; m++) {
            int newmask = m;

            if (node == "fft") newmask |= 1;   // bit 0
            if (node == "dac") newmask |= 2;   // bit 1

            res[newmask] += sub[m];
        }
    }

    computed[node] = true;
    memo[node] = res;
    return memo[node];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("input.txt");
    if (!fin) {
        cout << "Ne mogu otvoriti z11.txt\n";
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        line = trim(line);
        if (line.empty()) continue;

        size_t pos = line.find(':');
        if (pos == string::npos) continue;

        string from = trim(line.substr(0, pos));
        string rest = trim(line.substr(pos + 1));

        stringstream ss(rest);
        string to;
        while (ss >> to) {
            graph[from].push_back(trim(to));
        }
    }

    auto result = dfs("svr");

    cout << result[3] << "\n";  // maska 3 = fft + dac
    return 0;
}