#include "header.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

Fluid_hll::Fluid_hll(){}
Fluid_hll::~Fluid_hll(){}

void Fluid_hll::recon(const Cell& CELLl,const Cell& CELLc,const Cell& CELLr,Cell& FACEl,Cell& FACEr){

        double Sl,Sr,S;

        for(int i=0;i<5;++i){
                if(i == 2 || i == 3){
                        continue;
                }

                Sl = (CELLc.U.at(i) - CELLl.U.at(i)) / dx;
                Sr = (CELLr.U.at(i) - CELLc.U.at(i)) / dx;

                if(Sl * Sr > 0.0){
                        if(abs(Sl) > abs(Sr)){
                                S = Sr;
                        }else{
                                S = Sl;
                        }
                }else{
                        S = 0.0;
                }

                FACEl.U.at(i) = CELLc.U.at(i) - 0.5 * dx * S;
                FACEr.U.at(i) = CELLc.U.at(i) + 0.5 * dx * S;
        }
}

void Fluid_hll::face_halftime(Cell& FACEl,Cell& FACEr){

        vector<double> Ul(FACEl.U),Ur(FACEr.U);

        FACEl.U.at(0) -= 0.5 * dt / dx * (Ur.at(0) * FACEr.v.at(0) - Ul.at(0) * FACEl.v.at(0));
        FACEr.U.at(0) -= 0.5 * dt / dx * (Ur.at(0) * FACEr.v.at(0) - Ul.at(0) * FACEl.v.at(0));

        FACEl.U.at(1) -= 0.5 * dt / dx * ((Ur.at(1) * FACEr.v.at(0) + FACEr.p) - (Ul.at(1) * FACEl.v.at(0) + FACEl.p));
        FACEr.U.at(1) -= 0.5 * dt / dx * ((Ur.at(1) * FACEr.v.at(0) + FACEr.p) - (Ul.at(1) * FACEl.v.at(0) + FACEl.p));

        FACEl.U.at(4) -= 0.5 * dt / dx * ((Ur.at(4) + FACEr.p) * FACEr.v.at(0) - (Ul.at(4) + FACEl.p) * FACEl.v.at(0));
        FACEr.U.at(4) -= 0.5 * dt / dx * ((Ur.at(4) + FACEr.p) * FACEr.v.at(0) - (Ul.at(4) + FACEl.p) * FACEl.v.at(0));
}

void Fluid_hll::Sv(Cell& FACEr,Cell& FACEl){// 引数の順番に注意

        double vx_ = 0.5 * (FACEr.v.at(0) + FACEl.v.at(0));
        double c2_ = 0.5 * (FACEr.c2() + FACEl.c2());

        FACEr.Svmin = min({0.0,(vx_ - c2_) / (1.0 - vx_ * c2_),(FACEr.v.at(0) - FACEr.c2()) / (1.0 - FACEr.v.at(0) * FACEr.c2())});
        FACEr.Svmax = max({0.0,(vx_ + c2_) / (1.0 + vx_ * c2_),(FACEl.v.at(0) + FACEl.c2()) / (1.0 + FACEl.v.at(0) * FACEl.c2())});
}

void Fluid_hll::Gflux(Cell& FACEr,Cell& FACEl){
        vector<double> Fr(5,0.0),Fl(5,0.0);

        Fr.at(0) = FACEr.U.at(0) * FACEr.v.at(0);
        Fl.at(0) = FACEl.U.at(0) * FACEl.v.at(0);

        Fr.at(1) = FACEr.U.at(1) * FACEr.v.at(0) + FACEr.p;
        Fl.at(1) = FACEl.U.at(1) * FACEl.v.at(0) + FACEl.p;

        Fr.at(2) = FACEr.U.at(2) * FACEr.v.at(1) + FACEr.p;
        Fl.at(2) = FACEl.U.at(2) * FACEl.v.at(1) + FACEl.p;
        Fr.at(3) = FACEr.U.at(3) * FACEr.v.at(2) + FACEr.p;
        Fl.at(3) = FACEl.U.at(3) * FACEl.v.at(2) + FACEl.p;

        Fr.at(4) = (FACEr.U.at(4) + FACEr.p) * FACEr.v.at(0);
        Fl.at(4) = (FACEl.U.at(4) + FACEl.p) * FACEl.v.at(0);

        for(int i=0;i<5;++i){
                FACEr.G.at(i) = (FACEr.Svmax * Fr.at(i) - FACEr.Svmin * Fl.at(i) + FACEr.Svmin * FACEr.Svmax * (FACEl.U.at(i) - FACEr.U.at(i))) / (FACEr.Svmax - FACEr.Svmin);
        }
}

void Fluid_hll::evU(Cell& CELL,const Cell& FACEl,const Cell& FACEr){
        for(int i=0;i<5;++i){
                CELL.U.at(i) -= dt / dx * (FACEr.G.at(i) - FACEl.G.at(i));
        }
}

void Fluid_hll::bc(vector<Cell>& CELL){
        for(int i=0;i<SC;++i){
                CELL[SC - 1 - i] = CELL[SC + i];
                CELL[CELL.size() - SC + i] = CELL[CELL.size() - SC - 1 - i];
        }
}

void Fluid_hll::fluid(vector<Cell>& CELL,vector<Cell>& FACEl,vector<Cell>& FACEr){

        for(int i=1;i<CELL.size()-1;++i){// faceの両端は計算しなくて良い(利用しない)
                this->recon(CELL[i-1],CELL[i],CELL[i+1],FACEl[i],FACEr[i]);

                PvalSolver* ps = new PvalSolver_hll();
                ps->pval_solver(FACEl[i]);
                ps->pval_solver(FACEr[i]);
                delete ps;

                this->face_halftime(FACEl[i],FACEr[i]);
        }

        for(int i=1;i<CELL.size()-2;++i){// 計算セルの両側面にあたる表面を右側面にもつセルを計算
                this->Sv(FACEr[i],FACEl[i+1]);

                this->Gflux(FACEr[i],FACEl[i+1]);
        }

        for(int i=SC;i<CELL.size()-SC;++i){
                this->evU(CELL[i],FACEr[i-1],FACEr[i]);
        }

        this->bc(CELL);

        for(int i=0;i<CELL.size();++i){
                PvalSolver* ps = new PvalSolver_hll();
                ps->pval_solver(CELL[i]);
                delete ps;
        }

        Cell::t += dt;

        cout << "time = " << Cell::t << " : : : " << (int)(floor(Cell::t / dt + 0.5)) << "STEP / " << STEPs << endl;
}

void Fluid_hll::evolve(vector<Cell>& CELL,vector<Cell>& FACEl,vector<Cell>& FACEr){

        File_1d* f = new File_1d();
        f->file(CELL);
        delete f;

        while(true){
                if(Cell::t > tfinal){
                        cout << "Done! time = " << Cell::t << " / " << tfinal << endl;
                        break;
                }

                this->fluid(CELL,FACEl,FACEr);

                if((int)(floor(Cell::t / dt + 0.5)) % 1 == 0){
                File_1d* f = new File_1d();
                f->file(CELL);
                delete f;
                }
        }
}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
