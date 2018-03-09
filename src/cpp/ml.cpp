#include <climits>
#include <math.h>
#include <omp.h>

#include "ml.h"

const std::string Ml::WHO = "ML";

Ml::Ml (double mi, double lambda, int max_iterations) :
Method(
	WHO,
	"STATIC",
	"mi", mi,
	"lambda",  lambda ,
	"",0,
	"",0,
	"",0,
	lambda,
	max_iterations,
	SEED
)
{
	if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tConstructor.\n";};
	this->mi=getParam(0);
	this->lambda =getParam(1);
	if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tConstructor.\n";};
};

void Ml::operator () () {
    timer.start();
    bestPoint = new Point(optimize(initPoints));
    timer.stop();
    runTime = timer.delta();
    runTimeString = timer.deltaToString();
};

Point Ml::optimize(const std::vector<Point>& initialPoints) {
	if (DEBUG_MODE) {std::cout<<"START:\t"<<WHO<<"\tOptimize.\n";};
	if (DEBUG_MODE) {std::cout<<"INFO:\t"<<WHO<<"\tPoints to process: "<<initialPoints.size()<<"\n";};

	int size=initialPoints.size();

	//Init
	std::vector<Individual*> basePopulation;
	for (int i =0; i <size; ++i){
		basePopulation.push_back(new Individual(initialPoints[i]));
	}
	Point bestPoint=*basePopulation[0];

	int iter = 0;
	while (iter<getIterationsNumber()) {
		iter++;
		std::vector<Individual*> tmpPopulation;
		//Reproduct
		for (int i = 0; i <lambda; ++i){
			tmpPopulation.push_back(new Individual(basePopulation[rand()%basePopulation.size()]));
		}
		//Crossover
		//	#pragma acc loop
			#pragma omp parallel for num_threads(OMP_THREADS)
			for (int i = 0; i < (int)lambda/2; ++i){
				tmpPopulation[2*i]->crossover(tmpPopulation[2*i+1]);
			}

  	//Mutate
		//	#pragma acc loop
		  #pragma omp parallel for num_threads(OMP_THREADS)
		  for (int i =0; i <lambda; ++i){
				tmpPopulation[i]->mutate();
			}
		//Evaluate
		//	#pragma acc loop
			#pragma omp parallel for num_threads(OMP_THREADS)
			for (int i =0; i <lambda; ++i){
				tmpPopulation[i]->evaluate();
			}

			basePopulation.clear();
			for (int it = 0; it<tmpPopulation.size(); ++it){
				int ib;
				for (ib = 0; ib<basePopulation.size(); ++ib){
					if (*tmpPopulation[it]<*basePopulation[ib] || ib>mi){
						basePopulation.insert(basePopulation.begin()+ib,new Individual(*tmpPopulation[it]));
						break;
					}
				}
				if (basePopulation.size()<=mi && ib==basePopulation.size()){
					basePopulation.push_back(new Individual(*tmpPopulation[it]));
				}
			}
			basePopulation.resize(mi);

		//Select best point
		for (int i=0; i<basePopulation.size(); ++i)
			if (*basePopulation[i]<bestPoint)
				bestPoint=*basePopulation[i];

		if (ITERATION_LOG) {
			Point* bestPopPoint=basePopulation[0];
			Point* worstPopPoint=basePopulation[0];
			for (int i =1; i <size; ++i){
				if (*basePopulation[i]<*bestPopPoint)
					bestPopPoint=basePopulation[i];
				if (*worstPopPoint<*basePopulation[i])
					worstPopPoint=basePopulation[i];
			}
			saveIteration (WHO, iter, worstPopPoint->getEval() , bestPopPoint->getEval(), bestPoint.getEval());
		}
	}

	if (DEBUG_MODE) {std::cout<<"END:\t"<<WHO<<"\tOptimize.\n";};

	return bestPoint;
}
