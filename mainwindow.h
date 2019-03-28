#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <vector>
#include "question.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void btnNext();
    void btnup();
    void btnAnswer();
    void btnNextPart();
    void showLCD();
    void showLCD2();

    void add1();
    void add2();
    void add3();
    void add4();
    void add5();
    void add6();
    void add7();
    void add8();
    void add9();
    void add10();

    void subtract1();
    void subtract2();
    void subtract3();
    void subtract4();
    void subtract5();
    void subtract6();
    void subtract7();
    void subtract8();
    void subtract9();
    void subtract10();

    void choosePath();

    void SBida1();
    void SQiangda1();
    void SPK();
    void SBida2();
    void SQiangda2();
    void SWheel();
    void SFinal();

    void TBida();
    void TQiangda();
    void TPK();
    void TChoose();
    void TTime();
    void TFinal();

    void chooseLevelD();
    void chooseLevelN();
    void chooseLevelE();

    void chooseKind(int index);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    void clear();
    void initial();
    void readQuestion(QString filePath, vector<Question> &st);

    QTimer *time=new QTimer(this);
    QTimer *time2=new QTimer(this);
    double count=20;
    QString path;
    QString filePath;
    int markAdd;
    int markSubtract;
    int part;
    int chooseCount;
    int level=3;
    int difficult=0;
    int normal=6;
    int easy=18;
    int choose=0;
    int chooseNum=0;
    int PKNum=0;
    int PKCount=0;
    double countlcd2=45;
    int timeCount=0;

    vector<Question> sBida1;
    vector<Question> sQiangda1;
    vector<Question> sPK;
    vector<Question> sBida2;
    vector<Question> sQiangda2;
    vector<Question> sWheel;
    vector<Question> sFinal;

    vector<Question> tBida;
    vector<Question> tQiangda;
    vector<Question> tPK;
    vector<Question> tChoose;
    vector<Question> tTime;
    vector<Question> tFinal;

    vector<Question> timu;
    int counter;

};

#endif // MAINWINDOW_H
