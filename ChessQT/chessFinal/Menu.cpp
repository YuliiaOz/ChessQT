/*
  Sert à gérer le menu principal du jeu (dans lequel
  apparaissent trois options de départ). 

  file   Menu.cpp
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#include "Menu.h"

Menu::Menu(Board* board)
{
	_board = board;

	QGroupBox* groupBox = new QGroupBox; 
	groupBox->setFixedSize(600, 410);

	QLabel* title = new QLabel;
	title->setText("ECHECS");
	title->setStyleSheet("font-weight: bold;");
	title->setStyleSheet("QLabel{font-size: 31pt;}");
	title->setFixedSize(200, 50);

	QLabel* names = new QLabel;
	names->setText("Par : \nJulien Légaré\nYulia Ozirska");
	names->setStyleSheet("QLabel{font-size: 7pt;}");
	names->setFixedSize(100, 45);

	QGridLayout* buttons = new QGridLayout;
	buttons->setVerticalSpacing(25);
	buttons->setHorizontalSpacing(0);

	buttons->addWidget(title, 0, 1);
	buttons->addWidget(names, 0, 2);

	QPushButton* button1 = new QPushButton("Option 1");
	button1->setFixedSize(100, 100);
	connect(button1, SIGNAL(clicked()), this, SLOT(createBoard1()));

	QPushButton* button2 = new QPushButton("Option 2");
	button2->setFixedSize(100, 100);
	connect(button2, SIGNAL(clicked()), this, SLOT(createBoard2()));

	QPushButton* button3 = new QPushButton("Option 3");
	button3->setFixedSize(100, 100);
	connect(button3, SIGNAL(clicked()), this, SLOT(createBoard3()));

	buttons->addWidget(button1, 1, 0);
	_buttonList[0] = button1;
	buttons->addWidget(button2, 1, 1);
	_buttonList[1] = button2;
	buttons->addWidget(button3, 1, 2);
	_buttonList[2] = button3;

	_labelList[0] = createLabel("Tour des noirs\n\nRoi blanc en 0, 0\nCavalier blanc en 1, 0\nRoi noir en 7, 7\nRoi noir en 5, 5\nTour noire en 6, 7");
	_labelList[1] = createLabel("Tour des blancs\n\nRoi blanc en 0, 0\nRoi noir en 7, 7\nTour noire en 7, 1\nTour noire en 1, 7");
	_labelList[2] = createLabel("Tour des noirs\n\nRoi blanc en 0, 7\nRoi noir en 2, 5\nTour noire en 0, 0\nCavalier noir en 5, 7");

	buttons->addWidget(_labelList[0], 2, 0);
	buttons->addWidget(_labelList[1], 2, 1);
	buttons->addWidget(_labelList[2], 2, 2);

	groupBox->setLayout(buttons);
	groupBox->show();

	QObject::connect(_board->getButton(), &QPushButton::clicked, this, [this]() {this->resetPartie(); });

	_box = groupBox;
}

QLabel* Menu::createLabel(QString string)
{
	QLabel* label = new QLabel;
	label->setFixedSize(200, 125);
	label->setText(string);

	return label;
}

void Menu::createBoard1()
{
	_box->close();
	_board->setTurn(false);
	_board->getSpace()->setText("Tour des noirs");

	Tour* Tour1 = new Tour(7, 6, false);
	Cavalier* cavalier = new Cavalier(0, 1, true);

	try {
		Roi* roi = new Roi(0, 0, true);
		_board->setPiece(roi);

		Roi* roi2 = new Roi(7, 7, false);
		_board->setPiece(roi2);

		Roi* roi3 = new Roi(5, 5, true);
		_board->setPiece(roi3);
	}
	catch (int myNumber) {
		std::cout << "Trop de Roi, pas plus que 2 instanciations possibles!\n";
		std::cout << "Vous avez déjà " << myNumber << " Rois" << std::endl;
	}

	_board->setPiece(Tour1);
	_board->setPiece(cavalier);
	_board->getBox()->show();
}


void Menu::createBoard2()
{
	_box->close();
	_board->setTurn(true);
	_board->getSpace()->setText("Tour des blancs");

	Tour* Tour2 = new Tour(7, 1, false);
	Tour* Tour3 = new Tour(1, 7, false);
	Roi* roi = new Roi(0, 0, true);	
	Roi* roi2 = new Roi(7, 7, false);

	_board->setPiece(roi2);
	_board->setPiece(roi);
	_board->setPiece(Tour3);
	_board->setPiece(Tour2);

	_board->getBox()->show();
}

void Menu::createBoard3()
{
	_box->close();
	_board->setTurn(false);
	_board->getSpace()->setText("Tour des noirs");

	Cavalier* fou = new Cavalier(5, 7, false);
	Tour* Tour1 = new Tour(0, 0, false);

	Roi* roi2 = new Roi(2, 5, false);
	Roi* roi = new Roi(0, 7, true);

	_board->setPiece(roi);
	_board->setPiece(roi2);
	_board->setPiece(Tour1);
	_board->setPiece(fou);

	_board->getBox()->show();
}


void Menu::resetPartie()
{
	_board->getBox()->close();
	Roi::_nKing = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_board->getElementsList(i, j)->getSquareButton()->setIcon(QIcon());

			if (_board->getElementsList(i, j)->getPiece() != nullptr) {
				bool isPieceWhiteKing = _board->getElementsList(i, j)->getPiece()->getName().toStdString() == "Roi blanc";
				bool isPieceBlackKing = _board->getElementsList(i, j)->getPiece()->getName().toStdString() == "Roi noir";
				if (isPieceWhiteKing || isPieceBlackKing) {
					Roi* roi;
					roi = dynamic_cast<Roi*> (_board->getElementsList(i, j)->getPiece());
					roi->_nKing -= roi->_nKing;
				}
				delete _board->getElementsList(i, j)->getPiece();
				_board->getElementsList(i, j)->setPiece(nullptr);
			}

		}
	}
	_box->show();
}

void Menu::quitApplication()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete _board->getElementsList(i, j)->getPiece(); // Delete des pieces* de square
			delete _board->getElementsList(i, j)->getSquareButton(); // Delete des QPushButtons* de squares
			delete _board->getElementsList(i, j); // Delete les squares
		}
	}

	for (int i = 0; i < 3; i++) {
		delete _labelList[i];
		delete _buttonList[i];
	}

	delete _board->getButton(); // delete du bouton reset
	delete _board->getGrid(); // delete du QGridLayout*
	delete _board->getBox(); // delete du QBoxLayout*

	delete _box;
	delete _board; // delete du new Board dans le main
	delete this; // delete du new Menu dans le main
}

Board* Menu::getBoard() { return _board; }
QGroupBox* Menu::getBox() { return _box; }