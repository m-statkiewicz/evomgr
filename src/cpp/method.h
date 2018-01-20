/*
 * method.h
 */

#ifndef METHOD		
#define METHOD

#include<vector>
#include<string>

#include"point.h"

class Method
{
public:
	Point operator () (const std::vector<Point*>& initialPoints) const;
};

#endif
