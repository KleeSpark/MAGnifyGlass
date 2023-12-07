#include "magnifyglass.h"
#include "./ui_magnifyglass.h"

#include <QGuiApplication>

#include <QTimer>

#include <QPushButton>
magnifyGlass::magnifyGlass(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::magnifyGlass)
{

    this->initWindow();
}

magnifyGlass::~magnifyGlass()
{
    delete ui;
}

void magnifyGlass::initWindow()
{
    // 无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    // 监听鼠标移动
    this->setMouseTracking(true);
    // Qt5中截取全屏的代码
    QScreen* pScreen = QGuiApplication::primaryScreen();
    m_pixMap = pScreen->grabWindow(0);
    this->resize(pScreen->size());
    // 设置鼠标的形状
    this->setCursor(Qt::CrossCursor);
    // 定时器
    QTimer* pTimer = new QTimer(this);
    pTimer->start(100);
    connect(pTimer, &QTimer::timeout, this, &magnifyGlass::TimerSlot);
}

void magnifyGlass::TimerSlot()
{
    this->update();
}

void magnifyGlass::paintEvent(QPaintEvent* pEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int x = QCursor::pos().x();//获得鼠标位置x
    int y = QCursor::pos().y();//获得鼠标位置Y

    QPen pen(Qt::black, 2);//设置画笔
    painter.setPen(pen);

    painter.save();//先画放大镜的那个把儿
    painter.setBrush(QBrush(QColor(0, 0, 0)));
    painter.translate(x, y);
    painter.rotate(45);
    painter.drawRect(60, -8, 80, 16);
    painter.restore();


    QTransform transform;
    transform.translate(x-60, y-60);
    transform.scale(3.0, 3.0);

    QPixmap map = m_pixMap.copy(x - 20, y - 20, 40, 40);//截取以鼠标位置为中心的40x40的矩形
    QBrush brush(map);//设置画刷
    brush.setTransform(transform);//画刷的矩阵转化会和painter叠加混合在一起
    painter.setBrush(brush);
    painter.save();
    pen.setColor(Qt::black);//放大镜的圆框颜色
    painter.setPen(pen);

    painter.drawEllipse(x - 60, y -60, 120, 120);//画出我们想要的放大部分
    painter.restore();
    QWidget::paintEvent(pEvent);
}

