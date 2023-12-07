#ifndef MAGNIFYGLASS_H
#define MAGNIFYGLASS_H

#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QScreen>
QT_BEGIN_NAMESPACE
namespace Ui { class magnifyGlass; }
QT_END_NAMESPACE

class magnifyGlass : public QWidget
{
    Q_OBJECT

public:
    magnifyGlass(QWidget *parent = nullptr);
    ~magnifyGlass();

private:
    Ui::magnifyGlass *ui;

public:
    void initWindow();

private slots:
    void TimerSlot();


protected:
    void paintEvent(QPaintEvent* pEvent);

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::RightButton)
        {
            close();//重写mousePressEvent函数来实现鼠标右键点击退出当前函数
        }
        else
        {
            QWidget::mousePressEvent(event);
        }
    }
private:
    QPixmap m_pixMap;

};
#endif // MAGNIFYGLASS_H
