#include "method.h"

bool compare(const Point& a,const Point& b)  {
    return a.getEval()<b.getEval();
};

Point Method::operator () (const std::vector<Point*>& initialPoints) const {
    std::vector<Point*> vec(initialPoints);
    Point v=*vec[0];
    for (int i=1; i<vec.size(); ++i)
        if (*vec[i]<v)
            v=vec[i];
    return v;
}

