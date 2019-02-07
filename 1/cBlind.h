#pragma once
class cBlind
{
	static int blind[];
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

