#include "mainwindow.h"
#include "qapplication.h"
#include <QDebug>

#include "Snapper/freesnapdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    isShotting=false;
    registerGlobalKey();
    initTray();

    connect(this,SIGNAL(hotkeyShotBgPressed()),SLOT(hotkeyShotBgReceived()));
    trayIcon->showMessage(tr("截图程序"),"程序已启动,按\"SHIFT+ALT+P\"后拖动鼠标！");
    trayIcon->setToolTip(tr("按\"SHIFT+ALT+P\"后拖动鼠标"));
    qApp->beep();

}

MainWindow::~MainWindow()
{

    if(UnregisterHotKey(HWND(this->winId()), hotkeyShotBgId))
    {
        qDebug("SHIFT+ALT+P IS UNREGISTED");
    }
}


void MainWindow::registerGlobalKey()
{
    //没有做重复判断?
    hotkeyShotBgId = GlobalAddAtom(L"SsotGlobalHotKey") - 0xC000;

    if(RegisterHotKey((HWND(this->winId())), hotkeyShotBgId,MOD_SHIFT|MOD_ALT,Qt::Key_P))
    {
        qDebug("SHIFT+ALT+P");
    }
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(eventType=="windows_generic_MSG")
    {
        //qDebug("This is windows MSG");
        MSG* msg=static_cast<MSG*>(message);
        if(msg->message==WM_HOTKEY)
        {
            UINT fuModifiers = (UINT) LOWORD(msg->lParam);  // key-modifier flags
            UINT uVirtKey = (UINT) HIWORD(msg->lParam);     // virtual-key code

            // qDebug("This is HotKey!");
            if(fuModifiers==(MOD_SHIFT|MOD_ALT) && uVirtKey== Qt::Key_P)
            {
                emit hotkeyShotBgPressed();
                qDebug("SHIFT+ALT+P is Pressed");

            }
            return true;

        }
    }
    //return  MainWindow::nativeEvent(eventType,message,result);
    return false;
}

void MainWindow::snapSuccessCallback(ScreenShotHelper::ShotType shotType, QPixmap pixmap)
{
    QApplication::clipboard()->setPixmap(pixmap);
}

void MainWindow::hotkeyShotBgReceived()
{
    if(!isShotting)
    {
        //如果正在截图，则不处理，否则进入截图状态，将list位置传给CTopLabel
        QPixmap pixmap;
        bool captured = true;
        FreeSnapDialog freeSnapDialog(&pixmap, captured, this);
        freeSnapDialog.exec();
        if (!captured) return;
        snapSuccessCallback(ScreenShotHelper::FreeShot, pixmap);
    }

    isShotting = true;
}

void MainWindow::initTray()
{
    trayIcon=new QSystemTrayIcon(this);

    trayIcon->setIcon(QIcon(":/image/icon.png"));

    QMenu* trayMenu=new QMenu;

    QAction* exitAction=new QAction(tr("退出 (&X)"),trayMenu);

    trayMenu->addSeparator();

    trayMenu->addAction(exitAction);

    connect(exitAction,SIGNAL(triggered()),this,SLOT(quitApp()));

    trayIcon->setContextMenu(trayMenu);

    trayIcon->show();
}

void MainWindow::quitApp(){
    trayIcon->hide();
    QApplication::quit();
}



void MainWindow::allowShot()
{
    isShotting=false;
}

