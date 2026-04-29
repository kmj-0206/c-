#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "ChaeshStudent.h"
#include "ChaeshCourse.h"
using namespace std;
class ChaeshStudent;
class ChaeshCourse;
class ChaeshEnrollment
{
private:
	string id;
	int count = 0;
	ChaeshStudent* student;
	ChaeshCourse* course;
	double grade;
public:
	ChaeshEnrollment(ChaeshStudent* student, ChaeshCourse* course);
	double getGrade();
	ChaeshCourse* getCourse();
	friend ostream& operator<< (ostream& out, const ChaeshEnrollment& enroll);
};

