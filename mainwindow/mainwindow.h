#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
#include <square.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generateBoard(int, int, QWidget *parent = nullptr);
    void showBoard();
    void showBoardWhite();
    void showBoardUnhighlighted();
    void setStandardBoard();
    void highlighting(square *);

    // board functions
    square * getSquare(int,int);
    bool canBeAttacked(int, int);

public slots:
    void move(int, int);
private:
    std::vector<std::vector<square*>> board;
    Color curPlayer = WHITE;
    square *selectedSquare = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
