#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>
#include <QPushButton>

enum Color { WHITE, BLACK, NONE };
enum Piece { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWNGRABBER, PIKEMAN, MONK, EMPTY };

class square : public QWidget
{
    Q_OBJECT
    int locX, locY, moves = 0;
    Color curColor;
    Piece curPiece;
    QWidget *curParent;
public:
    // vars and constructor
    explicit square(int, int, QWidget *parent = nullptr, Color = NONE,  Piece = EMPTY);
    ~square();
    QPushButton *curButton;
    bool highlighted, selected, attacked, canBeAttacked;


    //setters
    void removePiece();
    void setPiece(Piece);
    void setColor(Color);
    void setSquare(square*);
    void updateMoves(int);
    void updateButton();

    // getters
    Piece getCurPiece();
    Color getCurColor();
    int getX();
    int getY();
    int getMoves();

    // helpers
    void setNewIcon(const QString&);
signals:
    void buttonPress();

public slots:

};

#endif // SQUARE_H
