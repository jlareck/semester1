#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>

#include <paintscene.h>

namespace Ui {
class Paint;
}

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();

private:
    Ui::Paint *ui;
    QTimer *timer;
    paintScene *scene;

private:
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // PAINT_H
