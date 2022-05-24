/*
  Partie du programme qui sert pour la pièce d'échecs
  de type « Tour ».

  file   Rook.h
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#pragma once
#include "Piece.h"

namespace pieceEchiquier {
	class Tour : public Piece
	{
	public:
		Tour(int x = 0, int y = 0, bool isWhite = true);
		bool isMoveValid(Piece* piece, int xToGo, int yToGo) override;
	};
}
