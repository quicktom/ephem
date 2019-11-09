/*
 * CAAObserveTarget.cpp
 *
 *  Created on: Sep 19, 2019
 *      Author: thomas
 */


#include <ios>
#include <iomanip>
#include "CAAObserveTarget.hpp"
#include "CAAPrintValue.hpp"
#include "FK5_1.hpp"
#include "FK6.hpp"

std::ostream& operator<< (std::ostream &out, const CAAObserveTarget &obj)
{
	if(obj.printTraditional)
	{
		CAADate JDdate(obj.lastJD, true);
		out << 		  CAAPrintValue(obj.lastJD, 		CAAPrintValue::CAAPrintValueFormat::JDDATE);
		out << " " << CAAPrintValue(obj.RightAscension, CAAPrintValue::CAAPrintValueFormat::HOUR);
		out << " " << CAAPrintValue(obj.Declination, 	CAAPrintValue::CAAPrintValueFormat::DEGREE_M90_TO_P90);
		out << " " << CAAPrintValue(obj.LocalHourAngle, CAAPrintValue::CAAPrintValueFormat::HOUR);
		out << " " << CAAPrintValue(obj.Azimuth, 		CAAPrintValue::CAAPrintValueFormat::DEGREE_0_TO_360);
		out << " " << CAAPrintValue(obj.Altitude, 		CAAPrintValue::CAAPrintValueFormat::DEGREE_M90_TO_P90);
	} else
	{
		out <<		  CAAPrintValue(obj.lastJD, 		CAAPrintValue::CAAPrintValueFormat::DOUBLE);
		out << " " << CAAPrintValue(obj.RightAscension, CAAPrintValue::CAAPrintValueFormat::DOUBLE);
		out << " " << CAAPrintValue(obj.Declination, 	CAAPrintValue::CAAPrintValueFormat::DOUBLE);
		out << " " << CAAPrintValue(obj.LocalHourAngle, CAAPrintValue::CAAPrintValueFormat::DOUBLE);
		out << " " << CAAPrintValue(obj.Azimuth, 		CAAPrintValue::CAAPrintValueFormat::DOUBLE);
		out << " " << CAAPrintValue(obj.Altitude, 		CAAPrintValue::CAAPrintValueFormat::DOUBLE);
	}
	out << std::endl;

	return out;
}

void CAAObserveTarget::UpdateTargetData(double JD)
{
	lastJD = JD;

	double dynJD = CAADynamicalTime::UTC2TT(JD);

	SetRightAscensionDeclination(dynJD);
	SetLocalHourAngle(dynJD);
	SetAzimuthAltitude();

}

