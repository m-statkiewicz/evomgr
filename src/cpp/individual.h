/*
 * individual.h
 */

#ifndef INDIVIDUAL
#define INDIVIDUAL

#include"point.h"

#include<cstdlib>
#include<iostream>

class Individual : public Point {
private:
	float* sigma;

public:
	Individual(int size);
	Individual(const Individual* i);
	Individual(const Individual& i);
	Individual(const Point* p);
	Individual(const Point& p);
	~Individual();

	float getSigma(int i) const;
	void setSigma(int i, float val);
	void generateRandom();
	void mutate();
	void crossover(Individual* i1);
};
#endif
