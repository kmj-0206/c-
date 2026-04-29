//202311383 채성현 202312342 김민준 202510946 김두현 202511492 이창민
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "ChaeshStudent.h"
#include "ChaeshCourse.h"
class ChaeshCourseManager
{
private:
	int max;
	int studentCount = 0;
	int courseCount = 0;
	shared_ptr<ChaeshStudent*[]> studentList;
	shared_ptr<ChaeshCourse*[]> courseList;
public:
	ChaeshCourseManager(int num);
	~ChaeshCourseManager();
	void addStudent(ChaeshStudent* student);
	void addCourse(ChaeshCourse* course);
	ChaeshStudent* findStudent(string id);
	ChaeshCourse* findCourse(string id);
	bool enroll(ChaeshStudent* student, ChaeshCourse* course);
	bool setGrade(string studentId, string courseId, double grade);
	bool cancelEnroll(string studentId, string courseId);
	void printStudentRecord(string studentId);
	void printCommonCourse(ChaeshStudent& s1, ChaeshStudent& s2);
};

