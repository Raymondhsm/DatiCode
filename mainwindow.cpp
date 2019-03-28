#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <string>
#include <QDebug>
#include <QDir>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    count=0;
    part=11;
    markAdd=0;
    markSubtract=0;
    chooseCount=0;

    ui->setupUi(this);
    time->setInterval(1);
    time2->setInterval(1);
    ui->lcdNumber->display(QString::number(count,'f',3));
    ui->lcdNumber2->display(QString::number(0,'f',3));


    initial();
}

void MainWindow::choosePath(){
    path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "*", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }

    readQuestion(path+"/sBida1.txt",sBida1);
    readQuestion(path+"/sQiangda1.txt",sQiangda1);
    readQuestion(path+"/sPK.txt",sPK);
    readQuestion(path+"/sBida2.txt",sBida2);
    readQuestion(path+"/sQiangda2.txt",sQiangda2);
    readQuestion(path+"/sWheel.txt",sWheel);
    readQuestion(path+"/sFinal.txt",sFinal);

    readQuestion(path+"/tBida.txt",tBida);
    readQuestion(path+"/tQiangda.txt",tQiangda);
    readQuestion(path+"/tPK.txt",tPK);
    readQuestion(path+"/tChoose.txt",tChoose);
    readQuestion(path+"/tTime.txt",tTime);
    readQuestion(path+"/tFinal.txt",tFinal);
}

void MainWindow::readQuestion(QString filePath,vector<Question> &st){
    QFile *file=new QFile(filePath);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))  {
        QMessageBox::warning(this,"Warnning","can't open",QMessageBox::Yes);
    }
    QTextStream *in=new QTextStream(file);
    Question *ti;
    QString str;

    while(!in->atEnd()){
        ti=new Question();
        ti->setQuestion(in->readLine());
        str=in->readLine();
        if(str.mid(0,1)=="A"){
            ti->setOptionA(str);
            ti->setOptionB(in->readLine());
            ti->setOptionC(in->readLine());
            ti->setOptionD(in->readLine());
            ti->setAnswer(in->readLine());
            ti->setType(1);
        }else{
            ti->setAnswer(str);
        }
        st.push_back(*ti);
    }

}

void MainWindow::showLCD2()
{
    countlcd2=countlcd2-0.001;
    if(countlcd2>=0) ui->lcdNumber2->display(QString::number(countlcd2,'f',3));
    else {
        time2->stop();
        ui->lcdNumber2->display(QString::number(0,'f',3));
    }
}

void MainWindow::btnNext(){
    if(part==13||part==23){
        if(PKNum>=9)return;
        PKNum++;
    }
    counter++;
    if(part==26){
        if(easy==36||normal==18||difficult==6)return;
        if(level==1){counter=easy++;ui->rabEasy->setText("易（剩余"+QString::number(36-easy)+"题)");}
        else if(level==2){counter=normal++;ui->rabNormal->setText("中（剩余"+QString::number(18-normal)+"题)");}
        else if(level==3){counter=difficult++;ui->rabDifficult->setText("难（剩余"+QString::number(6-difficult)+"题)");}
    }
    if(part==24){
        if(chooseNum>=3)return;
        counter=choose++;
        chooseNum++;
    }
    if(part==25){
        qDebug()<<timeCount<<counter;
        if(timeCount>=8)return;
        timeCount++;
        time2->start();
    }

    if(counter<timu.size()){
        count=20.000;
        if(!(part==12||part==22||part==15||part==17))time->start();
        ui->textQuestion->setText(timu[counter].getQuestion());
        ui->ledOptionA->setText(timu[counter].getType()==1?timu[counter].getOptionA():"");
        ui->ledOptionB->setText(timu[counter].getType()==1?timu[counter].getOptionB():"");
        ui->ledOptionC->setText(timu[counter].getType()==1?timu[counter].getOptionC():"");
        ui->ledOptionD->setText(timu[counter].getType()==1?timu[counter].getOptionD():"");
        ui->labelAnswer->setText("");
    }
}


