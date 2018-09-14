#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <QCheckBox>
#include <QLabel>
#include <QtGlobal>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ReminderRand=0;
    reminderERROR=false;
    AdviceButton=new QPushButton(this);
    AdviceButton->setText("Advice");
    WeatherButton=new QPushButton(this);
    WeatherButton->setText("Weather");
    ReminderButton=new QPushButton(this);
    ReminderButton->setText("Reminder");
    QuitButton=new QPushButton(this);
    QuitButton->setText("Quit");
    te=new QTextEdit(this);

    layout = new QVBoxLayout(this);
    layout->addWidget(te);
    layout->addWidget(AdviceButton);
    layout->addWidget(WeatherButton);
    layout->addWidget(ReminderButton);
    layout->addWidget(QuitButton);

    connect(QuitButton,SIGNAL(clicked()),this,SLOT(showquit()));
    connect(ReminderButton,SIGNAL(clicked()),this,SLOT(showreminder()));
    connect(AdviceButton,SIGNAL(clicked()),this,SLOT(showadvice()));
     connect(WeatherButton,SIGNAL(clicked()),this,SLOT(showweather()));
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::advicelist()
{
    QStringList ReadAdvice;
    int RandNO;
    QString AdviceOut;
    QFile file("advice.dat");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream infile(&file);
        while(!infile.atEnd())
        {
            ReadAdvice.append(infile.readLine());
        }
    }

    RandNO=RandNoG(ReadAdvice.length()-1);
    AdviceOut="Advice: ";
    AdviceOut+=ReadAdvice.at(RandNO);
    while(AdviceOut.endsWith("\\")){
            RandNO++;
            if(RandNO<ReadAdvice.length())
            AdviceOut+=ReadAdvice.at(RandNO);
            else
                AdviceOut="Advice: Input Error. Backslash exists in the last line";
    }
    AdviceOut.replace("\\"," ");
    return AdviceOut;
}

void Widget::showadvice()
{
    te->append(advicelist());
}

QString Widget::weatherlist()
{
    QStringList ReadWeather;
    int RandNO;
    QString WeatherOut;
    QFile file("weather.dat");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream infile(&file);
        while(!infile.atEnd())
        {
            ReadWeather.append(infile.readLine());
        }
    }
    RandNO=RandNoG(ReadWeather.length()-1);
    WeatherOut="Weather: ";
    WeatherOut+=ReadWeather.at(RandNO);
    while(WeatherOut.endsWith("\\")){
            RandNO++;
            if(RandNO<ReadWeather.length())
                WeatherOut+=ReadWeather.at(RandNO);
            else
                WeatherOut="Weather: Input Error. Backslash exists in the last line";
    }
    WeatherOut.replace("\\"," ");
    return WeatherOut;
}

void Widget::showweather()
{

    te->append(weatherlist());
}

QString Widget::reminderlist()
{
    QStringList ReadReminder;
    QString ReminderOut;
    QFile file("reminder.dat");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream infile(&file);
        while(!infile.atEnd())
        {
            ReadReminder.append(infile.readLine());
        }
    }
    if(ReminderRand<ReadReminder.length()){
        ReminderOut=ReadReminder.at(ReminderRand);
    }
    while(ReminderOut.endsWith("\\")){
            ReminderRand++;
            if(ReminderRand<ReadReminder.length())
                ReminderOut+=ReadReminder.at(ReminderRand);
            else{
                reminderERROR=true;
                ReminderOut="Reminder: Input Error. Backslash exists in the last line";
            }
    }
    if(ReminderRand<ReadReminder.length())
    {
       ReminderOut.replace("\\"," ");
        return ReminderOut;
    }
    else if((ReminderOut=="Reminder: Input Error. Backslash exists in the last line")||reminderERROR==true)
    {
        return("Reminder: Input Error. Backslash exists in the last line");
    }
    else
        return "There are no more reminders";

}

void Widget::showreminder()
{

    QMessageBox *Message=new QMessageBox;
    QString reminderls=reminderlist();
    Message->setText(reminderls);
    Message->setIcon(QMessageBox::Information);
    Message->setWindowTitle("Advice");

    QCheckBox *checkbox= new QCheckBox("show this message again");
    checkbox->setChecked(true);
    Message->setCheckBox(checkbox);
    Message->checkBox();



    if(reminderls=="There are no more reminders")
        te->append(reminderls);
    else
        Message->exec();

    if(checkbox->isChecked()==true)
    {}
    else{
        ReminderRand++;
    }

}

int Widget::RandNoG(int length)
{
    int RandNo=0;
    qsrand(time(NULL));
    RandNo=qrand()%length;
    return RandNo;
}

void Widget::showquit()
{
    QMessageBox *box=new QMessageBox;

    QMessageBox::StandardButton reply=box->question(box,"Advisor","Are you sure you want to quit?",QMessageBox::No|QMessageBox::Yes);
    if(reply ==QMessageBox::Yes)
        QApplication::quit();
    //box->exec();
}
