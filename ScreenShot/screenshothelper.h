#ifndef SCREENSHOTHELPER_H
#define SCREENSHOTHELPER_H

#include <QPixmap>

class ScreenShotHelper
{
public:

    //忽略扩展，只用到FreeShot
    enum ShotType {
        ScreenShot, ActiveWindowShot, CursorShot, FreeShot, FreeHandShot, ShotByPoint, LongShot, Count
    };

    ScreenShotHelper();

    static QString lastProcessName;
    static unsigned long lastPId;

    static QPixmap grabWindow(int snapMethod, HWND hwnd, int type, bool includeCursor = false, int x = 0, int y = 0, int w = -1, int h = -1);

    static QPixmap grabCursor();

    static QPixmap screenshot(ShotType shotType, bool isHotKey);

    static bool savePicture(QWidget *msgBoxParent, QString filePath, QPixmap pixmap);

    static QPixmap getWindowPixmap(HWND winId, ShotType shotType, bool includeCursor = false, int x = 0, int y = 0, int w = -1, int h = -1);

    static QString getPictureName(ShotType shotType);

    static QString getSnapTypeName(ShotType shotType);

    static QPixmap getFullScreen();


    ///原先的数据放在publicdata
private :
    static Qt::WindowState mdiWindowInitState;
    static bool clickCloseToTray;
    static bool ignoreClickCloseToTray;
    static bool hotKeyNoWait;
    static bool includeCursor;
    static bool noBorder;
    static bool copyToClipBoardAfterSnap;

    //Utils方法
    static QString transformTemplateStr(QString templateStr, QHash<QString, QString> kv);

};

struct ShotTypeItem {
    ScreenShotHelper::ShotType shotType;
    int waitTime;
    QString hotKey;
    bool isAutoSave;
    bool isManualSave;
    QString autoSavePath;
    QString autoSaveExtName;
};

#endif // SCREENSHOTHELPER_H
