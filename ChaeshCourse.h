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
	//아이디
	string id;
	//이름
	string name;
	//교수이름
	string prof;
	//최대 수강인원
	int max;
	//현재 수강생
	int count;
	//듣고 있는 학생 목록 가리키는 포인터
	shared_ptr<ChaeshStudent*[]> studentList;
public:
	//코스 기본생성자 삭제
	ChaeshCourse() = delete;

	//코스 생성자(아이디,이름,
	ChaeshCourse(string id, string name, string prof, int max);

	//깊은복사
	ChaeshCourse& operator=(ChaeshCourse& course);
	//학생 수강(등록). 성공 여부 반환
	bool enrollStudent(ChaeshStudent& student);
	//학생 수강(등록) 취소. 성공 여부 반환
	bool cancelStudent(ChaeshStudent& student);

	//코스 아이디 get
	string getCourseId();
	//외부 출력시 정보 가져가기 쉽게하기
	friend ostream& operator<<(ostream& out, const ChaeshCourse& course);
	//최대 인원 바꾸기
	void changeCapacity(int num);
};