void CAAObserveTarget::SetRightAscensionDeclination(double JD)
{
	CAA2DCoordinate Topo, Equatorial;

	switch(target)
	{
	case CAAObserveTarget::CAATargetObject::LUNA 		:
		Equatorial = CAACoordinateTransformation::Ecliptic2Equatorial(CAAMoon::EclipticLongitude(JD), CAAMoon::EclipticLatitude(JD), CAANutation::TrueObliquityOfEcliptic(JD));
		Topo = CAAParallax::Equatorial2Topocentric(Equatorial.X, Equatorial.Y, CAAMoon::RadiusVector(JD)/149597870.691, longitude, latitude, height, JD);		break;
	case CAAObserveTarget::CAATargetObject::SUN 		: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::SUN);		break;
	case CAAObserveTarget::CAATargetObject::MERCURY 	: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::MERCURY); 	break;
	case CAAObserveTarget::CAATargetObject::VENUS 		: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::VENUS);		break;
	case CAAObserveTarget::CAATargetObject::MARS 		: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::MARS);		break;
	case CAAObserveTarget::CAATargetObject::JUPITER 	: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::JUPITER); 	break;
	case CAAObserveTarget::CAATargetObject::SATURN 		: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::SATURN); 	break;
	case CAAObserveTarget::CAATargetObject::URANUS 		: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::URANUS); 	break;
	case CAAObserveTarget::CAATargetObject::NEPTUNE 	: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::NEPTUNE); 	break;
	case CAAObserveTarget::CAATargetObject::PLUTO 		: Topo = GetRightAscensionDeclinationFromCAAElliptical(JD, CAAElliptical::EllipticalObject::PLUTO); 	break;
	// all conversions result in RightAscension and Declination
	case CAAObserveTarget::CAATargetObject::RADE		: Topo.X = RightAscension; Topo.Y = Declination; 														break;
	case CAAObserveTarget::CAATargetObject::AZAL		: Topo = GetRightAscensionDeclinationFromAzimuthAltitude(JD); 											break;
	case CAAObserveTarget::CAATargetObject::HADE		: Topo.X = GetRightAscensionFromLocalHourAngle(JD, LocalHourAngle); Topo.Y = Declination; 				break;
	case CAAObserveTarget::CAATargetObject::FK5STAR		: Topo = CAAFK5_1_Catalog::GetCatalogStarByNumber(catalogIndex, JD); 									break;
	case CAAObserveTarget::CAATargetObject::FK6STAR		: Topo = CAAFK6_Catalog::GetCatalogStarByNumber(catalogIndex, JD); 										break;

	default:;
	}

	RightAscension 		= CAACoordinateTransformation::MapTo0To24Range(Topo.X);
	Declination 		= CAACoordinateTransformation::MapToMinus90To90Range(Topo.Y);

};

void CAAObserveTarget::SetLocalHourAngle(double JD)
{
	double LongtitudeAsHourAngle 	= CAACoordinateTransformation::DegreesToHours(longitude);
	double AST 						= CAASidereal::ApparentGreenwichSiderealTime(JD);
	LocalHourAngle					= CAACoordinateTransformation::MapTo0To24Range(AST - LongtitudeAsHourAngle - RightAscension);
}

void CAAObserveTarget::SetAzimuthAltitude(void)
{
	CAA2DCoordinate Horizontal 		= CAACoordinateTransformation::Equatorial2Horizontal(LocalHourAngle, Declination, latitude);

	Horizontal.Y += CAARefraction::RefractionFromTrue(Horizontal.Y);

	Azimuth = CAACoordinateTransformation::MapTo0To360Range(Horizontal.X);
	Altitude = CAACoordinateTransformation::MapToMinus90To90Range(Horizontal.Y);
}

CAA2DCoordinate CAAObserveTarget::GetRightAscensionDeclinationFromCAAElliptical(double JD, CAAElliptical::EllipticalObject obj)
{
	CAAEllipticalPlanetaryDetails details = CAAElliptical::Calculate(JD, obj, true);

	return CAAParallax::Equatorial2Topocentric(	details.ApparentGeocentricRA, details.ApparentGeocentricDeclination,
			details.ApparentGeocentricDistance, longitude, latitude, height, JD);
}

double CAAObserveTarget::GetRightAscensionFromLocalHourAngle(double JD, double lha)
{
	double LongtitudeAsHourAngle 	= CAACoordinateTransformation::DegreesToHours(longitude);
	double AST 						= CAASidereal::ApparentGreenwichSiderealTime(JD);
	return CAACoordinateTransformation::MapTo0To24Range(AST - LongtitudeAsHourAngle - lha);
}

CAA2DCoordinate CAAObserveTarget::GetRightAscensionDeclinationFromAzimuthAltitude(double JD)
{
	Altitude +=CAARefraction::RefractionFromApparent(Altitude);
	CAA2DCoordinate p, Equatorial = CAACoordinateTransformation::Horizontal2Equatorial(Azimuth, Altitude, latitude);
	p.X = GetRightAscensionFromLocalHourAngle(JD, Equatorial.X);
	p.Y = Equatorial.Y;
	return  p;
}
