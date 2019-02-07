#pragma once
class cBlind
{
private:
	static int blind[10];
	static int i;
public:


	static void increase()
	{
		if (i<9)i++;
	}
	static int getblind()
	{
		return blind[i];
	}

};
