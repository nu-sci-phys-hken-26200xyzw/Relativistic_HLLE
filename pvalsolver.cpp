#include "header.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

PvalSolver::PvalSolver(){}
PvalSolver::~PvalSolver(){}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

PvalSolver_hll::PvalSolver_hll(){}
PvalSolver_hll::~PvalSolver_hll(){}

double PvalSolver_hll::g_v(const Cell& CELL){
        double gv = (Gam * CELL.v.at(0) * (CELL.U.at(4) - CELL.U.at(1) * CELL.v.at(0)) - CELL.U.at(1) * (1.0 - CELL.v.at(0) * CELL.v.at(0)));
        gv *= (Gam * CELL.v.at(0) * (CELL.U.at(4) - CELL.U.at(1) * CELL.v.at(0)) - CELL.U.at(1) * (1.0 - CELL.v.at(0) * CELL.v.at(0)));
        gv -= (1.0 - CELL.v.at(0) * CELL.v.at(0)) * CELL.v.at(0) * CELL.v.at(0) * (Gam - 1.0) * (Gam - 1.0) * CELL.U.at(0) * CELL.U.at(0);
        return gv;
}

double PvalSolver_hll::dg_v(const Cell& CELL){
        double dv = 1.0e-8;

        Cell* CELL_tmp = new Cell(CELL);
        CELL_tmp->v.at(0) += dv;
        double dgv = this->g_v(*CELL_tmp);

        *CELL_tmp = CELL;
        CELL_tmp->v.at(0) -= dv;
        dgv -= this->g_v(*CELL_tmp);

        delete CELL_tmp;

        dgv /= 2.0 * dv;
        return dgv;
}

void PvalSolver_hll::n_solver(Cell& CELL){
        CELL.n = CELL.U.at(0) / CELL.W();
}

void PvalSolver_hll::e_solver(Cell& CELL){
        CELL.e = CELL.U.at(4) - CELL.v.at(0) * CELL.U.at(1);
//        CELL.e -= CELL.v.at(1) * CELL.U.at(2) + CELL.v.at(2) * CELL.U.at(3);
}

void PvalSolver_hll::p_solver(Cell& CELL){}

void PvalSolver_hll::v_solver(Cell& CELL){

        double R = CELL.U.at(0);
        double Mx = CELL.U.at(1);
//        double My = CELL.U.at(2);
//        double Mz = CELL.U.at(3);
        double E = CELL.U.at(4);

        if(abs(Mx) < EPS){
                CELL.v.at(0) = 0.0;
                return;
        }

/*
        if(E < R || E < abs(Mx)){
                CELL.U.at(4) = max(R,abs(Mx)) + 1.0e-3;
                E = CELL.U.at(4);
        }
*/

        double sign;
        sign = (double)(Mx > 0.0) - (double)(Mx < 0.0);

        double vlow,vup,z;

        vlow = (Gam * E - sqrt(Gam * Gam * E * E - 4.0 * (Gam -1.0) * Mx * Mx)) / (2.0 * abs(Mx) * (Gam - 1.0));
        vup = min(1.0,abs(Mx) / E + 1.0e-6);

        if(vlow > 1.0e-9){
                z = 0.5 * (1.0 - R / E) * (vlow - vup);
        }else{
                z = 0.0;
        }

        double vold,vnew;

        vold = 0.5 * (vlow + vup) + z;

        int vitera = 9;// v_solver Newton method iteration

        for(int i=0;i<vitera;++i){
                Cell* CELL_tmp = new Cell(CELL);
                CELL_tmp->v.at(0) = vold;

                vnew = vold - this->g_v(*CELL_tmp) / this->dg_v(*CELL_tmp);

                if(abs(vnew - vold) < EPS){
                        delete CELL_tmp;
                        break;
                }

                vold = vnew;
                delete CELL_tmp;
        }

        CELL.v.at(0) = sign * vnew;
}

void PvalSolver_hll::pval_solver(Cell& CELL){

        this->v_solver(CELL);

        this->e_solver(CELL);

        this->n_solver(CELL);

        EoS* eos = new EoS_idgas();// eos_optional
        eos->eos_p(CELL);
        delete eos;
}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
