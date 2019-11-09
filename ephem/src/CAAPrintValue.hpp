/*
 * CAAPrintValue.hpp
 *
 *  Created on: Sep 19, 2019
 *      Author: thomas
 */

#ifndef CAAPRINTVALUE_HPP_
#define CAAPRINTVALUE_HPP_

#include <ios>
#include <iomanip>
#include <iostream>

class  CAAPrintValue
{
public:
	enum class CAAPrintValueFormat
	{
		HOUR,
		DEGREE_0_TO_360,
		DEGREE_M90_TO_P90,
		DOUBLE,
		JDDATE
	};

	double value;
	CAAPrintValueFormat format;

	CAAPrintValue(double v, CAAPrintValueFormat f) : value(v), format(f)
	{
	};
	friend std::ostream& operator<<(std::ostream &out, const CAAPrintValue &obj);
};


#endif /* CAAPRINTVALUE_HPP_ */
