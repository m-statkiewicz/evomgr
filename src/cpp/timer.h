/*
 * timer.h
 *
 *  Created on: Aug 15, 2013
 *      Author: Mateusz Statkiewicz
 */

#ifndef TIMER
#define TIMER

#include<exception>
#include<string>
#include<sstream>
#include<sys/time.h>
#include<unistd.h>

#include"const.h"


enum TimerExceptionMsg {
	WRONG_STATE, UNRECOGNIZED
};

class TimerException: public std::exception {
public:

private:
	TimerExceptionMsg msg;
	std::string getCommunicate() {
		std::string result = "Unrecognized exception.";
		switch (msg)
		{
		case WRONG_STATE :
			result = "Wrong operation for this state.";
			break;
		};
		return result;
	}
public:
	TimerException(TimerExceptionMsg newExMsg) {
		msg = newExMsg;
	}
	std::string getMsg() {
		return getCommunicate();
	}
};

class Timer {
private:
	static const std::string WHO;
	struct timeval start_t, end_t;
	char state;
public:
	Timer();
	Timer(bool s);
	~Timer();
	void start() throw(TimerException);
	void stop() throw(TimerException);
	double delta() throw(TimerException);
	std::string deltaToString();
	friend class TimerTest;
	const std::string currentDateTime();
};
#endif /* TIMER */
