#include <graphics.h>
#include <stdio.h>
#include <conio.h>

#define NUM 7
#define LEFT 180
#define TOP 40
#define BOTTOM 250
#define reWidth 60
#define toLeft 0
#define toRight 1

#define WIDTH LEFT * 2 + (NUM * 2 + 1) * reWidth
#define HIGH TOP + BOTTOM + 5 * reWidth
#define CARDPOS TOP + 5 * reWidth + 80

struct Position
{
	int posX;
	int posY;
};

struct cardPlay
{
	int posX;
	int posY;
	bool isUsed;
	bool isSelected;
};

struct usedCard
{
	int posX;
	int posY;
	int usedCardNo;
	bool isSelected;
};

enum cardNo {Two,Three,Fore,Five,Six,Severn,Eight,Nine,Ten,J,Q,K,One};

IMAGE chess_img,chessBK_img;
IMAGE cards_img,cardsBK_img;
IMAGE BK_img;
int chessWidth, chessHigh;
Position chessPos1,chessPos2,chessPos3;
Position pCardsPos[13];   //Card position in picture
usedCard cardPos1[3], cardPos2[3]; //cards position in the left or right
Position mousePos;
cardPlay cardPlay_one[13], cardPlay_two[13];  //cards position in the play windows
int selectedCard = -1;
int selectedBox = -1;
bool closeCard1, closeCard2, battle;
int changeBox[3];
int playFlag;

int cardWidth, cardHigh;
int cardsPos;
void init(void);
void updateWithInput(void);
void updateWithoutInput(void);
void show(void);
void drawMap(void);
void endGame(void);
void drawCards(void);
void drawCardsBK(void);
void drawCardsBK1(void);
void drawCardsBK2(void);
void drawCardsBK3(void);
void initCards(void);
void checkMousePos(cardPlay *plays, usedCard *cardPos);
void drawCards2(void);
void mouseRec(void);
void showCards(void);
void showCards2(void);
void battleCheck(void);
void chessChangePos(void);


int main()
{
	init();
	while (1)
	{
		show();
		updateWithInput();
		updateWithoutInput();

		Sleep(10);
	}
	
	getchar();
	endGame();
	return 0;
}

void init(void)
{
	cardHigh = 102;
	cardWidth = 69;
	/*cardHigh = 96;
	cardWidth = 62;*/ 
	cardsPos = WIDTH - (12 * 46 + cardWidth);
	initgraph(WIDTH, HIGH);	
	chessWidth = 28;
	chessHigh = 60;

	chessPos1.posX = LEFT + (NUM * 2 + 1) * reWidth/2 - 12 ;
	chessPos1.posY = TOP - 2;
	chessPos2.posX = LEFT + (NUM * 2 + 1) * reWidth / 2 - 12;
	chessPos2.posY = TOP - 2 + reWidth * 2;
	chessPos3.posX = LEFT + (NUM * 2 + 1) * reWidth / 2 - 12;
	chessPos3.posY = TOP - 2 + reWidth * 4;

	initCards();
	closeCard1 = false;
	closeCard2 = false;
	battle = false;
	playFlag = 1;
	for (int i = 0; i < 3; i++)
	{
		changeBox[i] = 0;
	}
	loadimage(&chess_img,"..\\resource\\chess.png");
	loadimage(&chessBK_img, "..\\resource\\chessBK.png");
	//loadimage(&cards_img,"E:\\vs2017\\Cゲーム\\senrekuTest\\resource\\cards.png",886,402,true);
	loadimage(&cards_img, "..\\resource\\card3.png");
	loadimage(&cardsBK_img, "..\\resource\\cardBk2.png");
	//loadimage(&BK_img, "E:\\vs2017\\Cゲーム\\senrekuTest\\resource\\BK.jpg", WIDTH, HIGH, true);
	//putimage(0, 0, WIDTH, HIGH, &BK_img, 0, 0);	
	BeginBatchDraw();
}

void updateWithInput(void)
{
	char input;
	mouseRec();
	if (_kbhit())
	{
		input = getchar();
		if (input == 'A' || input == 'a')
		{
			closeCard1 = true;
		}
		else if (input == 'K' || input == 'k')
		{
			closeCard2 = true;
		}
		else if (input == 'B' || input == 'b')
		{
			closeCard1 = false;
			closeCard2 = false;
			showCards();
			showCards2();
			chessChangePos();
		}
		else if (input == 'R' || input == 'r')
		{
			battle = true;
		}
	}
}

