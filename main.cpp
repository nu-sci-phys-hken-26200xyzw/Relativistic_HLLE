#include "header.hpp"
using namespace std;

int main(int argc,char** argv){system("clear");
auto hazime = chrono::system_clock::now();
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


Init* initiate = new Init_st1d(2.0,1.0,2.0,1.0,0.0,0.0,false);// (n,e(p),vx,true(false))
initiate->init(cell);
delete initiate;



/*
Init* initiate = new Init_file1d(*(argv+1));
delete initiate;
*/



Fluid_hll* ev = new Fluid_hll();
ev->evolve(cell,faceL,faceR);
delete ev;


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
for(int i=0;i<argc;++i){cout<<*(argv+i)<<" ";}
cout<<endl;
auto owari = chrono::system_clock::now();
cout << "プログラム実行時間 : " << chrono::duration_cast<chrono::milliseconds>(owari - hazime).count() << "[ms]" << endl;
return 0;
}
