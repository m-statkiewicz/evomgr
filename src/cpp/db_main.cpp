#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<omp.h>

#include"dbwrapper.h"

int main (int argc, char **argv){
   DBWrapper db;
   db.insertHeader("1234", "SA", "SIMPLE", 1.1, 2.2, 3.3, 0, 1000, 10, 123, 46546.243, "[0,0]", 10.0);
   db.insertDetail("1234", 123, 10.0, 34.23, 10.0);
	return 0;
}