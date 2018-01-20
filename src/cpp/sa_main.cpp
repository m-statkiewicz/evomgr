#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<omp.h>

#include"const.h"
#include"point.h"
#include"timer.h"
#include"symulate.h"
#include"sa.h"

int main (int argc, char **argv){

	DBWrapper db;
	Timer t0;
	std::string start_time=t0.currentDateTime();
	std::string log_file_name;

	int v_size = 200;
	
	srand(SEED);
	Sa m (0.8, 100, 1.2, 10, start_time);
	
	std::vector<Point*> initPoints;
        
    Point* p;
    for (int i=0; i<v_size; ++i) {
        p = new Point(POINT_SIZE);
        p->generateRandom();
        p->evaluate();
        initPoints.push_back(p);
	}
    Timer t(1);
	Point* r = new Point(m(initPoints));
    t.stop();
	
	model_veryfication(*r,0,m.name+start_time+".sym.log");
	model_veryfication(*r,1,m.name+start_time+".ver.log");
	
	log_file_name=m.name+start_time+".log";
	db.insertHeader(start_time, "SA", MODEL, double param1, double param2, double param3, double param4, int population_size, int iterations, SEED, t.deltaToString(), std::string best_point, double eval);
	std::fstream log;
	log.open( log_file_name.c_str(), std::ios::out );
	log<<m;
	log<<"Random seed: "<<SEED<<".\n";
	log<<"Run time: "<<t.deltaToString()<<" s.\n";
	log<<"Best point:\n"<<*r<<".";
	log.close();
	
	delete r;
	return 0;
}
