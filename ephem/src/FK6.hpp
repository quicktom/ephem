/*
 * FK6.hpp
 *
 *  Created on: Oct 21, 2019
 *  http://cdsarc.u-strasbg.fr/viz-bin/cat/I/264
 *      Author: thomas
 */

#ifndef FK6_HPP_
#define FK6_HPP_

#define _USE_MATH_DEFINES
#include "AA+.h"

class  CAAFK6_Catalog
{
public:
	typedef struct
	{
		unsigned int FK6_Number;
		double ra_hour, ra_minute, ra_second;
		double de_deg, de_minute, de_second;
		double ra_properMotion_MilliSecPerYear, d_properMotion_MilliArcSecPerYear;
		double Vmag;
	} FK6_star_record;

	static CAA2DCoordinate GetCatalogStarByNumber(unsigned int idx, double JD);

	static unsigned int GetNumStars(void);
};



#endif /* FK6_HPP_ */
