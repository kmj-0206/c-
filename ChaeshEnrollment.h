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
	//등록 객체의 고유 id
	string id;
	//id몇 번까지 생겼는지
	int count = 0;
	//학생 저장(주소로)
	ChaeshStudent* student;
	//코스 저장(주소로)
	ChaeshCourse* course;
	//성적
	double grade;
public:
	//등록 객체 생성자
	ChaeshEnrollment(ChaeshStudent* student, ChaeshCourse* course);

	//성적 받아오기
	double getGrade();

	//코스 받아오기
	ChaeshCourse* getCourse();

	//출력시 정보 가져가게 friend 선언
	friend ostream& operator<< (ostream& out, const ChaeshEnrollment& enroll);
};

