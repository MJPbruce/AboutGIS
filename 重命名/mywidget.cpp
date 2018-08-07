#include "mywidget.h"
#include "ui_mywidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>

#include <QTextStream>
#include <sstream>
#include <string>

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    ui->btnFix->setEnabled(false);
    ui->btnDeal->setEnabled(false);
    ui->btnSave->setEnabled(false);
}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::on_btnSelectFile_clicked()
{
    path = QFileDialog::getOpenFileName(this, tr("Open html"), ".", tr("html Files(*.html)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else
    {
        //QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
        ui->lineEditDir->setText(path);
        list = path.split("/");
        fileName = list[list.length()-1];
        QString old = fileName.section(".",1,fileName.length());
        ui->lineEditOld->setText(old);
        TotalPath = ui->lineEditDir->text();
        QString newN = ui->lineEditNew->text();
        QStringList listNew = fileName.split(".");
        QString newName = listNew[0];
        newName = newName.append(".");
        QString nNew = newName + newN;                             //文件名+newN
        qq2 = path.remove(list[list.length()-1]);            //上级目录
        newPath = qq2 + nNew;                               //完整目录
        newP= qq2 + "output.txt";
    }
    QFile file(newPath);
    if(file.exists(newPath)==false)
    {
        ui->btnFix->setEnabled(true);
    }
    QFile of(newP);
    if(of.exists(newP)==false)
    {
        ui->btnDeal->setEnabled(true);
    }

}

void myWidget::on_btnFix_clicked()
{


    //qDebug()<<newPath;
    QFile file(TotalPath);                                      //打开文件
    //qDebug()<<file.fileName();
    bool exist = QFile::exists("TotalPath");
    if(exist = true)
    {
        file.copy(TotalPath,newPath);
        QMessageBox::information(NULL, tr("TotalPath"), tr("File copy successed."));
        //qDebug()<<TotalPath<<newPath;
    }
    else
    {
        QMessageBox::information(NULL, tr("TotalPath"), tr("File has existed."));
    }
    ui->btnFix->setEnabled(false);

}

void myWidget::on_btnDeal_clicked()
{

    QFile f(newPath);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug() << "Open failed." << endl;
    }

    QFile of(newP);
    if(of.exists(newP)==true)
    {
        ui->btnDeal->setEnabled(false);
        QMessageBox::information(NULL, tr("Result"), tr("file has existed"));
    }
    else
    {
        if(!of.open(QIODevice::WriteOnly | QIODevice::Text) )//QIODevice::Text该标志指示在读写过程中要对end-of-line进行转换
        {
            //qDebug() << "Save failed." << endl;
        }
        QTextStream txtInput(&f);  //文本最好用textstream操作
        QTextStream txtOutput(&of);

        QString a=txtInput.readAll();
        //qDebug()<<a;
        QStringList OldTextList = a.split("<tr><td>");
        for(int m = 0; m<OldTextList.length();m++)
        {
            //qDebug() << OldTextList[m] << endl;
            QString b = OldTextList[m];
            QStringList bList = b.split("</td><td>");
            QStringList cList = bList[bList.length()-1].split("</td></tr>");
            //qDebug() << cList[0] << endl;
            QString c = cList[0];
            float numText = c.toFloat();
            //qDebug() << numText << endl;
            if(numText != 0  )
            {
                if(numText < ui->spinBox->text().toFloat() )
                {
                    //qDebug() << bList[1] << endl;
                    txtOutput<<bList[1]<<endl;//输出符合条件的相片名称
                    txtOutput.flush();
                }

            }

        }
        QMessageBox::information(NULL, tr("Result"), tr("SUCCESSED!"));
        ui->btnDeal->setEnabled(false);
    }
    f.close();



}
void myWidget::on_pushButton_clicked()
{
    pathImg = QFileDialog::getExistingDirectory(this);
    QFile of(newP);
    if(of.exists(newP)==false)
    {
        ui->btnSave->setEnabled(true);
    }
}

void myWidget::on_btnSave_clicked()
{
    QFile savef(newP);
    if(!savef.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
    }

    QTextStream txtImg(&savef);
    QString pathDir = QFileDialog::getExistingDirectory(this);
    //新文件
    QFile sf(pathDir);
    QString img = txtImg.readAll();
    QStringList imgList = img.split("\n");
    int p = 0;
    for(p=0;p<imgList.length()-1;p++)
    {
        imgName=imgList[p]+=".jpg";
        //qDebug()<<imgName;
        QString allImgName = pathImg+"/"+imgName;
        QString newImgName = pathDir+"/"+imgName;
        sf.copy(allImgName,newImgName);

    }
    savef.close();
    QMessageBox::information(NULL, tr("Result"), tr("Copy Done!"));
}

void myWidget::on_spinBox_valueChanged(const QString &arg1)
{
    ui->btnDeal->setEnabled(true);
    if(of.exists(newP)==true)
    {
        ui->btnDeal->setEnabled(false);
        QMessageBox::information(NULL, tr("Result"), tr("file has existed"));
    }
}
