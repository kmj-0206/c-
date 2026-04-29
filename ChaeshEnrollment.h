//202311383 채성현 202312342 김민준 202510946 김두현 202511492 이창민
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
	int count = 1;
	ChaeshStudent* student;
	ChaeshCourse* course;
	double grade;
public:
	ChaeshEnrollment(ChaeshStudent* student, ChaeshCourse* course);
	double getGrade();
	void setGrade(double grade);
	ChaeshCourse* getCourse();
	friend ostream& operator<< (ostream& out, const ChaeshEnrollment& enroll);
};

