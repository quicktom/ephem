/*
 * CAAPrintValue.cpp
 *
 *  Created on: Sep 19, 2019
 *      Author: thomas
 */

#include "CAAObserveTarget.hpp"
#include "CAAPrintValue.hpp"
#include <limits>
#include <stdio.h>

std::ostream& operator<<(std::ostream &out, const CAAPrintValue &obj)
{
	double sec;
	int deg, min;

	bool isNegative = obj.value<0.0;
	double degree = isNegative?-obj.value:obj.value;

	char buf[256] = "\0";
	// TODO fixed rounding issues JDdate.Second() which may return 60.0
	CAADate JDdate(obj.value + 0.001/86400, true);

	switch(obj.format)
	{
	case CAAPrintValue::CAAPrintValueFormat::JDDATE :
		snprintf (buf, 256, "%04ld-%02ld-%02ld %02ld:%02ld:%02.0f" , JDdate.Year(), JDdate.Month(), JDdate.Day(), JDdate.Hour(), JDdate.Minute(), JDdate.Second());
		break;

	case CAAPrintValue::CAAPrintValueFormat::HOUR   :
		deg	= (int)degree;
		degree -= deg;
		degree *= 60.0;
		min = (int)(degree);
		degree -= min;
		degree *= 60.0;
		sec = degree;
		if(isNegative)
			out << "-";
		else
			out << "+";

		snprintf ( buf, 256, "%02ih%02dm%05.2fs" , deg, min, sec);
		break;

	case CAAPrintValue::CAAPrintValueFormat::DEGREE_0_TO_360	:
		deg	= (int)degree;
		degree -= deg;
		degree *= 60.0;
		min = (int)(degree);
		degree -= min;
		degree *= 60.0;
		sec = degree;
		if(isNegative)
			out << "-";
		else
			out << "+";

		snprintf ( buf, 256, "%03i°%02dm%05.2fs" , deg, min, sec);
		break;

	case CAAPrintValue::CAAPrintValueFormat::DEGREE_M90_TO_P90	:
		deg	= (int)degree;
		degree -= deg;
		degree *= 60.0;
		min = (int)(degree);
		degree -= min;
		degree *= 60.0;
		sec = degree;
		if(isNegative)
			out << "-";
		else
			out << "+";

		snprintf ( buf, 256, "%02i°%02dm%05.2fs" , deg, min, sec);
		break;
	case CAAPrintValue::CAAPrintValueFormat::DOUBLE	:
	default		:
		snprintf ( buf, 256, "%+04.6f" , obj.value);
	}

	out << buf;

	return out;
}

