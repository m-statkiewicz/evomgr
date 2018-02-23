#include "method.h"

const std::string Method::WHO = "METHOD";

Method::Method(
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
) {
  if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tConstructor.\n";};
  this->startTime = timer.currentDateTime();
  this->methodName = methodName;
  this->modelName = modelName;
  this->params[0] = param0;
  this->params[1] = param1;
  this->params[2] = param2;
  this->params[3] = param3;
  this->params[4] = param4;
  this->paramNames[0] = paramName0;
  this->paramNames[1] = paramName1;
  this->paramNames[2] = paramName2;
  this->paramNames[3] = paramName3;
  this->paramNames[4] = paramName4;
  this->populationSize = populationSize;
  this->iterationsNumber = iterationsNumber;
  this->randomSeed = randomSeed;

  srand(SEED);
	if (LOG_MODE) {
    std::string log_file_name = this->methodName+this->startTime+".log";
    log.open(log_file_name.c_str(), std::ios::out);
  };
  if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tConstructor.\n";};

};

Method::~Method(){
  if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tDestructor.\n";};
  if (LOG_MODE) {
    log.close();
  };
  if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tDestructor.\n";};
};

std::string Method::getMethodName () const {return methodName;};
std::string Method::getModelName () const {return modelName;};
int Method::getRandomSeed () const {return randomSeed;};
int Method::getPopulationSize () const {return populationSize;};
int Method::getIterationsNumber () const {return iterationsNumber;};
std::string Method::getParamNames (int i) const {return paramNames[i];};
double Method::getParam (int i) const {return params[i];};
std::string Method::getStartTime () const {return startTime;};
std::string Method::getRunTimeString () const {return runTimeString;};
double Method::getRunTime () const {return runTime;};
Point Method::getBestPoint() const {return *bestPoint;};

void Method::init(){
  if (DEBUG_MODE) {std::cout<<"START:\t"<<WHO<<"\tInit.\n";};
  Point* p;
  for (int i=0; i<populationSize; ++i) {
    p = new Point(POINT_SIZE);
    p->generateRandom();
    p->evaluate();
    initPoints.push_back(*p);
  };
  if (DEBUG_MODE) {std::cout<<"END:\t"<<WHO<<"\tInit.\n";};

};

void Method::operator () () {
    timer.start();
    bestPoint = new Point(optimize(initPoints));
    timer.stop();
    runTime = timer.delta();
    runTimeString = timer.deltaToString();
};

Point Method::optimize(const std::vector<Point>& initialPoints) {
    if (DEBUG_MODE) {std::cout<<"START:\t"<<WHO<<"\tOptimize.\n";};
    int min=0;
    for (int i=1; i<initialPoints.size(); ++i){
    if (DEBUG_MODE) {std::cout<<"INFO:\t"<<WHO<<"\tCompare "<<initialPoints[min].getEval()<<" & "<<initialPoints[i].getEval()<<".\n";};
        if (initialPoints[i]<initialPoints[min]){
            min=i;
        }
    }
    if (DEBUG_MODE) {std::cout<<"END:\t"<<WHO<<"\tOptimize.\n";};
    return initialPoints[min];
};

void Method::showResult () const {
  std::cout<<toString()<<"\n";
};
void Method::logResult () {
  log<<toString()<<"\n";
};
void Method::dbResult () {
db.insertHeader(getStartTime(), getMethodName(), getModelName(),
getParam(0), getParam(1), getParam(2), getParam(3), getParam(4),
getPopulationSize(), getIterationsNumber(), getRandomSeed(),
getRunTime(), getBestPoint().toString(), getBestPoint().getEval());
};
void Method::showIteration (std::string who, int iteration, double worstPopEval, double bestPopEval, double bestEval) const {
std::cout<<"INFO:\t"<<who<<"\t["<<iteration<<"]\t"<<worstPopEval<<"\t"<<bestPopEval<<"\t"<<bestEval<<"\n";
};
void Method::logIteration (std::string who, int iteration, double worstPopEval, double bestPopEval, double bestEval) {
log<<"INFO:\t"<<who<<"\t["<<iteration<<"]\t"<<worstPopEval<<"\t"<<bestPopEval<<"\t"<<bestEval<<"\n";
};
void Method::dbIteration (std::string who, int iteration, double worstPopEval, double bestPopEval, double bestEval) {
db.insertDetail(getStartTime(), iteration, worstPopEval, bestPopEval, bestEval);
};

void Method::saveResult ()
{
  if (DEBUG_MODE) {
    showResult();
  };
  if (LOG_MODE) {
    logResult();
  };
  if (DB_MODE) {
    dbResult();
  };
};
void Method::saveIteration (std::string who, int iteration, double worstPopEval, double bestPopEval, double bestEval)
{
  if (DEBUG_MODE) {
    showIteration(who, iteration, worstPopEval, bestPopEval, bestEval);
  };
  if (LOG_MODE) {
    logIteration(who, iteration, worstPopEval, bestPopEval, bestEval);
  };
  if (DB_MODE) {
    dbIteration(who, iteration, worstPopEval, bestPopEval, bestEval);
  };
};

std::string Method::toString () const {
  std::stringstream ss;
	ss<<getMethodName()+"\n";
  ss<<getModelName()+"\n";
	ss<<"Parameters:\n";
  ss<<"\trandom seed:\t\t"    <<getRandomSeed()<<"\n";
	ss<<"\tpopulation size:\t"  <<getPopulationSize()<<"\n";
	ss<<"\titerations number:\t"<<getIterationsNumber()<<"\n";
	for(int i=0; i<5; i++)
  {
    ss<<"\tParam["<<i<<"]("<<getParamNames(i)<<"):\t"<<getParam(i)<<"\n";
  }
  ss<<"Results:\n";
  ss<<"\t"<<getBestPoint().toString()<<"\n";
  ss<<"\tValue:\t"<<getBestPoint().getEval()<<"\n";
  ss<<"\tElapsed time:\t"  <<getRunTimeString()<<" ("<<getRunTime()<<"s.). \n";
	return ss.str();
};

std::ostream& operator<< (std::ostream &os, Method &d){
	os<<d.toString();
	return os;
};
