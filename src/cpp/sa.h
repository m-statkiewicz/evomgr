#ifndef SA
#define SA

#include<cstdlib>
#include<vector>
#include<string>

#include"method.h"

class Sa : public Method
{
private:
  static const std::string WHO;
	double lambda ;
	double maxTemp;
	double minTemp;
	Point optimize(const std::vector<Point>& initialPoints);

public:
	Sa (double lambda, double maxTemp, double minTemp, int max_iterations, int populationSize);
	void operator () (); 

};

#endif
