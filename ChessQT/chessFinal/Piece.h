/*
  Sert � g�rer les pi�ces d'�chec du jeu en
  g�n�ral. 

  file   Piece.h
  author L�gar� et Ozirska
  date   6 mai 2022
  Cr�� le 12 avril 2022
*/

#pragma once

#include <string>
#include <iostream>

#include <QString>
#include <QIcon>

class Piece
{
public:
	Piece(int x = 0, int y = 0, bool isWhite = true);
	virtual ~Piece();

	QIcon getQIcon();
	QString getName();

	int getXCoordinate();
	int getYCoordinate();

	void setXCordinates(int newCoordinates);
	void setYCordinates(int newCoordinates);

	bool getColor();
	virtual bool isMoveValid(Piece* piece, int xToGo, int yToGo) = 0;
	void showCoordinates();

protected:
	QIcon _icon;
	QString _name;
	int _pCoordinates[2];
	bool _isWhite;
};