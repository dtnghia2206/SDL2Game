#pragma once
#include <list>
#include "Frame.h"
#include "GameObject.h"


class GameConsole
{
public:
	std::list<GameObject> dataSet;;
	Frame voLevel1;
	int vnInput = 0;

public:
	GameConsole(Frame ip_oLevel);
	~GameConsole();

	void Start();
	void Update();


};