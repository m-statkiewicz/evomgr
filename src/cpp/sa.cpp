#include "sa.h"
#include "timer.h"
#include "point.h"

#include <climits>
#include <math.h>
#include <omp.h>
#include <fstream>

Sa::Sa (float lambda, float maxTemp, float minTemp, int max_iterations, std::string start_time) : Method()
{
	this->name="sa";
	this->lambda=lambda;
	this->maxTemp=maxTemp;
	this->minTemp=minTemp;
	this->iterations=max_iterations;
	this->logfilename="sa"+start_time+".run.log";
	this->start_time=start_time;
};

Point Sa::operator () (const std::vector<Point*>& initialPoints) {
	//std::fstream log;
	//log.open( logfilename.c_str(), std::ios::out );
	//log<<"wPop\tbPop\tbest\n";
	//	DBWrapper db;
		
	size=initialPoints.size();

	Point bestPoint=*initialPoints[0];
	Point* worstPopPoint=initialPoints[0];
	Point* bestPopPoint=initialPoints[0];

	//Inicjacja
	std::vector<Point*> basePopulation;
	for (int i =0; i <size; ++i){
		basePopulation.push_back(new Point(initialPoints[i]));
	}
	for (float T = maxTemp; T >=minTemp; T*=lambda){
	int iter=0;
	while (iter<iterations) {
		std::cout<<"SA:\t(temp;iteration) - ("<<T<<";"<<iter<<")\n";
		std::vector<Point*> tmpPopulation;
		std::vector<Point*> tmpbPopulation;
		for (int i =0; i <size; ++i)
			tmpbPopulation.push_back(basePopulation[i]);
		
		basePopulation.clear();
		//Reprodukcja
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
		//Ewaluacja
		for (int i =0; i <size; ++i){
			tmpPopulation[i]->evaluate();
		}
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
		
		//Wybor najlepszego
		for (int i =0; i <size; ++i){
			if (*basePopulation[i]<bestPoint)
				bestPoint=*basePopulation[i];
		}

		bestPopPoint=basePopulation[0];
		worstPopPoint=basePopulation[0];
		for (int i =1; i <size; ++i){
			if (*basePopulation[i]<*bestPopPoint)
				bestPopPoint=basePopulation[i];
			if (*worstPopPoint<*basePopulation[i])
				worstPopPoint=basePopulation[i];
		}
		//db.insertDetail(start_time, iter, bestPopPoint->getEval(), worstPopPoint->getEval(), bestPoint.getEval());
		//log<<worstPopPoint->getEval()<<"\t";
		//log<<bestPopPoint->getEval()<<"\t";
		//log<<bestPoint.getEval()<<"\n";
		std::cout<<"SA:\t"<<worstPopPoint->getEval()<<"\t";
		std::cout<<bestPopPoint->getEval()<<"\t";
		std::cout<<bestPoint.getEval()<<"\n";
		iter++;
	}
	}
	return bestPoint;
}

std::ostream& operator<< (std::ostream &os, Sa &d){
	os<<"Simmulated Annealing\n";
	os<<"Parameters:\n";
	os<<"\tlambda: "<<d.lambda<<"\n";
	os<<"\tmax Temperature: "<<d.maxTemp<<"\n";
	os<<"\tmin Temperature: "<<d.minTemp<<"\n";
	os<<"\tpopulation size: "<<d.size<<"\n";
	os<<"\t#iterations: "<<d.iterations<<"\n";
	return os;
}

