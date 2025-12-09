#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
};

// Funkcija za provjeru da li je tačka unutar poligona (Ray Casting Algoritam)
// Vraca true ako je na granici ILI unutar poligona (Red/Green)
bool is_inside(ll px, ll py, const vector<Point>& polygon) {
    int n = polygon.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        ll xi = polygon[i].x, yi = polygon[i].y;
        ll xj = polygon[j].x, yj = polygon[j].y;

        // 1. Provjera da li je tačka na samoj IVICI (Granica Poligona)
        // Horizontalna granica (Segment)
        if (yi == yj && yi == py && px >= min(xi, xj) && px <= max(xi, xj)) return true;
        // Vertikalna granica (Segment)
        if (xi == xj && xi == px && py >= min(yi, yj) && py <= max(yi, yj)) return true;

        // 2. Standardni Ray Casting: Provjera presjeka
        if (((yi > py) != (yj > py)) &&
            (px < (xj - xi) * (py - yi) / (yj - yi) + xi)) {
            inside = !inside;
        }
    }
    return inside;
}

// Funkcija za provjeru da li je cijeli pravougaonik popunjen Dozvoljenim Skupom (Red/Green)
// Ovo je i dalje heuristička funkcija, fokusirana na provjeru rubova.
bool is_rectangle_pure(ll x_min, ll y_min, ll x_max, ll y_max, const vector<Point>& reds) {
    // 1. Provjerite rubove pravougaonika
    // Horizontalni rubovi
    for (ll x = x_min; x <= x_max; ++x) {
        if (!is_inside(x, y_min, reds)) return false; // Donji rub
        if (!is_inside(x, y_max, reds)) return false; // Gornji rub
    }
    // Vertikalni rubovi
    for (ll y = y_min; y <= y_max; ++y) {
        if (!is_inside(x_min, y, reds)) return false; // Lijevi rub
        if (!is_inside(x_max, y, reds)) return false; // Desni rub
    }

    // 2. Provjera unutrašnjosti
    // Pošto ne možemo iterirati cijelu unutrašnjost, provjeravamo samo jedan centar.
    // Ako su rubovi unutar i jedna unutrašnja tačka unutar, pretpostavljamo da je cijeli
    // pravougaonik unutar konveksnog oblika Red/Green Poligona (što je ovdje slučaj).
    if (x_max - x_min > 0 && y_max - y_min > 0) {
        ll cx = (x_min + x_max) / 2;
        ll cy = (y_min + y_max) / 2;
        if (!is_inside(cx, cy, reds)) return false;
    }

    // U slučaju tankih pravougaonika (W=1 ili H=1), već smo provjerili sve tačke
    // kroz rubnu provjeru, pa je ova provjera unutrašnjosti nepotrebna.

    return true;
}


ll solve() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Greska pri otvaranju input.txt" << endl;
        return 0;
    }

    vector<Point> reds;
    ll x, y;
    char comma;
    // Učitavanje koordinata u formatu X,Y
    while (inputFile >> x >> comma >> y) {
        reds.push_back({x, y});
    }

    if (reds.size() < 2) return 0;

    ll max_area = 0;

    // Iteriranje kroz sve parove crvenih pločica
    for (size_t i = 0; i < reds.size(); ++i) {
        for (size_t j = i + 1; j < reds.size(); ++j) {
            ll x1 = reds[i].x;
            ll y1 = reds[i].y;
            ll x2 = reds[j].x;
            ll y2 = reds[j].y;

            // Nema potrebe da se provjerava x1==x2 ili y1==y2, jer su i tanki
            // pravougaonici (W*1 ili 1*H) dozvoljeni.
            // if (x1 == x2 || y1 == y2) continue;

            ll x_min = min(x1, x2);
            ll x_max = max(x1, x2);
            ll y_min = min(y1, y2);
            ll y_max = max(y1, y2);

            // Ispravka: Površina se računa kao (W+1)*(H+1) jer su pločice uključive
            // Apsolutna razlika koordinata (npr. 9 i 2) je 7, što znaci 8 plocica.
            ll width = x_max - x_min + 1;
            ll height = y_max - y_min + 1;

            ll current_area = width * height;

            // Provjera da li su svi unutar pravougaonika Red/Green
            if (is_rectangle_pure(x_min, y_min, x_max, y_max, reds)) {
                max_area = max(max_area, current_area);
            }
        }
    }

    return max_area;
}

int main() {
    // Postavljamo ulazne podatke za testni primjer u input.txt:
    /*
    7,1
    11,1
    11,7
    9,7
    9,5
    2,5
    2,3
    7,3
    */

    ll result = solve();
    cout << "Najveca povrsina pravougaonika (Red/Green only) je: " << result << endl;

    return 0;
}