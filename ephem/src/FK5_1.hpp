/*
 * FK5_1.hpp
 *
 * FK5 Fifth Fundamental Catalogue (FK5) Part I from
 * http://cdsarc.u-strasbg.fr/ftp/I/149A/ReadMe
 *  Created on: Sep 29, 2019
 *      Author: thomas
 */

#ifndef FK5_1_HPP_
#define FK5_1_HPP_

#define _USE_MATH_DEFINES
#include "AA+.h"


class  CAAFK5_1_Catalog
{
public:
	typedef struct
	{
		unsigned int FK1_Number;
		double ra_hour, ra_minute, ra_second, ra_properMotion_SecPerHunderedYears;
		double de_deg, de_minute, de_second, de_properMotion_ArcSecPerHunderedYears;
		double Vmag;
	} FK5_I_star_record;

	static CAA2DCoordinate GetCatalogStarByNumber(unsigned int idx, double JD);

	static unsigned int GetNumStars(void);
};

#endif /* FK5_1_HPP_ */
