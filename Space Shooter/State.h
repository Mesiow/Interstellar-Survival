#pragma once

#include <SFML/Graphics.hpp>

enum states
{
	MENU = 0,
	PLAYING,
	EXIT
};


class State
{
public:
	explicit State(states type)
	{
		this->currentState = type;
	}
	~State(){}

	//State(const State &other) = delete;
	//State(State &&other) = delete;
	//State &operator=(const State &other) = delete;

public:
	inline states &getState() { return currentState; }
	inline void setState(states setState) { currentState = setState; }

private:
	states currentState;

};