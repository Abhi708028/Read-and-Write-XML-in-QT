#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QtXml/QDomDocument>
#include <QDebug>
#include<QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class savedata{
public:
    savedata(){
        Name="";
        Class="";
        DOB="";
        color="";
        isMale="";
    }
    QString Name;
    QString Class;
    QString DOB;
    QString color;
    QString isMale;
    QVector<QString>vec;
    void setName(const QString s1);
    void setClass(const QString s1);
    void setDOB(const QString s1);
    void setcolor(const QString s1);
    void setMale_Female(const QString s1);
    void setAge(const QString s1,const QString s2);
    QString showName();
    QString showClass();
    QString showDOB();
    QString showcolor();
    QString showisMale();
    QVector<QString> showAge();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     Ui::MainWindow *ui;
     void writefile(savedata d1);
     void readfile();

private slots:

     void on_Savebutton_clicked();

     void on_CancelButton_clicked();


     void on_StartButton_clicked();

private:
    Ui::MainWindow *ui1;
};
#endif // MAINWINDOW_H
