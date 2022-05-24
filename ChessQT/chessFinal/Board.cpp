/*
  Sert à gérer l'affichage du l'échiquier.

  file   Board.cpp
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#include "Board.h"

using namespace raii;
using namespace affichage;

template<class P> raii::GestionPiece<P>::~GestionPiece() { if (true) clean_(); }

template <typename P>
raii::GestionPiece<P> supprimer(P piece) {
	return raii::GestionPiece<P>(piece);
}


affichage::Board::Board(int x, int y)
{
	_isPieceSelected = false;
	_pieceSelected = nullptr;

	_turn = false;
	x, y;

	QGroupBox* groupBox = new QGroupBox; 
	groupBox->setFixedSize(810, 900);

	QGridLayout* grid = new QGridLayout; 
	grid->setVerticalSpacing(0);
	grid->setHorizontalSpacing(0);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Square* square = new Square(i, j); 

			bool isAlternateColumns = (square->getXCoordinate() % 2 != 0 && square->getYCoordinate() % 2 == 0);
			bool isAlternateLines = (square->getXCoordinate() % 2 == 0 && square->getYCoordinate() % 2 != 0);
			if (isAlternateColumns or isAlternateLines) {
				square->getSquareButton()->setStyleSheet("background-color : gray");
			}

			list[i][j] = square;

			connect(square->getSquareButton(), SIGNAL(clicked()), this, SLOT(selectPiece()));
			grid->addWidget(square->getSquareButton(), i, j);
		}
	}
	QLabel* space = new QLabel;
	space->setFixedSize(150, 50);
	space->setStyleSheet("color : red");
	grid->addWidget(space, 9, 0);

	QLabel* errorMessage = new QLabel;
	errorMessage->setFixedSize(300, 50);
	errorMessage->setStyleSheet("font-weight: bold;");
	errorMessage->setStyleSheet("QLabel{font-size: 12pt;}");
	grid->addWidget(errorMessage, 9, 3);

	QPushButton* button = new QPushButton("Nouvelle partie"); 
	button->setFixedSize(100, 40);
	grid->addWidget(button, 10, 0);
	_resetButton = button;

	groupBox->setLayout(grid);
	_box = groupBox;
	_grid = grid;
	_space = space;
	_errorMessage = errorMessage;
}

Square* affichage::Board::getElementsList(int i, int j) { return list[i][j]; }
QPushButton* affichage::Board::getButton() { return _resetButton; }
QGroupBox* affichage::Board::getBox() { return _box; }
QLabel* affichage::Board::getSpace() { return _space; }
QLabel* affichage::Board::getErrorMessage() { return _errorMessage; }
QGridLayout* affichage::Board::getGrid() { return _grid; }

void affichage::Board::movePiece(Piece* piece, int xToGo, int yToGo)
{
	if (!checkForEchecBoard(piece, xToGo, yToGo)) {
		if (piece->isMoveValid(piece, xToGo, yToGo) && checkForJump(piece, xToGo, yToGo) && checkColor(list[xToGo][yToGo]->getPiece(), piece)) {
			if (list[xToGo][yToGo]->getPiece() != nullptr) {
				deletePiece(list[xToGo][yToGo]->getPiece());
			}

			list[piece->getXCoordinate()][piece->getYCoordinate()]->setPiece(nullptr);
			list[piece->getXCoordinate()][piece->getYCoordinate()]->getSquareButton()->setIcon(QIcon());

			list[xToGo][yToGo]->setPiece(piece);
			list[xToGo][yToGo]->getPiece()->setXCordinates(xToGo);
			list[xToGo][yToGo]->getPiece()->setYCordinates(yToGo);

			list[xToGo][yToGo]->getSquareButton()->setIcon(piece->getQIcon());

			_turn = !_turn;

			if (_turn) {
				_space->setText("Tour des blancs");
			}
			else {
				_space->setText("Tour des noirs"); 
			}
			_errorMessage->setText("");
			} else {
				_errorMessage->setText("Ce mouvement n'est pas permis!");
			}
	}
}

void affichage::Board::deletePiece(Piece* piece)
{
	list[piece->getXCoordinate()][piece->getYCoordinate()]->setPiece(nullptr);
	list[piece->getXCoordinate()][piece->getYCoordinate()]->getSquareButton()->setText("");
	supprimer([piece] { std::cout << "La pièce " << piece->getName().toStdString() << " a été supprimée de l'échiquier! \n"; delete piece;  });

}

void affichage::Board::setPiece(Piece* piece)
{
	int positionX = piece->getXCoordinate(), positionY = piece->getYCoordinate();
	list[positionX][positionY]->setPiece(piece);

	list[positionX][positionY]->getSquareButton()->setIcon(piece->getQIcon());
}

void affichage::Board::setTurn(bool turn) { _turn = turn; }

bool affichage::Board::checkForJump(Piece* piece, int xToGo, int yToGo)
{
	if (piece != nullptr && (piece->getName().toStdString() == "Cavalier blanc" || piece->getName().toStdString() == "Cavalier noir")) {
		return true;
	}

	int i = 0, x = 0, j = 0, y = 0;

	if (xToGo < piece->getXCoordinate()) { i = piece->getXCoordinate() - 1; x = xToGo; }
	if (yToGo < piece->getYCoordinate()) { j = piece->getYCoordinate() - 1; y = yToGo; }
	if (piece->getXCoordinate() <= xToGo) { i = xToGo - 1; x = piece->getXCoordinate(); }
	if (piece->getYCoordinate() <= yToGo) { j = yToGo - 1; y = piece->getYCoordinate(); }

	while (y < j || x < i) {
		if (y < j) {
			y++;
		}
		if (x < i) {
			x++;
		}
		if (list[x][y]->getPiece() != nullptr) {
			_errorMessage->setText("Ne peut pas sauter par dessus une pièce");
			return false;
		}
	}
	return true;
}

bool affichage::Board::checkColor(Piece* pieceToGo, Piece* pieceOnSquare)
{
	if (pieceToGo == nullptr) {
		return true;
	}
	else if (pieceToGo->getColor() != pieceOnSquare->getColor()) {
		return true;
	}
	else { _errorMessage->setText("Ne peut pas manger une pièce de la même couleur"); return false; }
}

bool affichage::Board::checkForEchecPiece(Piece* piece)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (piece->isMoveValid(piece, i, j) && checkForJump(piece, i, j) && checkColor(list[i][j]->getPiece(), piece)) {
				if (list[i][j]->getPiece() != nullptr && piece->getColor() != list[i][j]->getPiece()->getColor() && (list[i][j]->getPiece()->getName().toStdString() == "Roi blanc" || list[i][j]->getPiece()->getName().toStdString() == "Roi noir")) {
					_errorMessage->setText("Attention! Risque d'échec!");
					return true;
				}
			}
		}
	}
	return false;
}

bool affichage::Board::checkForEchecBoard(Piece* piece, int x, int y)
{

	Piece* pieceMoved = list[piece->getXCoordinate()][piece->getYCoordinate()]->getPiece();
	Piece* pieceAte = list[x][y]->getPiece();

	list[x][y]->setPiece(pieceMoved);
	list[piece->getXCoordinate()][piece->getYCoordinate()]->setPiece(nullptr);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (list[i][j]->getPiece() != nullptr && list[i][j]->getPiece()->getColor() != piece->getColor()) {
				if (checkForEchecPiece(list[i][j]->getPiece())) {
					list[piece->getXCoordinate()][piece->getYCoordinate()]->setPiece(pieceMoved);
					list[x][y]->setPiece(pieceAte);

					return true;
				}
			}
		}
	}

	list[piece->getXCoordinate()][piece->getYCoordinate()]->setPiece(pieceMoved);
	list[x][y]->setPiece(pieceAte);

	return false;
}

void affichage::Board::selectPiece()
{
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());

	if (!_isPieceSelected) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (list[i][j]->getPiece() != nullptr && list[i][j]->getSquareButton() == buttonSender) {
					if (list[i][j]->getPiece()->getColor() == _turn) {
						_pieceSelected = list[i][j]->getPiece();
					}
					else { _errorMessage->setText("Ce n'est pas votre Tour! "); return; }
				}
			}
		}
		if (_pieceSelected == nullptr) { _errorMessage->setText("Pas de pièce à sélectionner..."); }
		else { _errorMessage->setText(_pieceSelected->getName() + " sélectionné(e)"); _isPieceSelected = true; }

	}

	else if (_isPieceSelected)
	{
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (list[i][j]->getSquareButton() == buttonSender) {
					movePiece(_pieceSelected, i, j);
				}
			}
		}
		_isPieceSelected = false;
		_pieceSelected = nullptr;
	}
}