#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QPoint>

class paintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintScene(QObject *parent = nullptr);
    ~paintScene();
    QVector<QPointF> qv;
    int orientation(QPointF p, QPointF q, QPointF r);
    QVector<QPointF> convexHull(QVector<QPointF> points, int n);
    QPolygonF polygon;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

};

#endif // PAINTSCENE_H
