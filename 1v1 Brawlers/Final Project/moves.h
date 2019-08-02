#pragma once
#include<string>
#include<fstream>
#include<random>
#include<iostream>
using namespace std;
class moves {
public:

	string name;
	int damage;
	int accuracy;

	moves();
	moves(string nameIn, int dmgIn, int accIn);

	string getName(); void setName(string nameIn);
	int getDmg(); void setDmg(int atkIn);
	int getAcc(); void setAcc(int accIn);

};
