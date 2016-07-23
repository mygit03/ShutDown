#include "mytrayicon.h"

#include <QApplication>
#include <QDebug>

MyTrayIcon::MyTrayIcon(QStringList &strList, QWidget *parent) : QWidget(parent)
{
    QIcon icon = QIcon(":/images/shutdown.png");
    trayIcon = new QSystemTrayIcon(parent);
    trayIcon->setIcon(icon);
    QString title = strList.at(0);
    QString msg = strList.at(1);
    trayIcon->show();
    qDebug() << "msg:" << msg;
    trayIcon->setToolTip(msg);
    trayIcon->showMessage(title, msg, QSystemTrayIcon::Information, 1000);

    doubleClickWidget = parent;

    createAct(parent);
    createMenu();
}

MyTrayIcon::~MyTrayIcon()
{

}

void MyTrayIcon::createAct(QWidget *parent)
{
    minAct = new QAction(QString("最小化"), this);
    connect(minAct, SIGNAL(triggered()), parent, SLOT(hide()));
    maxAct = new QAction(QString("最大化"), this);
    connect(maxAct, SIGNAL(triggered()), parent, SLOT(show()));
    quitAct = new QAction(QString("退出"), this);
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MyTrayIcon::createMenu()
{
    trayMenu = new QMenu(this);
    trayMenu->addAction(minAct);
    trayMenu->addAction(maxAct);
    trayMenu->addAction(quitAct);
    trayIcon->setContextMenu(trayMenu);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
}

void MyTrayIcon::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Unknown:
        break;
    case QSystemTrayIcon::Context:
        break;
    case QSystemTrayIcon::DoubleClick:
        doubleClickWidget->setWindowState(Qt::WindowActive);
        doubleClickWidget->showNormal();
        break;
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        break;
    }
}

