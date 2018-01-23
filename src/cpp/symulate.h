#ifndef SYMULATE
#define SYMULATE


double static_model_symulation(const Point p);
double static_model_veryfication(const Point p,const int data_ind, const std::string filename);
double dynamic_model_symulation(const Point p);
double dynamic_model_veryfication(const Point p,const int data_ind, const std::string filename);
double model_symulation(const Point p);
double model_veryfication(const Point p,const int data_ind, const std::string filename);

#endif