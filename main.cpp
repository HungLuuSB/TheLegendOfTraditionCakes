#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

const float pi = 3.141526535;

void writeToFile(int bc, int bg, float nd) {
  ofstream outputFileStream("output.out");
  outputFileStream << bc << " " << bg << " " << fixed << setprecision(3) << nd;
  outputFileStream.close();
}

float calculateNBC(int dc) { return dc * dc * sqrt(dc); }

float calculateNBG(int dg) { return (dg * dg * pi) / 3; }

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

void calculate(string &weather, int &n, int dc, int dg, int &ld, int &bc,
               int &bg, float &nd) {
  float n_bc = calculateNBC(dc);
  float n_bg = calculateNBG(dg);
  int ld_bc = calculateLDBC(dc);
  int ld_bg = calculateLDBG(dg);

  cout << "Nep needed to cook 1 BC = " << n_bc << endl;
  cout << "La dong needed to cook 1 BC = " << ld_bc << endl;
  cout << "Nep needed to cook 1 BG = " << n_bg << endl;
  cout << "La dong needed to cook 1 BG = " << ld_bg << endl;
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
  fstream inputFileStream("input.inp");
  int n = 0, dc = 0, dg = 0, ld = 0, bc = 0, bg = 0;
  float nd = 0;
  string w;

  inputFileStream >> n >> dc >> dg >> ld >> w;
  inputFileStream.close();

  cout << n << " " << dc << " " << dg << " " << ld << " " << w << endl;
  nd = n;

  if (dc == 0 && dg == 0) {
    writeToFile(-1, -1, n);
    return 0;
  }

  calculate(w, n, dc, dg, ld, bc, bg, nd);
  writeToFile(bc, bg, nd);
  cout << bc << " " << bg << " " << nd << endl;
  return 0;
}
