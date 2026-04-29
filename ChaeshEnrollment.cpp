#include "ChaeshEnrollment.h"

ChaeshEnrollment::ChaeshEnrollment(ChaeshStudent* student, ChaeshCourse* course)
{
	this->student = student;
	this->course = course;
	this->id = "E";
	this->grade = 1;
	if (count < 10)
	{
		id.append("00");
		id.append(to_string(count));
	}
	else if (count < 100 && count >= 10) {
		id.append("0");
		id.append(to_string(count));
	}
	else {
		id.append(to_string(count));
	}
	count++;
}

double ChaeshEnrollment::getGrade()
{
	return this->grade;
}

ChaeshCourse* ChaeshEnrollment::getCourse()
{
	return this->course;
}

ostream& operator<<(ostream& out, const ChaeshEnrollment& enroll)
{
	out << "수강 ID : " << enroll.id << endl;
	out << "학생 : " << *enroll.student;
	out << "강좌 : " << *enroll.course;
	out << "성적 : " << ((enroll.grade == 1) ? "미입력" : to_string(enroll.grade)) << endl;
	return out;
}
