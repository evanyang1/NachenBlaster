#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

#include <iostream>
#include <random>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(StudentWorld* s, int image, double startx, double starty, Direction di, double siz, unsigned int dept);

	bool get_active();
	void set_active(bool al);
	virtual void doSomething() = 0;

	bool get_alien();
	void set_alien(bool al);

	StudentWorld* getWorld();
private:
	StudentWorld * sw;
	bool active; // is it alive? True = yes. False = no.
	bool isAlien;
};


class Star : public Actor {
public:
	Star(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};

class Cabbage : public Actor {
public:
	Cabbage(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};

class Turnip : public Actor {
public: 
	Turnip(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};
// Two classes of FT's inherit from this class. FT = Flatulence Torpedo. 
class FT : public Actor {
public:
	FT(StudentWorld* sw, int x, int y, int dir) : Actor(sw, IID_TORPEDO, x, y, dir, 0.5, 1) {}
};

class FTPlayer : public FT {
public:
	FTPlayer(StudentWorld* sw, int x, int y) : FT(sw, x, y, 0){}
	virtual void doSomething();
};

class FTSnaggle : public FT {
public:
	FTSnaggle(StudentWorld* sw, int x, int y) : FT(sw, x, y, 180) {}
	virtual void doSomething();
};

class Explosion : public Actor {
public:
	Explosion(StudentWorld* sw, int x, int y);
	virtual void doSomething();
private:
	int ticksLeft;
};

class HP : public Actor { // HP = Hit Points. This is a virtual class.
public:
	HP(StudentWorld* sw, int image, double startx, double starty, Direction di, double siz, unsigned int dept, int hp);
		
	int get_hitpoints();
	void set_hitpoints(int hp) {
		hitpoints = hp;
	}
	void loseHP(int dmg) {
		hitpoints -= dmg;
	}
	void gainHP(int heal) {
		hitpoints += heal;
	}
	
private:
	int hitpoints;
	
};

class NachenBlaster : public HP {
public: 
	NachenBlaster(StudentWorld* sw);
	virtual void doSomething();

	int m_cabbage();
	int m_torpedoes();
	int get_torpedoes() { return torpedoes; }
	void set_torpedoes(int n) { torpedoes = n; }
	void incTorp(int n) { torpedoes += n; }
	void decTorp() { torpedoes--; }
private: 
	int cabbagesPoints;
	int torpedoes;
};

class Alien : public HP {
public:
	Alien(StudentWorld* sw, int image, double startx, double starty, Direction di, double siz, unsigned int dept,
		double travelSpeed, int hp);
	double get_tSpeed();
	void set_tSpeed(double ts) { tSpeed = ts; }
private:
	double tSpeed;

};

class Smallgon : public Alien {
public: 
	Smallgon(StudentWorld* sw);
	virtual void doSomething();
private:
	int flightPlanLength;
	int fplanCode;

};

class Smoregon : public Alien {
public: 
	Smoregon(StudentWorld* sw);
	virtual void doSomething();
private:
	int flightPlanLength;
	int fplanCode;
};

class Snagglegon : public Alien {
public:
	Snagglegon(StudentWorld* sw);
	virtual void doSomething();
private:
	int fplanCode;
	const int DOWN_LEFT = 0;
	const int UP_LEFT = 1;

};



class Goodie : public Actor {
public:
	Goodie(StudentWorld* sw, int image, double startx, double starty, Direction di, double siz, unsigned int dept);
};



class ExtraLifeGoodie : public Goodie {
public:
	ExtraLifeGoodie(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};

class RepairGoodie : public Goodie {
public: 
	RepairGoodie(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};


class FlatulenceTorpedoGoodie : public Goodie {
public: 
	FlatulenceTorpedoGoodie(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};









#endif // ACTOR_H_
