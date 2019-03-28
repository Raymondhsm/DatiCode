#include "question.h"

Question::Question()
{
    this->question="";
    this->answer="";
    this->optionA="";
    this->optionB="";
    this->optionC="";
    this->optionD="";
    this->type=0;
}

void Question::setQuestion(QString question)
{
    this->question=question;
}

void Question::setAnswer(QString answer)
{
    this->answer=answer;
}

void Question::setOptionA(QString optionA)
{
    this->optionA=optionA;
}

void Question::setOptionB(QString optionB)
{
    this->optionB=optionB;
}

void Question::setOptionC(QString optionC)
{
    this->optionC=optionC;
}

void Question::setOptionD(QString optionD)
{
    this->optionD=optionD;
}

void Question::setType(int type)
{
    this->type=type;
}

QString Question::getQuestion()
{
    return this->question;
}

QString Question::getAnswer()
{
    return this->answer;
}

QString Question::getOptionA()
{
    return this->optionA;
}

QString Question::getOptionB()
{
    return this->optionB;
}

QString Question::getOptionC()
{
    return this->optionC;
}

QString Question::getOptionD()
{
    return this->optionD;
}

int Question::getType()
{
    return type;
}
