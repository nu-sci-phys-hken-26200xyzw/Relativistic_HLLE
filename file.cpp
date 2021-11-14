#include "header.hpp"
using namespace std;

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */

File_1d::File_1d(){}
File_1d::~File_1d(){}

void File_1d::file(vector<Cell>& CELL){

        string file_name("");
        file_name += "output_";
        file_name += to_string((int)floor(Cell::t / dt + 0.5));
        file_name += ".dat";

        ofstream fout(file_name);

        fout << "# ";
        fout << setw(5) << setfill(' ') << left << "Nx =";
        fout << setw(8) << setfill(' ') << left << CELL.size() - 2*SC;
        fout << setw(5) << setfill(' ') << left << "Ny =";
        fout << setw(8) << setfill(' ') << left << Ny;
        fout << setw(5) << setfill(' ') << left << "dx =";
        fout << setw(8) << setfill(' ') << left << dx;
        fout << setw(6) << setfill(' ') << left << "CFL =";
        fout << setprecision(4) << setw(8) << setfill(' ') << left << CFL;
        fout << setw(6) << setfill(' ') << left << "Gam =";
        fout << setprecision(4) << setw(8) << setfill(' ') << left << Gam;
        fout << setw(4) << setfill(' ') << left << "t =";
        fout << setprecision(4) << setw(8) << setfill(' ') << left << Cell::t;
        fout << endl << endl;

        fout << "# ";
        fout << setw(11) << setfill(' ') << left << "x";
//        fout << setw(13) << setfill(' ') << left << "y";
//        fout << setw(13) << setfill(' ') << left << "z";
        fout << setw(13) << setfill(' ') << left << "n";
        fout << setw(13) << setfill(' ') << left << "e";
        fout << setw(13) << setfill(' ') << left << "p";
        fout << setw(13) << setfill(' ') << left << "vx";
//        fout << setw(13) << setfill(' ') << left << "vy";
//        fout << setw(13) << setfill(' ') << left << "vz";
        fout << setw(13) << setfill(' ') << left << "|v|";
        fout << setw(13) << setfill(' ') << left << "W";
        fout << setw(13) << setfill(' ') << left << "c2";
        fout << setw(13) << setfill(' ') << left << "R";
        fout << setw(13) << setfill(' ') << left << "Mx";
//        fout << setw(13) << setfill(' ') << left << "My";
//        fout << setw(13) << setfill(' ') << left << "Mz";
        fout << setw(13) << setfill(' ') << left << "E";
        fout << endl << endl;

        for(int i=SC;i<CELL.size()-SC;++i){

                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].x.at(0);
//                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].x.at(1);
//                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].x.at(2);
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].n;
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].e;
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].p;
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].v.at(0);
//                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].v.at(1);
//                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].v.at(2);
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].v2();
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].W();
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].c2();
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].U.at(0);
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].U.at(1);
//                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].U.at(2);
//                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].U.at(3);
                fout << setprecision(6) << setw(13) << setfill(' ') << left << CELL[i].U.at(4);
                fout << endl;
        }
        fout.close();
}

/* @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ */
