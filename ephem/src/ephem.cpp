//============================================================================
// Name        : ephem.cpp
// Author      : Thomas Rinder
// Version     :
// Copyright   : Copyright 2019 by Thomas
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
AA+ framework
Copyright (c) 2003 - 2019 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise)
when your product is released in binary form. You are allowed to modify the source code in any way you want
except you cannot modify the copyright details at the top of each module. If you want to distribute source
code with your application, then you are only allowed to distribute versions released by the author. This is
to maintain a single distribution point for the source code.

*/

//          Copyright Joe Coder 2004 - 2006.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)



#include <iostream>
#include <string>
#include <fstream>

#include "CAAObserveTarget.hpp"
#include "FK5_1.hpp"
#include "FK6.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/program_options.hpp>
#include <boost/version.hpp>

#include "config.hpp"

using namespace std;

/*
 * 	keep supportedTargetStrings in order of supportedTargets
 */
const std::vector<std::string> 	supportedTargetStrings  = {
		"sun",
		"mercury",
		"venus",
		"mars",
		"jupiter",
		"saturn",
		"uranus",
		"neptune",
		"pluto",
		"luna",
		"rade",
		"azal",
		"hade",
		"fk5",
		"fk6"};

const std::vector<CAAObserveTarget::CAATargetObject> supportedTargets = {
		CAAObserveTarget::CAATargetObject::SUN,
		CAAObserveTarget::CAATargetObject::MERCURY,
		CAAObserveTarget::CAATargetObject::VENUS,
		CAAObserveTarget::CAATargetObject::MARS,
		CAAObserveTarget::CAATargetObject::JUPITER,
		CAAObserveTarget::CAATargetObject::SATURN,
		CAAObserveTarget::CAATargetObject::URANUS,
		CAAObserveTarget::CAATargetObject::NEPTUNE,
		CAAObserveTarget::CAATargetObject::PLUTO,
		CAAObserveTarget::CAATargetObject::LUNA,
		CAAObserveTarget::CAATargetObject::RADE,
		CAAObserveTarget::CAATargetObject::AZAL,
		CAAObserveTarget::CAATargetObject::HADE,
		CAAObserveTarget::CAATargetObject::FK5STAR,
		CAAObserveTarget::CAATargetObject::FK6STAR,
		CAAObserveTarget::CAATargetObject::UNDEFINED
};

typedef struct
{
	double latitude, longitude, height, stepsize;
	double RightAscension, Declination, LocalHourAngle, Azimuth, Altitude;
	std::string datetimeUTC, target;
	unsigned int steps, catalog_number;
	bool printTraditional;
} ephemConfig;

int main(int argc, const char *argv[]) {

	ephemConfig cmd, configFile;
	cmd.printTraditional 		= false;

	std::string configFileName;

	CAAObserveTarget::CAATargetObject caaTarget = CAAObserveTarget::CAATargetObject::UNDEFINED;

	try
	{
		// parse arguments
		boost::program_options::options_description desc{"Options"};
		desc.add_options()
												  ("help,h", "print help")
												  ("lat",   		boost::program_options::value<double>(&cmd.latitude) 			->default_value( CAACoordinateTransformation::DMSToDegrees(54,19,16.79)), "observer latitude (decimal degrees, south is negative).")
												  ("long",  		boost::program_options::value<double>(&cmd.longitude)		 	->default_value(-CAACoordinateTransformation::DMSToDegrees(10, 8, 5.6 )), "observer longitude (decimal degrees, east is negative).")
												  ("height",  		boost::program_options::value<double>(&cmd.height)	 		 	->default_value(  7.0f), "observer height (meters).")
												  ("UTC",		    boost::program_options::value<std::string>(&cmd.datetimeUTC) 	->default_value(boost::posix_time::to_simple_string(boost::posix_time::second_clock::universal_time())), "observer date time UTC\nformat \"2019-Sep-15 17:55:39\"")
												  ("target,t",		boost::program_options::value<std::string>(&cmd.target)			->default_value("sun"),	"ephemerides target: \nsun, mercury, venus, luna, mars, jupiter, saturn, uranus, neptune, pluto and rade, azal, hade, fk5, fk6 (requires additional inputs - see below).")
												  ("stepsize", 		boost::program_options::value<double>(&cmd.stepsize)			->default_value(86400.0), "step size in s.")
												  ("steps", 		boost::program_options::value<unsigned int>(&cmd.steps)			->default_value(1),	"number of steps.")
												  ("traditional", "print in traditional form otherwise decimal.")
												  ("ra", 			boost::program_options::value<double>(&cmd.RightAscension)		->default_value(0.0), "RightAscension in decimal hours required for rade target.")
												  ("de", 			boost::program_options::value<double>(&cmd.Declination)			->default_value(0.0), "Declination in decimal degrees required for rade or hade target.")
												  ("ha", 			boost::program_options::value<double>(&cmd.LocalHourAngle)		->default_value(0.0), "LocalHourAngle in decimal hours required for hade target.")
												  ("az", 			boost::program_options::value<double>(&cmd.Azimuth)				->default_value(0.0), "Azimuth in decimal degrees required for azal target.")
												  ("al", 			boost::program_options::value<double>(&cmd.Altitude)			->default_value(0.0), "Altitude in decimal degrees required for azal target.")
												  ("catn,n",		boost::program_options::value<unsigned int>(&cmd.catalog_number)->default_value(1), "Number in star catalog required for fk5 or fk6 target.")
												  ("docu,d", "print documentation.")
												  ("config,c",		boost::program_options::value<std::string>(&configFileName), "Load config file.");

		boost::program_options::options_description fileOptions{"File"};
		fileOptions.add_options()
												("ObserverLatitude",   		boost::program_options::value<double>(&configFile.latitude), "observer latitude (decimal degrees, south is negative).")
												("ObserverLongitude",  		boost::program_options::value<double>(&configFile.longitude), "observer longitude (decimal degrees, east is negative).")
												("ObserverHeight",  		boost::program_options::value<double>(&configFile.height), "observer height (meters).")
												("DateTimeUTC",		    	boost::program_options::value<std::string>(&configFile.datetimeUTC), "observer date time UTC\nformat \"2019-Sep-15 17:55:39\"")
												("Target",					boost::program_options::value<std::string>(&configFile.target), "ephemerides target: \nsun, mercury, venus, luna, mars, jupiter, saturn, uranus, neptune, pluto and rade, azal, hade, fk5, fk6 (requires additional inputs - see below).")
												("StepSize", 				boost::program_options::value<double>(&configFile.stepsize), "step size in s.")
												("Steps", 					boost::program_options::value<unsigned int>(&configFile.steps), "number of steps.")
												("PrintTraditional", "print in traditional form otherwise decimal.")
												("RightAscension", 			boost::program_options::value<double>(&configFile.RightAscension), "RightAscension in decimal hours required for rade target.")
												("Declination", 			boost::program_options::value<double>(&configFile.Declination), "Declination in decimal degrees required for rade or hade target.")
												("LocalHourAngle", 			boost::program_options::value<double>(&configFile.LocalHourAngle), "LocalHourAngle in decimal hours required for hade target.")
												("LocalAzimuth", 			boost::program_options::value<double>(&configFile.Azimuth), "Azimuth in decimal degrees required for azal target.")
												("LocalAltitude", 			boost::program_options::value<double>(&configFile.Altitude), "Altitude in decimal degrees required for azal target.")
												("CatalogNumber",			boost::program_options::value<unsigned int>(&configFile.catalog_number), "Number in star catalog required for fk5 or fk6 target.");

		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);

		boost::program_options::notify(vm);
		// copy command line options and defaults
		if (vm.count("traditional"))	cmd.printTraditional = true;

	    if (vm.count("config"))
	    {
	    	std::ifstream ifs(configFileName.c_str());
	    	if(ifs.fail())
	    	{
	    		std::cerr << "Error opening config file: " << configFileName << std::endl;
	    	}
	    	else
	    	{
	    		boost::program_options::store(boost::program_options::parse_config_file(ifs, fileOptions), vm);
	    		boost::program_options::notify(vm);

	    		// override command line options from config file
	    		if(vm.count("ObserverLatitude")) 	cmd.latitude 			= configFile.latitude;
	    		if(vm.count("ObserverLongitude")) 	cmd.longitude 			= configFile.longitude;
	    		if(vm.count("ObserverHeight")) 		cmd.height 				= configFile.height;
	    		if(vm.count("DateTimeUTC")) 		cmd.datetimeUTC 		= configFile.datetimeUTC;
	    		if(vm.count("Target")) 				cmd.target 				= configFile.target;
	    		if(vm.count("StepSize")) 			cmd.stepsize 			= configFile.stepsize;
	    		if(vm.count("Steps")) 				cmd.steps 				= configFile.steps;
	    		if(vm.count("PrintTraditional"))	cmd.printTraditional 	= true;
	    		if(vm.count("RightAscension")) 		cmd.RightAscension 		= configFile.RightAscension;
	    		if(vm.count("Declination")) 		cmd.Declination 		= configFile.Declination;
	    		if(vm.count("LocalHourAngle")) 		cmd.LocalHourAngle 		= configFile.LocalHourAngle;
	    		if(vm.count("LocalAzimuth")) 		cmd.Azimuth 			= configFile.Azimuth;
	    		if(vm.count("LocalAltitude")) 		cmd.Altitude 			= configFile.Altitude;
	    		if(vm.count("CatalogNumber")) 		cmd.catalog_number 		= configFile.catalog_number;
	    	}
	    }

		if (vm.count("help"))
		{
			cout << "Usage: ephem -options ... " << std::endl << std::endl;
			cout << desc << std::endl;
			return 0;
		}

		if (vm.count("docu"))
		{
			cout 	<<  PROJECT_NAME << " version " << PROJECT_VER << "(" << PROJECT_HOST_SYSTEM << ")"	<< std::endl
					<< "------------------------------------------------------------" 	<< std::endl
					<< "ephem is a minimalistic astrometry tool which returns" 			<< std::endl
					<< "date/time Ra De Ha Az Al to stdout for a given target" 			<< std::endl
					<< "(sun, luna, planets, stars from FK5 and FK6)."					<< std::endl
					<< "It also converts Az Al -> Ra De(Ha) and"						<< std::endl
					<< "Ha De -> Ra De(and Az Al)."										<< std::endl
					<< "------------------------------------------------------------" 	<< std::endl
					<< "please report any issues to thomas.rinder@fh-kiel.de." 			<< std::endl
					<< "Compiled on " << __DATE__ << " " << __TIME__ << std::endl
					<< "------------------------------------------------------------" 	<< std::endl
					<< "ephem is published under the conditions as stated below:"  		<< std::endl
					<< "Do whatever you want to do with ephem but " 					<< std::endl
					<< "but respect all copyrights, licenses as used and use at your own risk." << std::endl
					<< "------------------------------------------------------------" 	<< std::endl
					<< "ephem uses the" << std::endl
					<< "------------------------------------------------------------" 	<< std::endl
					<< "AA+ v2.05 A class framework for Computational Astronomy" 		<< std::endl
					<< "(see http://www.naughter.com/aa.html for source, documentation and copyright)" 	<< std::endl
					<< "(unzip, cmake, make, make install and use LD_LIBRARY_PATH=\"/usr/local/lib\")" 	<< std::endl
					<< "------------------------------------------------------------" 	<< std::endl
					<< "Boost C++ libraries "  << "version " << BOOST_LIB_VERSION << std::endl
					<< "(see https://www.boost.org/ for source, documentation and https://www.boost.org/users/license.html for license)." << std::endl
					<< "(on ubuntu use \"sudo apt-get install libboost-all-dev\")"		<< std::endl
					<< "------------------------------------------------------------" 	<< std::endl
					<< "Catalogue of Fundamental Stars"									<< std::endl
					<< "FK5 (" << CAAFK5_1_Catalog::GetNumStars() << " stars)"		    << std::endl
					<< "http://cdsarc.u-strasbg.fr/viz-bin/cat/I/149"					<< std::endl
					<< "FK6 (" << CAAFK6_Catalog::GetNumStars() << " stars)"		    << std::endl
					<< "http://cdsarc.u-strasbg.fr/viz-bin/cat/I/264"					<< std::endl
					<< "(see http://cdsarc.u-strasbg.fr/ for license)"					<< std::endl
					<< "------------------------------------------------------------" 	<< std::endl;
			return 0;
		}

		for(unsigned int i = 0; i < supportedTargetStrings.size(); i++)
		{
			if(supportedTargetStrings[i].compare(cmd.target)==0)
			{
				caaTarget = supportedTargets[i];
				break;
			}
		}

		if(caaTarget == CAAObserveTarget::CAATargetObject::UNDEFINED)
		{
			cout << "Error: ephemerides target " << cmd.target << " not recognized. Exit." << std::endl;
			return 0;
		}

		// TODO if malformed datetimeUTC there is a not handled exception.
		boost::posix_time::ptime ptUTC = boost::posix_time::time_from_string(cmd.datetimeUTC);

		/*
		 *		use AA+
		 */

		// create CAAObserveTarget
		CAAObserveTarget obj(cmd.latitude, cmd.longitude, cmd.height, caaTarget, cmd.printTraditional, cmd.RightAscension, cmd.Declination, cmd.LocalHourAngle, cmd.Azimuth, cmd.Altitude, cmd.catalog_number);

		// calculate JD
		CAADate UTCdate(ptUTC.date().year(), ptUTC.date().month(), ptUTC.date().day(), ptUTC.time_of_day().hours(), ptUTC.time_of_day().minutes(), ptUTC.time_of_day().seconds(), true);

		double JD 			= UTCdate.Julian();
		double JDstepsize 	= cmd.stepsize / 86400.0;

		// calculate and dump results
		for(unsigned int i = 0; i < cmd.steps; i++, JD+=JDstepsize)
		{
			obj.UpdateTargetData(JD);
			cout << obj;
		}

	}
	catch (const boost::program_options::error &ex)
	{
		std::cerr << ex.what() << '\n';
	}
	return 0;
}
