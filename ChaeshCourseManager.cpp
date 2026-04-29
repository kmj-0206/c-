//202311383 채성현 202312342 김민준 202510946 김두현 202511492 이창민
#include "ChaeshCourseManager.h"

ChaeshCourseManager::ChaeshCourseManager(int num)
{
	if (num < 100)
	{
		this->max = num;
		this->studentList = make_shared<ChaeshStudent*[]>(num);
		this->courseList = make_shared<ChaeshCourse*[]>(num);
	}
	else {
		cout << "최대 100까지 등록 가능합니다." << endl;
		exit(0);
	}
}

ChaeshCourseManager::~ChaeshCourseManager()
{
	
	for (int i = 0; i < studentCount; i++)
	{
		if (studentList[i] != nullptr)
		{
			delete studentList[i];
			studentList[i] = nullptr;
		}
	}
	for (int i = 0; i < courseCount; i++)
	{
		if (courseList[i] != nullptr)
		{
			delete courseList[i];
			courseList[i] = nullptr;
		}
	}
}

void ChaeshCourseManager::addStudent(ChaeshStudent* student)
{
	if (studentCount >= max) {
		cout << "더 이상 학생을 추가할 수 없습니다." << endl;
		delete student;
		return;
	}
	for (int i = 0; i < studentCount; i++)
	{
		if (this->studentList[i]->getId() == student->getId()) {
			cout << "중복된 학생ID 입니다." << endl;
			delete student;
			return;
		}
	}
	this->studentList[studentCount] = student;
	studentCount++;
	cout << "학생 등록 완료." << endl;
	return;
}

void ChaeshCourseManager::addCourse(ChaeshCourse* course)
{
	if (courseCount >= max) {
		cout << "더 이상 강좌를 추가할 수 없습니다." << endl;
		delete course;
		return;
	}
	for (int i = 0; i < courseCount; i++)
	{
		if (this->courseList[i]->getCourseId() == course->getCourseId()) {
			cout << "중복된 강좌ID입니다." << endl;
			delete course;
			return;
		}
	}
	this->courseList[courseCount] = course;
	courseCount++;
	cout << "강좌 등록 완료" << endl;
	return;
}

ChaeshStudent* ChaeshCourseManager::findStudent(string id)
{
	for (int i = 0; i < studentCount; i++)
	{
		if (studentList[i]->getId() == id) {
			return studentList[i];
		}
	}
	cout << "검색한 ID의 학생이 없습니다." << endl;
	return nullptr;
}

ChaeshCourse* ChaeshCourseManager::findCourse(string id)
{
	for (int i = 0; i < courseCount; i++)
	{
		if (courseList[i]->getCourseId() == id) {
			return courseList[i];
		}
	}
	cout << "검색한 ID의 강좌가 없습니다." << endl;
	return nullptr;
}

bool ChaeshCourseManager::enroll(ChaeshStudent* student, ChaeshCourse* course)
{
	return (course->enrollStudent(*student) && student->enrollCourse(course)) ? true : false;
}

bool ChaeshCourseManager::setGrade(string studentId, string courseId, double grade)
{
	ChaeshStudent* student = findStudent(studentId);
	ChaeshCourse* course = findCourse(courseId);
	if (grade >= 0 && grade <=4.5)
	{
		for (int i = 0; i < student->getCountCourse(); i++)
		{
			if ((*student)[i]->getCourse()->getCourseId() == course->getCourseId())
			{
				(*student)[i]->setGrade(grade);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool ChaeshCourseManager::cancelEnroll(string studentId, string courseId)
{
	ChaeshStudent* student = findStudent(studentId);
	ChaeshCourse* course = findCourse(courseId);
	if (student != nullptr && course != nullptr)
	{
		student->cancelCourse(*course);
		course->cancelStudent(*student);
		return true;
	}
	else
	{
		return false;
	}
}

void ChaeshCourseManager::printStudentRecord(string studentId)
{
	ChaeshStudent* student = findStudent(studentId);
	double sum = 0;
	cout << "===" << student->getName() << "===" << endl;
	for (int i = 0; i < student->getCountCourse(); i++)
	{
		cout << *(*student)[i] << endl;
		sum += (*student)[i]->getGrade();
	}

	cout << "총 수강 강좌 수 : " << student->getCountCourse() << "개 / 평균 : " << sum / student->getCountCourse()<< endl;
}

void ChaeshCourseManager::printCommonCourse(ChaeshStudent& s1, ChaeshStudent& s2)
{
	bool hasCommon = false;
	int count1 = s1.getCountCourse();
	int count2 = s2.getCountCourse();


	for (int i = 0; i < count1; i++)
	{

		ChaeshEnrollment* enroll1 = s1[i];
		if (enroll1 == nullptr) continue;


		for (int j = 0; j < count2; j++)
		{
			ChaeshEnrollment* enroll2 = s2[j];
			if (enroll2 == nullptr) continue;


			if (enroll1->getCourse()->getCourseId() == enroll2->getCourse()->getCourseId())
			{

				cout << endl;
				cout << "강좌 ID : " << enroll1->getCourse()->getCourseId() << ", 강좌명 : " << enroll1->getCourse()->getCourseName();
				cout << " (" << enroll1->getCourse()->getProf() << ")" << endl;
				hasCommon = true;
				break;
			}
		}

		if (!hasCommon) {
			cout << "공통으로 수강 중인 강좌가 없습니다." << endl;
		}
	}
}