#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QtXml/QDomDocument>
#include <QDebug>
#include<QFile>
#include<QColorDialog>
#include<QColor>
#include<QMessageBox>
#include<QVector>
#include<QPair>
#include <QtXml>

    void savedata:: setName(const QString str){
        this->Name=str;
    }
    void savedata:: setClass(const QString str){
        this->Class=str;
    }
    void savedata:: setDOB(const QString str){
        this->DOB=str;
    }
    void savedata:: setcolor(const QString str){
        this->color=str;
    }
    void savedata:: setMale_Female(const QString str){
        this->isMale=str;
    }
    void savedata :: setAge(const QString str1,const QString str2){
        if(str1!=""){
            vec.push_back(str1);
        }
        if(str2!=""){
            vec.push_back(str2);
        }
    }
    QString savedata:: showName(){
        return Name;
    }
    QString savedata:: showClass(){
        return Class;
    }
    QString savedata:: showDOB(){
        return DOB;
    }
    QString savedata :: showcolor(){
        return color;
    }
    QString savedata::  showisMale(){
        return isMale;
    }
    QVector<QString> savedata:: showAge(){
        return vec;
     }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ColorEdit->addItem("Red");
    ui->ColorEdit->addItem("Blue");
    ui->ColorEdit->addItem("Black");
    ui->ColorEdit->addItem("Orange");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void retrievElements(QDomElement root, QString tag, QString att)
{
    QDomNodeList nodes = root.elementsByTagName(tag);

    qDebug() << "# nodes = " << nodes.count();
    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.attribute(att);
        }
    }
}
void MainWindow :: readfile(){
    // Create a document to write XML
        QDomDocument document;

        // Open a file for reading
        QFile file("LayerSession.xml");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open the file for reading.";
        }
        else
        {
            // loading
            if(!document.setContent(&file))
            {
                qDebug() << "Failed to load the file for reading.";
                //return -1;
            }
            file.close();
        }

        // Getting root element
        QDomElement root = document.firstChildElement();

        // retrievelements(QDomElement root, QString tag, QString att)
        retrievElements(root, "GISxml", "Path");

        //qDebug() << "\nGoing deeper level - getting the 'Room'";
        QDomNodeList dorms = root.elementsByTagName("GISxml");
        // Looping through each dorm
        for(int i = 0; i < dorms.count(); i++)
        {
            QDomNode dormnode = dorms.at(i);
            if(dormnode.isElement())
            {
                QDomElement dorm = dormnode.toElement();
                qDebug() << "Path at " << dorm.attribute("Path");
                /*
                 *-<Dorm Name="Dorm Building 0" ID="0">
                 *   <Room Name="Room 0" ID="0"/>
                 *   <Room Name="Room 1" ID="1"/>
                 *   <Room Name="Room 2" ID="2"/>
                 */
                retrievElements(dorm, "VectorLayer", "enable");
            }
        }

        qDebug() << "Reading finished";
}
void MainWindow:: writefile(class savedata d1){

    QFile file("data.xml");
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Write File not opened";
            return ;
        }

        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Users");


        xmlWriter.writeStartElement("Name" , d1.showName());
        xmlWriter.writeTextElement("Class", d1.showClass());
        xmlWriter.writeTextElement("DOB",d1.showDOB());
        xmlWriter.writeTextElement("color", d1.showcolor());
        int n=d1.showAge().size();
        int i=0;
        while(n--){
            xmlWriter.writeTextElement("Age",d1.showAge()[i]);
            i++;
        }
        xmlWriter.writeTextElement("isMale",d1.showisMale());
        xmlWriter.writeEndElement();

        //xmlWriter.writeEndDocument();
        qDebug()<<"writing is done";
        file.close();

}

void MainWindow::on_Savebutton_clicked()
{
    QString name = ui->NameEdit->text();
    QString class1 = ui->ClassEdit->text();
    QString dob =ui->DOBEdit->text();
    QString color =ui->ColorEdit->currentText();
    QString radio;
    if(ui->MaleRadio->isChecked()){

        radio="Male";
    }
    else{
        radio="Female";
    }
    QString str1="";
    QString str2="";
    if(ui->ageBox->isChecked()){
        str1+="11-22";
    }
    if(ui->agerange2->isChecked()){
        str2+="23 and above";
    }

    savedata d1;
    d1.setName(name);
    d1.setClass(class1);
    d1.setDOB(dob);
    d1.setcolor(color);
    d1.setAge(str1,str2);
    d1.setMale_Female(radio);
    writefile(d1);

}


void MainWindow::on_CancelButton_clicked()
{
    MainWindow::close();
}


void MainWindow::on_StartButton_clicked()
{
    readfile();
}

