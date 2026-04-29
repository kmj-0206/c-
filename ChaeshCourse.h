#pragma once
#include <iostream>
#include <string>
#include "ChaeshStudent.h"
using namespace std;

class ChaeshEnrollment;
class ChaeshStudent;
class ChaeshCourse
{
private:
	string id;
	string name;
	string prof;
	int max;
	int count;
	shared_ptr<ChaeshStudent*[]> studentList;
public:
	ChaeshCourse() = delete;
	ChaeshCourse(string id, string name, string prof, int max);
	ChaeshCourse& operator=(ChaeshCourse& course);
	bool enrollStudent(ChaeshStudent& student);
	bool cancelStudent(ChaeshStudent& student);
	string getCourseId();
	friend ostream& operator<<(ostream& out, const ChaeshCourse& course);
	void changeCapacity(int num);
};