void updateWithoutInput()
{
	if (battle == true)
	{
		setfillcolor(BLACK);
		//the place of left or right
		for (int i = 0; i < 3; i++)
		{
			solidrectangle(cardPos1[i].posX, cardPos1[i].posY, cardPos1[i].posX + cardWidth, cardPos1[i].posY + cardHigh);
			solidrectangle(cardPos2[i].posX, cardPos2[i].posY, cardPos2[i].posX + cardWidth, cardPos2[i].posY + cardHigh);
		}
		battle = false;
	}
	if (chessPos1.posX <= LEFT)
	{
		chessPos1.posX = LEFT + reWidth / 2;
	}
	if (chessPos1.posX >= WIDTH - LEFT)
	{
		chessPos1.posX = WIDTH - LEFT - reWidth / 2;
	}
	if (chessPos2.posX <= LEFT)
	{
		chessPos2.posX = LEFT + reWidth / 2;
	}
	if (chessPos2.posX >= WIDTH - LEFT)
	{
		chessPos2.posX = WIDTH - LEFT - reWidth / 2;
	}
	if (chessPos3.posX <= LEFT)
	{
		chessPos3.posX = LEFT + reWidth / 2;
	}
	if (chessPos3.posX >= WIDTH - LEFT)
	{
		chessPos3.posX = WIDTH - LEFT - reWidth / 2;
	}
}

void show()
{
	drawMap();
	//the image of chess
	putimage(chessPos1.posX, chessPos1.posY, chessWidth, chessHigh, &chessBK_img, 0, 0, NOTSRCERASE);
	putimage(chessPos1.posX, chessPos1.posY, chessWidth, chessHigh, &chess_img, 0,0, SRCINVERT);
	putimage(chessPos2.posX, chessPos2.posY, chessWidth, chessHigh, &chessBK_img, 0, 0, NOTSRCERASE);
	putimage(chessPos2.posX, chessPos2.posY, chessWidth, chessHigh, &chess_img, 0, 0, SRCINVERT);
	putimage(chessPos3.posX, chessPos3.posY, chessWidth, chessHigh, &chessBK_img, 0, 0, NOTSRCERASE);
	putimage(chessPos3.posX, chessPos3.posY, chessWidth, chessHigh, &chess_img, 0, 0, SRCINVERT);

	drawCards();
	drawCards2();
	drawCardsBK1();	
	if (closeCard1)
	{
		drawCards();
		drawCardsBK();
		drawCardsBK2();
		playFlag = 2;
		
	}
	if (closeCard2)
	{
		drawCardsBK1();
		drawCardsBK3();
		playFlag = 1;
	}

	//putimage(40, 30, 35, 50, &cards_img, 70, 0);
	FlushBatchDraw();
}

void drawMap(void)
{
	setlinecolor(WHITE);
	rectangle(LEFT, TOP, LEFT + (NUM * 2 + 1) * reWidth, TOP + 5 * reWidth + 1);
	int high = TOP;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < (NUM * 2 + 1); x++)
		{
			if (x == 0 || x == NUM * 2)
			{
				setfillcolor(RED);
			}
			else if (x == NUM)
			{
				setfillcolor(GREEN);
			}
			else
			{
				setfillcolor(((x % 2) == 1) ? YELLOW : WHITE);
				//solidrectangle(LEFT, TOP, LEFT + x * reWidth, reWidth + TOP);
			}
			solidrectangle(LEFT + x * reWidth, high + 1, LEFT + (x + 1) * reWidth, reWidth + high);
		}
		rectangle(LEFT, high, LEFT + (NUM * 2 + 1) * reWidth, reWidth + high + 1);
		high += reWidth * 2;
	}

	
}

void endGame(void)
{
	EndBatchDraw();
	closegraph();
}

