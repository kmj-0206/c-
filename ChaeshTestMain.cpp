//202311383 채성현 202312342 김민준 202510946 김두현 202511492 이창민
#ifdef _DEBUG
	#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DBG_NEW
#endif
#endif
#include "ChaeshStudent.h"
#include "ChaeshCourse.h"
#include "ChaeshEnrollment.h"
#include "ChaeshCourseManager.h"
#include <iostream>

using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << "학번 : 202311383 이름 : 채성현" << endl;
	ChaeshStudent s1("S101", "홍길동", 2);
	cout << s1 << endl;
	
	ChaeshCourse c1("C001", "자료구조", "김교수", 3);
	cout << c1 << endl;
	ChaeshCourse c2("C002", "운영체제", "이교수", 2);
	ChaeshCourse c3("C003", "알고리즘", "박교수", 2);

	ChaeshEnrollment e1(&s1, &c1);
	cout << e1 << endl;

	ChaeshCourseManager mgr(3);
	mgr.addCourse(new ChaeshCourse("C001", "자료구조", "김교수", 3));
	mgr.addCourse(new ChaeshCourse("C002", "운영체제", "이교수", 2));
	mgr.addCourse(new ChaeshCourse("C001", "중복강좌", "최교수", 1));
	mgr.addCourse(new ChaeshCourse("C003", "알고리즘", "박교수", 2));
	mgr.addCourse(new ChaeshCourse("C004", "초과강좌", "강교수", 1));

	mgr.addStudent(new ChaeshStudent("S101", "홍길동", 2));
	mgr.addStudent(new ChaeshStudent("S102", "이길동", 3));
	mgr.addStudent(new ChaeshStudent("S103", "차길동", 1));
	mgr.addStudent(new ChaeshStudent("S101", "박길동", 4));

	ChaeshCourse* c = mgr.findCourse("C002");
	ChaeshStudent* s = mgr.findStudent("S101");

	if (mgr.enroll(s, c))
		cout << "수강신청 완료" << endl;
	else
		cout << "수강신청 실패 ( 중복 또는 만석 )" << endl;

	if (mgr.enroll(s, c))
		cout << "수강신청 완료" << endl;
	else
		cout << "수강신청 실패 ( 중복 또는 만석 )" << endl;

	ChaeshStudent* s2 = mgr.findStudent("S102");
	if (mgr.enroll(s2, c))
		cout << "수강신청 완료" << endl;
	else
		cout << "수강신청 실패 ( 중복 또는 만석 )" << endl;

	ChaeshStudent* s3 = mgr.findStudent("S103");
	if (mgr.enroll(s3, c))
		cout << "수강신청 완료" << endl;
	else
		cout << "수강신청 실패 ( 중복 또는 만석 )" << endl;

	cout << *c << endl;

	
	if (mgr.setGrade("S101", "C002", 4.5))
	{
		cout << "성적 입력 완료." << endl;
	}
	else
	{
		cout << "성적 입력 실패 (범위 초과)" << endl;
	}
	if (mgr.setGrade("S101", "C002", 5.0))
	{
		cout << "성적 입력 완료." << endl;
	}
	else
	{
		cout << "성적 입력 실패 (범위 초과)" << endl;
	}

	mgr.setGrade("S101", "C002", 3.5);
	mgr.printStudentRecord("S101");

	if (mgr.cancelEnroll("S101", "C002"))
	{
		cout << "수강 취소 완료." << endl;
	}
	else
	{
		cout << "수강 기록 없음" << endl;
	}
	cout << *c << endl;

	mgr.enroll(s, mgr.findCourse("C001"));
	mgr.setGrade("S101", "C001", 4.0);
	mgr.printStudentRecord("S101");

	mgr.enroll(s2, mgr.findCourse("C001"));
	mgr.printCommonCourse(*s, *s2);

	ChaeshCourse* target = mgr.findCourse("C002");
	target->changeCapacity(1);
	target->changeCapacity(5);
	cout << *target << endl;
	return 0;
}