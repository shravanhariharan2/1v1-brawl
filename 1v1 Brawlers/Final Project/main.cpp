#include <SFML/Graphics.hpp>
#include<string>
#include "player.h"
#include "moves.h"
#include<fstream>
#include<random>
#include<iostream>
#include<sstream>
#include<time.h>

sf::Text titleText;
sf::Sprite bgSprite;
sf::Sprite bfSprite;
sf::Sprite shravSprite;
sf::Sprite playerSprite;
sf::Sprite mreSprite;
sf::Sprite ericSprite;
player player1;
player mre;
player eric;
player shravan;

int hey;
bool fight1won;
bool fight2won;

enum GameState {
	TITLE,
	STATS,
	DISPMOVES,
	FIGHTPAUSE,
	FIGHTQUERY,
	FIGHT,
	AFTERFIGHT1,
	BEFOREFIGHT2,
	FIGHTQUERY2,
	FIGHT2,
	AFTERFIGHT2,
	BEFOREFIGHT3,
	FIGHTQUERY3,
	FIGHT3,
	AFTERFIGHT3,
	END,
	GAMEPLAY
};

enum MoveSelected {
	MOVE1,
	MOVE2,
	MOVE3,
	MOVE4
};

void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

void displaySprites(sf::RenderWindow *windowIn) {
	windowIn->clear();
	windowIn->draw(bfSprite);
	windowIn->draw(playerSprite);	
	if (!fight1won && !fight2won)
		windowIn->draw(mreSprite);
	else if (fight1won && !fight2won)
		windowIn->draw(ericSprite);
	else if (fight2won && fight1won)
		windowIn->draw(shravSprite);
	windowIn->draw(titleText);
	windowIn->display();
}

void animateSprite(sf::RenderWindow *windowIn, sf::Sprite *spriteIn) {
	if (spriteIn == &playerSprite) {
		spriteIn->setPosition(190, 150);
		displaySprites(windowIn);
		delay(500);
		spriteIn->setPosition(150, 190);
		displaySprites(windowIn);
	}
	else {
		spriteIn->setPosition(510, 100);
		displaySprites(windowIn);
		delay(500);
		spriteIn->setPosition(550, 60);
		displaySprites(windowIn);
	}
}

void useMove(player *playerIn, player *playerDmged, moves *moveIn, sf::RenderWindow *windowIn) {
	
	random_device rd;
	hey++;
	titleText.setPosition(100, 425);
	titleText.setString(playerIn->getName() + " used " + moveIn->getName() + "!");
	if (playerIn == &player1)
		animateSprite(windowIn, &playerSprite);
	else if (playerIn == &mre)
		animateSprite(windowIn, &mreSprite);
	else if (playerIn == &eric)
		animateSprite(windowIn, &ericSprite);
	else if (playerIn == &shravan)
		animateSprite(windowIn, &shravSprite);
	
	displaySprites(windowIn);

	delay(2000);
	int rawDamage = moveIn->getDmg() + playerIn->getAtk();
	int rngDamage = rd() % 3;


	int totalAccuracy = playerIn->getAcc() * moveIn->getAcc();
	int rngAcc = (rd() % 100) + 1; 
	if (rngAcc > totalAccuracy) {
		titleText.setString(playerIn->getName() + " missed their attack!");
		displaySprites(windowIn);
	}
	else {
		int critChance = playerIn->getCrit();
		int rngCrit = (rd() % 100) + 1;
		if (rngCrit <= critChance){
			rawDamage *= 2;
			int totalDmg = rawDamage + rngDamage;
			titleText.setString(playerIn->getName() + " dealt " + to_string(totalDmg) + " damage to " + playerDmged->getName() + "! \nIt was a critical hit!");
			playerDmged->setHealth(playerDmged->getHealth() - totalDmg);
			displaySprites(windowIn);
			delay(2000);
			if (playerDmged->getHealth() <= 0) {
				titleText.setString(playerDmged->getName() + " has no health remaining!");
				displaySprites(windowIn);
				delay(2000);

			}
			else {
				titleText.setString(playerDmged->getName() + " has " + to_string(playerDmged->getHealth()) + " health remaining!");
				displaySprites(windowIn);
				delay(2000);
			}
		}
		else {
			int totalDmg = rawDamage + rngDamage;
			titleText.setString(playerIn->getName() + " dealt " + to_string(totalDmg) + " damage to " + playerDmged->getName() + "!");
			playerDmged->setHealth(playerDmged->getHealth() - totalDmg);
			displaySprites(windowIn);
			delay(2000);
			if (playerDmged->getHealth() <= 0) {
				titleText.setString(playerDmged->getName() + " has no health remaining!");
				displaySprites(windowIn);
				delay(2000);

			}
			else {
				titleText.setString(playerDmged->getName() + " has " + to_string(playerDmged->getHealth()) + " health remaining!");
				displaySprites(windowIn);
				delay(2000);
			}
		}
	}
	
	


}

