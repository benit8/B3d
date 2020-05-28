/*
** B, 2019
** Utils / Timeout.cpp
*/

#include "B/Platform/Time.hpp"
#include "B/Utils/Timeout.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Timeout::Timeout(const f64 seconds)
: m_duration(seconds)
, m_started(getTime())
{}

Timeout::Timeout(const unsigned fps)
: m_duration(1.0f / (float)fps)
, m_started(getTime())
{}


bool Timeout::expired() const
{
	return getTime() - m_started >= m_duration;
}

void Timeout::restart()
{
	m_started = getTime();
}

////////////////////////////////////////////////////////////////////////////////

}