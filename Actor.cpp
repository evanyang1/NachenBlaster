#include "Actor.h"
#include "StudentWorld.h"

#include <cmath>
#include <iostream>

using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

double Euclid(double a1, double a2, double b1, double b2) {
	return sqrt(pow(a1 - b1, 2.0) + pow(a2 - b2, 2.0)); // sqrt(a^2 + b^2)
}

bool collided(Actor* a1, Actor* a2) {
	if (Euclid(a1->getX(), a1->getY(), a2->getX(), a2->getY()) < 0.75 * (a1->getRadius() + a2->getRadius())) {
		return true;
	}
	else return false;
}

Actor::Actor(StudentWorld* s, int image, double startx, double starty, Direction di, double siz, unsigned int dept) 
	: GraphObject(image, startx, starty, di, siz, dept), active(true) {
	sw = s;
}

bool Actor::get_active() {
	return active;
}

void Actor::set_active(bool al) {
	active = al;
}

bool Actor::get_alien() { return isAlien; }
void Actor::set_alien(bool al) { isAlien = al; }

StudentWorld* Actor::getWorld() {
	return sw;
}

Star::Star(StudentWorld* sw, int x, int y) : Actor(sw, IID_STAR, x, y, 0, randInt(5, 50) / 100.0, 3) { // random between 0.05 to 0.5
	set_active(true); //
} 

void Star::doSomething() {
	moveTo(getX() - 1, getY());
	if (getX() <= -1) {
		//dead
		set_active(false);
	}
}

Cabbage::Cabbage(StudentWorld* sw, int x, int y) : Actor(sw, IID_CABBAGE, x, y, 0, .5, 1) {
	set_active(true);
}

void Cabbage::doSomething() {
	if (!get_active()) return; // again, no need do anythang
	// #2
	if (getX() >= VIEW_WIDTH) {
		set_active(false); // dead, get out of screen
		return;
	} 
	// #3
	// check actor class for collision
	for (int i = 0; i < getWorld()->getV().size(); i++) {
		if (getWorld()->getV()[i]->get_alien() == true) {
			// getWorld()->getV()[i]->loseHP();
			HP* alien = (HP*) getWorld()->getV()[i];
			if (collided(this, alien)) {
				alien->loseHP(2);
				// SOUND_BLAST
				if (alien->get_active() == true) getWorld()->playSound(SOUND_BLAST);

				set_active(false); // cabbage is done after hitting an alien
				return; // only dmg to one alien. "return" is stronger than "break" since "Do nothing else in this tick"
			}
			
		}
	}
	// #4
	moveTo(getX() + 8, getY());
	// #5
	setDirection(getDirection() + 20);
	// #6
	for (int i = 0; i < getWorld()->getV().size(); i++) {
		if (getWorld()->getV()[i]->get_alien() == true) {
			// getWorld()->getV()[i]->loseHP();
			HP* alien = (HP*)getWorld()->getV()[i];
			if (collided(this, alien)) {
				alien->loseHP(2);
				// SOUND_BLAST
				if (alien->get_active() == true) getWorld()->playSound(SOUND_BLAST);

				set_active(false); // cabbage is done after hitting an alien
				return; // only dmg to one alien. "return" is stronger than "break" since "Do nothing else in this tick"
			}

		}
	}
}

Turnip::Turnip(StudentWorld* sw, int x, int y) : Actor(sw, IID_TURNIP, x, y, 0, .5, 1){}

void Turnip::doSomething() {
	if (!get_active()) return;
	// #2
	if (getX() >= VIEW_WIDTH) {
		set_active(false); // dead, get out of screen
		return;
	}
	// #3
	if (collided(this, getWorld()->get_nach())) {
		getWorld()->get_nach()->loseHP(2);
		getWorld()->playSound(SOUND_BLAST);
		set_active(false); return; // dead, get out of screen
	}
	// #4
	moveTo(getX() - 6, getY());
	// #5
	setDirection(getDirection() + 20);
	// #6
	if (collided(this, getWorld()->get_nach())) {
		getWorld()->get_nach()->loseHP(2);
		getWorld()->playSound(SOUND_BLAST); // play SOUND_BLAST whenever NachenBlaster hit by projectile
		set_active(false); return; // dead, get out of screen
	} 
}

