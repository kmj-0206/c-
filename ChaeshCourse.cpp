#include "ChaeshCourse.h"

ChaeshCourse::ChaeshCourse(string id, string name, string prof, int max)
	:id(id),name(name),prof(prof),max(max)
{
	this->count = 0;
	this->studentList = make_shared<ChaeshStudent*[]>(max);
}

ChaeshCourse& ChaeshCourse::operator=(ChaeshCourse& course)
{
	if (this == &course)
	{
		return *this;
	}
	this->id = course.id;
	this->max = course.max;
	this->name = course.name;
	this->prof = course.prof;
	return *this;
}

bool ChaeshCourse::enrollStudent(ChaeshStudent& student)
{
	if (&student == nullptr)
	{
		return false;
	}
	if (this->max == this->count)
	{
		return false;
	}
	for (int i = 0; i < count; i++)
	{
		if (this->studentList[i]->getId() == student.getId()) {
			return false;
		}
	}
	this->studentList[count] = &student;
	count++;
	return true;
}

bool ChaeshCourse::cancelStudent(ChaeshStudent& student)
{
	for (int i = 0; i < count; i++)
	{
		if (this->studentList[i]->getId() == student.getId()) {
			delete this->studentList[i];
			return true;
		}
	}
	return false;
}

string ChaeshCourse::getCourseId()
{
	return this->id;
}

void ChaeshCourse::changeCapacity(int num)
{
	if (num > this->max)
	{
		this->max = num;
		cout << "강의실 변경 완료 (새 수용 인원 : " << this->max << ")" << endl;
	}
	else {
		cout << "더 큰 강의실로만 이동 가능합니다." << endl;
	}
	return;
}

ostream& operator<<(ostream& out, const ChaeshCourse& course)
{
	out << "강좌 ID : " << course.id << ", 강좌명 : " << course.name << endl;
	out << "담당교수 : " << course.prof << ", 수강가능인원 : " << course.count << "/" << course.max << endl;
	out << "------" << endl;
	if (course.count == 0)
	{
		out << "수강생 없음." << endl;
		return out;
	}
	for (int i = 0; i < course.count; i++)
	{
		out << *course.studentList[i] << endl;
	}
	return out;
}

