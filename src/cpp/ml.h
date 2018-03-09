#ifndef SA
#define SA

#include<cstdlib>
#include<vector>
#include<string>

#include"method.h"
#include"individual.h"

class Ml : public Method
{
private:
  static const std::string WHO;

	double mi;
	double lambda ;
	Point optimize(const std::vector<Point>& initialPoints);

public:
	Ml (double mi, double lambda, int max_iterations);
	void operator () ();

};

#endif
