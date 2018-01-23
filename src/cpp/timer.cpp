/*
 * timer.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: Mateusz Statkiewicz
 */

#include"timer.h"

Timer::Timer() {
	state = 'n';
}

Timer::Timer(bool startsAtStart) {
	Timer();
	if (startsAtStart == true)
		start();
}

Timer::~Timer() {
}

void Timer::start() throw (TimerException) {
	if (state == 'm') {
		throw TimerException(WRONG_STATE);
	}
	state = 'm';
	gettimeofday(&start_t, NULL);
}

void Timer::stop() throw (TimerException) {
	if (state != 'm') {
		throw TimerException(WRONG_STATE);
	}
	state = 's';
	gettimeofday(&end_t, NULL);
}

double Timer::delta() throw (TimerException) {
	if (state != 's') {
		throw TimerException(WRONG_STATE);
	}
	return (end_t.tv_sec - start_t.tv_sec) + (double) (end_t.tv_usec - start_t.tv_usec) / 1000000;
}
std::string Timer::deltaToString()
{
	std::stringstream ss;
	double sec = delta();
    ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
	ss << sec;
	return ss.str();
}
const std::string Timer::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d.%H%M%S", &tstruct);
    return buf;
}
