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
	//학생id
	string id;
	//학생이름
	string name;
	//학생 학년
	double grade;
	//수강 강좌 수
	int countCourse;

	//수강중인 강좌 목록 가리키는 포인터
	shared_ptr<ChaeshCourse*[]> courseList;
	
	//수강중인 등록객체 목록 가리키는 포인터
	shared_ptr<ChaeshEnrollment*[]> enrollList;
public:
	//기본생성자 제거
	ChaeshStudent() = delete;
	//생성자(아이디,학생이름,학년)
	ChaeshStudent(string id, string name, double grade);

	//깊은복사
	ChaeshStudent& operator=(ChaeshStudent& student);

	//학생 아이디 반환
	string getId();

	//학생명 반환
	string getName();

	//수강 강좌 수 반환
	int getCountCourse();

	//학생에서 수강하기 //성공여부 반환
	bool enrollCourse(ChaeshCourse& course);
	//학생에서 수강 취소 //성공여부 반환
	bool cancelCourse(ChaeshCourse& course);

	//성적 등록
	void setGrade(double grade);

	//출력시 정보 빼가게 friend
	friend ostream& operator<< (ostream& out, const ChaeshStudent& student);
	//배열처럼 쓰게 함.
	ChaeshEnrollment* operator[](int num);
};

