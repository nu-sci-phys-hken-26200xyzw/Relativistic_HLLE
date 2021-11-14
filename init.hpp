#pragma once
#include "bits.hpp"
#include "cell.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class Init{
        public:

        Init();
        virtual ~Init();

        virtual void init(vector<Cell>&) = 0;
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class Init_st1d : public Init {
        private:

        const double nl,nr;
        const double epl,epr;

        const double vxl,vxr;
//        const double vyl,vyr;
//        const double vzl,vzr;

        const bool t_f;// 初期状態にe(p)を使うとき,true(false)

        public:

        Init_st1d(double,double,double,double,double,double,bool);
        ~Init_st1d();

        void init(vector<Cell>&);
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class Init_file1d : public Init {
        private:

        string file_name;

        public:

        Init_file1d(string);
        ~Init_file1d();

        void init(vector<Cell>&);// 任意のセル数をファイル読み込みするので,初期化作業はコンストラクタ内でcell,faceR,faceLを直接編集する
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