void MainWindow::btnNextPart()
{
    time->stop();
    count=20.001;
    showLCD();
    switch(part){
    case 11:
        SQiangda1();
        break;
    case 12:
        SPK();
        break;
    case 13:
        if(PKCount<4){counter=((counter-1)/9)*9+8;PKCount++;PKNum=0;ui->textQuestion->setText("请接下来两位选手做好准备");}
        else SBida2();
        break;
    case 14:
        SQiangda2();
        break;
    case 15:
        SWheel();
        break;
    case 16:
        SFinal();
        break;
    case 17:
        TBida();
        break;
    case 21:
        TQiangda();
        break;
    case 22:
        TPK();
        break;
    case 23:
        if(PKCount<4){counter=((counter-1)/9)*9+8;PKCount++;PKNum=0;ui->textQuestion->setText("请接下来两支队伍做好准备");}
        else TChoose();
        break;
    case 24:
        if(chooseCount<9){
            QString str="<html>"+tr("请选手抢答选择题目类型")+"</html>";
            str+="<html><br>"+tr("  地理        华工      生活      文学      军事")+"</html>";
            str+="<html><br>"+tr("  娱乐        计算机      体育      历史      时事")+"</html>";
            ui->textQuestion->setText(str);chooseCount++;chooseNum=0;}
        else TTime();
        break;
    case 25:
        if(counter<timu.size()-1){counter=((counter-1)/8)*8+7;countlcd2=45.001;timeCount=0;time2->stop();showLCD2();ui->textQuestion->setText("请下一支队伍做好准备");}
        else TFinal();
        break;

    }
}


void MainWindow::btnup()
{
    if(counter>=1){
        counter--;
        count=20.000;
        time->start();
        ui->textQuestion->setText(timu[counter].getQuestion());
        ui->ledOptionA->setText(timu[counter].getType()==1?timu[counter].getOptionA():"");
        ui->ledOptionB->setText(timu[counter].getType()==1?timu[counter].getOptionB():"");
        ui->ledOptionC->setText(timu[counter].getType()==1?timu[counter].getOptionC():"");
        ui->ledOptionD->setText(timu[counter].getType()==1?timu[counter].getOptionD():"");
        ui->labelAnswer->setText("");

    }
}

void MainWindow::btnAnswer()
{
    if(counter<timu.size())
        ui->labelAnswer->setText(timu[counter].getAnswer());
}

void MainWindow::showLCD(){
    count=count-0.001;
    if(count>=0) ui->lcdNumber->display(QString::number(count,'f',3));
    else {
        time->stop();
        ui->lcdNumber->display(QString::number(0,'f',3));
    }
}

