#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QFile>

namespace Ui {
class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = 0);
    ~myWidget();

private slots:
    void on_btnSelectFile_clicked();

    void on_btnFix_clicked();

    void on_btnDeal_clicked();

    void on_btnSave_clicked();

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(const QString &arg1);

private:
    Ui::myWidget *ui;
    QString path;
    QString newP;
    QStringList list;
    QString fileName;
    QString qq2;
    QString newPath;
    QString pathImg;
    QString imgName;
    QFile of;
    QString TotalPath;

};

#endif // MYWIDGET_H
