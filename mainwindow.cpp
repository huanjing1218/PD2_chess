#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->scene = new QGraphicsScene(0,0,ui->graphicsView->width()-2,ui->graphicsView->height()-2);
    ui->graphicsView->setScene(scene);
    for(int row = 0; row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            chess[row][col] = new QGraphicsPixmapItem();
            record[row][col] = "";
        }
    }
    chess[0][0]->setPixmap(QPixmap(":/img/black_rook.png").scaled(70,70));
    chess[0][1]->setPixmap(QPixmap(":/img/black_knight.png").scaled(70,70));
    chess[0][2]->setPixmap(QPixmap(":/img/black_bishop.png").scaled(70,70));
    chess[0][3]->setPixmap(QPixmap(":/img/black_queen.png").scaled(70,70));
    chess[0][4]->setPixmap(QPixmap(":/img/black_king.png").scaled(70,70));
    chess[0][5]->setPixmap(QPixmap(":/img/black_bishop.png").scaled(70,70));
    chess[0][6]->setPixmap(QPixmap(":/img/black_knight.png").scaled(70,70));
    chess[0][7]->setPixmap(QPixmap(":/img/black_rook.png").scaled(70,70));
    chess[7][0]->setPixmap(QPixmap(":/img/white_rook.png").scaled(70,70));
    chess[7][1]->setPixmap(QPixmap(":/img/white_knight.png").scaled(70,70));
    chess[7][2]->setPixmap(QPixmap(":/img/white_bishop.png").scaled(70,70));
    chess[7][3]->setPixmap(QPixmap(":/img/white_queen.png").scaled(70,70));
    chess[7][4]->setPixmap(QPixmap(":/img/white_king.png").scaled(70,70));
    chess[7][5]->setPixmap(QPixmap(":/img/white_bishop.png").scaled(70,70));
    chess[7][6]->setPixmap(QPixmap(":/img/white_knight.png").scaled(70,70));
    chess[7][7]->setPixmap(QPixmap(":/img/white_rook.png").scaled(70,70));
    for(int i = 0; i < 8; ++i) {
        chess[1][i]->setPixmap(QPixmap(":/img/black_pawn.png").scaled(70,70));
        chess[6][i]->setPixmap(QPixmap(":/img/white_pawn.png").scaled(70,70));
    }

    record[0][0] = "br";
    record[0][1] = "bn";
    record[0][2] = "bb";
    record[0][3] = "bq";
    record[0][4] = "bk";
    record[0][5] = "bb";
    record[0][6] = "bn";
    record[0][7] = "br";
    record[7][0] = "wr";
    record[7][1] = "wn";
    record[7][2] = "wb";
    record[7][3] = "wq";
    record[7][4] = "wk";
    record[7][5] = "wb";
    record[7][6] = "wn";
    record[7][7] = "wr";
    for(int i = 0; i < 8; ++i) {
        record[1][i] = "bp";
        record[6][i] = "wp";
    }

    for(int row = 0; row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            box[row][col] = new QGraphicsRectItem();
            box[row][col]->setRect(0, 0, 70, 70);
            box[row][col]->setPen(QPen(Qt::transparent));
            box[row][col]->setPos(70*col, 70*row);
            chess[row][col]->setPos(70*col, 70*row);
            scene->addItem(box[row][col]);
            scene->addItem(chess[row][col]);
        }
    }

    setboard();
    row = -1;
    col = -1;

    turn = "w";// white move first

    cover = new QGraphicsRectItem();
    cover->setRect(0, 0, 560, 560);
    cover->setBrush(QColor(255, 255, 255, 100));
    scene->addItem(cover);

    title = new QGraphicsTextItem("CHESS");
    title->setFont(QFont("Comic Sans MS", 90));
    title->setDefaultTextColor(QColor(Qt::darkBlue));
    title->setPos(80, 190);
    scene->addItem(title);

    result_black = new QGraphicsTextItem("Black won!");
    result_black->setFont(QFont("Comic Sans MS", 70));
    result_black->setDefaultTextColor(QColor(Qt::darkBlue));
    result_black->setPos(60, 210);
    scene->addItem(result_black);
    result_black->hide();

    result_white = new QGraphicsTextItem("White won!");
    result_white->setFont(QFont("Comic Sans MS", 70));
    result_white->setDefaultTextColor(QColor(Qt::darkBlue));
    result_white->setPos(35, 210);
    scene->addItem(result_white);
    result_white->hide();

    Turn = new QGraphicsRectItem();
    Turn->setBrush(Qt::black);
    Turn->setRect(0, 0, 280, 70);
    Turn->setPos(0, 560);
    scene->addItem(Turn);
    Turn->hide();

    Start = new QPushButton("START", this);
    Start->setGeometry(0, 560, 280, 70);
    Start->setPalette(QColor(Qt::darkCyan));
    Start->setStyleSheet("border:none");
    Start->setFont(QFont("Waree", 25));
    Start->setStyleSheet("color:white");
    connect(Start, SIGNAL(clicked(bool)), this, SLOT(start()));

    Set = new QPushButton("SET", this);
    Set->setGeometry(280, 560, 280, 70);
    Set->setPalette(QColor(Qt::darkCyan));
    Set->setFont(QFont("Waree", 25));
    Set->setStyleSheet("color:white");
    connect(Set, SIGNAL(clicked(bool)), this, SLOT(set()));

    Quit = new QPushButton("QUIT", this);
    Quit->setGeometry(280, 560, 280, 70);
    Quit->setPalette(QColor(Qt::darkCyan));
    Quit->setFont(QFont("Waree", 25));
    Quit->setStyleSheet("color:white");
    connect(Quit, SIGNAL(clicked(bool)), this, SLOT(quit()));
    Quit->hide();

    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 6; ++j) {
            setChess[i][j] = new QGraphicsPixmapItem();
            setChess[i][j]->setPos(35*j, 560+35*i);
            scene->addItem(setChess[i][j]);
            setChess[i][j]->hide();
        }
    }
    setChess[0][0]->setPixmap(QPixmap(":/img/white_king.png").scaled(35,35));
    setChess[0][1]->setPixmap(QPixmap(":/img/white_queen.png").scaled(35,35));
    setChess[0][2]->setPixmap(QPixmap(":/img/white_rook.png").scaled(35,35));
    setChess[0][3]->setPixmap(QPixmap(":/img/white_bishop.png").scaled(35,35));
    setChess[0][4]->setPixmap(QPixmap(":/img/white_knight.png").scaled(35,35));
    setChess[0][5]->setPixmap(QPixmap(":/img/white_pawn.png").scaled(35,35));
    setChess[1][0]->setPixmap(QPixmap(":/img/black_king.png").scaled(35,35));
    setChess[1][1]->setPixmap(QPixmap(":/img/black_queen.png").scaled(35,35));
    setChess[1][2]->setPixmap(QPixmap(":/img/black_rook.png").scaled(35,35));
    setChess[1][3]->setPixmap(QPixmap(":/img/black_bishop.png").scaled(35,35));
    setChess[1][4]->setPixmap(QPixmap(":/img/black_knight.png").scaled(35,35));
    setChess[1][5]->setPixmap(QPixmap(":/img/black_pawn.png").scaled(35,35));

    recordSet[0][0] = "wk";
    recordSet[0][1] = "wq";
    recordSet[0][2] = "wr";
    recordSet[0][3] = "wb";
    recordSet[0][4] = "wn";
    recordSet[0][5] = "wp";
    recordSet[1][0] = "bk";
    recordSet[1][1] = "bq";
    recordSet[1][2] = "br";
    recordSet[1][3] = "bb";
    recordSet[1][4] = "bn";
    recordSet[1][5] = "bp";
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::check(int row, int col) {
    if(record[row][col] == "bp") {
        if(record[row+1][col] == "") {
            box[row+1][col]->setBrush(Qt::darkCyan);
            if(row == 1) {
                if(record[3][col] == "")
                    box[3][col]->setBrush(Qt::darkCyan);
            }
        }//move
        if(col == 0) {
            if(record[row+1][col+1][0] == "w")
                box[row+1][col+1]->setBrush(Qt::darkCyan);
        } else if(col == 7) {
            if(record[row+1][col-1][0] == "w")
                box[row+1][col-1]->setBrush(Qt::darkCyan);
        } else {
            for(int i = -1; i <= 1; i += 2) {
                if(record[row+1][col+i][0] == "w")
                    box[row+1][col+i]->setBrush(Qt::darkCyan);
            }
        }//eat
    }//black pawn
    else if(record[row][col] == "wp") {
        if(record[row-1][col] == "") {
            box[row-1][col]->setBrush(Qt::darkCyan);
            if(row == 6) {
                if(record[4][col] == "")
                    box[4][col]->setBrush(Qt::darkCyan);
            }
        }//move
        if(col == 0) {
            if(record[row-1][col+1][0] == "b")
                box[row-1][col+1]->setBrush(Qt::darkCyan);
        } else if(col == 7) {
            if(record[row-1][col-1][0] == "b" )
                box[row-1][col-1]->setBrush(Qt::darkCyan);
        } else {
            for(int i = -1; i <= 1; i += 2) {
                if(record[row-1][col+i][0] == "b")
                    box[row-1][col+i]->setBrush(Qt::darkCyan);
            }
        }//eat
    }//white pawn
    else if(record[row][col][1] == "r") {
        for(int i = 1; i <= row; ++i) {
            if(record[row-i][col] == "")
                box[row-i][col]->setBrush(Qt::darkCyan);
            else if(record[row-i][col][0] != record[row][col][0]) {
                box[row-i][col]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; i < (8-row); ++i) {
            if(record[row+i][col] == "")
                box[row+i][col]->setBrush(Qt::darkCyan);
            else if(record[row+i][col][0] != record[row][col][0]) {
                box[row+i][col]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; i <= col; ++i) {
            if(record[row][col-i] == "")
                box[row][col-i]->setBrush(Qt::darkCyan);
            else if(record[row][col-i][0] != record[row][col][0]) {
                box[row][col-i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; i < (8-col); ++i) {
            if(record[row][col+i] == "")
                box[row][col+i]->setBrush(Qt::darkCyan);
            else if(record[row][col+i][0] != record[row][col][0]) {
                box[row][col+i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
    }//rook
    else if(record[row][col][1] == "b") {
        for(int i = 1; (row-i) >= 0 && (col+i) < 8; ++i) {
            if(record[row-i][col+i] == "")
                box[row-i][col+i]->setBrush(Qt::darkCyan);
            else if(record[row-i][col+i][0] != record[row][col][0]) {
                box[row-i][col+i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; (row+i) < 8 && (col+i) < 8; ++i) {
            if(record[row+i][col+i] == "")
                box[row+i][col+i]->setBrush(Qt::darkCyan);
            else if(record[row+i][col+i][0] != record[row][col][0]) {
                box[row+i][col+i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; (row-i) >= 0 && (col-i) >= 0; ++i) {
            if(record[row-i][col-i] == "")
                box[row-i][col-i]->setBrush(Qt::darkCyan);
            else if(record[row-i][col-i][0] != record[row][col][0]) {
                box[row-i][col-i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; (row+i) < 8 && (col-i) >= 0; ++i) {
            if(record[row+i][col-i] == "")
                box[row+i][col-i]->setBrush(Qt::darkCyan);
            else if(record[row+i][col-i][0] != record[row][col][0]) {
                box[row+i][col-i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
    }//bishop
    else if(record[row][col][1] == "q") {
        for(int i = 1; i <= row; ++i) {
            if(record[row-i][col] == "")
                box[row-i][col]->setBrush(Qt::darkCyan);
            else if(record[row-i][col][0] != record[row][col][0]) {
                box[row-i][col]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; i < (8-row); ++i) {
            if(record[row+i][col] == "")
                box[row+i][col]->setBrush(Qt::darkCyan);
            else if(record[row+i][col][0] != record[row][col][0]) {
                box[row+i][col]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; i <= col; ++i) {
            if(record[row][col-i] == "")
                box[row][col-i]->setBrush(Qt::darkCyan);
            else if(record[row][col-i][0] != record[row][col][0]) {
                box[row][col-i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; i < (8-col); ++i) {
            if(record[row][col+i] == "")
                box[row][col+i]->setBrush(Qt::darkCyan);
            else if(record[row][col+i][0] != record[row][col][0]) {
                box[row][col+i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; (row-i) >= 0 && (col+i) < 8; ++i) {
            if(record[row-i][col+i] == "")
                box[row-i][col+i]->setBrush(Qt::darkCyan);
            else if(record[row-i][col+i][0] != record[row][col][0]) {
                box[row-i][col+i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; (row+i) < 8 && (col+i) < 8; ++i) {
            if(record[row+i][col+i] == "")
                box[row+i][col+i]->setBrush(Qt::darkCyan);
            else if(record[row+i][col+i][0] != record[row][col][0]) {
                box[row+i][col+i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; (row-i) >= 0 && (col-i) >= 0; ++i) {
            if(record[row-i][col-i] == "")
                box[row-i][col-i]->setBrush(Qt::darkCyan);
            else if(record[row-i][col-i][0] != record[row][col][0]) {
                box[row-i][col-i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
        for(int i = 1; (row+i) < 8 && (col-i) >= 0; ++i) {
            if(record[row+i][col-i] == "")
                box[row+i][col-i]->setBrush(Qt::darkCyan);
            else if(record[row+i][col-i][0] != record[row][col][0]) {
                box[row+i][col-i]->setBrush(Qt::darkCyan);
                break;
            } else
                break;
        }
    }//queen
    else if(record[row][col][1] == "k") {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if ((row+i) > 7 || (row+i) < 0 || (col+j) > 7 || (col+j) < 0)
                    continue;
                if (record[row+i][col+j][0] != record[row][col][0])

                    box[row+i][col+j]->setBrush(Qt::darkCyan);
            }
        }
        if(record[row][col] == "bk" && row == 0 && col == 4) {
            if(bk == true && br1 == true && record[0][1] == "" && record[0][2] == "" && record[0][3] == "")
                box[0][2]->setBrush(Qt::darkCyan);
            if(bk == true && br2 == true && record[0][5] == "" && record[0][6] == "")
                box[0][6]->setBrush(Qt::darkCyan);
        }
        if(record[row][col] == "wk" && row == 7 && col == 4) {
            if(wk == true && wr1 == true && record[7][1] == "" && record[7][2] == "" && record[7][3] == "")
                box[7][2]->setBrush(Qt::darkCyan);
            if(wk == true && wr2 == true && record[7][5] == "" && record[7][6] == "" )
                box[7][6]->setBrush(Qt::darkCyan);
        }
    }//king
    else if(record[row][col][1] == "n") {
        if((row-2) >= 0 && (col-1) >= 0) {
            if(record[row-2][col-1][0] != record[row][col][0])
                box[row-2][col-1]->setBrush(Qt::darkCyan);
        }
        if((row-1) >= 0 && (col-2) >= 0) {
            if(record[row-1][col-2][0] != record[row][col][0])
                box[row-1][col-2]->setBrush(Qt::darkCyan);
        }
        if((row-2) >= 0 && (col+1) <= 7) {
            if(record[row-2][col+1][0] != record[row][col][0])
                box[row-2][col+1]->setBrush(Qt::darkCyan);
        }
        if((row-1) >= 0 && (col+2) <= 7) {
            if(record[row-1][col+2][0] != record[row][col][0])
                box[row-1][col+2]->setBrush(Qt::darkCyan);
        }
        if((row+2) <= 7 && (col-1) >= 0) {
            if(record[row+2][col-1][0] != record[row][col][0])
                box[row+2][col-1]->setBrush(Qt::darkCyan);
        }
        if((row+1) <= 7 && (col-2) >= 0) {
            if(record[row+1][col-2][0] != record[row][col][0])
                box[row+1][col-2]->setBrush(Qt::darkCyan);
        }
        if((row+2) <= 7 && (col+1) <= 7) {
            if(record[row+2][col+1][0] != record[row][col][0])
                box[row+2][col+1]->setBrush(Qt::darkCyan);
        }
        if((row+1) <= 7 && (col+2) <= 7) {
            if(record[row+1][col+2][0] != record[row][col][0])
                box[row+1][col+2]->setBrush(Qt::darkCyan);
        }
    }//knight
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(movable == 0) {
        if(event->y() > 560) {
            row = -1;
            col = -1;
            setboard();
            qDebug() << row << "" << col;
            return;
        }

        if(row == -1 && col == -1 && record[event->y()/70][event->x()/70][0] == turn) {
            row = event->y() / 70;
            col = event->x() / 70;
            check(row, col);
            qDebug() << row << "" << col;
            return;
        } else if(row != -1 && col != -1) {
            if(box[event->y() / 70][event->x() / 70]->brush() == Qt::darkCyan) {
                qDebug() << event->y() / 70 << "" << event->x() / 70;
                if(row == 0 && col == 4)
                    bk = false;
                if(row == 0 && col == 0)
                    br1 = false;
                if(row == 0 && col == 7)
                    br2 = false;
                if(row == 7 && col == 4)
                    wk = false;
                if(row == 7 && col == 0)
                    wr1 = false;
                if(row == 7 && col == 7)
                    wr2 = false;
                if(row == 0 && col == 4 && record[0][4] == "bk") {
                    if(event->y() / 70 == 0 && event->x() / 70 == 2) {
                        chess[0][0]->hide();
                        record[0][0] = "";
                        chess[0][3]->setPixmap(chess[0][0]->pixmap());
                        chess[0][3]->show();
                        record[0][3] = "br";
                        qDebug() << "castling";
                    }
                    if(event->y() / 70 == 0 && event->x() / 70 == 6) {
                        chess[0][7]->hide();
                        record[0][7] = "";
                        chess[0][5]->setPixmap(chess[0][7]->pixmap());
                        chess[0][5]->show();
                        record[0][5] = "br";
                        qDebug() << "castling";
                    }
                }
                if(row == 7 && col == 4 && record[7][4] == "wk") {
                    if(event->y() / 70 == 7 && event->x() / 70 == 2) {
                        chess[7][0]->hide();
                        record[7][0] = "";
                        chess[7][3]->setPixmap(chess[7][0]->pixmap());
                        chess[7][3]->show();
                        record[7][3] = "wr";
                        qDebug() << "castling";
                    }
                    if(event->y() / 70 == 7 && event->x() / 70 == 6) {
                        chess[7][7]->hide();
                        record[7][7] = "";
                        chess[7][5]->setPixmap(chess[7][7]->pixmap());
                        chess[7][5]->show();
                        record[7][5] = "wr";
                        qDebug() << "castling";
                    }
                }
                chess[row][col]->hide();
                chess[event->y() / 70][event->x() / 70]->setPixmap(chess[row][col]->pixmap());
                chess[event->y() / 70][event->x() / 70]->show();// move

                if(record[event->y() / 70][event->x() / 70] == "bk") {
                    setboard();
                    cover->show();
                    result_white->show();
                    movable = -1;
                    return;
                }
                if(record[event->y() / 70][event->x() / 70] == "wk") {
                    setboard();
                    cover->show();
                    result_black->show();
                    movable = -1;
                    return;
                }//stop the game

                record[event->y() / 70][event->x() / 70] = record[row][col];
                record[row][col] = "";//update chess record

                if(record[event->y() / 70][event->x() / 70][1] == "p") {
                    if(record[event->y() / 70][event->x() / 70][0] == "b" && event->y() / 70 == 7) {
                        record[event->y() / 70][event->x() / 70] = "bq";
                        chess[event->y() / 70][event->x() / 70]->setPixmap(QPixmap(":/img/black_queen.png").scaled(70,70));
                        qDebug() << "promotion";
                    }
                    if(record[event->y() / 70][event->x() / 70][0] == "w" && event->y() / 70 == 0) {
                        record[event->y() / 70][event->x() / 70] = "wq";
                        chess[event->y() / 70][event->x() / 70]->setPixmap(QPixmap(":/img/white_queen.png").scaled(70,70));
                        qDebug() << "promotion";
                    }
                }//promotion

                if(turn == "b") {
                    turn = "w";
                    Turn->hide();
                } else {
                    turn = "b";
                    Turn->show();
                }
            }
            row = -1;
            col = -1;
            setboard();
        }
        qDebug() << row << "" << col;
    } else if(movable == 1) {
        if(row == -1 && col == -1) {
            if(event->y() > 560 && event->y() < 630 &&event->x() > 0 && event->x() < 210) {
                row = (event->y()-560) / 35;
                col = event->x() / 35;
                qDebug() << row << "" << col;
                return;
            }
        } else if(row != -1 && col != -1) {
            if(event->y() > 560 || record[event->y()/70][event->x()/70] != "") {
                row = -1;
                col = -1;
                qDebug() << row << "" << col;
                return;
            } else {
                chess[event->y() / 70][event->x() / 70]->setPixmap(setChess[row][col]->pixmap().scaled(70,70));
                record[event->y() / 70][event->x() / 70] = recordSet[row][col];
                qDebug() << event->y() / 70 << "" << event->x() / 70;
                num[row][col]--;
            }
            row = -1;
            col = -1;
            for(int i = 0; i < 2; ++i) {
                for(int j = 0; j < 6; ++j) {
                    if(num[i][j] <= 0)
                        setChess[i][j]->setPixmap(QPixmap());
                }
            }
            if(num[0][0] == 0 && num[1][0] == 0)
                Start->show();
        }
        qDebug() << row << "" << col;
    }
}

void MainWindow::setboard() {
    for(int row = 0; row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            if((row+col) % 2 == 0)
                box[row][col]->setBrush(QColor(254,210,207));
            else
                box[row][col]->setBrush(QColor(252,118,106));
        }
    }
}

void MainWindow::start() {
    Start->hide();
    Set->hide();
    cover->hide();
    title->hide();
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 6; ++j) {
            setChess[i][j]->hide();
        }
    }
    movable = 0;
    Quit->show();
}

void MainWindow::set() {
    movable = 1;
    Start->hide();
    Set->hide();
    cover->hide();
    title->hide();
    for(int row = 0; row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            chess[row][col]->setPixmap(QPixmap());
            record[row][col] = "";
        }
    }//clean up the chess board
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 6; ++j) {
            setChess[i][j]->show();
        }
    }
    Start->setGeometry(280, 560, 280, 70);
}

void MainWindow::quit() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