void FTPlayer::doSomething() {
	if (!get_active()) return; // again, no need do anythang #1
	// #2
	if (getX() >= VIEW_WIDTH) {
		set_active(false);
		return;
	}
	// #3
	for (int i = 0; i < getWorld()->getV().size(); i++) {
		if (getWorld()->getV()[i]->get_alien() == true) {
			// getWorld()->getV()[i]->loseHP();
			HP* alien = (HP*)getWorld()->getV()[i];
			if (collided(this, alien)) {
				alien->loseHP(8);
				// SOUND_BLAST
				if (alien->get_active() == true) getWorld()->playSound(SOUND_BLAST);

				set_active(false); // FT is done after hitting an alien
				return; // only dmg to one alien. "return" is stronger than "break" since "Do nothing else in this tick"
			}

		}
	}
	// #4
	moveTo(getX() + 8, getY());
	// #6
	for (int i = 0; i < getWorld()->getV().size(); i++) {
		if (getWorld()->getV()[i]->get_alien() == true) {
			// getWorld()->getV()[i]->loseHP();
			HP* alien = (HP*)getWorld()->getV()[i];
			if (collided(this, alien)) {
				alien->loseHP(8);
				// SOUND_BLAST
				if (alien->get_active() == true) getWorld()->playSound(SOUND_BLAST);

				set_active(false); // FT is done after hitting an alien
				return; // only dmg to one alien. "return" is stronger than "break" since "Do nothing else in this tick"
			}

		}
	}
}

void FTSnaggle::doSomething() {

	
	if (!get_active()) return; // again, no need do anythang #1
							   // #2
	

	if (getX() >= VIEW_WIDTH) {
		set_active(false);
		return;
	}
		
	cout << get_active() << endl;
	
	// #3
	if (collided(this, getWorld()->get_nach())) {
		getWorld()->get_nach()->loseHP(8);
		getWorld()->playSound(SOUND_BLAST);
		set_active(false);
		return;
	}
	// #4
	moveTo(getX() - 8, getY()); 
	// #6
	if (collided(this, getWorld()->get_nach())) {
		getWorld()->get_nach()->loseHP(8);
		getWorld()->playSound(SOUND_BLAST);
		set_active(false);
		return;
	}
}

Explosion::Explosion(StudentWorld* sw, int x, int y) : Actor(sw, IID_EXPLOSION, x, y, 0, 1, 0) {
	ticksLeft = 4;
	sw->incD();
}

void Explosion::doSomething() {
	// Expand 1.5 x
	setSize(1.5 * getSize()); ticksLeft--;
	if (ticksLeft <= 0) set_active(false); //dead
	
}

HP::HP(StudentWorld* sw, int image, double startx, double starty, Direction di, double siz, unsigned int dept, int hp) :
	hitpoints(hp), Actor(sw, image, startx, starty, di, siz, dept) {}

int HP::get_hitpoints() { // Q: should it be virtual?
	return hitpoints;
}

NachenBlaster::NachenBlaster(StudentWorld* sw) : HP(sw, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, 50) {
	cabbagesPoints = 30;
	torpedoes = 0;
	set_active(true); // it's alive
}


