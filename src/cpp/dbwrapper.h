/*
 * dbwrapper.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Mateusz Statkiewicz
 */

#ifndef DBWRAPPER
#define DBWRAPPER

#include<string>
#include<sqlite3.h>

#include"const.h"

class DBWrapper {
private:
  static const std::string WHO;
	sqlite3 *db;
public:
	DBWrapper();
	~DBWrapper();
	void execute(std::string sql);
  bool checkDB();
  void generateDB();
	void insertHeader(std::string timestamp, std::string method, std::string model, double param0, double param1, double param2, double param3, double param4, int population_size, int iterations, int random_seed, double runtime, std::string best_point, double eval);
	void insertDetail(std::string timestamp, int iteration, double pbest, double pworst, double best);
};
#endif /* DBWRAPPER */
