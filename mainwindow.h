#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QString>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
//    int  onInLineEditPress();
    int  onOutLineEditPress();
//    void onInFnameComfirmed();
    void onOutFnameComfirmed();

signals:
//    void inFnameComfirmed();
    void outFnameComfirmed();
private:
    Ui::MainWindow *ui;
    QLineEdit* lineEdit;
    char* inFname;
    char* outFname;
    char* deFname;
    int  flag;
    QString path;
    QByteArray tmp;
};

#endif // MAINWINDOW_H