void NachenBlaster::doSomething() {
	// no hp = dead
	if (get_hitpoints() <= 0) set_active(false);

	if (!get_active()) return; // If dead, SKIP ALL THIS we don't need to do anything aghhhhh

	int ch;
	if (getWorld()->getKey(ch)) {
		// user hit a key during this tick!!
		switch (ch) {
		case KEY_PRESS_LEFT:
			// move it to the left
			if (getX() - 6 >= 0) moveTo(getX() - 6, getY());
			break;
		case KEY_PRESS_RIGHT:
			if (getX() + 6 < VIEW_WIDTH) moveTo(getX() + 6, getY());
			break;
		case KEY_PRESS_DOWN:
			if (getY() - 6 >= 0) moveTo(getX(), getY() - 6);
			break;
		case KEY_PRESS_UP:
			if (getY() + 6 < VIEW_HEIGHT) moveTo(getX(), getY() + 6);
			break;
		case KEY_PRESS_SPACE:
			if (cabbagesPoints >= 5) {
				getWorld()->addNewItem(new Cabbage(getWorld(), getX() + 12, getY()));
				cabbagesPoints -= 5;
			}
			getWorld()->playSound(SOUND_PLAYER_SHOOT);
			break;
		case KEY_PRESS_TAB:
			// if there are FT's in inventory
			if (get_torpedoes() >= 1) {
				getWorld()->addNewItem(new FTPlayer(getWorld(), getX() + 12, getY()));
				decTorp();
			}
			getWorld()->playSound(SOUND_TORPEDO);
			
			//

			break;
		}

		

	}
	if (cabbagesPoints < 30) cabbagesPoints++;
}

int NachenBlaster::m_cabbage() {
	return cabbagesPoints;
}

int NachenBlaster::m_torpedoes() {
	return torpedoes;
}

Alien::Alien(StudentWorld* sw, int image, double startx, double starty, Direction di, double siz, unsigned int dept,
	double travelSpeed, int hp) :
	HP(sw, image, startx, starty, di, siz, dept, hp), tSpeed(travelSpeed) {
	set_alien(true);
	set_active(true);
}

double Alien::get_tSpeed() { return tSpeed; }

Smallgon::Smallgon(StudentWorld* sw) :
	Alien(sw, IID_SMALLGON, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), 0, 1.5, 1, 2.0, 5 * (1 + ((sw->getLevel()) - 1) * .1)) , flightPlanLength(0)
{
}

void Smallgon::doSomething() {
	// #1
	if (get_hitpoints() <= 0) {
		set_active(false); // ran out of hitpoints. dead.
		getWorld()->increaseScore(250);
		getWorld()->playSound(SOUND_DEATH);
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));

	}
	if (!get_active()) {

		return;
	}
	// #2
	if (getX() < 0) {
		set_active(false);
		return; // dead. done.
	}
	// #3
	//IF(euclidian_dist(x1, y1, x2, y2) < .75 * (R1 + R2))
		//THEN the two flying objects collided;
	if (collided(this, getWorld()->get_nach())) {
		// Dmg the ship
		getWorld()->get_nach()->loseHP(5);
		// Dies
		set_active(false);
		// Player gets 250 points (add to score) 
		getWorld()->increaseScore(250);
		// Play the death sound effect
		getWorld()->playSound(SOUND_DEATH);
		//Introduce a new explosion object into the space field at the same x,y coordinates
		//as the Smallgon(see the Explosion section for more details)
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
	}
	// #4

	const int DOWN_LEFT = 1;
	const int UP_LEFT = 2;
	const int DUE_LEFT = 3;
	if (flightPlanLength <= 0 || getY() <= 0 || getY() >= VIEW_HEIGHT - 1) {
		if (getY() >= VIEW_HEIGHT - 1) {
			fplanCode = DOWN_LEFT;
		}
		else if (getY() <= 0) {
			fplanCode = UP_LEFT;
		}
		else {
			fplanCode = randInt(DOWN_LEFT, DUE_LEFT); // 1 to 3
		}
		// Renewed FPlan
		flightPlanLength = randInt(1, 32);
	}
	// #5 
	//If the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y
		//coordinate that is within[-4, 4] pixels of the NachenBlaster’s y coordinate
	if (getWorld()->get_nach()->getX() < getX() && abs(getY() - getWorld()->get_nach()->getY()) <= 4) {
		int x = randInt(1, 20 + 5 * getWorld()->getLevel());
		if (x <= getWorld()->getLevel()) {
			// Fire a turnip
			getWorld()->addNewItem(new Turnip(getWorld(), getX() - 14, getY()));
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			// Do nothing else that tick.
			return;
		}
	}
	// #6
	switch (fplanCode) {
	case(DOWN_LEFT):
		moveTo(getX() - get_tSpeed(), getY() - get_tSpeed());
		break;
	case(UP_LEFT):
		moveTo(getX() - get_tSpeed(), getY() + get_tSpeed());
		break;
	case(DUE_LEFT):
		moveTo(getX() - get_tSpeed(), getY());
		break;
	}
	flightPlanLength--;
	// #7
	if (collided(this, getWorld()->get_nach())) {
		// Dmg the ship
		getWorld()->get_nach()->loseHP(5);
		// Dies
		set_active(false);
		// Player gets 250 points (add to score) 
		getWorld()->increaseScore(250);
		// Play the death sound effect
		getWorld()->playSound(SOUND_DEATH);
		//Introduce a new explosion object into the space field at the same x,y coordinates
		//as the Smallgon(see the Explosion section for more details)
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
	}
}

