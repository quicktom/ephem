/*
 * CAAObserveTarget.hpp
 *
 *  Created on: Sep 18, 2019
 *      Author: thomas
 */

#ifndef CAAOBSERVETARGET_HPP_
#define CAAOBSERVETARGET_HPP_

#include <iostream>
#define _USE_MATH_DEFINES
#include "AA+.h"

class  CAAObserveTarget
{
public:
	enum class CAATargetObject
	{
				SUN,
				MERCURY,
				VENUS,
				MARS,
				JUPITER,
				SATURN,
				URANUS,
				NEPTUNE,
				PLUTO,
				LUNA,
				RADE,														// assumes a fix object 						requires actual RightAscension, Declination
				AZAL,														// assumes a fix object at given UTC  			requires Azimuth, Altitude
				HADE,														// assumes a fix object at given UTC			requires LocalHourAngle, Declination
				FK5STAR,
				FK6STAR,
				UNDEFINED
	};

	CAAObserveTarget(double lat, double lon, double h, CAATargetObject t, bool printTrad, double ra, double de, double lHA, double az, double al, unsigned int catIdx) noexcept	:
			latitude(lat), longitude(lon), height(h), target(t), printTraditional(printTrad), RightAscension(ra), Declination(de), LocalHourAngle(lHA), Azimuth(az), Altitude(al), catalogIndex(catIdx)
	{
		lastJD = -1;
	};

	void UpdateTargetData(double JD);

	friend std::ostream& operator<<(std::ostream &out, const CAAObserveTarget &obj);

private:
	double latitude, longitude, height;
	CAATargetObject target;
	bool printTraditional;
	double RightAscension, Declination, LocalHourAngle, Azimuth, Altitude, lastJD;
	unsigned int catalogIndex;

	void SetRightAscensionDeclination(double JD);
	void SetLocalHourAngle(double JD);
	void SetAzimuthAltitude(void);

	CAA2DCoordinate GetRightAscensionDeclinationFromCAAElliptical(double JD, CAAElliptical::EllipticalObject obj);
	double GetRightAscensionFromLocalHourAngle(double JD, double lha);
	CAA2DCoordinate GetRightAscensionDeclinationFromAzimuthAltitude(double JD);
};

#endif /* CAAOBSERVETARGET_HPP_ */
