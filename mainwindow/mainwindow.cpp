
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateBoard(int x, int y, QWidget *parent)
{
    this->board.resize(x);
    for (int i = 0; i < x; i++)
    {
        this->board[i].resize(y);
        for (int j = 0; j < y; j++)
        {
            this->board[i][j] = new square(i, j, this->centralWidget());
            QRect aRect(i*100, j*100, 100, 100);
            square* aSquare = this->board[i][j];
            auto aButton = aSquare->curButton;
            if ((i%2 == 0 && j%2 != 0) || (i%2 != 0 && j%2==0))
            {
                aButton->setStyleSheet("background-color:BurlyWood;");
            }
            else {aButton->setStyleSheet("background-color:FireBrick;");}
            aButton->setGeometry(aRect);
            aButton->show();

            connect(aButton, &QPushButton::clicked, this, [this, i, j] {this->move(i, j);});
        }
    }
}

void MainWindow::showBoard()
{
    QSize size = this->size();
    int sizeMult = size.height();
    if (size.width() < size.height()) sizeMult = size.width();
    sizeMult = 0.9 * sizeMult/(this->board.size());
    for (int i = 0; i < this->board.size(); i++)
    {
        for (int j = 0; j < this->board[i].size(); j++)
        {
            QRect aRect(i*sizeMult, j*sizeMult, sizeMult, sizeMult);
            square* aSquare = this->board[i][j];
            auto aButton = aSquare->curButton;
            aSquare->updateButton();
            aButton->setGeometry(aRect);
            aButton->show();
        }
    }
}

void MainWindow::showBoardWhite()
{
    QSize size = this->size();
    int sizeMult = size.height();
    if (size.width() < size.height()) sizeMult = size.width();
    sizeMult = sizeMult/(this->board.size());
    for (int i = 0; i < this->board.size(); i++)
    {
        for (int j = 0; j < this->board[i].size(); j++)
        {
            QRect aRect(i*sizeMult, j*sizeMult, sizeMult, sizeMult);
            square* aSquare = this->board[i][j];
            auto aButton = aSquare->curButton;
            aSquare->updateButton();
            aButton->setGeometry(aRect);
            aButton->show();
        }
    }
}

void MainWindow::showBoardUnhighlighted()
{
    for (int i = 0; i < this->board.size(); i++)
    {
        for (int j = 0; j < this->board[i].size(); j++)
        {
            square* aSquare = this->board[i][j];
            aSquare->highlighted = false;
            aSquare->attacked = false;
            aSquare->selected = false;
            auto aButton = aSquare->curButton;
            if ((i%2 == 0 && j%2 != 0) || (i%2 != 0 && j%2==0))
            {
                aButton->setStyleSheet("background-color:BurlyWood;");
            }
            else {aButton->setStyleSheet("background-color:FireBrick;");}
            aSquare->updateButton();
            aButton->show();
        }
    }
}


// board functions

square* MainWindow::getSquare(int x, int y)
{
    return this->board[x][y];
}

bool MainWindow::canBeAttacked(int x, int y) // not finished, write the piece functions first
{

}

void MainWindow::setStandardBoard() // disgusting, recode later
{
    int x = board.size();
    if (x > 8) x = 8;
    for (int i = 0; i < x; i++)
    {
        square* aSquare = this->board[i][1];
        aSquare->setPiece(PAWN);
        aSquare->setColor(WHITE);
        square* aSquare2 = this->board[i][6];
        aSquare2->setPiece(PAWN);
        aSquare2->setColor(BLACK);
    }
    {
        auto queenSquare1 = this->board[4][0];
        queenSquare1->setPiece(QUEEN);
        queenSquare1->setColor(WHITE);
        auto queenSquare2 = this->board[4][7];
        queenSquare2->setPiece(QUEEN);
        queenSquare2->setColor(BLACK);
    }
    {
        auto queenSquare1 = this->board[3][0];
        queenSquare1->setPiece(PAWNGRABBER);
        queenSquare1->setColor(WHITE);
        auto queenSquare2 = this->board[3][7];
        queenSquare2->setPiece(PAWNGRABBER);
        queenSquare2->setColor(BLACK);
    }
    {
        auto kingSquare1 = this->board[1][0];
        kingSquare1->setPiece(KNIGHT);
        kingSquare1->setColor(WHITE);
    }
    {
        auto kingSquare1 = this->board[6][0];
        kingSquare1->setPiece(KNIGHT);
        kingSquare1->setColor(WHITE);
    }
    {
        auto kingSquare1 = this->board[1][7];
        kingSquare1->setPiece(KNIGHT);
        kingSquare1->setColor(BLACK);
    }
    {
        auto kingSquare1 = this->board[6][7];
        kingSquare1->setPiece(KNIGHT);
        kingSquare1->setColor(BLACK);
    }
    {
        auto queenSquare1 = this->board[0][0];
        queenSquare1->setPiece(PIKEMAN);
        queenSquare1->setColor(WHITE);
        auto queenSquare2 = this->board[0][7];
        queenSquare2->setPiece(PIKEMAN);
        queenSquare2->setColor(BLACK);
    }
    {
        auto queenSquare1 = this->board[7][0];
        queenSquare1->setPiece(ROOK);
        queenSquare1->setColor(WHITE);
        auto queenSquare2 = this->board[7][7];
        queenSquare2->setPiece(ROOK);
        queenSquare2->setColor(BLACK);
    }
    {
        auto queenSquare1 = this->board[2][0];
        queenSquare1->setPiece(BISHOP);
        queenSquare1->setColor(WHITE);
        auto queenSquare2 = this->board[5][0];
        queenSquare2->setPiece(BISHOP);
        queenSquare2->setColor(WHITE);
    }
    {
        auto queenSquare1 = this->board[2][7];
        queenSquare1->setPiece(BISHOP);
        queenSquare1->setColor(BLACK);
        auto queenSquare2 = this->board[5][7];
        queenSquare2->setPiece(BISHOP);
        queenSquare2->setColor(BLACK);
    }
    {
        auto squareRAN = this->board[5][5];
        squareRAN->setPiece(MONK);
        squareRAN->setColor(WHITE);
    }
    {
        auto squareRAN = this->board[5][6];
        squareRAN->setPiece(MONK);
        squareRAN->setColor(BLACK);
    }

}