void initCards(void)
{
	/*pCardsPos[0].posX = 0;
	pCardsPos[0].posY = cardHigh;*/
	for (int i = 0; i < 13; i++)
	{
		/*pCardsPos[i].posX = cardWidth * i + i * 6;
		pCardsPos[i].posY = cardHigh;*/
		pCardsPos[i].posX = cardWidth * i + i;   
		pCardsPos[i].posY = 0;

		cardPlay_one[i].posX = i * 46;
		cardPlay_one[i].posY = CARDPOS;
		cardPlay_one[i].isUsed = false;
		cardPlay_one[i].isSelected = false;

		cardPlay_two[i].posX = cardsPos + i * 46;
		cardPlay_two[i].posY = CARDPOS;
		cardPlay_two[i].isUsed = false;
		cardPlay_two[i].isSelected = false;
	}

	for (int i = 0; i < 3; i++)
	{
		cardPos1[i].posX = LEFT - cardWidth - 20;
		cardPos1[i].posY =TOP + reWidth * 2 * i -4;
		cardPos1[i].usedCardNo = -1;
		cardPos1[i].isSelected = false;

		cardPos2[i].posX = 1100;
		cardPos2[i].posY =TOP + reWidth * 2 * i - 4;
		cardPos2[i].usedCardNo = -1;
		cardPos2[i].isSelected = false;
		//rectangle(cardPos1[i].posX, cardPos1[i].posY, cardPos1[i].posX+ cardWidth, cardPos1[i].posY+ cardHigh);
	}
	
}
void drawCards(void)
{
	for (int i = 0; i < 13; i++)
	{
		if (cardPlay_one[i].isUsed == false)
		{
			putimage(cardPlay_one[i].posX, cardPlay_one[i].posY, cardWidth, cardHigh, &cards_img, pCardsPos[i].posX, pCardsPos[i].posY);
		}
		if (cardPlay_two[i].isUsed == false)
		{
			putimage(cardPlay_two[i].posX, cardPlay_two[i].posY, cardWidth, cardHigh, &cards_img, pCardsPos[i].posX, pCardsPos[i].posY);
		}
		
		//putimage(cardsPos + i *40, CARDPOS, cardWidth + 1, cardHigh + 3, &cards_img, pCardsPos[i].posX, pCardsPos[i].posY);
	}

	
	//the place of left or right
	for (int i = 0; i < 3; i++)
	{
		rectangle(cardPos1[i].posX, cardPos1[i].posY, cardPos1[i].posX + cardWidth, cardPos1[i].posY + cardHigh);
		rectangle(cardPos2[i].posX, cardPos2[i].posY, cardPos2[i].posX + cardWidth, cardPos2[i].posY + cardHigh);
	}
	//setcolor(RED);
	//solidrectangle(550, 320, 600, 360);
}

void drawCardsBK(void)
{
	for (int i = 0; i < 13; i++)
	{
		//putimage(i * 40, CARDPOS, 64, 96, &cardsBK_img, 0, 0);
		putimage(cardPlay_one[i].posX, cardPlay_one[i].posY, cardWidth , cardHigh , &cardsBK_img, 0, 0);
	}

}
void drawCardsBK1(void)
{
	for (int i = 0; i < 13; i++)
	{
		//putimage(i * 40, CARDPOS, 64, 96, &cardsBK_img, 0, 0);
		putimage(cardPlay_two[i].posX, cardPlay_two[i].posY, cardWidth , cardHigh , &cardsBK_img, 0, 0);
	}

}
void drawCardsBK2(void)
{
	for (int i = 0; i < 3; i++)
	{
		//putimage(i * 40, CARDPOS, 64, 96, &cardsBK_img, 0, 0);
		putimage(cardPos1[i].posX, cardPos1[i].posY, cardWidth , cardHigh , &cardsBK_img, 0, 0);
		cardPlay_one[cardPos1[i].usedCardNo].isUsed = true;
		//change the used card light
	}

}
void drawCardsBK3(void)
{
	for (int i = 0; i < 3; i++)
	{
		//putimage(i * 40, CARDPOS, 64, 96, &cardsBK_img, 0, 0);
		putimage(cardPos2[i].posX, cardPos2[i].posY, cardWidth , cardHigh , &cardsBK_img, 0, 0);
		cardPlay_two[cardPos2[i].usedCardNo].isUsed = true;
		//change the used card light
	}

}

void mouseRec(void)
{
	MOUSEMSG m;		
	while (MouseHit())  
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) 
		{
			mousePos.posX = m.x;
			mousePos.posY = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (playFlag == 1)
			{
				checkMousePos(cardPlay_one, cardPos1);
			}
			if (playFlag == 2)
			{
				checkMousePos(cardPlay_two, cardPos2);
			}			
			
		}
	}
}

