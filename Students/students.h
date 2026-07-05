#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
public:
    Student();
    Student(const QString& surname, qint64 course, qint32 phone);

    // Геттеры
    QString getSurname() const;
    qint64 getCourse() const;
    qint32 getPhone() const;

    // Сеттеры
    void setSurname(const QString& surname);
    void setCourse(qint64 course);
    void setPhone(qint32 phone);

private:
    QString m_surname;
    qint64 m_course;
    qint32 m_phone;
};

#endif // STUDENT_H