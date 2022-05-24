/*
  Sert à gérer l'affichage du l'échiquier.

  file   Board.h
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#pragma once
#include <QObject>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>

#include <iostream>

#include "Square.h"
#include "Knight.h"
#include "Rook.h"
#include "Piece.h"


namespace raii {
	template <typename P>
	class GestionPiece {
	public:
		GestionPiece(P piece) : clean_{ piece } {}
		~GestionPiece();
	private:
		P clean_;
	};
}

template <typename P>
raii::GestionPiece<P> supprimer(P piece);

namespace affichage {
	using raii::GestionPiece;
	class Board : public QObject
	{
		Q_OBJECT
	public:
		Board(int x = 0, int y = 0);

		Square* getElementsList(int i, int j);
		QPushButton* getButton();
		QGroupBox* getBox();
		QLabel* getSpace();
		QLabel* getErrorMessage();
		QGridLayout* getGrid();

		void movePiece(Piece* piece, int xToGo, int yToGo);
		void deletePiece(Piece* piece);
		void setPiece(Piece* piece);
		void setTurn(bool turn);
		bool checkForJump(Piece* piece, int xToGo, int yToGo);
		bool checkColor(Piece* pieceToGo, Piece* pieceOnSquare);
		bool checkForEchecPiece(Piece* piece);
		bool checkForEchecBoard(Piece* piece, int x, int y);

	signals:
		void clicked();

	public slots:
		void selectPiece();

	private:
		bool _isPieceSelected;
		Piece* _pieceSelected;
		bool _turn;
		Square* list[8][8];
		QGridLayout* _grid;
		QGroupBox* _box;
		QPushButton* _resetButton;
		QLabel* _space;
		QLabel* _errorMessage;
	};
}
