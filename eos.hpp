#pragma once
#include "bits.hpp"
#include "cell.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class EoS{
        public:

        EoS();
        virtual ~EoS();

        virtual void eos_p(Cell&) = 0;

        virtual void eos_e(Cell&) = 0;
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class EoS_idgas : public EoS {
        public:

        EoS_idgas();
        ~EoS_idgas();

        void eos_p(Cell&);

        void eos_e(Cell&);
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

class EoS_ridgas : public EoS {
        public:

        EoS_ridgas();
        ~EoS_ridgas();

        void eos_p(Cell&);

        void eos_e(Cell&);
};

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
