#include "header.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

GetU::GetU(){}
GetU::~GetU(){}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

GetU_rhd::GetU_rhd(){}
GetU_rhd::~GetU_rhd(){}

void GetU_rhd::getR(Cell& CELL){
        CELL.U.at(0) = CELL.W() * CELL.n;
}

void GetU_rhd::getM(Cell& CELL){
        CELL.U.at(1) = CELL.W() * CELL.W() * (CELL.e + CELL.p) * CELL.v.at(0);
        CELL.U.at(2) = CELL.W() * CELL.W() * (CELL.e + CELL.p) * CELL.v.at(1);
        CELL.U.at(3) = CELL.W() * CELL.W() * (CELL.e + CELL.p) * CELL.v.at(2);
}

void GetU_rhd::getE(Cell& CELL){
        CELL.U.at(4) = CELL.W() * CELL.W() * (CELL.e + CELL.p) - CELL.p;
}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
