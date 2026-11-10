#include "problem.h"
#include <QString>

problem::problem()
    :name("empty")
    ,paragraph("empty"){

}

problem::problem(const QString& name, const QString& paragraph)
    :name(name)
    ,paragraph(paragraph){

}

problem::~problem(){

}
QString problem::getName() const{
    return name;
}

QString problem::getParagraph() const{
    return paragraph;
}