Smoregon::Smoregon(StudentWorld* sw) : 
	Alien(sw, IID_SMOREGON, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), 0, 1.5, 1, 2.0, 5 * (1 + (sw->getLevel() - 1) * .1)) , flightPlanLength(0){}
// do not use getWOrld() bc sw not yet. 

void Smoregon::doSomething() {
	// #1
	if (get_hitpoints() <= 0) {
		set_active(false); // ran out of hitpoints. dead.
		getWorld()->increaseScore(250);
		getWorld()->playSound(SOUND_DEATH);
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
		int q = randInt(1, 6);
		if (q == 1) getWorld()->addNewItem(new RepairGoodie(getWorld(), getX(), getY()));
		else if (q == 2) getWorld()->addNewItem(new FlatulenceTorpedoGoodie(getWorld(), getX(), getY()));
	}
	if (!get_active()) {

		return;
	}
	// #2
	if (getX() < 0) {
		set_active(false);
		return; // dead. done.
	}
	// #3
	//IF(euclidian_dist(x1, y1, x2, y2) < .75 * (R1 + R2))
	//THEN the two flying objects collided;
	if (collided(this, getWorld()->get_nach())) {
		// Dmg the ship
		getWorld()->get_nach()->loseHP(5);
		// Dies
		set_active(false);
		// Player gets 250 points (add to score) 
		getWorld()->increaseScore(250);
		// Play the death sound effect
		getWorld()->playSound(SOUND_DEATH);
		//Introduce a new explosion object into the space field at the same x,y coordinates
		//as the Smallgon(see the Explosion section for more details)
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
		int q = randInt(1, 6);
		if (q == 1) getWorld()->addNewItem(new RepairGoodie(getWorld(), getX(), getY()));
		else if (q == 2) getWorld()->addNewItem(new FlatulenceTorpedoGoodie(getWorld(), getX(), getY()));
	}
	// #4

	const int DOWN_LEFT = 1;
	const int UP_LEFT = 2;
	const int DUE_LEFT = 3;
	if (flightPlanLength <= 0 || getY() <= 0 || getY() >= VIEW_HEIGHT - 1) {
		if (getY() >= VIEW_HEIGHT - 1) {
			fplanCode = DOWN_LEFT;
		}
		else if (getY() <= 0) {
			fplanCode = UP_LEFT;
		}
		else {
			fplanCode = randInt(DOWN_LEFT, DUE_LEFT); // 1 to 3
		}
		// Renewed FPlan
		flightPlanLength = randInt(1, 32);
	}
	// #5 
	//If the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y
	//coordinate that is within[-4, 4] pixels of the NachenBlaster’s y coordinate
	if (getWorld()->get_nach()->getX() < getX() && abs(getY() - getWorld()->get_nach()->getY()) <= 4) {
		int x = randInt(1, 20 + 5 * getWorld()->getLevel());
		if (x <= getWorld()->getLevel()) {
			// Fire a turnip
			getWorld()->addNewItem(new Turnip(getWorld(), getX() - 14, getY()));
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			// Do nothing else that tick.
			return;
		}
		int y = randInt(1, 20 + 5 * getWorld()->getLevel());
		if (y <= getWorld()->getLevel()) {
			fplanCode = DUE_LEFT;
			flightPlanLength = VIEW_WIDTH;
			set_tSpeed(5); // RAMMING SPEED
		}
	}
	// #6
	switch (fplanCode) {
	case(DOWN_LEFT):
		moveTo(getX() - get_tSpeed(), getY() - get_tSpeed());
		break;
	case(UP_LEFT):
		moveTo(getX() - get_tSpeed(), getY() + get_tSpeed());
		break;
	case(DUE_LEFT):

		moveTo(getX() - get_tSpeed(), getY());
		break;
	}
	flightPlanLength--;
	// #7 
	if (collided(this, getWorld()->get_nach())) {
		// Dmg the ship
		getWorld()->get_nach()->loseHP(5);
		// Dies
		set_active(false);
		// Player gets 250 points (add to score) 
		getWorld()->increaseScore(250);
		// Play the death sound effect
		getWorld()->playSound(SOUND_DEATH);
		//Introduce a new explosion object into the space field at the same x,y coordinates
		//as the Smallgon(see the Explosion section for more details)
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
		int q = randInt(1, 6);
		if (q == 1) getWorld()->addNewItem(new RepairGoodie(getWorld(), getX(), getY()));
		else if (q == 2) getWorld()->addNewItem(new FlatulenceTorpedoGoodie(getWorld(), getX(), getY()));
	}
}

