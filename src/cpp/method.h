/*
 * method.h
 */

#ifndef METHOD
#define METHOD

#include"const.h"
#include"point.h"
#include"dbwrapper.h"
#include"timer.h"

class Method
{
private:
  static const std::string WHO;
	std::string startTime;
 	std::string methodName;
	std::string modelName;
	std::string paramNames[5];
	double params[5];
	int populationSize;
	int iterationsNumber;
	int randomSeed;
	std::vector<Point> initPoints;
  double runTime;
	std::string runTimeString;
	Point* bestPoint;

	Timer timer;
	std::fstream log;
  DBWrapper db;

	Point optimize(const std::vector<Point>& initialPoints) const;

	void showResult () const;
	void logResult () ;
	void dbResult () ;
	void showIteration (int iteration, double worstPopEval, double bestPopEval, double bestEval) const;
	void logIteration (int iteration, double worstPopEval, double bestPopEval, double bestEval);
	void dbIteration (int iteration, double worstPopEval, double bestPopEval, double bestEval);


public:
	Method(
		std::string methodName,
		std::string modelName,
		std::string paramName0,
		double param0,
		std::string paramName1,
		double param1,
		std::string paramName2,
		double param2,
		std::string paramName3,
		double param3,
		std::string paramName4,
		double param4,
		int populationSize,
		int iterationsNumber,
		int randomSeed
);
	~Method();

	std::string getMethodName () const;
	std::string getModelName () const;
	std::string getParamNames (int i) const;
	double getParam (int i) const;
	int getPopulationSize () const;
	int getIterationsNumber () const;
	int getRandomSeed () const;
	std::string getStartTime () const;
  std::string getRunTimeString () const;
	double  getRunTime () const;
	Point getBestPoint () const;
	std::string toString () const;

	void init ();
	//void operator () (const std::vector<Point*>& initialPoints);
	void operator () ();

	void saveResult ();
	void saveIteration (int iteration, double worstPopEval, double bestPopEval, double bestEval);

	friend std::ostream& operator<< (std::ostream &os, Method &d);
};

#endif