// movement functions

void MainWindow::move(int x, int y)
{

    square *aSquare = board[x][y];
    if (selectedSquare != nullptr && aSquare->highlighted == false && aSquare->attacked == false) this->showBoardUnhighlighted();
    if (aSquare->getCurColor() != this->curPlayer && aSquare->highlighted == false && aSquare->attacked == false) return;
    this->highlighting(aSquare);
    bool moving = false;
    if (aSquare->highlighted || aSquare->attacked) moving = true;
    if (selectedSquare == aSquare || selectedSquare == nullptr) moving = false;
    if (moving && selectedSquare->getCurPiece() == MONK)
    {
        if (aSquare->attacked == true) aSquare->setColor(selectedSquare->getCurColor());
        else {
            aSquare->setSquare(selectedSquare);
            this->board[selectedSquare->getX()][selectedSquare->getY()]->removePiece();
        }
        this->selectedSquare = nullptr;
        this->showBoardUnhighlighted();
        if (this->curPlayer == WHITE) { this->curPlayer = BLACK;}
        else {this->curPlayer = WHITE;}
        this->showBoard();
        return;
    }
    if (moving)
    {
        aSquare->setSquare(selectedSquare);
        this->board[selectedSquare->getX()][selectedSquare->getY()]->removePiece();
        this->selectedSquare = nullptr;
        this->showBoardUnhighlighted();
        if (this->curPlayer == WHITE) { this->curPlayer = BLACK;}
        else {this->curPlayer = WHITE;}
    }
    if (!moving)
    {
        this->selectedSquare = aSquare;
    }

    this->showBoard();

}




