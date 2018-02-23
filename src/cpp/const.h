#ifndef CONST
#define CONST

#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<climits>
#include<vector>
#include<math.h>


// outputs
#define ITERATION_LOG 1
#define DEBUG_MODE 1
#define MEMO_MODE 0
#define LOG_MODE 0
#define DB_MODE 0
#define TESTS_DB "/tmp/tests.db"

// data generation
#define SEED 1
#define RADIUS 2
#define PRECISION 100000

//Models
#define SIMPLE  0
#define STATIC  1
#define DYNAMIC 2
#define MODEL SIMPLE

#if (MODEL == STATIC)
	#define POINT_SIZE (5*K+1)
#elif (MODEL == DYNAMIC)
	#define POINT_SIZE (6*K+1)
#else
	#define POINT_SIZE 2
#endif

//Neural Net
#define K 6 // hidden neurons

//openMP settings
#define OMP_THREADS 2

//Symulation/Verification
#define DATA_SAMPLES_COUNT 2000

#endif
