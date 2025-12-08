#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Skupine {
    vector<int> roditelj;
    vector<int> velicina;
    int broj_komponenti;

    Skupine(int n) {
        roditelj.resize(n);
        velicina.resize(n, 1);
        broj_komponenti = n;
        for (int i = 0; i < n; i++) {
            roditelj[i] = i;
        }
    }

    int pronadji(int x) {
        if (roditelj[x] == x) {
            return x;
        }
        roditelj[x] = pronadji(roditelj[x]);
        return roditelj[x];
    }

    bool spoji(int a, int b) {
        int korijen_a = pronadji(a);
        int korijen_b = pronadji(b);

        if (korijen_a == korijen_b) {
            return false;
        }

        if (velicina[korijen_a] < velicina[korijen_b]) {
            swap(korijen_a, korijen_b);
        }

        roditelj[korijen_b] = korijen_a;
        velicina[korijen_a] += velicina[korijen_b];
        broj_komponenti--;
        return true;
    }
};

struct Tacka {
    long long x;
    long long y;
    long long z;
};

struct Grana {
    long long distanca_kvadrat;
    int indeks_a;
    int indeks_b;
};

bool porediGrane(const Grana& a, const Grana& b) {
    return a.distanca_kvadrat < b.distanca_kvadrat;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream ulazna_datoteka("input.txt");
    if (!ulazna_datoteka) {
        cerr << "Greska: ne mogu otvoriti z8.1.txt\n";
        return 1;
    }

    vector<Tacka> tacke;
    string linija;
    while (getline(ulazna_datoteka, linija)) {
        if (linija.empty()) continue;
        stringstream ss(linija);
        Tacka t;
        char c1, c2;
        ss >> t.x >> c1 >> t.y >> c2 >> t.z;
        tacke.push_back(t);
    }

    int n = tacke.size();
    if (n == 0) return 0;

    vector<Grana> sve_grane;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long dx = tacke[i].x - tacke[j].x;
            long long dy = tacke[i].y - tacke[j].y;
            long long dz = tacke[i].z - tacke[j].z;
            long long d2 = dx * dx + dy * dy + dz * dz;

            Grana nova_grana;
            nova_grana.distanca_kvadrat = d2;
            nova_grana.indeks_a = i;
            nova_grana.indeks_b = j;
            sve_grane.push_back(nova_grana);
        }
    }

    sort(sve_grane.begin(), sve_grane.end(), porediGrane);

    Skupine dsu(n);

    long long rezultat = 0;

    for (size_t k = 0; k < sve_grane.size(); k++) {
        Grana trenutna_grana = sve_grane[k];

        if (dsu.spoji(trenutna_grana.indeks_a, trenutna_grana.indeks_b)) {

            if (dsu.broj_komponenti == 1) {
                int a = trenutna_grana.indeks_a;
                int b = trenutna_grana.indeks_b;
                long long x1 = tacke[a].x;
                long long x2 = tacke[b].x;
                rezultat = x1 * x2;
                break;
            }
        }
    }

    cout << rezultat << "\n";
    return 0;
}