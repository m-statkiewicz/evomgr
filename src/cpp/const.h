#ifndef CONST
#define CONST

// additional outputs
#define DEBUG_MODE 1

// ziarno do generowania danych poczatkowych
#define SEED 5779
// promien generowania danych poczatkowych
#define RAND_RADIUS 10

//Zdefiniowane modele
#define SIMPLE  0
#define STATIC  1
#define DYNAMIC 2

//Wybór funkcji
#define MODEL SIMPLE

//Parametry sieci neuronowej
#define K 6 // liczba neuronów ukrytych

//Watki openMP
#define OMP_THREADS 2

//Licznosc danych do symulacji
#define DATA_SAMPLES_COUNT 2000

#define TESTS_DB "/tmp/tests.db"

#if (MODEL == STATIC) 
	#define POINT_SIZE (5*K+1)
#elif (MODEL == DYNAMIC)
	#define POINT_SIZE (6*K+1)
#else
	#define POINT_SIZE 2
#endif
#endif
