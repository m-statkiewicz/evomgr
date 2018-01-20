/*
 * point.h
 */

#ifndef POINT
#define POINT

#include<cstdlib>
#include<iostream>

#define RADIUS 2
#define PRECISION 100000

class Point {
protected:
	int size;	
	float* value;
	float eval;
    bool isEvalCorrect;

public:
	Point();
	Point(int size);
	Point(const Point* p);
	Point(const Point& p);
	~Point();
	
	int getSize() const;
	float getEval() const;
	float getCoord(int i) const;
	void setCoord(int i, float val);
	
	void evaluate();
	void generateRandom();
    
    bool operator<(const Point& other) const;

	friend std::ostream& operator<< (std::ostream &os, Point & p);
};


#endif
