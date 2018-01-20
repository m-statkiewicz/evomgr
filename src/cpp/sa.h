#ifndef SA
#define SA

#include<cstdlib>
#include<vector>
#include<string>

#include"method.h"

class Sa : public Method
{
private:
	int size;
	float lambda;			//współczynnik zmniejszania temperatury
	float maxTemp;
	float minTemp;
	int iterations;
	std::string logfilename;
	std::string start_time;

public:
	std::string name;
	Sa (float lambda, float maxTemp, float minTemp, int max_iterations, std::string start_time);
	Point operator () (const std::vector<Point*>& initialPoints);
	friend std::ostream& operator<< (std::ostream &os, Sa &s);
};

#endif
