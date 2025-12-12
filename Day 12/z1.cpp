#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <stdexcept>

using namespace std;

struct Point {
    int r, c;
    bool operator<(const Point& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }
};

typedef vector<Point> Shape;
vector<Shape> baseShapes;

Shape normalize(const Shape& shape) {
    if (shape.empty()) return shape;
    int minR = shape[0].r;
    int minC = shape[0].c;
    for (const auto& p : shape) {
        minR = min(minR, p.r);
        minC = min(minC, p.c);
    }
    Shape normalizedShape;
    for (const auto& p : shape) {
        normalizedShape.push_back({p.r - minR, p.c - minC});
    }
    sort(normalizedShape.begin(), normalizedShape.end());
    return normalizedShape;
}

vector<Shape> rotateAndFlip(const Shape& shape) {
    set<Shape> uniqueVariations;
    Shape current = shape;

    for (int i = 0; i < 4; ++i) {
        uniqueVariations.insert(normalize(current));

        Shape flipped;
        for (const auto& p : current) flipped.push_back({p.r, -p.c});
        uniqueVariations.insert(normalize(flipped));

        Shape nextRot;
        for (const auto& p : current) nextRot.push_back({p.c, -p.r});
        current = nextRot;
    }
    return vector<Shape>(uniqueVariations.begin(), uniqueVariations.end());
}

bool canPlace(const vector<vector<bool>>& grid, const Shape& shape, int start_r, int start_c, int H, int W) {
    for (const auto& p : shape) {
        int nr = start_r + p.r;
        int nc = start_c + p.c;
        if (nr < 0 || nr >= H || nc < 0 || nc >= W || grid[nr][nc]) {
            return false;
        }
    }
    return true;
}

void toggleShape(vector<vector<bool>>& grid, const Shape& shape, int start_r, int start_c, bool val) {
    for (const auto& p : shape) {
        grid[start_r + p.r][start_c + p.c] = val;
    }
}

bool solve(vector<vector<bool>>& grid, const vector<int>& piecesToFit, int pieceIdx, const vector<vector<Shape>>& allVariations, int H, int W) {

    if (pieceIdx == piecesToFit.size()) {
        return true;
    }

    int currentShapeID = piecesToFit[pieceIdx];
    const vector<Shape>& variations = allVariations[currentShapeID];

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {

            for (const auto& var : variations) {

                if (canPlace(grid, var, r, c, H, W)) {

                    toggleShape(grid, var, r, c, true);

                    if (solve(grid, piecesToFit, pieceIdx + 1, allVariations, H, W)) {
                        return true;
                    }

                    toggleShape(grid, var, r, c, false);
                }
            }
        }
    }

    return false;
}

int main() {

    ifstream infile("input.txt");
    if (!infile.is_open()) {
        cout << "[GRESKA] Ne mogu otvoriti input.txt! Provjerite putanju." << endl;
        return 1;
    }

    string line;
    vector<string> rawRegions;

    vector<string> currentShapeLines;
    int shapeID = 0;

    cout << "[INFO] Ucitavam podatke..." << endl;

    while (getline(infile, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line.empty()) {
            if (!currentShapeLines.empty()) {
                Shape newShape;
                for (int r = 0; r < currentShapeLines.size(); ++r) {
                    for (int c = 0; c < currentShapeLines[r].length(); ++c) {
                        if (currentShapeLines[r][c] == '#') {
                            newShape.push_back({r, c});
                        }
                    }
                }
                if (!newShape.empty()) {
                    baseShapes.push_back(newShape);
                    cout << " -> Ucitavam oblik ID: " << shapeID++ << " (Velicina: " << newShape.size() << ")" << endl;
                }
                currentShapeLines.clear();
            }
        }
        else if (line.find('x') != string::npos && line.find(':') != string::npos) {
            rawRegions.push_back(line);
        }
        else {
            currentShapeLines.push_back(line);
        }
    }

    if (!currentShapeLines.empty()) {
        Shape newShape;
        for (int r = 0; r < currentShapeLines.size(); ++r) {
            for (int c = 0; c < currentShapeLines[r].length(); ++c) {
                if (currentShapeLines[r][c] == '#') {
                    newShape.push_back({r, c});
                }
            }
        }
        if (!newShape.empty()) {
            baseShapes.push_back(newShape);
            cout << " -> Ucitavam oblik ID: " << shapeID++ << " (Velicina: " << newShape.size() << ")" << endl;
        }
    }


    cout << "[INFO] Generiram rotacije i zrcaljenja oblika..." << endl;
    vector<vector<Shape>> allVariations;
    for (const auto& shape : baseShapes) {
        allVariations.push_back(rotateAndFlip(shape));
    }

    cout << "[INFO] Pocirem rjesavanje regija..." << endl;
    int successfulRegions = 0;

    for (const string& regionLine : rawRegions) {
        stringstream ss(regionLine);
        string segment;

        getline(ss, segment, 'x'); int W = stoi(segment);
        getline(ss, segment, ':'); int H = stoi(segment);

        vector<int> piecesToFit;
        int count, currentShapeID = 0;
        long long totalPiecesArea = 0;

        while (ss >> count) {
            for (int k = 0; k < count; ++k) piecesToFit.push_back(currentShapeID);

            if (currentShapeID < baseShapes.size()) {
                 totalPiecesArea += (long long)count * baseShapes[currentShapeID].size();
            }

            currentShapeID++;
        }

        long long gridArea = (long long)H * W;

        sort(piecesToFit.begin(), piecesToFit.end(), [&](int a, int b) {
            return baseShapes[a].size() > baseShapes[b].size();
        });

        cout << " -> Provjeravam regiju " << W << "x" << H << ": ";

        if (totalPiecesArea > gridArea) {
            cout << "NEUSPJEH (Nedovoljno prostora: " << totalPiecesArea << " > " << gridArea << ")" << endl;
            continue;
        }

        vector<vector<bool>> grid(H, vector<bool>(W, false));

        if (solve(grid, piecesToFit, 0, allVariations, H, W)) {
            successfulRegions++;
            cout << "USPJEH!" << endl;
        } else {
            cout << "NEUSPJEH " << endl;
        }
    }

    cout << "\n[REZULTAT] Ukupno uspješnih regija: " << successfulRegions << endl;

    return 0;
}