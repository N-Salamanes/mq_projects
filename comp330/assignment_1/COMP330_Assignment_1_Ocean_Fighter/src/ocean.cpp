/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   12 Apr 2017
 *
 * ocean.cpp
 *
 * the ocean functions
 *
 */
#include "../include/ocean.hpp"

Ocean::Ocean()
{
	m_oceanInc = 0.15f;
	m_upperLimit = 0.9f;
	m_lowerLimit = 0.45f;
	m_ocean = m_lowerLimit;
}

Ocean::~Ocean(){}

void Ocean::update(int v)
{
	int delta_t = globals.time - v;

	m_ocean += m_oceanInc * (delta_t / 1000.0);

	if (m_ocean >= m_upperLimit)
	{
		// start decrementing
		m_oceanInc = -fabs(m_oceanInc);
	}
	else if (m_ocean <= m_lowerLimit)
	{
		// start incrementing
		m_oceanInc = fabs(m_oceanInc);
	}
}

float Ocean::get_ocean()
{
	return m_ocean;
}
