#pragma once
#include "bits.hpp"
using namespace std;

/*   @   @   @   @   @   @   @   @   *\

@+-+-+-+-+ PHYSICS VARIABLE +-+-+-+-+@

\*   @   @   @   @   @   @   @   @   */

// specific heat parameter
constexpr double Gam = 5.0/3.0;// 1.0 <= Gam <= 2.0

/*   @   @   @   @   @   @   @   @   *\

@+-+-+-+-+ PHYSICS CONSTANT +-+-+-+-+@

\*   @   @   @   @   @   @   @   @   */

// natural unit constant
constexpr double hbarc = 197.326980;// [MeV * fm]
constexpr double hbarcGeV = 0.197326980;
constexpr double hbarcGeVinv = 1.0 / hbarcGeV;

constexpr double PI = 3.14159265358979;

/*   @   @   @   @   @   @   @   @   @   @   *\

@+-+-+-+-+ COMPUTATIONAL CONSTANT +-+-+-+-+@

\*   @   @   @   @   @   @   @   @   @   @   */

// mathematical constant
constexpr double EPS = 1.0e-8;// convergence parameter of Newton method

//constexpr int vitera = 8;// v_solver Newton method iteration 今はv_solver内で直接定義
//constexpr int Ritera = 8;// Riemann solver iteration

/*   @   @   @   @   @   @   @   @   @   @   *\

@+-+-+-+-+ COMPUTATIONAL VARIABLE +-+-+-+-+@

\*   @   @   @   @   @   @   @   @   @   @   */

//computational variable
constexpr double CFL = 1.0 / 5.0;// CFL condition 0.1 <= CFL <= 0.4

constexpr int SC = 3;// 計算セルの両端に準備

constexpr int Nx = 200;
constexpr int Ny = 10;
constexpr int Nz = 10;
//constexpr int Ntot = (Nx + 2*SC) * (Ny + 2*SC) * (Nz + 2*SC);

constexpr double dx = 0.5;
constexpr double dy = 0.5;
constexpr double dz = 0.5;
constexpr double dt = dx * CFL;

constexpr int STEPs = 500;
constexpr double tfinal = dt * STEPs;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
