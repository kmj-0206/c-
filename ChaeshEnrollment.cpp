//202311383 채성현 202312342 김민준 202510946 김두현 202511492 이창민
#include "ChaeshEnrollment.h"
#include <iomanip>

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

void ChaeshEnrollment::setGrade(double grade)
{
	this->grade = grade;
}

ChaeshCourse* ChaeshEnrollment::getCourse()
{
	return this->course;
}

ostream& operator<<(ostream& out, const ChaeshEnrollment& enroll)
{
	out << "수강 ID : " << enroll.id << endl;
	out << "학생 : " << enroll.student->getId() << " " << enroll.student->getName() <<  " (" << enroll.student->getStudentGrade() << "학년)" << endl;
	out << "강좌 : " << enroll.course->getCourseId() << " " << enroll.course->getCourseName() << " (" << enroll.course->getProf() << ")" << endl;
	out << "성적 : ";
	if (enroll.grade == 1)
	{
		out << "미입력" << endl;
	}
	else 
	{
		out << fixed << setprecision(1) << enroll.grade << endl;
	}
	return out;
}
