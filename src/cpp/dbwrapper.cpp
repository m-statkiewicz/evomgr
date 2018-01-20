/*
 * dbwrapper.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Mateusz Statkiewicz
 */

#include"dbwrapper.h"
#include"const.h"
#include <stdio.h>
#include <sqlite3.h> 
#include <sstream>
#include <iostream>


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

DBWrapper::DBWrapper() {
   sqlite3_open(TESTS_DB, &db);
}

DBWrapper::~DBWrapper() {
   sqlite3_close(db);
}

void DBWrapper::execute(std::string sql) {
	
	
   char *zErrMsg = 0;
   int rc;
   
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   //rc = sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);
}

void DBWrapper::insertHeader(std::string timestamp, std::string method, std::string model, double param1, double param2, double param3, double param4, int population_size, int iterations, int random_seed, double runtime, std::string best_point, double eval
) {
	std::stringstream ss;
	ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
	ss <<"INSERT INTO HEADER (TIMESTAMP, METHOD, MODEL, PARAM1, PARAM2, PARAM3, PARAM4, POPULATION_SIZE, ITERATIONS, RANDOM_SEED, RUN_TIME, BEST_POINT, EVAL ) VALUES (\"";
	ss <<timestamp;
	ss <<"\",\"";	
	ss <<method;
	ss <<"\",\"";
	ss <<model;
	ss <<"\",";
	ss <<param1;
	ss <<",";
	ss <<param2;
	ss <<",";
	ss <<param3;
	ss <<",";
	ss <<param4;
	ss <<",";
	ss <<population_size;
	ss <<",";
	ss <<iterations;
	ss <<",";
	ss <<random_seed;
	ss <<",";
	ss <<runtime;
	ss <<",\"";
	ss <<best_point;
	ss <<"\",";
	ss <<eval;
	ss <<")";
	std::string sql= ss.str();
	std::cout<<sql<<"\n";
	execute(sql);

}

void DBWrapper::insertDetail(std::string timestamp, int iteration, double pbest, double pworst, double best) {
	
	std::stringstream ss;
	ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
	ss <<"INSERT INTO DETAILS (TIMESTAMP, ITERATION, POPULATION_BEST, POPULATION_WORST, BEST) VALUES (\"";
	ss <<timestamp;
	ss <<"\",";
	ss <<iteration;
	ss <<",";
	ss <<pbest;
	ss <<",";
	ss <<pworst;
	ss <<",";
	ss <<best;
	ss <<");";
	std::string sql= ss.str();
	std::cout<<sql<<"\n";
	execute(sql);
};
   