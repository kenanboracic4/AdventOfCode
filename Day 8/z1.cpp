#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <functional>

using namespace std;

struct Skupine {
    vector<int> roditelj;
    vector<int> velicina;

    Skupine(int n) {
        roditelj.resize(n);
        velicina.assign(n, 1);
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

    void spoji(int a, int b) {
        a = pronadji(a);
        b = pronadji(b);

        if (a != b) {
            if (velicina[a] < velicina[b]) {
                swap(a, b);
            }
            roditelj[b] = a;
            velicina[a] += velicina[b];
        }
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

    int K;
    if (n == 20) {
        K = 10;
    } else {
        K = 1000;
    }

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

    if (K > (int)sve_grane.size()) {
        K = (int)sve_grane.size();
    }

    for (int i = 0; i < K; i++) {
        Grana g = sve_grane[i];
        dsu.spoji(g.indeks_a, g.indeks_b);
    }

    map<int, long long> velicine_skupina;
    for (int i = 0; i < n; i++) {
        int korijen = dsu.pronadji(i);
        velicine_skupina[korijen]++;
    }

    vector<long long> lista_velicina;
    for (auto const& par : velicine_skupina) {
        lista_velicina.push_back(par.second);
    }

    sort(lista_velicina.begin(), lista_velicina.end(), greater<long long>());

    while (lista_velicina.size() < 3) {
        lista_velicina.push_back(1);
    }

    long long rezultat = lista_velicina[0] * lista_velicina[1] * lista_velicina[2];
    cout << rezultat << "\n";

    return 0;
}