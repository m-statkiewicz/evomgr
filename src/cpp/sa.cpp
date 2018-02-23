#include "sa.h"
#include "timer.h"
#include "point.h"

#include <climits>
#include <math.h>
#include <omp.h>
#include <fstream>

const std::string Sa::WHO = "SA";

Sa::Sa (double lambda, double maxTemp, double minTemp, int max_iterations, int populationSize) :
Method(
	"SA",
	"STATIC",
	"lambda",  lambda ,
	"maxTemp", maxTemp,
	"minTemp", minTemp,
	"",0,
	"",0,
	populationSize,
	max_iterations,
	SEED
)
{
	if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tConstructor.\n";};
	this->lambda =getParam(0);
	this->maxTemp=getParam(1);
	this->minTemp=getParam(2);
	if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tConstructor.\n";};
};

void Sa::operator () () {
    timer.start();
    bestPoint = new Point(optimize(initPoints));
    timer.stop();
    runTime = timer.delta();
    runTimeString = timer.deltaToString();
};

Point Sa::optimize(const std::vector<Point>& initialPoints) {
	if (DEBUG_MODE) {std::cout<<"START:\t"<<WHO<<"\tOptimize.\n";};
	if (DEBUG_MODE) {std::cout<<"INFO:\t"<<WHO<<"\tPoints to process: "<<initialPoints.size()<<"\n";};

	int size=initialPoints.size();

	//Init
	std::vector<Point*> basePopulation;
	for (int i =0; i <size; ++i){
		basePopulation.push_back(new Point(initialPoints[i]));
	}

	Point bestPoint=*basePopulation[0];
	int tempIter = 0;
	for (double T = maxTemp; T >= minTemp; T*=lambda){
		tempIter++;
		int iter=0;
		while (iter<getIterationsNumber()) {
			iter++;
			if (DEBUG_MODE) {std::cout<<"INFO:\t"<<WHO<<"\t(temp;iteration) - ("<<T<<";"<<iter<<")\n";};
			std::vector<Point*> tmpPopulation;
			std::vector<Point*> tmpbPopulation;
			for (int i =0; i <size; ++i)
				tmpbPopulation.push_back(basePopulation[i]);

			basePopulation.clear();

			//Reproduct
			for (int i =0; i <size; ++i){
			    Point p(bestPoint.getSize());
				for (int crd =0; crd<p.getSize(); crd++){
					double tmp=0;
					double a=rand() / (double) RAND_MAX;
					tmp+=2*a-1;
					p.setCoord(crd,tmp);
				}
				tmpPopulation.push_back(new Point(&p));
			}

			//Evaluate
			for (int i =0; i <size; ++i){
				tmpPopulation[i]->evaluate();
			}

			//Create new population
			for (int i =0; i <tmpPopulation.size(); ++i){
				double q=rand() / (double) RAND_MAX;
				if (*tmpPopulation[i]<*tmpbPopulation[i] || exp((tmpbPopulation[i]->getEval()-tmpPopulation[i]->getEval())/T)>=q) {
					basePopulation.push_back(tmpPopulation[i]);
				}
				else
				{
					basePopulation.push_back(tmpbPopulation[i]);
				}
			}
			//Choose the best
			for (int i =0; i <size; ++i){
				if (*basePopulation[i]<bestPoint)
					bestPoint=*basePopulation[i];
			}

		}
		if (ITERATION_LOG) {
			Point* bestPopPoint=basePopulation[0];
			Point* worstPopPoint=basePopulation[0];
			for (int i =1; i <size; ++i){
				if (*basePopulation[i]<*bestPopPoint)
					bestPopPoint=basePopulation[i];
				if (*worstPopPoint<*basePopulation[i])
					worstPopPoint=basePopulation[i];
			}
			saveIteration (WHO, tempIter, worstPopPoint->getEval() , bestPopPoint->getEval(), bestPoint.getEval());
		}
	}

	if (DEBUG_MODE) {std::cout<<"END:\t"<<WHO<<"\tOptimize.\n";};

	return bestPoint;
}
