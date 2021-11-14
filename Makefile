PROGRAM = a.exe
CL = g++
CFLAGS = -std=gnu++17 -Wall -I /usr/local/include/eigen3

SRC = main.cpp cell.o file.o eos.o init.o getU.o pvalsolver.o fluid.o

$(PROGRAM) : $(SRC)
	$(CL) $(CFLAGS) $^ -o $@

%.o : %.cpp
	$(CL) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm *.o $(PROGRAM) output_*.dat

#.SILENT :
