#pragma once
#include<string>
#include<fstream>
#include<random>
#include<vector>
#include<iostream>
#include <SFML/Graphics.hpp>
#include "moves.h"
using namespace std;
class player {
public:

	fstream file;
	string filename;

	string name;
	int health;
	int atk;
	int def;
	int accuracy;
	int crit;
	int speed;

	vector<moves> playerMoves;

	player();
	player(string nameIn, int healthIn, int atkIn, int defIn, int accIn, int critIn, int speedIn, vector<moves> movesIn);

	string getName(); void setName(string nameIn);
	int getHealth(); void setHealth(int healthIn);
	int getAtk(); void setAtk(int atkIn);
	int getDef(); void setDef(int defIn);
	int getAcc(); void setAcc(int accIn);
	int getCrit(); void setCrit(int critIn);
	int getSpeed(); void setSpeed(int speedIn);
	string dispStats();
	void learnMove(moves moveIn); string displayMoves();


};
