//202311383 채성현 202312342 김민준 202510946 김두현 202511492 이창민
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
	int grade;
	int countCourse;
	shared_ptr<ChaeshCourse*[]> courseList;
	shared_ptr<ChaeshEnrollment*[]> enrollList;
public:
	ChaeshStudent() = delete;
	ChaeshStudent(string id, string name, int grade);
	~ChaeshStudent();
	ChaeshStudent& operator=(ChaeshStudent& student);
	string getId();
	string getName();
	double getStudentGrade();
	int getCountCourse();
	bool enrollCourse(ChaeshCourse* course);
	bool cancelCourse(ChaeshCourse& course);
	void setGrade(int grade);
	friend ostream& operator<< (ostream& out, const ChaeshStudent& student);
	ChaeshEnrollment* operator[](int num);
};

