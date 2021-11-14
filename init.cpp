#include "header.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

Init::Init(){}
Init::~Init(){}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

Init_st1d::Init_st1d(double nl,double nr,double epl,double epr,double vxl,double vxr,bool t_f) : nl(nl),nr(nr),epl(epl),epr(epr),vxl(vxl),vxr(vxr),t_f(t_f) {}
Init_st1d::~Init_st1d(){}

void Init_st1d::init(vector<Cell>& CELL){

        for(int i=0;i<CELL.size();++i){

                CELL[i].x.at(0) = (-SC + i) * dx;

                if(CELL[i].x.at(0) < Nx / 2 * dx){
                        CELL[i].n = this->nl;
                        if(this->t_f){
                                CELL[i].e = this->epl;
                        }else{
                                CELL[i].p = this->epl;
                        }
                        CELL[i].v.at(0) = this->vxl;
//                        CELL[i].v.at(1) = this->vyl;
//                        CELL[i].v.at(2) = this->vzl;
                }else{
                        CELL[i].n = this->nr;
                        if(this->t_f){
                                CELL[i].e = this->epr;
                        }else{
                                CELL[i].p = this->epr;
                        }
                        CELL[i].v.at(0) = this->vxr;
//                        CELL[i].v.at(1) = this->vyr;
//                        CELL[i].v.at(2) = this->vzr;
                }

                EoS* eos = new EoS_idgas();// eos_optional
                if(this->t_f){
                        eos->eos_p(CELL[i]);
                }else{
                        eos->eos_e(CELL[i]);
                }
                delete eos;

                GetU* getU = new GetU_rhd();// getU_optional
                getU->getR(CELL[i]);
                getU->getM(CELL[i]);
                getU->getE(CELL[i]);
                delete getU;
        }
}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

Init_file1d::Init_file1d(string file_name) : file_name(file_name) {

        ifstream fin(this->file_name);
        bool t_f;// 初期状態にe(p)を使うとき,true(false)
        fin >> t_f;

        vector<double> n_in,ep_in,vx_in;
        double n_tmp,ep_tmp,vx_tmp;

        while(fin >> n_tmp >> ep_tmp >> vx_tmp){
                n_in.push_back(n_tmp);
                ep_in.push_back(ep_tmp);
                vx_in.push_back(vx_tmp);
        }
        fin.close();

        vector<Cell> Cell_tmp(n_in.size());
        cell = faceL = faceR = Cell_tmp;

        for(int i=0;i<cell.size();++i){
                cell[i].x.at(0) = (-SC + i) * dx;
                cell[i].n = n_in[i];
                if(t_f){
                        cell[i].e = ep_in[i];
                }else{
                        cell[i].p = ep_in[i];
                }
                cell[i].v.at(0) = vx_in[i];

                EoS* eos = new EoS_idgas();// eos_optional
                if(t_f){
                        eos->eos_p(cell[i]);
                }else{
                        eos->eos_e(cell[i]);
                }
                delete eos;

                GetU* getU = new GetU_rhd();// getU_optional
                getU->getR(cell[i]);
                getU->getM(cell[i]);
                getU->getE(cell[i]);
                delete getU;
        }
}
/*   @   @   @   @   @ > > > file_name < < < @   @   @   @   @   *\
0(1)   *** 初期状態にpの値を使う場合は0,vice versa ***
n0 e(p)0 vx0
n1 e(p)1 vx1
::::::::::::
nend e(p)end vxend
\*   @   @   @   @   @   @   @   @   @   @   @   @   @   @   @   */

Init_file1d::~Init_file1d(){}
void Init_file1d::init(vector<Cell>&){}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
