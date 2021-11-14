#pragma once
#include "bits.hpp"
#include "cell.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class GetU{
        public:

        GetU();
        virtual ~GetU();

        virtual void getR(Cell&) = 0;
        virtual void getM(Cell&) = 0;
        virtual void getE(Cell&) = 0;
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class GetU_rhd : public GetU {
        public:

        GetU_rhd();
        ~GetU_rhd();

        void getR(Cell&);
        void getM(Cell&);
        void getE(Cell&);
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
