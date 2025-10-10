#include "Observer.h"


void Subiect::addObserver(Observer* obs)
{
	this->observers.push_back(obs);
}

void Subiect::notify()
{
	for (auto obs : observers)
	{
		obs->update();
	}
}
