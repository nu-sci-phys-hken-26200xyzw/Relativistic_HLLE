#pragma once
#include "bits.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class Cell{
        public:

        vector<double> x;

        double n;
        double e;
        double p;

        vector<double> v;

        double v2();
        double W();

        double c2();

        vector<double> U;

        //cellの右側表面であるfaceRにおいてのみ有意義
        double Svmin,Svmax;// signal velocity
        vector<double> G;// numerical flux

        Cell();
        ~Cell();

        static double t;
};

extern vector<Cell> cell,faceL,faceR;
//extern vector<vector<vector<Cell>>> cell;
