#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "ChaeshStudent.h"
#include "ChaeshCourse.h"
class ChaeshCourseManager
{
private:
	//저장 가능 학생 및 등록 수
	int max;
	//학생배열의 현재 저장 수
	int studentCount = 0;
	//코스 배열의 현재 저장 수
	int courseCount = 0;

	//학생 목록 가리키는 포인터
	shared_ptr<ChaeshStudent*[]> studentList;

	//강의 목록 가리키는 포인터
	shared_ptr<ChaeshCourse*[]> courseList;
public:
	//생성자
	ChaeshCourseManager(int num);
	//학생 추가
	void addStudent(ChaeshStudent* student);
	//강의 추가
	void addCourse(ChaeshCourse* course);
	
	//학생 찾기
	ChaeshStudent* findStudent(string id);
	//강의 찾기
	ChaeshCourse* findCourse(string id);
	
	//등록 /성공여부 반환
	bool enroll(ChaeshStudent* student, ChaeshCourse* course);
	//등록취소 //성공여부 반환
	bool cancelEnroll(string studentId, string courseId);
	
	//성적입력  //성공여부 반환
	bool setGrade(string studentId, string courseId, double grade);
	
	//특정 학생 전체수강내역
	void printStudentRecord(string studentId);

	//공통 수강 출력
	void printCommonCourse(ChaeshStudent* s1, ChaeshStudent* s2);
};

