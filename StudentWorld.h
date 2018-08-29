#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GraphObject.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <iostream>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	NachenBlaster* get_nach() { return nach; }

	// added stuff
	std::vector<Actor*> getV() { return actor; }

	void addNewItem(Actor* act);
	~StudentWorld() {
		cleanUp();
	}

	void incD() { D++; }


private:
	std::vector<Actor*> actor;
	NachenBlaster* nach;
	int D; // # alien ships destroyed
	int T; // # alien ships per level


};

#endif // STUDENTWORLD_H_
