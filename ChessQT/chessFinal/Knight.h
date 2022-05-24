/*
  Partie du programme qui sert pour la pi�ce d'�checs
  de type � Cavalier �.

  file   Knight.h
  author L�gar� et Ozirska
  date   6 mai 2022
  Cr�� le 12 avril 2022
*/

#pragma once

#include "Piece.h"

namespace pieceEchiquier {
	class Cavalier : public Piece
	{
	public:
		Cavalier(int x = 0, int y = 0, bool isWhite = true);
		bool isMoveValid(Piece* piece, int xToGo, int yToGo) override;
	};
}