#include "header.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

double Cell::t = 0.0;

Cell::Cell(){
        vector<double> zero3d(3,0.0),zero5d(5,0.0);

        this->x = this->v = zero3d;
        this->U = this->G = zero5d;

        this->n = this->e = this->p = 0.0;

        this->Svmin = this->Svmax = 0.0;
}

Cell::~Cell(){}

double Cell::v2(){
        return sqrt(this->v.at(0)*this->v.at(0) + this->v.at(1)*this->v.at(1) + this->v.at(2)*this->v.at(2));
}

double Cell::W(){
        return 1.0 / sqrt(1.0 - this->v2() * this->v2());
}

double Cell::c2(){
        //return sqrt(Gam * (Gam - 1.0) * (this->e) / (this->n + Gam * this->e));
        return sqrt(Gam * (Gam - 1.0) * (this->e - this->n) / (this->n + Gam * (this->e - this->n)));
}

vector<Cell> cell(Nx + 2*SC),faceL(Nx + 2*SC),faceR(Nx + 2*SC);
//vector<vector<vector<Cell>>> cell(Nx + 2*SC,vector<vector<Cell>>(Ny + 2*SC,vector<Cell>(Nz + 2*SC)));