Snagglegon::Snagglegon(StudentWorld* sw) : 
	 Alien(sw, IID_SNAGGLEGON, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), 0, 1.5, 1, 1.75, 10 * (1 + (sw->getLevel() - 1) * .1)) {

}

void Snagglegon::doSomething() {
	// #1
	if (get_hitpoints() <= 0) {
		set_active(false); // ran out of hitpoints. dead.
		getWorld()->increaseScore(1000);
		getWorld()->playSound(SOUND_DEATH);
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
		int ran = randInt(1, 6);
		if(ran == 1)
			getWorld()->addNewItem(new ExtraLifeGoodie(getWorld(), getX(), getY()));

	}
	if (!get_active()) {

		return;
	}
	// #2
	if (getX() < 0) {
		set_active(false);
		return; // dead. done.
	}
	// #3
	
	if (collided(this, getWorld()->get_nach())) {
		// Dmg the ship
		getWorld()->get_nach()->loseHP(15); // 15 by the Snagglegon
		// Dies
		set_active(false);
		// Player gets 1000 points (add to score) 
		getWorld()->increaseScore(1000);
		// Play the death sound effect
		getWorld()->playSound(SOUND_DEATH);
		//Introduce a new explosion object into the space field at the same x,y coordinates
		//as the Smallgon(see the Explosion section for more details)
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
		// extra life goodie
		int ran = randInt(1, 6);
		if (ran == 1)
			getWorld()->addNewItem(new ExtraLifeGoodie(getWorld(), getX(), getY()));
	}
	// #4


	if (getY() >= VIEW_HEIGHT - 1) {
		fplanCode = DOWN_LEFT;
	}

	else if (getY() <= 0) fplanCode = UP_LEFT; 
	
	// #5 
	//If the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y
	//coordinate that is within[-4, 4] pixels of the NachenBlaster’s y coordinate
	if (getWorld()->get_nach()->getX() < getX() && abs(getY() - getWorld()->get_nach()->getY()) <= 4) {
		int x = randInt(1, 20 + 5 * getWorld()->getLevel());
		if (x <= getWorld()->getLevel()) {
			
			getWorld()->addNewItem(new FTSnaggle(getWorld(), getX() - 14, getY()));
			getWorld()->playSound(SOUND_TORPEDO);
			// Do nothing else that tick.
			return;
		}
	}
	// #6

	if (fplanCode == DOWN_LEFT) {
		moveTo(getX() - get_tSpeed(), getY() - get_tSpeed()); 
	}
	if (fplanCode == UP_LEFT) {
		moveTo(getX() - get_tSpeed(), getY() + get_tSpeed()); 
	}
	// #7 
	if (collided(this, getWorld()->get_nach())) {
		// Dmg the ship
		getWorld()->get_nach()->loseHP(15); // 15 by the Snagglegon
											// Dies
		set_active(false);
		// Player gets 1000 points (add to score) 
		getWorld()->increaseScore(1000);
		// Play the death sound effect
		getWorld()->playSound(SOUND_DEATH);
		//Introduce a new explosion object into the space field at the same x,y coordinates
		//as the Smallgon(see the Explosion section for more details)
		getWorld()->addNewItem(new Explosion(getWorld(), getX(), getY()));
		// extra life goodie
		int ran = randInt(1, 6);
		if (ran == 1)
			getWorld()->addNewItem(new ExtraLifeGoodie(getWorld(), getX(), getY()));
	}
}






