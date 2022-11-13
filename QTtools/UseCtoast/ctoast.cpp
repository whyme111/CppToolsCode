#include "ctoast.h"
#include "ui_ctoast.h"
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include <QTimer>

int CToast::countnum=0;

CToast::CToast(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CToast)
{
    ui->setupUi(this);
    countnum++;
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);// 无边框 无任务栏
    setAttribute(Qt::WA_TranslucentBackground, true);   // 背景透明
}

CToast::~CToast()
{
    delete ui;
    countnum--;

}
void CToast::setText(const QString& text)
{
    ui->label->setText(text);
}

void CToast::setFont(const QFont &font)
{
    ui->label->setFont(font);
}

void CToast::showAnimation(int timeout)
{
    // 开始动画透明度变化。从0到1，300毫秒
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    show();

    QTimer::singleShot(timeout, [&]
    {
        // 结束动画
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(10);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        connect(animation, &QPropertyAnimation::finished, [&]
        {
            close();
            deleteLater();// 关闭后析构
        });
    });
}

void CToast::showTip(const QString& text, QWidget* parent /*= nullptr*/)
{
    CToast* toast = new CToast(parent);
    toast->setWindowFlags(toast->windowFlags() | Qt::WindowStaysOnTopHint); // 置顶
    toast->setText(text);
    toast->adjustSize();    //设置完文本后调整下大小
    QFont temp("黑体",25);
    toast->setFont(temp);

    // 随着数量增多，一直往下移
    QScreen* pScreen = QGuiApplication::primaryScreen();
    if(countnum<5)
    {
        toast->move((pScreen->size().width() - toast->width()) / 2, pScreen->size().height() * countnum / 20);
    }
    else
    {
        toast->move((pScreen->size().width() - toast->width()) / 2, pScreen->size().height() * 4 / 20);
    }

    toast->showAnimation();
}

void CToast::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    //paint.begin(this);
    auto kBackgroundColor = QColor(255, 255, 255);
    kBackgroundColor.setAlpha(0.0 * 255);// 透明度为0
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(Qt::NoPen);
    paint.setBrush(QBrush(kBackgroundColor, Qt::SolidPattern));//设置画刷形式
    paint.drawRect(0, 0, width(), height());
    paint.end();
}

