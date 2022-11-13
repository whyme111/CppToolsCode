#ifndef CTOAST_H
#define CTOAST_H

#include <QWidget>

namespace Ui {
class CToast;
}

class CToast : public QWidget
{
    Q_OBJECT

public:
    explicit CToast(QWidget *parent = nullptr);
    ~CToast();
    void setText(const QString& text);
    void setFont(const QFont& font);

    void showAnimation(int timeout = 2000);// 动画方式show出，默认2秒后消失

public:
    // 静态调用
    static void showTip(const QString& text, QWidget* parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);
    static int countnum;
private:
    Ui::CToast *ui;
};

#endif // CTOAST_H