void MainWindow::SBida1()
{
    clear();
    markAdd=2;
    markSubtract=2;
    timu=sBida1;
    counter=-1;
    part=11;
    QString str="<html>"+tr("接下来是必答环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得两分,答错不扣分，一共5题，每名选手都要作答")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::SQiangda1()
{
    markAdd=2;
    markSubtract=1;
    timu=sQiangda1;
    counter=-1;
    part=12;
    QString str="<html>"+tr("接下来是抢答环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得两分，答错扣一分，最后一题答对得4分，答错扣两分，一共7题,请每名选手听到“嘟”一声后进行抢答，否则算违规，重新抢答")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::SPK()
{
    clear();
    markAdd=1;
    markSubtract=1;
    timu=sPK;
    counter=-1;
    part=13;
    QString str="<html>"+tr("接下来是双人PK环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("双方通过抢答形式进行回答，答对一题得一分，答错不扣分,一共7题，答对题数多者获胜，请手听到“嘟”一声后进行抢答，否则算违规，重新抢答。")+"</html>";
    str+="<html><br>"+tr("本轮将淘汰五人")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::SBida2()
{
    clear();
    markAdd=2;
    markSubtract=0;
    timu=sBida2;
    counter=-1;
    part=14;
    QString str="<html>"+tr("接下来是必答环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得两分，答错不扣分，一共5题,每名选手都要作答")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::SQiangda2()
{
    markAdd=2;
    markSubtract=1;
    timu=sQiangda2;
    counter=-1;
    part=15;
    QString str="<html>"+tr("接下来是抢答环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得两分，答错扣一分，最后一题答对得4分，答错扣两分，一共7题,请每名选手听到“嘟”一声后进行抢答，否则算违规，重新抢答")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::SWheel()
{
    markAdd=2;
    markSubtract=2;
    timu=sWheel;
    counter=-1;
    part=16;
    QString str="<html>"+tr("接下来是车轮战环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得两分，答错的选手退出本环节，请每名选手轮流作答")+"</html>";
    str+="<html><br>"+tr("本轮过后将根据积分淘汰两人")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::SFinal()
{
    clear();
    markAdd=1;
    markSubtract=1;
    timu=sFinal;
    counter=-1;
    part=17;
    QString str="<html>"+tr("接下来是个人赛决赛环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得一分，答错不扣分，率先获得6分的同学获胜，若30道题后依然没有人答满6道题，则按照答对的题数进行排名。若决出第一名后，剩余两人继续抢答，直至决出二三名")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::TBida()
{
    clear();
    markAdd=2;
    markSubtract=2;
    timu=tBida;
    counter=-1;
    part=21;
    QString str="<html>"+tr("接下来是必答环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得两分,答错不扣分，一共5题，每支队伍都要作答")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::TQiangda()
{
    markAdd=2;
    markSubtract=1;
    timu=tQiangda;
    counter=-1;
    part=22;
    PKCount=0;
    PKNum=0;
    QString str="<html>"+tr("接下来是抢答环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得两分，答错扣一分，最后一题答对得4分，答错扣两分，一共7题,请每支队伍听到“嘟”一声后进行抢答，否则算违规，重新抢答")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::TPK()
{
    clear();
    markAdd=1;
    markSubtract=1;
    timu=tPK;
    counter=-1;
    part=23;
    QString str="<html>"+tr("接下来是两两队伍PK环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("双方通过抢答形式进行回答，答对一题得一分，答错不扣分,一共7题，答对题数多者获胜，请手听到“嘟”一声后进行抢答，否则算违规，重新抢答")+"</html>";
    str+="<html><br>"+tr("本轮过后将淘汰五支队伍")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::TChoose()
{
    clear();
    markAdd=1;
    markSubtract=1;
    timu=tChoose;
    counter=-1;
    part=24;
    QString str="<html>"+tr("接下来是选题必答环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("双方通过抢答形式获得选题资格，每支队伍拥有两次选题机会，每种类型题目一共三题，答对一题得一分，答错不扣分,请手听到“嘟”一声后进行抢答，否则算违规，重新抢答")+"</html>";
    str+="<html><br>"+tr("  地理        华工      生活      文学      军事")+"</html>";
    str+="<html><br>"+tr("  娱乐        计算机      体育      历史      时事")+"</html>";
    ui->textQuestion->setText(str);
}


void MainWindow::TTime()
{
    markAdd=1;
    markSubtract=1;
    timu=tTime;
    counter=-1;
    countlcd2=45;
    part=25;
    QString str="<html>"+tr("接下来是限时答题环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("答对一题得一分，答错不扣分,每支队伍拥有45秒时间进行答题，最多可回答8题。")+"</html>";
    str+="<html><br>"+tr("本轮过后将根据积分淘汰两人")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::TFinal()
{
    clear();
    markAdd=1;
    markSubtract=1;
    timu=tFinal;
    counter=-1;
    part=26;
    QString str="<html>"+tr("接下来是团体赛决赛环节，请选手做好准备。")+"</html>";
    str+="<html><br>"+tr("题目分难易程度，难题一共有6道，答对的对伍得3分，答错则另外两只队伍得2分；中等题为12道，答对得2分，答错另外两支队伍得1分；较易题共有18题，答对得1，答错对手不加分；三队轮流作答，第四轮4进3赛排名靠前的队伍先进行回答，先获得13分的队伍获胜。")+"</html>";
    ui->textQuestion->setText(str);
}

void MainWindow::chooseLevelD()
{
    level=3;
}

void MainWindow::chooseLevelN()
{
    level=2;
}

void MainWindow::chooseLevelE()
{
    level=1;
}

void MainWindow::chooseKind(int index)
{
    choose=(index-1)*3;
}

void MainWindow::add1(){
    QString str=ui->textEdit_1->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_1->setPlainText(QString::number(goal));
}

void MainWindow::add2(){
    QString str=ui->textEdit_2->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_2->setPlainText(QString::number(goal));
}

void MainWindow::add3(){
    QString str=ui->textEdit_3->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_3->setPlainText(QString::number(goal));
}

void MainWindow::add4(){
    QString str=ui->textEdit_4->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_4->setPlainText(QString::number(goal));
}

void MainWindow::add5(){
    QString str=ui->textEdit_5->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_5->setPlainText(QString::number(goal));
}


void MainWindow::add6(){
    QString str=ui->textEdit_6->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_6->setPlainText(QString::number(goal));
}


void MainWindow::add7(){
    QString str=ui->textEdit_7->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_7->setPlainText(QString::number(goal));
}


void MainWindow::add8(){
    QString str=ui->textEdit_8->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_8->setPlainText(QString::number(goal));
}


void MainWindow::add9(){
    QString str=ui->textEdit_9->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_9->setPlainText(QString::number(goal));
}


void MainWindow::add10(){
    QString str=ui->textEdit_10->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()+markAdd;
    ui->textEdit_10->setPlainText(QString::number(goal));
}


void MainWindow::subtract1(){
    QString str=ui->textEdit_1->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_1->setPlainText(QString::number(goal));
}

void MainWindow::subtract2(){
    QString str=ui->textEdit_2->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_2->setPlainText(QString::number(goal));
}

void MainWindow::subtract3(){
    QString str=ui->textEdit_3->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_3->setPlainText(QString::number(goal));
}

void MainWindow::subtract4(){
    QString str=ui->textEdit_4->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_4->setPlainText(QString::number(goal));
}

void MainWindow::subtract5(){
    QString str=ui->textEdit_5->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_5->setPlainText(QString::number(goal));
}

void MainWindow::subtract6(){
    QString str=ui->textEdit_6->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_6->setPlainText(QString::number(goal));
}

void MainWindow::subtract7(){
    QString str=ui->textEdit_7->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_7->setPlainText(QString::number(goal));
}

void MainWindow::subtract8(){
    QString str=ui->textEdit_8->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_8->setPlainText(QString::number(goal));
}

void MainWindow::subtract9(){
    QString str=ui->textEdit_9->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_9->setPlainText(QString::number(goal));
}

void MainWindow::subtract10(){
    QString str=ui->textEdit_10->toPlainText();
    str=str==""?"0":str;
    int goal=str.toInt()-markSubtract;
    ui->textEdit_10->setPlainText(QString::number(goal));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear()
{
    ui->textEdit_1->setText("0");
    ui->textEdit_2->setText("0");
    ui->textEdit_3->setText("0");
    ui->textEdit_4->setText("0");
    ui->textEdit_5->setText("0");
    ui->textEdit_6->setText("0");
    ui->textEdit_7->setText("0");
    ui->textEdit_8->setText("0");
    ui->textEdit_9->setText("0");
    ui->textEdit_10->setText("0");

}

void MainWindow::initial()
{
    connect(this->time,SIGNAL(timeout()),this,SLOT(showLCD()));
    connect(this->time2,SIGNAL(timeout()),this,SLOT(showLCD2()));
    connect(ui->btnNext,SIGNAL(clicked(bool)),this,SLOT(btnNext()));
    connect(ui->btnUp,SIGNAL(clicked(bool)),this,SLOT(btnup()));
    connect(ui->btnNextPart,SIGNAL(clicked(bool)),this,SLOT(btnNextPart()));
    connect(ui->btnAnswer,SIGNAL(clicked(bool)),this,SLOT(btnAnswer()));

    connect(ui->btnAdd1,SIGNAL(clicked(bool)),this,SLOT(add1()));
    connect(ui->btnAdd2,SIGNAL(clicked(bool)),this,SLOT(add2()));
    connect(ui->btnAdd3,SIGNAL(clicked(bool)),this,SLOT(add3()));
    connect(ui->btnAdd4,SIGNAL(clicked(bool)),this,SLOT(add4()));
    connect(ui->btnAdd5,SIGNAL(clicked(bool)),this,SLOT(add5()));
    connect(ui->btnAdd6,SIGNAL(clicked(bool)),this,SLOT(add6()));
    connect(ui->btnAdd7,SIGNAL(clicked(bool)),this,SLOT(add7()));
    connect(ui->btnAdd8,SIGNAL(clicked(bool)),this,SLOT(add8()));
    connect(ui->btnAdd9,SIGNAL(clicked(bool)),this,SLOT(add9()));
    connect(ui->btnAdd10,SIGNAL(clicked(bool)),this,SLOT(add10()));

    connect(ui->btnsubtract1,SIGNAL(clicked(bool)),this,SLOT(subtract1()));
    connect(ui->btnsubtract2,SIGNAL(clicked(bool)),this,SLOT(subtract2()));
    connect(ui->btnsubtract3,SIGNAL(clicked(bool)),this,SLOT(subtract3()));
    connect(ui->btnsubtract4,SIGNAL(clicked(bool)),this,SLOT(subtract4()));
    connect(ui->btnsubtract5,SIGNAL(clicked(bool)),this,SLOT(subtract5()));
    connect(ui->btnsubtract6,SIGNAL(clicked(bool)),this,SLOT(subtract6()));
    connect(ui->btnsubtract7,SIGNAL(clicked(bool)),this,SLOT(subtract7()));
    connect(ui->btnsubtract8,SIGNAL(clicked(bool)),this,SLOT(subtract8()));
    connect(ui->btnsubtract9,SIGNAL(clicked(bool)),this,SLOT(subtract9()));
    connect(ui->btnsubtract10,SIGNAL(clicked(bool)),this,SLOT(subtract10()));

    connect(ui->actionPath,SIGNAL(triggered(bool)),this,SLOT(choosePath()));

    connect(ui->actionbida1,SIGNAL(triggered(bool)),this,SLOT(SBida1()));
    connect(ui->actionqd1,SIGNAL(triggered(bool)),this,SLOT(SQiangda1()));
    connect(ui->actionpk,SIGNAL(triggered(bool)),this,SLOT(SPK()));
    connect(ui->actionbida2,SIGNAL(triggered(bool)),this,SLOT(SBida2()));
    connect(ui->actionqiangda2,SIGNAL(triggered(bool)),this,SLOT(SQiangda2()));
    connect(ui->actionwheel,SIGNAL(triggered(bool)),this,SLOT(SWheel()));
    connect(ui->actionfinal,SIGNAL(triggered(bool)),this,SLOT(SFinal()));

    connect(ui->actionBida,SIGNAL(triggered(bool)),this,SLOT(TBida()));
    connect(ui->actionQD,SIGNAL(triggered(bool)),this,SLOT(TQiangda()));
    connect(ui->actionPK,SIGNAL(triggered(bool)),this,SLOT(TPK()));
    connect(ui->actionChoose,SIGNAL(triggered(bool)),this,SLOT(TChoose()));
    connect(ui->actiontime,SIGNAL(triggered(bool)),this,SLOT(TTime()));
    connect(ui->actionFinal,SIGNAL(triggered(bool)),this,SLOT(TFinal()));

    connect(ui->rabDifficult,SIGNAL(clicked(bool)),this,SLOT(chooseLevelD()));
    connect(ui->rabNormal,SIGNAL(clicked(bool)),this,SLOT(chooseLevelN()));
    connect(ui->rabEasy,SIGNAL(clicked(bool)),this,SLOT(chooseLevelE()));

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(chooseKind(int)));
}