Goodie::Goodie(StudentWorld* sw, int image, double startx, double starty, Direction di, double siz, unsigned int dept)
	: Actor(sw, image, startx, starty, di, siz, dept) {}

ExtraLifeGoodie::ExtraLifeGoodie(StudentWorld* sw, int x, int y) :
	Goodie(sw, IID_LIFE_GOODIE, x, y, 0, .5, 1) {}

void ExtraLifeGoodie::doSomething() {
	if (!get_active()) { // #1
		return;
	}
	if (getX() <= 0 || getY() <= 0) {
		set_active(false);
		return;
	}
	// #3
	if (collided(getWorld()->get_nach(), this)) {
		getWorld()->increaseScore(100);
		set_active(false); // out by next tick
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->incLives();
		return; // done
	}
	// #4
	moveTo(getX() - 0.75, getY() - 0.75);
	// #5
	if (collided(getWorld()->get_nach(), this)) {
		getWorld()->increaseScore(100);
		set_active(false); // out by next tick
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->incLives();
		return; // done
	}

}

RepairGoodie::RepairGoodie(StudentWorld* sw, int x, int y) : 
	Goodie(sw, IID_REPAIR_GOODIE, x, y, 0, .5, 1) {}

void RepairGoodie::doSomething() {
	if (!get_active()) { // #1
		return;
	}
	if (getX() <= 0 || getY() <= 0) {
		set_active(false);
		return;
	}
	// #3
	if (collided(getWorld()->get_nach(), this)) {
		getWorld()->increaseScore(100);
		set_active(false); // out by next tick
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->get_nach()->gainHP(10);
		if (getWorld()->get_nach()->get_hitpoints() > 50) {
			getWorld()->get_nach()->set_hitpoints(50); // Max HP = 50
		}
		return; // done
	}
	// #4
	moveTo(getX() - 0.75, getY() - 0.75);
	// #5
	if (collided(getWorld()->get_nach(), this)) {
		getWorld()->increaseScore(100);
		set_active(false); // out by next tick
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->get_nach()->gainHP(10);
		if (getWorld()->get_nach()->get_hitpoints() > 50) {
			getWorld()->get_nach()->set_hitpoints(50); // Max HP = 50
		}
		return; // done
	}
}

FlatulenceTorpedoGoodie::FlatulenceTorpedoGoodie(StudentWorld* sw, int x, int y) :
	Goodie(sw, IID_TORPEDO_GOODIE, x, y, 0, .5, 1) {}

void FlatulenceTorpedoGoodie::doSomething() {
	if (!get_active()) { // #1
		return;
	}
	if (getX() <= 0 || getY() <= 0) {
		set_active(false);
		return;
	}
	// #3
	if (collided(getWorld()->get_nach(), this)) {
		getWorld()->increaseScore(100);
		set_active(false); // out by next tick
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->get_nach()->incTorp(5); // +5 FT's
		return; // done
	}
	// #4
	moveTo(getX() - 0.75, getY() - 0.75);
	// #5
	if (collided(getWorld()->get_nach(), this)) {
		getWorld()->increaseScore(100);
		set_active(false); // out by next tick
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->get_nach()->incTorp(5); // +5 FT's
		return; // done
	}
}