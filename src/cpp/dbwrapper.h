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

class DBWrapper {
private:
	sqlite3 *db;
public:
	DBWrapper();
	~DBWrapper();
	void execute(std::string sql);
	void insertHeader(std::string timestamp, std::string method, std::string model, double param1, double param2, double param3, double param4, int population_size, int iterations, int random_seed, double runtime, std::string best_point, double eval);
	void insertDetail(std::string timestamp, int iteration, double pbest, double pworst, double best);
};
#endif /* DBWRAPPER */