void checkMousePos(cardPlay *plays , usedCard *cardPos)
{
	//if in the rec of card
	for (int i = 0; i < 13; i++)
	{
		//selected the card
		if (mousePos.posX >= plays[i].posX && mousePos.posX <= (plays[i].posX + 46)
			&& mousePos.posY >= plays[i].posY && mousePos.posY <= (plays[i].posY + cardHigh)
			&& plays[i].isUsed == false && plays[i].isSelected == false)
		{
			if (selectedCard == -1)
			{
				selectedCard = i;			
			}
			else
			{
				plays[selectedCard].isSelected = false;
				selectedCard = i;
			}
			plays[i].isSelected = true;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (mousePos.posX >= cardPos[i].posX && mousePos.posX <= (cardPos[i].posX + 46)
			&& mousePos.posY >= cardPos[i].posY &&  mousePos.posY <= (cardPos[i].posY + cardHigh))
		{
			//if (cardPos[i].isSelected == false)
			//{

				/*if (selectedBox != i && selectedBox != -1)
				{
					cardPos[selectedBox].isSelected = false;

				}*/
			cardPos[i].isSelected = true;
			selectedBox = i;
			//}						
		}
	}

}


void chessChangePos(void)
{
	battleCheck();
	chessPos1.posX += reWidth * changeBox[0];
	chessPos2.posX += reWidth * changeBox[1];
	chessPos3.posX += reWidth * changeBox[2];
	
}

void drawCards2(void)
{
	//if the card selected
	if (selectedCard != -1 )
	{
		//the card change light

		//if the box be selected and the card selected draw the card in the box
		if (selectedBox != -1)
		{
			if (playFlag == 1) {
			//has been selected
			if (cardPos1[selectedBox].isSelected == true)
			{
				//reset the attribute of the cards
				cardPlay_one[cardPos1[selectedBox].usedCardNo].isSelected = false;
			}
			putimage(cardPos1[selectedBox].posX, cardPos1[selectedBox].posY, cardWidth , cardHigh , &cards_img, pCardsPos[selectedCard].posX, pCardsPos[selectedCard].posY);
			cardPos1[selectedBox].usedCardNo = selectedCard;
			selectedCard = -1;
			selectedBox = -1;
			}
			if (playFlag == 2) {
				//has been selected
				if (cardPos2[selectedBox].isSelected == true)
				{
					//reset the attribute of the cards
					cardPlay_one[cardPos2[selectedBox].usedCardNo].isSelected = false;
				}
				putimage(cardPos2[selectedBox].posX, cardPos2[selectedBox].posY, cardWidth, cardHigh, &cards_img, pCardsPos[selectedCard].posX, pCardsPos[selectedCard].posY);
				cardPos2[selectedBox].usedCardNo = selectedCard;
				selectedCard = -1;
				selectedBox = -1;
			}
		}
	}
}

void showCards(void)
{
	for (int i = 0; i < 3; i++)
	{
		//putimage(i * 40, CARDPOS, 64, 96, &cardsBK_img, 0, 0);
		putimage(cardPos1[i].posX, cardPos1[i].posY, cardWidth , cardHigh , &cards_img, pCardsPos[cardPos1[i].usedCardNo].posX, pCardsPos[cardPos1[i].usedCardNo].posY);
	}

}

void showCards2(void)
{
	for (int i = 0; i < 3; i++)
	{
		//putimage(i * 40, CARDPOS, 64, 96, &cardsBK_img, 0, 0);
		putimage(cardPos2[i].posX, cardPos2[i].posY, cardWidth, cardHigh , &cards_img, pCardsPos[cardPos2[i].usedCardNo].posX, pCardsPos[cardPos2[i].usedCardNo].posY);
	}

}

void battleCheck(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (cardPos2[i].usedCardNo != -1 && cardPos1[i].usedCardNo != -1)
		{
			if ((cardPos1[i].usedCardNo - cardPos2[i].usedCardNo) < 7 
				&& (cardPos1[i].usedCardNo - cardPos2[i].usedCardNo) > -7)
			{
				changeBox[i] = cardPos1[i].usedCardNo - cardPos2[i].usedCardNo;
			}
			else if((cardPos1[i].usedCardNo - cardPos2[i].usedCardNo) >= 7)
				changeBox[i] = 1;
			else if((cardPos1[i].usedCardNo - cardPos2[i].usedCardNo) <= -7)
				changeBox[i] = -1;
		}	
	}
}