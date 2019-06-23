#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QColor>
#include <QPen>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QProcess>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void check(int row, int col);
    void mousePressEvent(QMouseEvent *event);
    void setboard();//set original color on board

  public slots:
    void start();
    void set();
    void quit();

  private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *box[8][8];
    QGraphicsRectItem *cover;
    QGraphicsRectItem *Turn;
    QGraphicsPixmapItem *chess[8][8];
    QString record[8][8];
    QGraphicsPixmapItem *setChess[2][6];
    QString recordSet[2][6];
    QGraphicsPixmapItem *promotion[2][4];
    QString recordPromotion[2][4];
    QString turn;
    QPushButton *Start, *Set, *Quit;
    QGraphicsTextItem *title, *result_black, *result_white;
    bool br1 = true, br2 = true, bk = true;
    bool wr1 = true, wr2 = true, wk = true;
    int row, col;
    int movable = -1;//cannot do anything
    int num[2][6] = {{1,1,2,2,2,8}, {1,1,2,2,2,8}};
    int x = -1, y = -1;// record for promotion
};

#endif // MAINWINDOW_H
