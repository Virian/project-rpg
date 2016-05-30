#pragma once
/*fragment biblioteki Thor*/
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class StopWatch
{
public:
	StopWatch();
	sf::Time getElapsedTime() const;
	bool isRunning() const;
	void start();
	void stop();
	void reset();
	void restart();
private:
	sf::Clock mClock;
	sf::Time mTimeBuffer;
	bool mRunning;
};

class Timer
{
public:
	Timer();
	virtual ~Timer();
	sf::Time getRemainingTime() const;
	bool isRunning() const;
	bool isExpired() const;
	void start();
	void stop();
	virtual void reset(sf::Time timeLimit);
	virtual void restart(sf::Time timeLimit);
private:
	StopWatch mStopWatch;
	sf::Time mLimit;
};