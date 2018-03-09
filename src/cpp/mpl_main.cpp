#include"mpl.h"

int main (int argc, char **argv){

	Mpl m (100, 150, 200);

	m.init();
	m();
	// m.verify();
	// m.verify();

	// model_veryfication(*r,0,m.name+start_time+".sym.log");
	// model_veryfication(*r,1,m.name+start_time+".ver.log");

	m.saveResult();
	return 0;
}