int main() {
	int count = 0;
	hey = 0;
	bool canLearn = false;
	bool isFight = false;
	fight1won = false;
	fight2won = false;
	

	random_device rd;
	//setup of window + title

	sf::RenderWindow window(sf::VideoMode(800, 600), "1v1 Brawl");
	
	GameState state = TITLE;
	MoveSelected movestate ;
	sf::Font font;
	font.loadFromFile("Fonts/Candal.ttf");

	sf::Texture bg;
	bg.loadFromFile("Textures/background.jpg");
	bgSprite.setTexture(bg);
	
	sf::Texture bf;
	bf.loadFromFile("Textures/battlefield.png");
	bfSprite.setTexture(bf);

	sf::Texture player2;
	player2.loadFromFile("Textures/playersprite.png");
	playerSprite.setTexture(player2);
	playerSprite.setPosition(150, 190);

	sf::Texture mreText;
	mreText.loadFromFile("Textures/mre.png");
	mreSprite.setTexture(mreText);
	mreSprite.setPosition(550, 60);

	sf::Texture ericText;
	ericText.loadFromFile("Textures/eric.png");
	ericSprite.setTexture(ericText);
	ericSprite.setPosition(550, 60);

	sf::Texture shrav;
	shrav.loadFromFile("Textures/newShrav.png");
	shravSprite.setPosition(550, 60);
	shravSprite.setTexture(shrav);

	titleText.setFont(font);
	
	titleText.setString("   Welcome to 1v1 Brawl! \n	 Press space to start.");
	titleText.setCharacterSize(40);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(100, 100);	
	
	//creation of all moves
	
	//bad moves
	moves spit("Spit", 1, 80);
	moves poke("Poke", 1, 100);
	moves nudge("Nudge", 1, 100);

	//mediocre moves
	moves kick("Kick", 5, 80);
	moves punch("Punch", 4, 80);
	moves chop("Chop", 6, 65);
	moves shove("Shove", 4, 100);

	//eric mixtaper moves
	moves hotbars("hot bars", 5, 100);

	//good moves
	moves triplekick("Triple Kick", 10, 60);
	moves doublepunch("Double Punch", 8, 100);
	moves ram("Ram", 10, 100);

	
	
	//legendary moves
	
	//creation of main guy
	vector<moves> player1moves;
	player1moves.push_back(spit);
	player1moves.push_back(poke);
	player1 = player("Player1", 20, 2, 2, 80, 0, 4, player1moves);


	//creation of enemy #1
	vector<moves> mreMoves;
	mreMoves.push_back(spit);
	mre = player("Mr. E", 5, 1, 1, 100, 2, 2, mreMoves);


	//creation of enemy #2
	vector<moves> ericMoves;
	ericMoves.push_back(hotbars);
	eric = player("Eric Mixtaper", 15, 2, 2, 100, 0, 3, ericMoves);

	//creation of enemy #3
	vector<moves> shravanMoves;
	shravanMoves.push_back(doublepunch);
	shravan = player("Master Shravan", 30, 5, 3, 100, 30, 5, shravanMoves);
	 
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Space) {

					if (state == TITLE)
						state = STATS;

					else if (state == STATS)
						state = DISPMOVES;

					else if (state == DISPMOVES)
						state = FIGHTPAUSE;
					else if (state == FIGHTPAUSE)
						state = FIGHTQUERY;
					else if (state == AFTERFIGHT1)
						state = BEFOREFIGHT2;
					else if (state == BEFOREFIGHT2)
						state = FIGHTQUERY2;
					else if (state == AFTERFIGHT2)
						state = BEFOREFIGHT3;
					else if (state == BEFOREFIGHT3)
						state = FIGHTQUERY3;
					else if (state == AFTERFIGHT3)
						state = END;
					
				}

				if (event.key.code == sf::Keyboard::Num1 && state == FIGHTQUERY) {
					movestate = MOVE1;
					if (count == 0)
						state = FIGHT;
					else if (count == 1)
						state = FIGHT2;
				}
				else if (event.key.code == sf::Keyboard::Num2 && state == FIGHTQUERY) {
					movestate = MOVE2;
					if (count == 0)
						state = FIGHT;
					else if (count == 1)
						state = FIGHT2;
				}
				else if (event.key.code == sf::Keyboard::Num3 && state == FIGHTQUERY) {
					movestate = MOVE3;
					if (count == 0)
						state = FIGHT;
					else if (count == 1)
						state = FIGHT2;
				}
				else if (event.key.code == sf::Keyboard::Num4 && state == FIGHTQUERY) {
					movestate = MOVE4;
					if (count == 0)
						state = FIGHT;
					else if (count == 1)
						state = FIGHT2;
				}
		
				if (event.key.code == sf::Keyboard::Num1 && state == FIGHTQUERY2) {
					movestate = MOVE1;				
					state = FIGHT2;
				}
				else if (event.key.code == sf::Keyboard::Num2 && state == FIGHTQUERY2) {
					movestate = MOVE2;
					
					state = FIGHT2;
				}
				else if (event.key.code == sf::Keyboard::Num3 && state == FIGHTQUERY2) {
					movestate = MOVE3;
					
					state = FIGHT2;
				}
				else if (event.key.code == sf::Keyboard::Num4 && state == FIGHTQUERY2) {
					movestate = MOVE4;
			
					state = FIGHT2;
				}

				if (event.key.code == sf::Keyboard::Num1 && state == FIGHTQUERY3) {
					movestate = MOVE1;
					state = FIGHT3;
				}
				else if (event.key.code == sf::Keyboard::Num2 && state == FIGHTQUERY3) {
					movestate = MOVE2;

					state = FIGHT3;
				}
				else if (event.key.code == sf::Keyboard::Num3 && state == FIGHTQUERY3) {
					movestate = MOVE3;

					state = FIGHT3;
				}
				else if (event.key.code == sf::Keyboard::Num4 && state == FIGHTQUERY3) {
					movestate = MOVE4;

					state = FIGHT3;
				}


			}


		}

		if (state == TITLE) {
			titleText.setString("   Welcome to 1v1 Brawl! \n	 Press space to start.");
		}
		
		else if (state == STATS) {
			titleText.setCharacterSize(24);
			titleText.setString("You are playing as a human with insane \npotential. Here are your stats: " + player1.dispStats() +
				"\n\nSpacebar to continue");
		}
		
		else if (state == DISPMOVES) {
			titleText.setString("You have moves that you can use against \npotential enemies that you come across."
				"\nYou can have up to four moves that \nyou can know at once."
				"\nYour current moves are: \n" + player1.displayMoves() + "\n\nSpacebar to continue");
		}
		
		else if (state == FIGHTPAUSE) {
			
			titleText.setString("You are about to face your first adversary, Mr. E. \nThe fight will start when you press space!");
		}
		
		else if (state == FIGHTQUERY) {
			isFight = true;
			titleText.setPosition(100, 425);
			titleText.setString("What will you do? \n" + player1.displayMoves());
		}
		
		else if (state == FIGHT){ 
			isFight = false;
			bool fighting = true;
			while (fighting) {
				if (movestate == MOVE1) {
					if (player1.getSpeed() > mre.getSpeed()) {
						useMove(&player1, &mre, &player1moves[0], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						useMove(&mre, &player1, &mreMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else if (player1.getSpeed() < mre.getSpeed()) {
						useMove(&mre, &player1, &player1moves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1; 
							break;
						}
						useMove(&player1, &mre, &player1moves[0], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &mre, &player1moves[0], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&mre, &player1, &player1moves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
						else {
							useMove(&mre, &player1, &player1moves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&player1, &mre, &player1moves[0], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
					}

				}

				else if (movestate == MOVE2) {
					if (player1.getSpeed() > mre.getSpeed()) {
						useMove(&player1, &mre, &player1moves[1], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						useMove(&mre, &player1, &mreMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else if (player1.getSpeed() < mre.getSpeed()) {
						useMove(&mre, &player1, &player1moves[1], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						useMove(&player1, &mre, &mreMoves[0], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &mre, &player1moves[1], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&mre, &player1, &mreMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
						else {
							useMove(&mre, &player1, &player1moves[1], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&player1, &mre, &mreMoves[0], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
					}
				}
				else if (movestate == MOVE3) {
					if (player1.getSpeed() > mre.getSpeed()) {
						useMove(&player1, &mre, &player1moves[2], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						useMove(&mre, &player1, &mreMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else if (player1.getSpeed() < mre.getSpeed()) {
						useMove(&mre, &player1, &player1moves[2], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						useMove(&player1, &mre, &mreMoves[0], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &mre, &player1moves[2], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&mre, &player1, &mreMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
						else {
							useMove(&mre, &player1, &player1moves[2], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&player1, &mre, &mreMoves[0], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
					}
				}
				else if (movestate == MOVE4) {
					if (player1.getSpeed() > mre.getSpeed()) {
						useMove(&player1, &mre, &player1moves[3], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						useMove(&mre, &player1, &mreMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else if (player1.getSpeed() < mre.getSpeed()) {
						useMove(&mre, &player1, &player1moves[3], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						useMove(&player1, &mre, &mreMoves[0], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT1;
							break;
						}
						state = FIGHTQUERY;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &mre, &player1moves[3], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&mre, &player1, &mreMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
						else {
							useMove(&mre, &player1, &player1moves[3], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							useMove(&player1, &mre, &mreMoves[0], &window);
							if (mre.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT1;
								break;
							}
							state = FIGHTQUERY;
							break;
						}
					}
				}
				//sdsdf
			}
			
			
		}

		else if (state == AFTERFIGHT1) {
			
			if (player1.getHealth() <= 0) {
				titleText.setString("Oh no! You lost! The game will close in 3 seconds.");
				delay(3000);
				window.close();
			}
			else {
				titleText.setPosition(100, 100);
				isFight = false;
				titleText.setString("Congratulations! You beat Mr. E! That battle\nwas fairly straightforward, but you will \nfight against harder opponents later."
					"\nDue to your victory, your teacher taught you the \nmove 'Kick'! \n\nSpacebar to continue.");
				count++;
				fight1won = true;
				player1.setHealth(20);
				cout << hey << endl;
				player1moves.push_back(kick);
			}
				
		}

		else if (state == BEFOREFIGHT2) {
			titleText.setString("You are about to fight your second opponent, \nEric Mixtaper! Be careful of his flaming hot bars! \n\nSpacebar to begin fight.");
		}
		
		else if (state == FIGHTQUERY2) {
			titleText.setPosition(100, 410);
			isFight = true;
			titleText.setString("What will you do? \nMoves\n1. Spit \n2. Poke \n3. Kick");
		}
		
		else if (state == FIGHT2) {
			isFight = false;
			bool fighting = true;
			while (fighting) {
				if (movestate == MOVE1) {
					if (player1.getSpeed() > eric.getSpeed()) {
						useMove(&player1, &eric, &player1moves[0], &window);
						if (eric.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else if (player1.getSpeed() < eric.getSpeed()) {
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&player1, &eric, &player1moves[0], &window);
						if (eric.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &eric, &player1moves[0], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
						else {
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&player1, &eric, &player1moves[0], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
					}

				}

				else if (movestate == MOVE2) {
					if (player1.getSpeed() > eric.getSpeed()) {
						useMove(&player1, &eric, &player1moves[1], &window);
						if (eric.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else if (player1.getSpeed() < eric.getSpeed()) {
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&player1, &eric, &player1moves[1], &window);
						if (eric.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &eric, &player1moves[1], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
						else {
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&player1, &eric, &player1moves[1], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
					}
				}
				else if (movestate == MOVE3) {
					if (player1.getSpeed() > eric.getSpeed()) {
						useMove(&player1, &eric, &player1moves[2], &window);
						if (eric.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else if (player1.getSpeed() < eric.getSpeed()) {
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&player1, &eric, &player1moves[0], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &eric, &player1moves[2], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
						else {
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&player1, &eric, &player1moves[2], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
					}
				}
				else if (movestate == MOVE4) {
					if (player1.getSpeed() > eric.getSpeed()) {
						useMove(&player1, &eric, &player1moves[3], &window);
						if (eric.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else if (player1.getSpeed() < eric.getSpeed()) {
						useMove(&eric, &player1, &ericMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						useMove(&player1, &eric, &player1moves[3], &window);
						if (mre.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT2;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &eric, &player1moves[3], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
						else {
							useMove(&eric, &player1, &ericMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							useMove(&player1, &mre, &player1moves[3], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT2;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
					}
				}
				//sdsdf
			}


		}

		else if (state == AFTERFIGHT2) {
			titleText.setPosition(100, 100);
			isFight = false;
			titleText.setString("Congratulations! You beat Eric Mixtaper! Looks \nlike his mixtapes were not spicy enough, but \nthere is still one more opponent that stands \nin your way between you and the victory screen."
				"\n\nDue to your victory, your teacher taught you the \nmove 'Triple Kick'! \n\nSpacebar to continue.");
			count++;
			fight2won = true;
			player1.setHealth(20);
			player1moves[3] = triplekick;
		}

		else if (state == BEFOREFIGHT3) {
			titleText.setString("You are about to fight your last \nopponent and prove your worth. \n\nUp next is Master Shravan. \n\nSpacebar to start");
		}
		
		else if (state == FIGHTQUERY3) {
			isFight = true;
			titleText.setPosition(100, 400);
			titleText.setString("What will you do? \nMoves\n1. Spit \n2. Poke \n3. Kick \n4. Triple Kick");
		}
		
		else if (state == FIGHT3) {
			bool fighting = true;
			while (fighting) {
				if (movestate == MOVE1) {
					if (player1.getSpeed() > shravan.getSpeed()) {
						useMove(&player1, &shravan, &player1moves[0], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						state = FIGHTQUERY3;
						break;
					}
					else if (player1.getSpeed() < shravan.getSpeed()) {
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						titleText.setString("You spit into Shravan-sama's eyes! You \ndisgusted him so much that he had to leave!");
						animateSprite(&window, &playerSprite);
						window.clear();
						window.draw(bfSprite);
						window.draw(shravSprite);
						window.draw(playerSprite);
						window.draw(titleText);
						window.display();
						delay(2000);
						fighting = false;
						/*useMove(&player1, &shravan, &player1moves[0], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}*/
						state = AFTERFIGHT3;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &shravan, &player1moves[0], &window);
							if (shravan.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY3;
							break;
						}
						else {
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&player1, &shravan, &player1moves[0], &window);
							if (shravan.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY3;
							break;
						}
					}

				}

				else if (movestate == MOVE2) {
					if (player1.getSpeed() > shravan.getSpeed()) {
						useMove(&player1, &shravan, &player1moves[1], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						state = FIGHTQUERY3;
						break;
					}
					else if (player1.getSpeed() < shravan.getSpeed()) {
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						useMove(&player1, &shravan, &player1moves[1], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						state = FIGHTQUERY3;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &shravan, &player1moves[1], &window);
							if (shravan.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY3;
							break;
						}
						else {
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&player1, &shravan, &player1moves[1], &window);
							if (eric.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY3;
							break;
						}
					}
				}
				else if (movestate == MOVE3) {
					if (player1.getSpeed() > shravan.getSpeed()) {
						useMove(&player1, &shravan, &player1moves[2], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						state = FIGHTQUERY3;
						break;
					}
					else if (player1.getSpeed() < shravan.getSpeed()) {
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						useMove(&player1, &shravan, &player1moves[0], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						state = FIGHTQUERY2;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &shravan, &player1moves[2], &window);
							if (shravan.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY3;
							break;
						}
						else {
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&player1, &shravan, &player1moves[2], &window);
							if (shravan.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY2;
							break;
						}
					}
				}
				else if (movestate == MOVE4) {
					if (player1.getSpeed() > shravan.getSpeed()) {
						useMove(&player1, &shravan, &player1moves[3], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						state = FIGHTQUERY3;
						break;
					}
					else if (player1.getSpeed() < shravan.getSpeed()) {
						useMove(&shravan, &player1, &shravanMoves[0], &window);
						if (player1.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						useMove(&player1, &shravan, &player1moves[3], &window);
						if (shravan.getHealth() <= 0) {
							fighting = false;
							state = AFTERFIGHT3;
							break;
						}
						state = FIGHTQUERY3;
						break;
					}
					else {
						int speedtie = (rd() % 2);
						if (speedtie == 0) {
							useMove(&player1, &shravan, &player1moves[3], &window);
							if (shravan.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY3;
							break;
						}
						else {
							useMove(&shravan, &player1, &shravanMoves[0], &window);
							if (player1.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							useMove(&player1, &shravan, &player1moves[3], &window);
							if (shravan.getHealth() <= 0) {
								fighting = false;
								state = AFTERFIGHT3;
								break;
							}
							state = FIGHTQUERY3;
							break;
						}
					}
				}
			}
		}

		else if (state == AFTERFIGHT3) {
			titleText.setPosition(100, 100);
			isFight = false;
			if (player1.getHealth() <= 0) {
				titleText.setString("Oh no! You lost! The game will close in 3 seconds.");
				window.clear();
				window.draw(titleText);
				delay(3000);
				window.close();
			}
			else{
				titleText.setString("Unbelievable! You defeated your own master! \nYou are officially the strongest member of your \ntown. Congratulations on your success! \n\nSpacebar to continue");				
				player1.setHealth(20);			
			}
		}
		else if (state == END) {
			titleText.setCharacterSize(40);
			titleText.setString("The End! Thanks for playing!");
		}
		if (isFight == true) {
			window.clear();
			window.draw(bfSprite);
			window.draw(playerSprite);
			if (!fight1won && !fight2won)
				window.draw(mreSprite);
			else if (fight1won && !fight2won)
				window.draw(ericSprite);
			else if (fight2won && fight1won)
				window.draw(shravSprite);
			window.draw(titleText);
			window.display();
		}
		else {
			window.clear();			
			window.draw(bgSprite);			
			window.draw(titleText);
			window.display();
		}
	}
	return 0;
}