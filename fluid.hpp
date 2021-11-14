#pragma once
#include "bits.hpp"
#include "cell.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class Fluid_hll{
        public:

        Fluid_hll();
        ~Fluid_hll();

        void recon(const Cell&,const Cell&,const Cell&,Cell&,Cell&);

        void face_halftime(Cell&,Cell&);

        void Sv(Cell&,Cell&);

        void Gflux(Cell&,Cell&);

        void evU(Cell&,const Cell&,const Cell&);

        void bc(vector<Cell>&);

        void fluid(vector<Cell>&,vector<Cell>&,vector<Cell>&);

        void evolve(vector<Cell>&,vector<Cell>&,vector<Cell>&);
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
