#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
}

int StudentWorld::init()
{
	nach = new NachenBlaster(this); // Do not say NachenBlaster* nach = new NachenBlaster(*this)
	for (int i = 0; i < 30; i++) { // 30 stars placed randomly
		// [0, VIEW_WIDTH), and [0, VIEW_HEIGHT)
		int m_x = randInt(0, VIEW_WIDTH - 1);
		int m_y = randInt(0, VIEW_HEIGHT - 1);
		actor.push_back(new Star(this, m_x, m_y));

	}
	T = 6 + (4 * getLevel());
	D = 0; // when u begin a level u destroyed 0 alien ships
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	
	for (int j = 0; j < actor.size(); j++) {
		if (actor[j]->get_active()) { // if active
			actor[j]->doSomething();
		}
	} 
	if (nach->get_active()) nach->doSomething(); // don't forget the nachenblaster, check if it's active too

	if (nach->get_active() == false) {
		decLives();
		return  GWSTATUS_PLAYER_DIED;
	}
	// 1b. Next lvl
	if (D >= 6 + (4 * getLevel())) {
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}

	// Remove newly dead actors.
	
	for (auto it = actor.begin(); it != actor.end();) {
		if ((*it)->get_active() == false) {
			if ((*it)->get_alien() == true);
			delete (*it); // deallocate
			it = actor.erase(it); // erases the elt at it and sets it equal to the next element 
		}
		else it++;
	}

	//There is a one in fifteen chance that you will introduce a new star into the game
	//on the far right side of the screen

	int xoxo = randInt(1, 15);
	if (xoxo == 1) {
		actor.push_back(new Star(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
	}

	// Make alien ships (pg.7)

	int R = T - D;
	int M = 4 + (.5 * getLevel());
	int currAliens = 0;
	for (int i = 0; i < actor.size(); i++) {
		if (actor[i]->get_alien()) {
			currAliens++;
		}
	}
	if (currAliens < min(M, R)) {
		// Add an alien ship
		int S1 = 60; int S2 = 20 + (getLevel() * 5); int S3 = 5 + (getLevel() * 10);
		int S = S1 + S2 + S3;
		int x = randInt(1, S);
		if (x >= 1 && x <= S1) addNewItem(new Smallgon(this));
		else if (x >= S1 + 1 && x <= S1 + S2) {
			
			addNewItem(new Smoregon(this));
		}
		else addNewItem(new Snagglegon(this));
		// finish the rest later

	}

	// update display text

	ostringstream oss; 
	oss.setf(ios::fixed);
	oss.precision(0);
	oss << "Lives: " << getLives() << "  " << "Health: " << (nach->get_hitpoints()) * 2 << "%  " << "Score: "
		<< getScore() << "  " << "Level: " << getLevel() << "  " << "Cabbage: " <<	(nach->m_cabbage()) * (10.0 / 3);
	oss	<< "%  " << "Torpedoes: " << nach->m_torpedoes();
	setGameStatText(oss.str());



	return GWSTATUS_CONTINUE_GAME;

	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	//decLives();
	//return GWSTATUS_PLAYER_DIED;

}

void StudentWorld::cleanUp()
{
	// deallocate memory
	
	for (int j = 0; j < actor.size(); j++) {
		delete actor[j]; // everything needs to be gone
	} 
	actor.clear(); // if this isn't used, you gonna have a runtime error
	
	if (nach != nullptr) {
		delete nach; // get rid of the NachenBlaster
		nach = nullptr;
	}
}


void StudentWorld::addNewItem(Actor* act) {
	actor.push_back(act);
}