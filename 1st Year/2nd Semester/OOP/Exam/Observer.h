#pragma once
#include <vector>
using namespace std;
class Observer
{
public: 
	virtual void update() = 0;
};

class Subiect {
private:
	vector<Observer*> observers;
public:
	void addObserver(Observer * obs);
	void notify();
};