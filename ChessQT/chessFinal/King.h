/*
  Partie du programme qui sert pour la pi�ce d'�checs
  de type � Roi �.

  file   King.h
  author L�gar� et Ozirska
  date   6 mai 2022
  Cr�� le 12 avril 2022
*/

#pragma once

#include "Piece.h"

namespace pieceEchiquier {
	class Roi : public Piece
	{
	public:
		Roi(int x = 0, int y = 0, bool isWhite = true);
		bool isMoveValid(Piece* piece, int xToGo, int yToGo) override;
		int getNKing();
		static int _nKing;
	};
}