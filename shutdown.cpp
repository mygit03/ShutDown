#include "shutdown.h"
#include "ui_shutdown.h"

#include <QMessageBox>
#include <QDebug>

#include "mytrayicon.h"

ShutDown::ShutDown(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShutDown)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    QStringList strList;
    strList << "程序启动" << "托盘";
    MyTrayIcon *trayIcon = new MyTrayIcon(strList, this);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_timer()));

    time1 = QTime::currentTime();
    ui->timeEdit_time->setTime(time1);

    ui->btn_cancel->setEnabled(false);
}

ShutDown::~ShutDown()
{
    delete ui;
}

void ShutDown::closeEvent(QCloseEvent *e)
{
    int ret = QMessageBox::warning(this, tr("提示:"), tr("最小化还是退出?"),
                         tr("最小化"), tr("退出"), 0, 1);
    switch (ret) {
    case 0:
        qDebug() << "000";
        e->ignore();
        this->hide();
        break;
    case 1:
        qDebug() << "111";
        e->accept();
        this->close();
        break;
    default:
        break;
    }
}

void ShutDown::on_groupBox_clicked(bool checked)
{
    if(checked){
        ui->btn_showDown->setEnabled(false);
        ui->btn_reboot->setEnabled(false);
    }else{
        ui->btn_showDown->setEnabled(true);
        ui->btn_reboot->setEnabled(true);
    }
}

void ShutDown::on_btn_timer_clicked()
{
    qDebug() << "启动定时关机";
    time1 = ui->timeEdit_time->time();
    QTime time = QTime::currentTime();
    count = time.msecsTo(time1) / 1000;
    if(count <= 0){
        qDebug() << "sssss";
        QMessageBox::warning(this, tr("提示:"), tr("请重新设置关机时间！"));
    }else{
        QString command = "shutdown -s -t ";
        command.append(QString::number(count));
        QByteArray ba = command.toLocal8Bit();
        char *c_cmd = ba.data();
        system(c_cmd);
        qDebug() << "c_cmd:" << c_cmd;
        timer->start(1000);
        ui->btn_cancel->setEnabled(true);
    }
}

void ShutDown::on_btn_cancel_clicked()
{
    timer->stop();
    ui->lineEdit->setText("00:00:00");
    system("shutdown -a");
}

void ShutDown::on_btn_showDown_clicked()
{
    switch( QMessageBox::warning(this,tr("提示"),tr("是否立即关闭计算机?"),
                                 QMessageBox::Ok|QMessageBox::Cancel))
    {
    case QMessageBox::Ok:
        system("shutdown -p");
        break;
    case QMessageBox::Cancel:
        return;
        break;
     default:;
    }
}

void ShutDown::on_btn_reboot_clicked()
{
    switch( QMessageBox::warning(this,tr("提示"),tr("是否立即重启计算机?"),
                                 QMessageBox::Ok|QMessageBox::Cancel))
    {
    case QMessageBox::Ok:
        system("shutdown -r -t 0");
        break;
    case QMessageBox::Cancel:
        return;
        break;
     default:;
    }
}

void ShutDown::on_btn_exit_clicked()
{
    this->close();
}

void ShutDown::slot_timer()
{
    int hour = count / 3600;
    int min = count % 3600 / 60;
    int msc = count % 60;
    QString str;
    str.sprintf("%02d:%02d:%02d", hour, min, msc);
    ui->lineEdit->setText(str);
    qDebug() << "count:" << count;

    count--;
}
