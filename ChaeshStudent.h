#pragma once
#include <iostream>
#include <string>
#include "ChaeshCourse.h"
#include <memory>
#include "ChaeshEnrollment.h"
using namespace std;

class ChaeshEnrollment;
class ChaeshCourse;
class ChaeshStudent
{
private:
	string id;
	string name;
	double grade;
	int countCourse;
	shared_ptr<ChaeshCourse*[]> courseList;
	shared_ptr<ChaeshEnrollment*[]> enrollList;
public:
	ChaeshStudent() = delete;
	ChaeshStudent(string id, string name, double grade);
	ChaeshStudent& operator=(ChaeshStudent& student);
	string getId();
	string getName();
	int getCountCourse();
	bool enrollCourse(ChaeshCourse& course);
	bool cancelCourse(ChaeshCourse& course);
	void setGrade(double grade);
	friend ostream& operator<< (ostream& out, const ChaeshStudent& student);
	ChaeshEnrollment* operator[](int num);
};

