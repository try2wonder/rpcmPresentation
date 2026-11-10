#ifndef PROBLEM_H
#define PROBLEM_H
#include <QString>

class problem
{
public:
    problem();
    problem(const QString& name, const QString& paragraph);

    ~problem();

    QString getName() const;
    QString getParagraph() const;

private:
    QString name;
    QString paragraph;

};


#endif // PROBLEM_H
