#pragma once
#include "bits.hpp"
#include "cell.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class PvalSolver{
        public:

        PvalSolver();
        virtual ~PvalSolver();

        virtual void n_solver(Cell&) = 0;

        virtual void e_solver(Cell&) = 0;

        virtual void p_solver(Cell&) = 0;

        virtual void v_solver(Cell&) = 0;

        virtual void pval_solver(Cell&) = 0;
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class PvalSolver_hll : public PvalSolver {// Schneider1993
        public:

        PvalSolver_hll();
        ~PvalSolver_hll();

        double g_v(const Cell&);// g(v)
        double dg_v(const Cell&);// dg(v) / dv

        void n_solver(Cell&);

        void e_solver(Cell&);

        void p_solver(Cell&);

        void v_solver(Cell&);

        void pval_solver(Cell&);
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
