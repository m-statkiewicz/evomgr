#include<omp.h>

#include"const.h"
#include"method.h"

int main (int argc, char **argv){

	Method m (
		"METHOD",
		"SIMPLE",
		"param0",	0,
		"param1",	1,
		"param2",	2,
		"param3",	3,
		"param4",	4,
		10,
		1,
		SEED);

	m.init();
	m();
	// m.verify();
	// m.verify();

	// model_veryfication(*r,0,m.name+start_time+".sym.log");
	// model_veryfication(*r,1,m.name+start_time+".ver.log");

	m.saveResult();
	return 0;
}
