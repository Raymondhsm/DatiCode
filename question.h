#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{

private:
    QString question;
    QString answer;
    QString optionA;
    QString optionB;
    QString optionC;
    QString optionD;
    int type;

public:
    Question();

    void setQuestion(QString question);
    void setAnswer(QString answer);
    void setOptionA(QString optionA);
    void setOptionB(QString optionB);
    void setOptionC(QString optionC);
    void setOptionD(QString optionD);
    void setType(int type);

    QString getQuestion();
    QString getAnswer();
    QString getOptionA();
    QString getOptionB();
    QString getOptionC();
    QString getOptionD();
    int getType();
};


#endif // QUESTION_H
