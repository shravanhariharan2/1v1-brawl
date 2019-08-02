#include "player.h"
#include "moves.h"
#include <SFML/Graphics.hpp>
#include<vector>

player::player() {
	name = ""; health = 20; atk = 0; def = 0; accuracy = 0; crit = 0; 
}

player::player(string nameIn, int healthIn, int atkIn, int defIn, int accIn, int critIn, int speedIn, vector<moves> movesIn) {
	name = nameIn;
	health = healthIn;
	atk = atkIn;
	def = defIn;
	accuracy = accIn;
	crit = critIn;
	speed = speedIn;
	playerMoves = movesIn;
}


string player::getName() {
	return name;
}
int player::getHealth() {
	return health;
}
int player::getAtk() {
	return atk;
}
int player::getDef() {
	return def;
}
int player::getAcc() {
	return accuracy;
}
int player::getCrit() {
	return crit;
}
int player::getSpeed() {
	return speed;
}

void player::setName(string nameIn) {
	name = nameIn;
}
void player::setHealth(int healthIn) {
	health = healthIn;
}
void player::setAtk(int atkIn) {
	atk = atkIn;
}
void player::setDef(int defIn) {
	def = defIn;
}
void player::setAcc(int accIn) {
	accuracy = accIn;
}
void player::setCrit(int critIn) {
	crit = critIn;
}
void player::setSpeed(int speedIn) {
	speed = speedIn;
}
void player::learnMove(moves moveIn) {
	playerMoves.push_back(moveIn);
}
string player::displayMoves() {
	string dispMoves = "Moves: ";
	for (int i = 0; i < playerMoves.size(); i++) {
		dispMoves += "\n" + to_string(i+1) + ". " + playerMoves[i].getName();
	}
	return dispMoves;
}
string player::dispStats() {
	string stats = "\nHealth: " + to_string(health);
	stats += "\nAttack: " + to_string(atk);
	stats += "\nDefense: " + to_string(def);
	stats += "\nAccuracy: " + to_string(accuracy);
	stats += "\nCritical Strike Chance: " + to_string(crit);
	stats += "\nSpeed: " + to_string(speed);
	return stats;
	
}



