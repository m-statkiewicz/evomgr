#include "point.h"
#include "symulate.h"

const std::string Point::WHO = "POINT";

Point::Point(){
	if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tConstructor.\n";};
	size=0;
	value = NULL;
	isEvalCorrect=0;
	if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tConstructor.\n";};
};

Point::Point(int size){
	if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tConstructor.\n";};
	this->size=size;
	value = new float[size];
	for (int i = 0; i<size; ++i)
		value[i]=0;
	isEvalCorrect=0;
	if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tConstructor.\n";};
};


Point::Point(const Point * p){
	if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tConstructor.\n";};
	size=p->getSize();
	value = new float[size];
	for (int i = 0; i<size; ++i)
		value[i]=p->value[i];
	eval=p->eval;
	isEvalCorrect=p->isEvalCorrect;
	if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tConstructor.\n";};
};

Point::Point(const Point & p){
	if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tConstructor.\n";};
	size=p.getSize();
	value = new float[size];
	for (int i = 0; i<size; ++i)
		value[i]=p.value[i];
	eval=p.eval;
	isEvalCorrect=p.isEvalCorrect;
	if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tConstructor.\n";};
};

Point::~Point(){
	if (MEMO_MODE) {std::cout<<"START:\t"<<WHO<<"\tDestructor.\n";};
	delete value;
	if (MEMO_MODE) {std::cout<<"END:\t"<<WHO<<"\tDestructor.\n";};
}

int Point::getSize() const{
	return size;
}

float Point::getCoord(int i) const{
    return value[i];
}

void Point::setCoord(int i, float val){
    this->value[i]=val;
}

float Point::getEval() const {
    return eval;
}

void Point::evaluate() {
	eval=model_symulation(*this);
	isEvalCorrect=1;
};

void Point::generateRandom(){
	for (int i = 0; i<size; ++i)
		value[i]=(float)(rand()%(2*RADIUS*PRECISION))/PRECISION-RADIUS;
};


bool Point::operator<(const Point& other) const {
    return getEval()<other.getEval();
}

std::string Point::toString() const{
	std::stringstream ss;
	ss<<"[";
	for (int i=0; i<getSize(); ++i)
	{
	ss<<getCoord(i);
	if (i<getSize()-1)
		ss<<",";
	}
	ss<<"]";
	return ss.str();
};

std::ostream& operator<< (std::ostream &os, Point & p){
	os<<"values=[";
	for (int i=0; i<p.getSize(); ++i)
	{
	os<<p.getCoord(i);
	if (i<p.getSize()-1)
		os<<",";
	}
	os<<"]\t";
	os<<"E:"<<p.getEval()<<"\n";
	return os;
};
