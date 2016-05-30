/*fragment biblioteki Thor*/
#include "Time.h"
#include <algorithm>
#include <cassert>

StopWatch::StopWatch() : mClock(), mTimeBuffer(sf::Time::Zero), mRunning(false)
{

}

sf::Time StopWatch::getElapsedTime() const
{
	if (mRunning)
		return mTimeBuffer + mClock.getElapsedTime();
	else
		return mTimeBuffer;
}

bool StopWatch::isRunning() const
{
	return mRunning;
}

void StopWatch::start()
{
	if (!mRunning)
	{
		mRunning = true;
		mClock.restart();
	}
}

void StopWatch::stop()
{
	if (mRunning)
	{
		mRunning = false;
		mTimeBuffer += mClock.getElapsedTime();
	}
}

void StopWatch::reset()
{
	mTimeBuffer = sf::Time::Zero;
	mRunning = false;
}

void StopWatch::restart()
{
	reset();
	start();
}

Timer::Timer() : mStopWatch(), mLimit(sf::Time::Zero)
{

}

Timer::~Timer()
{

}

sf::Time Timer::getRemainingTime() const
{
	return std::max(mLimit - mStopWatch.getElapsedTime(), sf::Time::Zero);
}

bool Timer::isRunning() const
{
	return mStopWatch.isRunning() && !isExpired();
}

bool Timer::isExpired() const
{
	return mStopWatch.getElapsedTime() >= mLimit;
}

void Timer::start()
{
	mStopWatch.start();
}

void Timer::stop()
{
	mStopWatch.stop();
}

void Timer::reset(sf::Time timeLimit)
{
	assert(timeLimit > sf::Time::Zero);

	mLimit = timeLimit;
	mStopWatch.reset();
}

void Timer::restart(sf::Time timeLimit)
{
	reset(timeLimit);
	start();
}