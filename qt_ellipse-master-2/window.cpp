#include "window.h"

#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QPoint>
#include <cmath>
#include <iostream>
#include <QTransform>
#include <QGraphicsItem>
#include <QtMath>
const int WINDOW_HEIGHT = 500;
const qreal PRECISION = 0.0005;
const qreal A = 200;
const qreal B = 100;

Window::Window(QWidget *parent) :
    QWidget(parent)
    , p1(0,0)
    , p2(0,0)
{
    setStyleSheet("background-color:white;");
    p2.setX(p1.rx() + 1);
    p2.setY(1);
    p2.setY(9 * p2.rx() + 0.5);
   // i=0;
    side = getDirection(p1,p2);
    setFixedSize(WINDOW_HEIGHT, WINDOW_HEIGHT);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void Window::paintEvent(QPaintEvent*)
{

    QPen pen;
    pen.setWidth(3);
    QPainter painter(this);
    painter.setPen(pen);
    QPointF point(0, 0);
    painter.translate(WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
//    painter.rotate(180);
    painter.drawEllipse(point, A, B);

    painter.drawPoint(p2);
    if(ellipseFormula(p2) > 1) {
        drawTangentLine = true;
        tangentPoint1 = getTangentPoint(p1,p2);
        QPointF tangentPoint2 = computeTangentPoint2(tangentPoint1);

        tangentLine = QLineF(tangentPoint2,computeTangentPoint3(tangentPoint1));

        rayLine = QLineF(point, tangentPoint1);
        qreal angle = computeAngleToRotate(tangentLine,rayLine);
        p2 = rotatePoint(p1,tangentPoint1, angle);
        if (ellipseFormula(p2) > 1 + PRECISION) {
            p2 = rotatePoint(p2, tangentPoint1, 180);
        }
        p1 = tangentPoint1;
        side = getDirection(p1,p2);
    }
    else {
        QPointF p3 = getNewPoint(p1, p2, side);
        p1 = p2;
        p2 = p3;
    }
    //painter.drawLine(QLineF(tangentPoint1, p2));
    if (drawTangentLine) {
        painter.drawLine(QLineF(computeTangentPoint2(tangentPoint1), computeTangentPoint3(tangentPoint1)));
    }
}

QPointF Window::getTangentPoint(QPointF p1, QPointF p2) {
    QPointF p = p2;
    while (!(ellipseFormula(p) <= (1.0 + PRECISION) && ellipseFormula(p) >= (1.0 - PRECISION))) {
        qreal distance1 = qAbs(1 - ellipseFormula(p1));
        qreal distance2 = qAbs(1 - ellipseFormula(p2));
        if (distance1 > distance2) {
            p1 = QPointF((p1.rx() + p2.rx()) / 2, (p1.ry() + p2.ry()) / 2);
            p = p1;
        } else {
            p2 = QPointF((p1.rx() + p2.rx()) / 2, (p1.ry() + p2.ry()) / 2);
            p = p2;
        }
    }
    return p;
}

QPointF Window::rotatePoint(QPointF p, QPointF p0, qreal angle) {
    qreal radi = qDegreesToRadians(angle);
    qreal x = p0.rx() + (p.rx() - p0.rx()) * qCos(radi) - (p.ry() - p0.ry()) * qSin(radi);
    qreal y = p0.ry() + (p.ry() - p0.ry()) * qCos(radi) + (p.rx() - p0.rx()) * qSin(radi);
    return QPointF(x,y);
}

qreal Window::computeAngleToRotate(QLineF tangentLine, QLineF line) {
    qreal angle = tangentLine.angleTo(line);
    return 360 - 2 * (360 - angle);
}

qreal Window::ellipseFormula(QPointF p) {
    return pow(p.rx() / A, 2) + pow(p.ry() / B, 2);
}

QPointF Window::computeTangentPoint3(QPointF tangentPoint) {
    qreal y = tangentPoint.ry() - 30;
    qreal aPow = qPow(A,2);
    qreal bPow = qPow(B,2);
    qreal x = 0;
//    qreal x = (aPow * (bPow - y * tangentPoint.ry())) / (bPow * tangentPoint.rx());
    x = (aPow - (aPow * y * tangentPoint.ry())/bPow) / tangentPoint.rx();
    return QPointF(x, y);
}

QPointF Window::computeTangentPoint2(QPointF tangentPoint) {
    qreal y = tangentPoint.ry() + 30;
    qreal aPow = qPow(A,2);
    qreal bPow = qPow(B,2);

    qreal x = 0;
    //x = (aPow * (bPow- y * tangentPoint.ry())) / (bPow * tangentPoint.rx());
    x = (aPow - (aPow * y * tangentPoint.ry())/bPow) / tangentPoint.rx();
    return QPointF(x, y);
}



Window::Side Window::getDirection(QPointF p1, QPointF p2)
{
    bool checkX = (p2.rx()-p1.rx())>0;
    bool checkY = (p2.ry()-p1.ry())>0;

    if (checkX && checkY)
        return xPlusYplus;
    else if(!checkX && checkY)
        return xMinusYplus;
    else if(checkX && !checkY)
        return xPlusYminus;
    else
        return xMinusYminus;

}
QPointF Window::getNewPoint(QPointF p1, QPointF p2, Side side)
{
    qreal x3;
    if(side == xPlusYminus || side == xPlusYplus) {
        x3 = p2.rx() + 1;
    } else {
        x3 = p2.rx() - 1;
    }
    qreal y = (((x3 - p1.rx()) * (p1.ry() - p2.ry())) / (p1.rx() - p2.rx())) + p1.ry();
    return QPointF(x3,y);
}
