/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   17 Apr 2017
 *
 * wake.cpp
 *
 * the wake declarations
 *
 */
#ifndef WAKE_HPP_
#define WAKE_HPP_
#include "../include/global.hpp"
#include "../include/object.hpp"

class Wake : public Object
{
public:
	Wake(double, double);
	~Wake();
	void update(int v);
	void draw();

	static int wakeTimer;			// last time since wake was created
	static int wakeTimerThreshold;	// threshold for wake timer
private:
	void set_circleSegments(int);	// get how many points should the circle have
	int get_circleSegments();		// set how many points should the circle have
	int m_circleSegments;			// circle segments

	double m_scaleFactor;			// wake scale factor
	double m_scaleInc;				// wake increment factor
	double m_scaleLimit;			// wake scale limit

	double m_alphaFactor;			// alpha scale factor
	double m_alphaInc;				// alpha increment factor
	double m_alphaLimit;			// alpha scale limit
};



#endif /* WAKE_HPP_ */
