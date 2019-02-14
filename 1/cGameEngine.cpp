#include "stdafx.h"




	deck::deck() {
		Shuffle();
		srand(static_cast<unsigned int>(time(NULL)));
	}

	void deck::Shuffle() {
		for (int i = 0; i < 52; i++) d[i] = 1;
		cleft = 52;
	}

	card deck::CardDraw() {
		card x = { -1,-1 };

		if (cleft > 0) {
			int k = rand() % cleft;
			int c = 0;
			int i;
			for (i = 0; i < 52; i++) {
				if (d[i] == 1) {
					if (c == k)break;
					else c++;
				}
			}
			d[i] = 0;
			cleft--;
			x.f = (i / 4) + 2;
			x.c = i % 4;
		}
		return x;
	}

	
	void cGameEngine::UpdateUserGD() {
		hGD->dealer = sGD.dealer;
		hGD->eGS = sGD.eGS;
		hGD->eSS = sGD.eSS;
		hGD->actual = sGD.actual;
		hGD->stack = sGD.stack;
		hGD->maxbet = sGD.maxbet;
		hGD->blind = sGD.blind;
		for (int i = 0; i < 3; i++) hGD->flop[i] = sGD.flop[i];
		hGD->turn = sGD.turn;
		hGD->river = sGD.river;
		hGD->winner = sGD.winner;
		for (int i = 0; i < 10; i++) {
			hGD->player[i].allin = sGD.player[i].allin;
			hGD->player[i].bet = sGD.player[i].bet;
			hGD->player[i].card1 = sGD.player[i].card1;
			hGD->player[i].card2 = sGD.player[i].card2;
			if (sGD.showdown == 0 && sGD.player[i].ingame == 1 && sGD.player[i].fold == 0 && sGD.player[i].human == 0 && sGD.player[i].card1.f) {
				hGD->player[i].card1 = { 1,1 };
				hGD->player[i].card2 = { 1,1 };
			}
			///////////////////////////////////////////////////
			//hGD->player[i].card1 = sGD.player[i].card1;
			//hGD->player[i].card2 = sGD.player[i].card2;
			///////////////////debug//////////////////////
			hGD->player[i].totalbet = sGD.player[i].totalbet;
			hGD->player[i].value = sGD.player[i].value;
			hGD->player[i].check = sGD.player[i].check;
			hGD->player[i].fold = sGD.player[i].fold;
			hGD->player[i].winner = sGD.player[i].winner;
			hGD->player[i].ingame = sGD.player[i].ingame;
			hGD->player[i].raise = sGD.player[i].raise;
			hGD->player[i].stack = sGD.player[i].stack;
			hGD->player[i].human = sGD.player[i].human;
		}

		if (sGD.showdown)
		{
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].ingame == 1 && sGD.player[i].fold == 0)
				{
					hGD->player[i].card1 = sGD.player[i].card1;
					hGD->player[i].card2 = sGD.player[i].card2;
				}
		}
	}


	//returns an sValue object for ccc player
	sValue cGameEngine::ValueCalculate(int ccc)
	{
		///load temp
		card ctab[7];
		card temp;
		sValue result = { 0,0,0,0 };
		bool mask[7] = { 1,1,1,1,1,1,1 };
		int kicker = 0;
		int highcard = 0;
		int highcard2 = 0;
		int lowcard = 0;
		bool colour = 0;
		bool strit = 0;
		bool flush = 0;
		bool poker = 0;
		bool pair = 0, three = 0, dpair = 0, caret = 0, fullhouse = 0;
		int counter = 0;
		ctab[0] = sGD.player[ccc].card1;
		ctab[1] = sGD.player[ccc].card2;
		ctab[2] = sGD.flop[0];
		ctab[3] = sGD.flop[1];
		ctab[4] = sGD.flop[2];
		ctab[5] = sGD.turn;
		ctab[6] = sGD.river;


		//segregation
		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 6; i++)
			{
				if (ctab[i].f > ctab[i + 1].f)
				{
					temp = ctab[i];
					ctab[i] = ctab[i + 1];
					ctab[i + 1] = temp;
				}
			}
		}

		//colour check
		for (int j = 0; j < 4; j++)
		{
			counter = 0;
			for (int i = 0; i < 7; i++)
			{
				if (ctab[i].c == j)
				{
					counter++;
					if (counter >= 5)
					{
						highcard = ctab[i].f;
						colour = 1;
					}
				}
			}
		}

		//flushcheck
		counter = 0;
		if (ctab[6].f == 14 && ctab[0].f == 2)counter++;

		for (int i = 0; i < 6; i++)
		{
			if (ctab[i + 1].f - ctab[i].f == 1)
			{
				counter++;
				if (counter >= 4)
				{
					highcard = ctab[i + 1].f;
					flush = 1;
				}
			}
			else if (ctab[i + 1].f - ctab[i].f == 0);
			else counter = 0;
		}

		//paircheck

		counter = 0;
		for (int i = 0; i < 6; i++)
		{

			if (ctab[i + 1].f == ctab[i].f)
			{
				counter++;
				highcard2 = ctab[i + 1].f;

			}
			if (i == 5 || ctab[i + 1].f != ctab[i].f)
			{

				if (counter == 3)
				{
					caret = 1;
					break;
				}
				else if (counter == 2)three = 1;

				else if (counter == 1 && pair == 1)dpair = 1;

				else if (counter == 1)pair = 1;

				counter = 0;
			}
		}

		// combinations
		if (colour&&flush)poker = 1;
		if (pair&&three)
		{
			fullhouse = 1;
			pair = 0;
			three = 0;
			dpair = 0;
		};

		//kicker

		if (pair || dpair || three)
		{
			int counter2;
			if (dpair || three)counter2 = 2;
			else if (pair)counter2 = 1;
			counter = 0;

			for (int i = 6; i > 0; i--)
			{
				if (counter2 == 0) { kicker = ctab[i].f; break; }
				if (ctab[i - 1].f == ctab[i].f)
					counter++;
				else if (counter == 0) { kicker = ctab[i].f; break; }
				else
				{
					counter = 0;
					counter2--;
				}
			}
		}


		//lowcard
		if (dpair || fullhouse)
		{
			int counter2;
			if (fullhouse)counter2 = 3;
			else if (dpair)counter2 = 2;
			counter = 0;

			for (int i = 6; i >= 0; i--)
			{
				if (counter == counter2) { lowcard = ctab[i].f; break; }
				if (i)if (ctab[i - 1].f == ctab[i].f)
					counter++;
			}
		}

		// highest combination seeking
		if (poker) result = { 8,highcard,0,0 };
		else if (caret) result = { 7,highcard2,0,0 };
		else if (fullhouse) result = { 6,highcard2,lowcard,0 };
		else if (colour) result = { 5,highcard,0,0 };
		else if (flush) result = { 4,highcard,0,0 };
		else if (three) result = { 3,highcard2,0,kicker };
		else if (dpair) result = { 2,highcard2,lowcard,kicker };
		else if (pair) result = { 1,highcard2,0,kicker };
		else
		{
			highcard = ctab[6].f;
			result = { 0,highcard,0,0 };
		}
		return result;
	}

	//card1,fold,dealer,actual of all
	int cGameEngine::DealerRoll()
	{
		sGD.dealer = hGD->dealer = -1;
		for (int i = 0; i < 10; i++)
		{
			if (sGD.player[i].fold == 0 && sGD.player[i].ingame == 1)sGD.player[i].card1 = hDeck->CardDraw();
			else sGD.player[i].card1 = { 0,0 };
		}
		int max = 0;
		for (int i = 0; i < 10; i++)
		{
			if (sGD.player[i].fold == 0 && sGD.player[i].ingame == 1)
				if (sGD.player[i].card1.f > max)max = sGD.player[i].card1.f;
		}
		int winner = 0;
		for (int i = 0; i < 10; i++)
		{
			if (sGD.player[i].fold == 0 && sGD.player[i].ingame == 1)
				if (sGD.player[i].card1.f == max)winner++;
				else
				{
					sGD.player[i].fold = 1;
				}
		}
		if (winner == 1)
		{
			for (int i = 0; i < 10; i++)
			{
				if (sGD.player[i].fold == 0 && sGD.player[i].ingame == 1)
					if (sGD.player[i].card1.f == max)
						sGD.dealer = sGD.actual = sGD.blindinc = i;
			}
			return 1;
		}
		return 0;
	}

	///card1,card2 of all
	void cGameEngine::HandFill()
	{
		for (int i = 0; i < 10; i++)
		{
			if (sGD.player[i].ingame == 1)
			{
				sGD.player[i].card1 = hDeck->CardDraw();
				sGD.player[i].card2 = hDeck->CardDraw();
				/////////////////debug/////////////////////
				//sGD.player[i].card1 = debug1[i];
				//sGD.player[i].card2 = debug2[i];
				////////////////////////////////////////
			}
			else
			{
				sGD.player[i].card1 = { 0,0 };
				sGD.player[i].card2 = { 0,0 };
			}
		}
	}

	///fold of all
	void cGameEngine::FoldReset()
	{
		for (int i = 0; i < 10; i++)sGD.player[i].fold = 0;
	}
	///fold of all
	void cGameEngine::AllinReset()
	{
		for (int i = 0; i < 10; i++)sGD.player[i].allin = 0;
	}

	////check of all
	void cGameEngine::CheckReset()
	{
		for (int i = 0; i < 10; i++)sGD.player[i].check = 0;

	}

	///all
	cGameEngine::cGameEngine(sInitData k, sGameData* s)
	{
		hGD = s;
		hDeck = new deck;
		sGD.eGS = GS_DEALER;
		sGD.eSS = SS_INIT;
		nextGS = GS_DEALER;
		bool changeGS = 0;

		sGD.actual = 0;
		sGD.stack = 0;
		sGD.maxbet = 0;

		iteration = 0;
		sGD.blind = cBlind::getblind();
		sGD.showdown = 0;
		sGD.winner = -1;
		for (int i = 0; i < 10; i++)
		{
			sGD.player[i].allin = 0;
			sGD.player[i].bet = 0;
			sGD.player[i].totalbet = 0;
			sGD.player[i].card1.f = 0;
			sGD.player[i].card1.c = 0;
			sGD.player[i].card2.f = 0;
			sGD.player[i].card2.c = 0;
			sGD.player[i].check = 0;
			sGD.player[i].fold = 0;
			sGD.player[i].winner = 0;
			sGD.player[i].ingame = 1;
			sGD.player[i].raise = 0;
			sGD.player[i].value = { 0,0,0,0 };
			sGD.player[i].stack = k.stack;
			sGD.player[i].human = k.human[i];
			///////////////////debug//////////////////////////////
			//sGD.player[0].ingame = sGD.player[2].ingame = sGD.player[3].ingame = sGD.player[5].ingame = 0;
			//sGD.player[i].stack = i * 100+100;
			//sGD.player[i].human = 1;
			////////////////////////////////////////////////////
		}
		if (k.players == 6)
		{
			sGD.player[1].ingame = 0;
			sGD.player[4].ingame = 0;
			sGD.player[6].ingame = 0;
			sGD.player[9].ingame = 0;
		}
		UpdateUserGD();
	}

	///actual
	int cGameEngine::BiddingCheck()
	{
		//0-gramy dalej, 1-licytacja skonczona
		int result = 0;
		if (!sGD.showdown)
		{


			int playersleft = 0;
			int allinplayers = 0;
			for (int i = 0; i < 10; i++)
			{
				if (sGD.player[i].ingame == 1 && sGD.player[i].fold == 0 && sGD.player[i].allin == 0) playersleft++;
				if (sGD.player[i].allin == 1)allinplayers++;
			}

			if (playersleft + allinplayers == 1) result = 2;

			else
			{
				do
				{
					sGD.actual++;
					if (sGD.actual >= 10)sGD.actual = 0;
					if (sGD.actual == hGD->actual)
					{
						result = 1;
						break;
					}
				} while (!(sGD.player[sGD.actual].ingame == 1 && sGD.player[sGD.actual].fold == 0 && sGD.player[sGD.actual].allin == 0));
				if (sGD.player[sGD.actual].bet == sGD.maxbet&&sGD.maxbet > 0 && sGD.player[sGD.actual].raise == 1)result = 1;
				if (sGD.player[sGD.actual].bet == sGD.maxbet&& sGD.player[sGD.actual].check == 1)result = 1;
			}
			if (result == 1)
			{
				if (playersleft < 2 && allinplayers>0)
				{
					sGD.showdown = 1;
				}
				if (sGD.eGS == GS_RIVER)sGD.showdown = 1;
			}
		}
		else result = 1;
		return result;
	}

	////fold,check,raise,allin,stack,bet, of actual player, maxbet
	void cGameEngine::Bet(int k, int r)
	{
		int act = sGD.actual + r;
		if (act >= 10)act = 0;
		if (k == 0 && sGD.player[act].bet < sGD.maxbet)
		{
			sGD.player[act].fold = 1;
			sGD.player[act].card1 = { 0,0 };
			sGD.player[act].card2 = { 0,0 };
		}
		else if (k == 0 && sGD.maxbet == 0)sGD.player[act].check = 1;
		else sGD.player[act].raise = 1;

		if (k > sGD.player[act].stack - cBlind::getblind() / 2)
		{
			k = sGD.player[act].stack;
			sGD.player[act].allin = 1;
		}
		sGD.player[act].bet += k;
		sGD.player[act].totalbet += k;
		if (sGD.player[act].bet > sGD.maxbet)sGD.maxbet = sGD.player[act].bet;
		sGD.player[act].stack = sGD.player[act].stack - k;
	}

	void cGameEngine::temppostflop()
	{
		srand(static_cast<unsigned int>(time(NULL)));
		int result = rand() % 7;
		if (result < 2)Bet(0);
		else if (result > 5)Bet(sGD.maxbet + sGD.stack);
		else Bet(sGD.maxbet);
	}

	void cGameEngine::BotBet(int n)
	{
		int bet = 0;
		switch (sGD.eGS)
		{
		case GS_PREFLOP:
		{
			//handvalue 
			bool pair = 0;
			bool colour = 0;
			bool highcard1 = 0;
			bool highcard2 = 0;
			bool as1 = 0;
			bool as2 = 0;
			bool raise = 0;
			bool connector = 0;
			int pairv = 50;
			int colourv = 20;
			int connectorv = 20;
			int highcardv = 10;
			int asv = 10;
			if (sGD.player[n].card1.f == sGD.player[n].card2.f) pair = 1;
			if (sGD.player[n].card1.f == sGD.player[n].card2.f) colour = 1;
			if (sGD.player[n].card1.f >= 10) highcard1 = 1;
			if (sGD.player[n].card2.f >= 10) highcard2 = 1;
			if (sGD.player[n].card1.f == 14) as1 = 1;
			if (sGD.player[n].card2.f == 14) as2 = 1;
			if ((sGD.player[n].card2.f - sGD.player[n].card1.f == 1) || (sGD.player[n].card2.f - sGD.player[n].card1.f == -1)) connector = 1;
			int value = pair * pairv + colour * colourv + highcard1 * highcardv + highcard2 * highcardv + as1 * asv + as2 * asv + connector * connectorv + sGD.player[n].card1.f*sGD.player[n].card2.f;
			//position
			int counter = 0;
			int counter2 = n;
			for (int i = 0; i < 10; i++)
			{
				if (counter2 == sGD.dealer)break;
				counter++;
				counter2++;
				if (counter2 >= 10)counter2 -= 10;
			}
			int position = 50 - (5 * counter);
			//totalbet, maxbet on table
			int totalbet = 0;
			for (int i = 0; i < 10; i++)
				if (n != i)totalbet += sGD.player[i].bet;
			int maxbet = 0;
			for (int i = 0; i < 10; i++)
				if (i != n)
					if (sGD.player[i].bet > maxbet)maxbet = sGD.player[i].bet;
			maxbet = maxbet - sGD.player[n].bet;
			//decision
			if (maxbet < 2 * cBlind::getblind())value += position;
			if (value < 90) Bet(0);
			else if (value >= 90 && value < 150)
			{
				if (maxbet < 2 * cBlind::getblind())Bet(maxbet);
				else Bet(0);
			}
			else if (value >= 150 && value <= 200)
			{
				if (maxbet < 2 * cBlind::getblind())Bet((maxbet + sGD.player[n].bet) * 3);
				else if (maxbet >= 2 * cBlind::getblind() && maxbet < 5 * cBlind::getblind())Bet(maxbet);
				else Bet(0);
			}
			else Bet(maxbet * 3);
			break;
		}

		case GS_FLOP: {
			temppostflop();
			break;
		}
		case GS_TURN: {
			temppostflop();
			break;
		}
		case GS_RIVER: {
			temppostflop();
			break;
		}

		}

	}

	int cGameEngine::Bidding(GameStage egs)
	{
		if (egs == GS_PREFLOP)
		{
			int raises = 0;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].raise == 1)raises++;
			if (raises == 0)
			{
				BiddingCheck();
				Bet(cBlind::getblind() / 2);
				BiddingCheck();
				Bet(cBlind::getblind());
				sGD.player[sGD.actual].raise = 0;
				return 0;
			}


		}

		int result = 0;
		switch (BiddingCheck())///raise of actual,egs
		{
		case 0:
		{



			if (sGD.player[sGD.actual].human == 1)
			{
				sGD.eGS = GS_HUMAN;
				nextGS = egs;

			}
			else BotBet(sGD.actual);
			break;
		}
		case 1:
			result = 1;
			break;

		case 2:
			result = 2;
			break;
		}
		return result;
	}

	cGameEngine::~cGameEngine()
	{
		delete hDeck;
	}



	void cGameEngine::BiddingClear()
	{
		for (int i = 0; i < 10; i++)
		{
			sGD.stack += sGD.player[i].bet;
			sGD.player[i].bet = 0;
			sGD.player[i].raise = 0;
			sGD.player[i].check = 0;
			sGD.maxbet = 0;

		}
		sGD.actual = sGD.dealer;

	}
	int cGameEngine::TurnClear()
	{
		sGD.stack = 0;
		for (int i = 0; i < 10; i++)
		{

			sGD.player[i].bet = 0;
			sGD.player[i].totalbet = 0;
			sGD.player[i].raise = 0;
			sGD.player[i].check = 0;
			sGD.player[i].allin = 0;
			sGD.player[i].fold = 0;
			sGD.player[i].winner = 0;
			sGD.player[i].value = { 0,0,0,0 };
			sGD.maxbet = 0;
			sGD.player[i].card1 = sGD.player[i].card2 = { 0,0 };
			if (sGD.player[i].stack == 0)sGD.player[i].ingame = 0;
		}
		do

		{
			sGD.dealer++;
			if (sGD.dealer == 10)sGD.dealer = 0;
			if (sGD.dealer == sGD.blindinc) { cBlind::increase(); sGD.blind = cBlind::getblind(); }
		} while (sGD.player[sGD.dealer].ingame == 0);

		sGD.actual = sGD.dealer;
		hDeck->Shuffle();
		//Endgamecheck
		for (int i = 0; i < 10; i++)
		{
			if (sGD.player[i].human == 1 && sGD.player[i].ingame == 0) return 1;
		}
		int playersleft = 0;
		for (int i = 0; i < 10; i++)
		{
			if (sGD.player[i].ingame)playersleft++;

		}
		return playersleft;

	}

	void cGameEngine::Shuffle()
	{
		FoldReset();
		AllinReset();

		HandFill();


	}

	//returns number of win players
	int cGameEngine::WinnersCalc()
	{
		int playersleft = 0;

		for (int i = 0; i < 10; i++)
		{
			if (sGD.player[i].ingame == 1 && sGD.player[i].fold == 0 && sGD.player[i].totalbet) playersleft++;
			sGD.player[i].value = { 0,0,0,0 };
			sGD.player[i].winner = 0;
		}
		if (playersleft == 0)
		{
			return playersleft;
		}

		else if (playersleft == 1)
		{
			for (int i = 0; i < 10; i++)
			{
				if (sGD.player[i].ingame == 1 && sGD.player[i].fold == 0 && sGD.player[i].totalbet)sGD.player[i].winner = 1;

			}
			return playersleft;
		}
		else
		{

			for (int i = 0; i < 10; i++)
				if (sGD.player[i].ingame&&sGD.player[i].fold == 0 && sGD.player[i].totalbet > 0) sGD.player[i].value = ValueCalculate(i);

		}


		int counter = 0;
		int winners = 0;

		for (int i = 0; i < 10; i++)sGD.player[i].winner = 0;

		for (int i = 0; i < 10; i++)
			if (sGD.player[i].value.combination > counter)counter = sGD.player[i].value.combination;
		for (int i = 0; i < 10; i++)
			if (sGD.player[i].value.combination == counter)
			{
				sGD.player[i].winner = 1;
				winners++;
			}

		if (winners > 1)
		{
			counter = 0;
			winners = 0;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].winner == 1)
					if (sGD.player[i].value.highcard > counter)counter = sGD.player[i].value.highcard;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].winner == 1)
				{
					if (sGD.player[i].value.highcard == counter) winners++;
					else sGD.player[i].winner = 0;
				}
		}

		if (winners > 1)
		{
			counter = 0;
			winners = 0;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].winner == 1)
					if (sGD.player[i].value.lowcard > counter)counter = sGD.player[i].value.lowcard;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].winner == 1)
				{
					if (sGD.player[i].value.lowcard == counter) winners++;
					else sGD.player[i].winner = 0;
				}
		}

		if (winners > 1)
		{
			counter = 0;
			winners = 0;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].winner == 1)
					if (sGD.player[i].value.kicker > counter)counter = sGD.player[i].value.kicker;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].winner == 1)
				{
					if (sGD.player[i].value.kicker == counter) winners++;
					else sGD.player[i].winner = 0;
				}
		}



		return winners;
	}

	int cGameEngine::Loot()
	{
		int winleft = 0;
		//shares a semiloot between win players (semiloot calculated on lowest stack)
		do
		{
			//wins calc
			int wins = WinnersCalc();





			//lowest totalbet seek
			int lowtotbet = 20000;
			for (int i = 0; i < 10; i++)
				if ((sGD.player[i].totalbet < lowtotbet) && sGD.player[i].totalbet > 0)lowtotbet = sGD.player[i].totalbet;



			//semi stack calculate
			int semistack = 0;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].totalbet > 0)
				{
					sGD.player[i].totalbet -= lowtotbet;
					semistack += lowtotbet;
					sGD.stack -= lowtotbet;
				}
			//semistack share for winners
			for (int i = 0; i < 10; i++)
			{
				if (sGD.player[i].winner)
					sGD.player[i].stack += semistack / wins;


			}
			//Winners left
			winleft = 0;
			for (int i = 0; i < 10; i++)
				if (sGD.player[i].winner&&sGD.player[i].totalbet > 0)winleft++;
		} while (winleft);




		int playersleft = 0;
		//playersleft calculation
		for (int i = 0; i < 10; i++)
			if (sGD.player[i].totalbet > 0)playersleft++;

		if (playersleft) return 0;
		else return 1;


	}


	void cGameEngine::ChangeStage(GameStage gamestage, bool flaggs)
	{
		if (flaggs)
		{
			changeGS = 1;
			nextGS = gamestage;
		}
	}
	void cGameEngine::ChangeStage(StageStage stagestage, bool flagss)
	{
		if (flagss)
		{
			changeSS = 1;
			nextSS = stagestage;
		}

	}
	void cGameEngine::ChangeStage(GameStage gamestage, bool flaggs, StageStage stagestage, bool flagss)
	{
		ChangeStage(gamestage, flaggs);
		ChangeStage(stagestage, flagss);
	}


	//Main function, game algorithm
	void cGameEngine::Trigger(int k)
	{
		if (changeGS)///egs
		{
			sGD.eGS = nextGS;
			changeGS = 0;
		}
		if (changeSS)///ess
		{
			sGD.eSS = nextSS;
			changeSS = 0;
		}
		switch (sGD.eGS)
		{
		case GS_DEALER://dealer,actual,fold
		{
			sGD.showdown = 1;
			if (DealerRoll())
			{
				FoldReset();
				hDeck->Shuffle();
				ChangeStage(GS_PREFLOP, 1);
			}
			break;

		}

		case GS_PREFLOP:
		{
			if (sGD.eSS == SS_INIT)
			{
				sGD.showdown = 0;

				Shuffle();
				ChangeStage(SS_BIDDING, 1);
			}
			else if (sGD.eSS == SS_BIDDING)
			{
				int result = Bidding(GS_PREFLOP);
				if (result == 1) ChangeStage(SS_CLEAR, 1);
				else if (result == 2) ChangeStage(GS_RIVER, 1, SS_CLEAR, 1);

			}
			else if (sGD.eSS == SS_CLEAR)
			{
				BiddingClear();
				ChangeStage(GS_FLOP, 1, SS_INIT, 1);
			}
			break;
		}
		case GS_HUMAN:///egs
		{
			Bet(k);

			sGD.eGS = nextGS;

			break;
		}
		case GS_FLOP://flop cards,stack,actual
		{
			if (sGD.eSS == SS_INIT)
			{

				sGD.flop[0] = hGD->flop[0] = hDeck->CardDraw();
				sGD.flop[1] = hGD->flop[1] = hDeck->CardDraw();
				sGD.flop[2] = hGD->flop[2] = hDeck->CardDraw();
				///////////////////debug///////////////////////////
				//sGD.flop[0] = hGD->flop[0] = debug3[0];
				//sGD.flop[1] = hGD->flop[1] = debug3[1];
				//sGD.flop[2] = hGD->flop[2] = debug3[2];
				////////////////////////////////////////////

				ChangeStage(SS_BIDDING, 1);
			}

			else if (sGD.eSS == SS_BIDDING)
			{
				int result = Bidding(GS_FLOP);
				if (result == 1)ChangeStage(SS_CLEAR, 1);
				else if (result == 2) ChangeStage(GS_RIVER, 1, SS_CLEAR, 1);
			}
			else if (sGD.eSS == SS_CLEAR)
			{
				BiddingClear();
				ChangeStage(GS_TURN, 1, SS_INIT, 1);
			}
			break;
		}


		case GS_TURN://TURN cards,stack,actual
		{
			if (sGD.eSS == SS_INIT)
			{
				sGD.turn = hDeck->CardDraw();
				////////////////debug/////////////
				//sGD.turn = debug4;
				//////////////////////////////////
				ChangeStage(SS_BIDDING, 1);
			}

			else if (sGD.eSS == SS_BIDDING)
			{
				int result = Bidding(GS_TURN);
				if (result == 1) ChangeStage(SS_CLEAR, 1);
				else if (result == 2)ChangeStage(GS_RIVER, 1, SS_CLEAR, 1);
			}
			else if (sGD.eSS == SS_CLEAR)
			{
				BiddingClear();
				ChangeStage(GS_RIVER, 1, SS_INIT, 1);
			}
			break;
		}
		case GS_RIVER:
		{

			if (sGD.eSS == SS_INIT)
			{
				sGD.river = hDeck->CardDraw();
				////////////debug//////////////
				//sGD.river = debug5;
				//////////////////////////////
				ChangeStage(SS_BIDDING, 1);
			}

			else if (sGD.eSS == SS_BIDDING)
			{
				int result = Bidding(GS_RIVER);
				if (result) ChangeStage(SS_CLEAR, 1);
			}
			else if (sGD.eSS == SS_CLEAR)
			{
				BiddingClear();
				ChangeStage(GS_ENDTURN, 1, SS_INIT, 1);
			}
			break;
		}
		case GS_ENDTURN:
		{
			if (sGD.eSS == SS_INIT)
			{
				if (Loot())
				{
					ChangeStage(SS_CLEAR, 1);

				}

			}
			else if (sGD.eSS == SS_CLEAR)
			{
				if (TurnClear() == 1)
					ChangeStage(GS_ENDGAME, 1, SS_CLEAR, 1);
				else
					ChangeStage(GS_PREFLOP, 1, SS_INIT, 1);

			}

		}
		case GS_ENDGAME:

			break;
		}
		UpdateUserGD();
	}

