#include "square.h"

square::square(int x, int y, QWidget *parent, Color aColor, Piece aPiece) : QWidget(parent)
{
    this->locX = x;
    this->locY = y;
    this->curParent = parent;
    this->curButton = new QPushButton(parent);
    this->curColor = aColor;
    this->curPiece = aPiece;
    this->highlighted = false;
    this->selected = false;
    this->attacked = false;
    this->canBeAttacked = false;
    connect(this->curButton, &QPushButton::clicked, this, &square::buttonPress);

}

square::~square()
{
    delete curButton;
}

void square::removePiece()
{
    this->curColor = NONE;
    this->curPiece = EMPTY;
    this->moves = 0;
}

void square::setPiece(Piece aPiece)
{
    this->curPiece = aPiece;
}

void square::setColor(Color aColor)
{
    this->curColor = aColor;
}

void square::updateMoves(int x)
{
    this->moves = x+1;
}

//void square::setSquare(square aSquare)
//{
//    this->curPiece = aSquare.getCurPiece();
//    this->curColor = aSquare.getCurColor();
//}

Piece square::getCurPiece()
{
    return this->curPiece;
}

Color square::getCurColor()
{
    return this->curColor;
}

int square::getX()
{
    return this->locX;
}

int square::getY()
{
    return this->locY;
}

int square::getMoves()
{
    return this->moves;
}

void square::updateButton() // slowly turning into a nightmare
{
    Color aColor = curColor;
    Piece aPiece = curPiece;
    if (highlighted) {curButton->setStyleSheet("background-color: rgb(255, 255, 0); border: none;");}
    else if (attacked) {curButton->setStyleSheet("background-color: rgb(255, 0, 0); border: none;");}
    else if (selected) {curButton->setStyleSheet("background-color: rgb(0, 255, 0); border: none;");}
    auto aButton = this->curButton;
    switch (aColor)
    {
        case WHITE:
        {
            switch(curPiece)
            {
                case PAWN:
                {
                    this->setNewIcon(":/new/pieces/whitePawn.png");
                    break;
                }
                case BISHOP:
                {
                    this->setNewIcon(":/new/pieces/whiteBishop.png");
                    break;
                }
                case KNIGHT:
                {
                    this->setNewIcon(":/new/pieces/whiteKnight.png");
                    break;
                }
                case ROOK:
                {
                    this->setNewIcon(":/new/pieces/whiteRook.png");
                    break;
                }
                case QUEEN:
                {
                    this->setNewIcon(":/new/pieces/whiteQueen.png");
                    break;
                }
                case KING:
                {
                    this->setNewIcon(":/new/pieces/whiteKingAiden.png");
                    break;
                }
                case PAWNGRABBER:
                {
                    this->setNewIcon(":/new/pieces/whitePawnGrabber.png");
                    break;
                }
                case PIKEMAN:
                {
                    this->setNewIcon(":/new/pieces/whiteLancer.png");
                    break;
                }
                case MONK:
                {
                    this->setNewIcon(":/new/pieces/whiteKing.png");
                    break;
                }
            }
            break;

        }
        case BLACK:
        {
            switch(curPiece)
            {
                case PAWN:
                {
                    this->setNewIcon(":/new/pieces/blackPawn.png");
                    break;
                }
                case BISHOP:
                {
                    this->setNewIcon(":/new/pieces/blackBishop.png");
                    break;
                }
                case KNIGHT:
                {
                    this->setNewIcon(":/new/pieces/blackKnight.png");
                    break;
                }
                case ROOK:
                {
                    this->setNewIcon(":/new/pieces/blackRook.png");
                    break;
                }
                case QUEEN:
                {
                    this->setNewIcon(":/new/pieces/blackQueen.png");
                    break;
                }
                case KING:
                {
                    this->setNewIcon(":/new/pieces/blackKingMearl.png");
                    break;
                }
                case PAWNGRABBER:
                {
                    this->setNewIcon(":/new/pieces/blackPawnGrabber.png");
                    break;
                }
                case PIKEMAN:
                {
                    this->setNewIcon(":/new/pieces/blackLancer.png");
                    break;
                }
                case MONK:
                {
                    this->setNewIcon(":/new/pieces/blackKing.png");
                    break;
                }
            }
            break;
        }
        case NONE:
        {
            aButton->setIcon(QIcon());
            break;
        }
    }
    aButton->update();
}


// Helper functions

// syntax is this->setNewIcon(iconpath)
void square::setNewIcon(const QString &fileName)
{
    QPixmap pixmap(fileName);
    QIcon ButtonIcon(pixmap);
    auto aButton = this->curButton;
    aButton->setIcon(ButtonIcon);
    aButton->setIconSize(pixmap.rect().size());
}


void square::setSquare(square* aSquare)
{
    this->setPiece(aSquare->curPiece);
    this->setColor(aSquare->curColor);
    this->updateMoves(aSquare->getMoves());

}
