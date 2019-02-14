#include <ctime>
#include <cstdlib>
//////////////////////////
//All in game alghorithms
//////////////////////////

// instance of card contain figure and colour
struct card{
	int f;
	int c;
};

// usefull in definiotion of player cards value
struct sValue{
	int combination;
	int highcard;
	int lowcard;
	int kicker;
};

class deck{
	bool d[52];
	int cleft;
public:
	deck(){
		Shuffle();
		srand(static_cast<unsigned int>(time(NULL)));
	}

	void Shuffle(){
		for (int i = 0; i < 52; i++) d[i] = 1;
		cleft = 52;
	}

	card CardDraw(){
		card x = { -1,-1 };

		if (cleft > 0){
			int k = rand() % cleft;
			int c = 0;
			int i;
			for (i = 0; i < 52; i++){
				if (d[i] == 1){
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
};

class cBlind
{
	static int blind[];
	static int i;
public:
	static void increase()
	{
		if (i < 9)i++;
	}
	static int getblind()
	{
		return blind[i];
	}
};
//Major stage
enum GameStage { GS_DEALER, GS_PREFLOP,GS_HUMAN,GS_FLOP,GS_TURN,GS_RIVER, GS_ENDTURN,GS_ENDGAME};
//Minor
enum StageStage{SS_INIT,SS_BIDDING,SS_CLEAR};

struct sInitData{
	int players;
	int stack;
	int blind;
	unsigned int starttime;	
	bool human[10];
};
struct sGameData{
	GameStage eGS;
	StageStage eSS;
	bool showdown;
	int dealer;
	int blindinc;
	int maxbet;
	int stack;
	int actual;
	int blind;
	int winner;
	card flop[3];
	card turn;
	card river;
	unsigned int t;
	
	struct players{
		bool human;
		int stack;
		int totalbet;
		card card1;
		card card2;
		int bet;
		bool ingame, check, raise, allin, fold,winner;
		sValue value;

	}player[10];
};

//Main GAME ENGINE class definiotion

class cGameEngine
{
	deck* hDeck;
	GameStage nextGS;
	StageStage nextSS;
	bool changeGS;
	bool changeSS;
	int iteration;
	sGameData sGD;
	sGameData* hGD;
	void UpdateUserGD();
	//Calculates value of player ccc hand
	sValue ValueCalculate(int ccc);
	int DealerRoll();
	void HandFill();
	void FoldReset();
	void AllinReset();
	void CheckReset();
	int BiddingCheck();
	void Bet(int k, int r = 0);
	void temppostflop();
	void BotBet(int n);
	int Bidding(GameStage egs);
	void BiddingClear();
	int TurnClear();
	void Shuffle();
	int WinnersCalc();
	int Loot();
	void ChangeStage(GameStage gamestage, bool flaggs);
	void ChangeStage(StageStage stagestage, bool flagss);
	void ChangeStage(GameStage gamestage, bool flaggs, StageStage stagestage, bool flagss);

public:

	cGameEngine(sInitData k, sGameData* s);
	//Updates user Game Data after each call
	void Trigger(int playerBet);
	~cGameEngine();
};


