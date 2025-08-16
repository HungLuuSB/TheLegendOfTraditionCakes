#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

const float pi = 3.141526535;

vector<string> split(const string& input, char delimiter) {
    vector<string> tokens;
    stringstream ss(input);
    string item;

    while (getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}


void writeToFile(int bc, int bg, float nd) {
    ofstream outputFileStream("output.out");
    outputFileStream << bc << " " <<  bg << " " << fixed << setprecision(3) << nd;
    outputFileStream.close();
}

float calculateNBC(int dc) {
    return dc * dc * sqrt(dc);
}

float calculateNBG(int dg) {
    return (dg * dg * pi) / 3;
}

int calculateLDBC(int dc) {
    if (dc >= 5)
        return 2;
    return 1;
}

int calculateLDBG(int dg) {
    if (dg >= 8)
        return 2;
    return 1;
}

void calculate(string& weather, int& n, int dc, int dg, int& ld, int& bc, int& bg, float& nd) {
    float n_bc = calculateNBC(dc);
    float n_bg = calculateNBG(dg);
    int ld_bc = calculateLDBC(dc);
    int ld_bg = calculateLDBG(dg);
    if (weather == "Windy") {
        while (nd >= n_bc && ld >= ld_bc) {
            bc++;
            ld -= ld_bc;
            nd -= n_bc;
        }
        while (nd >= n_bg && ld >= ld_bg) {
            bg++;
            ld -= ld_bg;
            nd -= n_bg;
        }
    } else if (weather == "Rainy") {
        bool can_cook_bc = true, can_cook_bg = true;
        while (can_cook_bc || can_cook_bg) {
            if (nd >= n_bc && ld >= ld_bc) {
                bc++;
                ld -= ld_bc;
                nd -= n_bc;
            } else {
                can_cook_bc = false;
            }

            if (nd >= n_bg && ld >= ld_bg) {
                bg++;
                ld -= ld_bg;
                nd -= n_bg;
            } else {
                can_cook_bg = false;
            }
        }
    }
}

int main() {
    string value;

    ifstream inputFileStream("input.inp");
    getline(inputFileStream, value);
    inputFileStream.close();

    vector<string> values = split(value, ' ');

    int n = 0, dg = 0, dc = 0, ld = 0, bc = 0, bg = 0;
    float nd = 0;
    string w;

    n = stoi(values[0]);
    dc = stoi(values[1]);
    dg = stoi(values[2]);
    ld = stoi(values[3]);
    w = values[4];

    nd = n;

    if (dc == 0 && dg == 0) {
        writeToFile(-1, -1, n);
        return 0;
    }

    calculate(w, n, dc, dg, ld, bc, bg, nd);
    writeToFile(bc, bg, nd);
    return 0;
}