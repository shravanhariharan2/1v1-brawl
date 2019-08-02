#include "moves.h"

moves::moves() {
	name = "";
	damage = 0;
	accuracy = 0;
}

moves::moves(string nameIn, int dmgIn, int accIn) {
	name = nameIn;
	damage = dmgIn;
	accuracy = accIn;
}

string moves::getName() {
	return name;
}
void moves::setName(string nameIn) {
	name = nameIn;
}
int moves::getDmg() {
	return damage;
}
void moves::setDmg(int dmgIn) {
	damage = dmgIn;
}
int moves::getAcc() {
	return accuracy;
}
void moves::setAcc(int accIn) {
	accuracy = accIn;
}
