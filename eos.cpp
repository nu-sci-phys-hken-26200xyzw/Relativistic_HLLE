#include "header.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

EoS::EoS(){}
EoS::~EoS(){}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

EoS_idgas::EoS_idgas(){}
EoS_idgas::~EoS_idgas(){}

void EoS_idgas::eos_p(Cell& CELL){
        CELL.p = (Gam - 1.0) * (CELL.e - CELL.n);
}

void EoS_idgas::eos_e(Cell& CELL){
        CELL.e = CELL.p / (Gam - 1.0) + CELL.n;
}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

EoS_ridgas::EoS_ridgas(){}
EoS_ridgas::~EoS_ridgas(){}

void EoS_ridgas::eos_p(Cell& CELL){
        CELL.p = (Gam - 1.0) * CELL.e;
}

void EoS_ridgas::eos_e(Cell& CELL){
        CELL.e = CELL.p / (Gam - 1.0);
}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
