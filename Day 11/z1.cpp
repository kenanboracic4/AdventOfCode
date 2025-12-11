#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> graph;
unordered_map<string, long long> memo;

// uklanja SVE whitespace (ASCII + Unicode) sa početka i kraja
string trim(const string &s) {
    int i = 0, j = (int)s.size() - 1;

    auto is_ws = [&](char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
               c == '\v' || c == '\f';
    };

    while (i <= j && is_ws(s[i])) i++;
    while (j >= i && is_ws(s[j])) j--;
    return s.substr(i, j - i + 1);
}

long long dfs(const string &node) {
    if (node == "out") return 1;
    if (memo.count(node)) return memo[node];

    long long total = 0;
    for (auto &nxt : graph[node]) total += dfs(nxt);
    return memo[node] = total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("z11.1.txt");
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
        string right = trim(line.substr(pos + 1));

        stringstream ss(right);
        string to;
        while (ss >> to) {
            graph[from].push_back(trim(to));
        }
    }

    long long result = dfs("you");

    cout << result << "\n";
    return 0;
}