void MainWindow::highlighting(square *aSquare) // currently creating segmentation faults, also needs to be cleaned up. Bishops currently do not create seg faults, but will not move
{
    Piece aPiece = aSquare->getCurPiece();
    Color pieceColor = aSquare->getCurColor();
    if (aPiece != EMPTY) aSquare->selected = true;
    int x = aSquare->getX();
    int y = aSquare->getY();
    switch (aPiece)
    {
        case PAWN:
        {
            switch (pieceColor)
            {
                case WHITE:
                {
                    for (int i = -1; i <= 1; i++)
                    {
                        if (x+i < 0 || x+i  >= this->board.size()) continue;
                        if (y+1 > board.size()) continue;
                        auto movementSquare = this->getSquare(x+i, y+1);
                        if (i == 0 && movementSquare->getCurPiece() == EMPTY)
                        {
                            movementSquare->highlighted = true;
                            if (aSquare->getMoves() == 0)
                            {
                                auto movementSquare = this->getSquare(x, y+2);
                                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                            }
                            continue;
                        }
                        Color aColor = movementSquare->getCurColor();
                        if (aColor != NONE && aColor != pieceColor && movementSquare->getCurPiece()!= EMPTY && i != 0)
                        {
                            movementSquare->attacked = true;
                        }
                    }
                    break;
                }

                case BLACK:
                {
                    for (int i = -1; i <= 1; i++)
                    {
                        if (x+i < 0 || x+i >= this->board[x].size()) continue;
                        if (y+1 > board.size()) continue;
                        auto movementSquare = this->getSquare(x+i, y-1);
                        if (i == 0 && movementSquare->getCurPiece() == EMPTY)
                        {
                            movementSquare->highlighted = true;
                            if (aSquare->getMoves() == 0)
                            {
                                auto movementSquare = this->getSquare(x, y-2);
                                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                            }
                            continue;
                        }
                        Color aColor = movementSquare->getCurColor();
                        if (aColor != NONE && aColor != pieceColor && movementSquare->getCurPiece()!= EMPTY && i != 0)
                        {
                            movementSquare->attacked = true;
                        }
                    }
                    break;
                }
                case NONE:
                {
                    break;
                }


            }
            break;
        }
        case KING:
        {
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    //if (i > )
                    if (i+x < 0 || i+x >= this->board.size()) continue;
                    if (j+y < 0 || j+y >= this->board[0].size()) continue;
                    auto movementSquare = this->getSquare(x+i, y+j);
                    if (movementSquare->getCurColor() != pieceColor)
                    {
                        if (!movementSquare->canBeAttacked)
                        {
                            if (movementSquare->getCurColor() == NONE) movementSquare->highlighted = true;
                            else movementSquare->attacked = true;
                        }
                    }
                }
            }
            break;
        }
        case ROOK: // works
        {
            int size = board.size();
            //looking right
            for (int i = 1; (i+x) <= size; i++)
            {
                if (i+x >= size || x+i < 0) continue;
                auto movementSquare = board[x+i][y];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking left
            for (int i = -1; (i+x) >= 0; i-= 1)
            {
                if (i+x >= size || x+i < 0) continue;
                auto movementSquare = board[x+i][y];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking down
            for (int i = 1; (i+y) <= size; i++)
            {
                if (i+y >= size || y+i < 0) continue;
                auto movementSquare = board[x][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking up
            for (int i = -1; (y+i) >= 0; i--)
            {
                if (y+i >= size || y+i < 0) continue;
                auto movementSquare = board[x][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            break;
        }
        case BISHOP:
        {
            int size = board.size();
            //looking right and down
            for (int i = 1; (i+x) <= size; i++)
            {
                if (i+x >= size || x+i < 0 || y+i >= size || y+i < 0) continue;
                auto movementSquare = board[x+i][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }

            // looking left and up
            for (int i = -1; (i+x) >= 0; i--)
            {
                if (i+x >= size || x+i < 0 || y+i >= size || y+i < 0) continue;
                auto movementSquare = board[x+i][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking down and left
            for (int i = 1; (i+x) <= size; i++)
            {
                if (i+x >= size || x+i < 0 || y-i >= size || y-i < 0) continue;
                auto movementSquare = board[x+i][y-i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking up and right
            for (int i = -1; (x+i) >= 0; i--)
            {
                if (i+x >= size || x+i < 0 || y-i >= size || y-i < 0) continue;
                auto movementSquare = board[x+i][y-i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            break;
        }
        case KNIGHT: // works great, no touch
        {
            for (int i = -2; i <= 2; i+=4)
            {
                for (int j = -1; j<=1; j+=2)
                {
                    if (i+x < 0 || i+x >= this->board.size()) continue;
                    if (j+y < 0 || j+y >= this->board[0].size()) continue;
                    auto movementSquare = this->getSquare(x+i, y+j);
                    if (movementSquare->getCurColor() == NONE)
                    {
                        movementSquare->highlighted = true;
                    }
                    else if (movementSquare->getCurColor() != curPlayer)
                    {
                        movementSquare->attacked = true;
                    }
                }
            }
            for (int i = -2; i <= 2; i+=4)
            {
                for (int j = -1; j<=1; j+=2)
                {
                    if (j+x < 0 || j+x >= this->board.size()) continue;
                    if (i+y < 0 || i+y >= this->board[0].size()) continue;
                    auto movementSquare = this->getSquare(x+j, y+i);
                    if (movementSquare->getCurColor() == NONE)
                    {
                        movementSquare->highlighted = true;
                    }
                    else if (movementSquare->getCurColor() != curPlayer)
                    {
                        movementSquare->attacked = true;
                    }
                }
            }
            break;
        }
        case QUEEN:
        {
            int size = board.size();
            //looking right
            for (int i = 1; (i+x) <= size; i++)
            {
                if (i+x >= size || x+i < 0) continue;
                auto movementSquare = board[x+i][y];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking left
            for (int i = -1; (i+x) >= 0; i-= 1)
            {
                if (i+x >= size || x+i < 0) continue;
                auto movementSquare = board[x+i][y];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking down
            for (int i = 1; (i+y) <= size; i++)
            {
                if (i+y >= size || y+i < 0) continue;
                auto movementSquare = board[x][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking up
            for (int i = -1; (y+i) >= 0; i--)
            {
                if (y+i >= size || y+i < 0) continue;
                auto movementSquare = board[x][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            //looking right and down
            for (int i = 1; (i+x) <= size; i++)
            {
                if (i+x >= size || x+i < 0 || y+i >= size || y+i < 0) continue;
                auto movementSquare = board[x+i][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }

            // looking left and up
            for (int i = -1; (i+x) >= 0; i--)
            {
                if (i+x >= size || x+i < 0 || y+i >= size || y+i < 0) continue;
                auto movementSquare = board[x+i][y+i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking down and left
            for (int i = 1; (i+x) <= size; i++)
            {
                if (i+x >= size || x+i < 0 || y-i >= size || y-i < 0) continue;
                auto movementSquare = board[x+i][y-i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            // looking up and right
            for (int i = -1; (x+i) >= 0; i--)
            {
                if (i+x >= size || x+i < 0 || y-i >= size || y-i < 0) continue;
                auto movementSquare = board[x+i][y-i];
                if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                else if (movementSquare->getCurColor() == pieceColor) break;
                else {movementSquare->attacked = true; break;}
            }
            break;
        }
        case PAWNGRABBER:
        {
            for (int i = 0; i < this->board.size(); i++)
            {
                for (int j = 0; j < this->board[i].size(); j++)
                {
                    auto movementSquare = board[i][j];
                    if (movementSquare->getCurPiece() == PAWN && movementSquare->getCurColor() != pieceColor)
                    {
                        movementSquare->attacked = true;
                    }
                }
            }
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    //if (i > )
                    if (i+x < 0 || i+x >= this->board.size()) continue;
                    if (j+y < 0 || j+y >= this->board[0].size()) continue;
                    auto movementSquare = this->getSquare(x+i, y+j);
                    if (movementSquare->getCurColor() != pieceColor)
                    {
                        if (!movementSquare->canBeAttacked)
                        {
                            if (movementSquare->getCurColor() == NONE) movementSquare->highlighted = true;
                            else movementSquare->attacked = true;
                        }
                    }
                }
            }
            break;
        }
        case PIKEMAN:
        {
            switch (pieceColor)
            {
                case WHITE:
                {
                    for (int i = -1; i <= 1; i++)
                    {
                        if (x+i < 0 || x+i  >= this->board.size()) continue;
                        if (y+1 > board.size()) continue;
                        auto movementSquare = this->getSquare(x+i, y+1);
                        Color aColor = movementSquare->getCurColor();
                        if (i == 0)
                        {
                            if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                            if (aColor != NONE && aColor != pieceColor) continue;
                            if (y+2 < board.size())
                            {
                                auto movementSquare2 = this->getSquare(x, y+2);
                                if (movementSquare2->getCurColor() == pieceColor) continue;
                                if (movementSquare2->getCurColor() == NONE) movementSquare2->highlighted = true;
                                else movementSquare2->attacked = true;

                            }
                            continue;
                        }
                        if (aColor != NONE && aColor != pieceColor && movementSquare->getCurPiece()!= EMPTY && i != 0)
                        {
                            movementSquare->attacked = true;
                        }

                    }
                    break;
                }

                case BLACK:
                {
                    for (int i = -1; i <= 1; i++)
                    {
                        if (x+i < 0 || x+i >= this->board[x].size()) continue;
                        if (y+1 > board.size()) continue;
                        auto movementSquare = this->getSquare(x+i, y-1);
                        Color aColor = movementSquare->getCurColor();
                        if (i == 0)
                        {
                            if (movementSquare->getCurPiece() == EMPTY) movementSquare->highlighted = true;
                            if (aColor != NONE && aColor != pieceColor) continue;
                            if (y-2 < board.size())
                            {
                                auto movementSquare2 = this->getSquare(x, y-2);
                                if (movementSquare2->getCurColor() == pieceColor) continue;
                                if (movementSquare2->getCurColor() == NONE) movementSquare2->highlighted = true;
                                else movementSquare2->attacked = true;

                            }
                            continue;
                        }
                        if (aColor != NONE && aColor != pieceColor && movementSquare->getCurPiece()!= EMPTY && i != 0)
                        {
                            movementSquare->attacked = true;
                        }
                    }
                    break;
                }
                case NONE:
                {
                    break;
                }

            }
            break;
        }
        case MONK:
        {
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (i+x < 0 || i+x >= this->board.size()) continue;
                    if (j+y < 0 || j+y >= this->board[0].size()) continue;
                    auto movementSquare = this->getSquare(x+i, y+j);
                    if (movementSquare->getCurColor() != pieceColor)
                    {
                        if (!movementSquare->canBeAttacked)
                        {
                            if (movementSquare->getCurColor() == NONE) movementSquare->highlighted = true;
                            else movementSquare->attacked = true;
                        }
                    }
                }
            }
            break;
        }
        case EMPTY:
        {
            break;
        }
    }
}
