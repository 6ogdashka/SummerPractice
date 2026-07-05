#include "students.h"

Student::Student() : m_surname(""), m_course(1), m_phone(0)
{
}

Student::Student(const QString& surname, qint64 course, qint32 phone)
    : m_surname(surname), m_course(course), m_phone(phone)
{
}

QString Student::getSurname() const { return m_surname; }
qint64 Student::getCourse() const { return m_course; }
qint32 Student::getPhone() const { return m_phone; }

void Student::setSurname(const QString& surname) { m_surname = surname; }
void Student::setCourse(qint64 course) { m_course = course; }
void Student::setPhone(qint32 phone) { m_phone = phone; }