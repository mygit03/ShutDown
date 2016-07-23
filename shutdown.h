#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTimer>
#include <QTime>

namespace Ui {
class ShutDown;
}

class ShutDown : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShutDown(QWidget *parent = 0);
    ~ShutDown();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_groupBox_clicked(bool checked);

    void on_btn_timer_clicked();

    void on_btn_cancel_clicked();

    void on_btn_showDown_clicked();

    void on_btn_reboot_clicked();

    void on_btn_exit_clicked();

    void slot_timer();

private:
    Ui::ShutDown *ui;

    QTimer *timer;
    QTime time1;
    int count;              //剩余秒数
};

#endif // SHUTDOWN_H
