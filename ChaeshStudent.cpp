//202311383 채성현 202312342 김민준 202510946 김두현 202511492 이창민
#include "ChaeshStudent.h"

ChaeshStudent::ChaeshStudent(string id, string name, int grade)
	:id(id),name(name),grade(grade),countCourse(0)
{
	courseList = make_shared<ChaeshCourse*[]>(100);
	enrollList = make_shared<ChaeshEnrollment * []>(100);
}

ChaeshStudent::~ChaeshStudent()
{
	
	for (int i = 0; i < countCourse; i++)
	{
		if (enrollList[i] != nullptr)
		{
			delete this->enrollList[i];
			enrollList[i] = nullptr;
		}
	}
}

ChaeshStudent& ChaeshStudent::operator=(ChaeshStudent& student)
{
	if (this == &student)
	{
		return *this;
	}
	this->grade = student.grade;
	this->id = student.id;
	this->name = student.name;
	return *this;
}

string ChaeshStudent::getId()
{
	return this->id;
}

string ChaeshStudent::getName()
{
	return this->name;
}

double ChaeshStudent::getStudentGrade()
{
	return this->grade;
}

int ChaeshStudent::getCountCourse()
{
	return this->countCourse;
}

bool ChaeshStudent::enrollCourse(ChaeshCourse* course)
{
	if (&course == nullptr)
	{
		return false;
	}
	for (int i = 0; i < countCourse; i++)
	{
		if (this->courseList[i]->getCourseId() == course->getCourseId()) {
			return false;
		}
	}
	this->courseList[countCourse] = course;
	this->enrollList[countCourse] = new ChaeshEnrollment(this, course);
	countCourse++;
	return true;
}

bool ChaeshStudent::cancelCourse(ChaeshCourse& course)
{
	for (int i = 0; i < countCourse; i++)
	{
		if (this->courseList[i]->getCourseId() == course.getCourseId()) {

			delete this->enrollList[i];
			for (int j = i; j < countCourse - 1; j++)
			{
				this->courseList[j] = this->courseList[j + 1];
				this->enrollList[j] = this->enrollList[j + 1];
			}
			this->courseList[countCourse - 1] = nullptr;
			this->enrollList[countCourse - 1] = nullptr;
			countCourse--;
			return true;
		}
	}
	return false;
}

void ChaeshStudent::setGrade(int grade)
{
	this->grade = grade;
}

ChaeshEnrollment* ChaeshStudent::operator[](int num)
{
	if (num >= 0 && num < this->countCourse)
	{
		return enrollList[num];
	}
	else
	{
		cout << "배열 참조 오류" << endl;
		exit(0);
	}
}

ostream& operator<<(ostream& out, const ChaeshStudent& student)
{
	out << "학생 ID : " << student.id << ", 이름 : " << student.name << ", 학년 : " << student.grade;
	out << "학년" << endl;
	return out;
}
