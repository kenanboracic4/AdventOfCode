#include <bits/stdc++.h>
using namespace std;

// Helper: trim spaces from both ends
static inline string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a==string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b-a+1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Cannot open input.txt\n";
        return 1;
    }

    string line;
    long long total_min = 0;
    int line_no = 0;
    while (std::getline(fin, line)) {
        line_no++;
        line = trim(line);
        if (line.empty()) continue;

        // parse [pattern]
        size_t lb = line.find('[');
        size_t rb = line.find(']');
        if (lb==string::npos || rb==string::npos || rb<=lb) {
            cerr << "Parse error: no [..] on line " << line_no << "\n";
            return 1;
        }
        string pattern = line.substr(lb+1, rb-lb-1);
        int n = (int)pattern.size();
        // target mask: '#' -> 1, '.' -> 0
        unsigned long long target = 0;
        if (n > 63) {
            cerr << "Too many indicators (>63) on line " << line_no << "\n";
            return 1;
        }
        for (int i=0;i<n;i++) if (pattern[i]=='#') target |= (1ull<<i);

        // parse all (...) button groups between rb and next '{' (or end)
        vector<unsigned long long> buttons;
        size_t pos = rb+1;
        while (true) {
            size_t lp = line.find('(', pos);
            size_t rp = line.find(')', pos);
            if (lp==string::npos || rp==string::npos) break;
            if (rp <= lp) { pos = rp+1; continue; }
            string inside = line.substr(lp+1, rp-lp-1);
            // parse comma separated ints
            unsigned long long mask = 0;
            stringstream ss(inside);
            string tok;
            while (getline(ss, tok, ',')) {
                tok = trim(tok);
                if (tok.empty()) continue;
                int idx = stoi(tok);
                if (idx < 0 || idx >= n) {
                    cerr << "Button index out of range on line " << line_no << "\n";
                    return 1;
                }
                mask ^= (1ull<<idx); // toggle bit for this button's mask
            }
            buttons.push_back(mask);
            pos = rp+1;
        }

        int m = (int)buttons.size();
        if (m == 0) {
            // no buttons: only solvable if target == 0
            if (target == 0) {
                // zero presses needed
            } else {
                cerr << "No buttons but nonzero target on line " << line_no << "\n";
                return 1;
            }
            continue;
        }

        // Brute-force subsets of buttons. If m is large this is exponential.
        // We set a reasonable safety cutoff to avoid insane runtimes.
        if (m > 28) {
            // fallback: use Gaussian elimination to check solvability but not guarantee minimum.
            // For typical puzzle inputs this branch should not be needed.
            // We'll try to find *a* solution with minimal weight via enumerating nullspace if small.
            // For simplicity here: report error.
            cerr << "Too many buttons (" << m << ") on line " << line_no << " for brute-force solver.\n";
            return 1;
        }

        unsigned long long best = ULLONG_MAX;
        unsigned long long totalComb = 1ull<<m;
        for (unsigned long long mask = 0; mask < totalComb; ++mask) {
            unsigned long long cur = 0;
            // apply each button present in mask
            // also count number of set bits (presses)
            unsigned int presses = 0;
            unsigned long long mm = mask;
            while (mm) {
                unsigned long long lowbit = mm & -mm;
                int idx = __builtin_ctzll(mm);
                cur ^= buttons[idx];
                mm -= lowbit;
                ++presses;
                // small optimization: if presses already >= best, break
                if (presses >= best) break;
            }
            if (presses >= best) continue;
            if (cur == target) {
                if (presses < best) best = presses;
            }
        }

        if (best == ULLONG_MAX) {
            cerr << "No solution for machine on line " << line_no << "\n";
            return 1;
        }

        total_min += (long long)best;
    }

    cout << total_min << "\n";
    return 0;
}
