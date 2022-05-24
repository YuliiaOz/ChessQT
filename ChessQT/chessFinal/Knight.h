/*
  Partie du programme qui sert pour la pièce d'échecs
  de type « Cavalier ».

  file   Knight.h
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
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