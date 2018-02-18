/*
 * point.h
 */

#ifndef POINT
#define POINT

#include"const.h"

class Point {
protected:
	static const std::string WHO;
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
	std::string toString() const;

	void evaluate();
	void generateRandom();

  bool operator<(const Point& other) const;

	friend std::ostream& operator<< (std::ostream &os, Point & p);
};


#endif
