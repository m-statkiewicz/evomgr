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


	Sa m (0.8, 100, 1.2, 10, 10);

	m.init();
	m();
	// m.verify();
	// m.verify();

	// model_veryfication(*r,0,m.name+start_time+".sym.log");
	// model_veryfication(*r,1,m.name+start_time+".ver.log");

	m.saveResult();
	return 0;
}
