#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QStringList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString reminderlist();
    QString advicelist();
    QString weatherlist();
    int RandNoG(int length);


private slots:
    void showreminder();
    void showadvice();
    void showweather();
    void showquit();


private:
    Ui::Widget *ui;
    QPushButton *AdviceButton;
    QPushButton *WeatherButton;
    QPushButton *ReminderButton;
    QPushButton *QuitButton;
    QTextEdit *te;
    QVBoxLayout *layout;
    int ReminderRand;
    bool reminderERROR;


};

#endif // WIDGET_H
