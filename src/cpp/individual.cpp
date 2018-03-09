/*
 * individual.cpp
 */

#include "individual.h"
#include <math.h>
#include <climits>

Individual::Individual(int size) : Point(size){
	sigma = new float[size];
	for (int i = 0; i<size; ++i)
		sigma[i]=0;
};

Individual::Individual(const Individual * i) : Point(i){
	sigma = new float[size];
	for (int it = 0; it<size; ++it)
		sigma[it]=i->sigma[it];
};

Individual::Individual(const Individual & i) : Point(i){
	sigma = new float[size];
	for (int it = 0; it<size; ++it)
		sigma[it]=i.sigma[it];
};

Individual::Individual(const Point * p) : Point(p){
	sigma = new float[size];
	for (int it = 0; it<size; ++it)
		sigma[it]=(float)(rand()%(2*PRECISION))/PRECISION-1;
};

Individual::Individual(const Point & p) : Point(p){
	sigma = new float[size];
	for (int it = 0; it<size; ++it)
		sigma[it]=(float)(rand()%(2*PRECISION))/PRECISION-1;
};

Individual::~Individual(){
	delete sigma;
}

float Individual::getSigma(int i) const{
    return sigma[i];
}

void Individual::setSigma(int i, float val){
    this->sigma[i]=val;
}

void Individual::generateRandom(){
	for (int i = 0; i<size; ++i) {
		value[i]=(float)(rand()%(2*RADIUS*PRECISION))/PRECISION-RADIUS;
		sigma[i]=(float)(rand()%(2*RADIUS*PRECISION))/PRECISION-RADIUS;
	}
};

void Individual::mutate(){
	float xi = (float)rand()/RAND_MAX*2-1;
//	float tau = 1/sqrt(2*size),tau_=1/sqrt(2*sqrt(size));
	float tau = 1/(2*size),tau_=1/sqrt(2*(size));
	for (int i=0; i<size; ++i){
		float xi_sigma=(float)rand()/INT_MAX;
		sigma[i]=sigma[i]*exp(tau_*xi+tau*xi_sigma);
		float xi_val=(float)rand()/INT_MAX;
		value[i]=value[i]+sigma[i]*xi_val;
	}
    isEvalCorrect=0;
};

void Individual::crossover(Individual* ind){
	float a = (float)rand()/INT_MAX;
	for (int i=0; i<size; ++i){
		float x1,x2;
		x1=a*value[i]+(1-a)*ind->value[i];
		x2=a*ind->value[i]+(1-a)*value[i];
		value[i]=x1;
		ind->value[i]=x2;
		if ((float)rand()/INT_MAX<=a){
			float tmp_sigma=sigma[i];
			sigma[i]=ind->sigma[i];
			ind->sigma[i]=tmp_sigma;
		}
	}
	isEvalCorrect=0;
}
