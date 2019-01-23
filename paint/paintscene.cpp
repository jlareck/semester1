#include "paintscene.h"
#include "paint.h"
#include <iostream>
paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    addEllipse(event->scenePos().x(),
               event->scenePos().y(),
               3,
               3,
               QPen(Qt::red),
               QBrush(Qt::NoBrush));
   // std::cout << event->scenePos().x()<<std::endl;;
    qv.append(event->scenePos());
}
int  paintScene::orientation(QPointF p, QPointF q, QPointF r)
{
    int val = (q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}
QVector<QPointF> paintScene::convexHull(QVector<QPointF> points, int n)
{
    QVector<QPointF> hull;
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x() < points[l].x())
            l = i;
    int p = l, q;
    do
    {
        hull.append(points[p]);
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {

           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
        p = q;

    } while (p != l);
  return hull;
}

