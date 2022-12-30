#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "screenshothelper.h"
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //托盘图标
    //注册热键
    void registerGlobalKey();

    //开始截图热键ID
    int hotkeyShotBgId;

    //初始化托盘;
    void initTray();

    //是否正在截图
    bool isShotting;

    //本地事件
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    //系统弹窗
    QSystemTrayIcon* trayIcon;

    // 获取到截图后回调函数，用来更新mdiwindow
    void snapSuccessCallback(ScreenShotHelper::ShotType shotType, QPixmap pixmap);


private slots:

    //开始截图
    void hotkeyShotBgReceived();
public slots:

    //设置isShotting为false，允许再次截屏
    void allowShot();

    void quitApp();

signals:
    //开始截屏热键按下
    void hotkeyShotBgPressed();

};
#endif // MAINWINDOW_H
