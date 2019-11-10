# ephem

**ephem is a minimalistic astrometry tool which returns
date/time Ra De Ha Az Al to stdout for a given target
(sun, luna, planets, stars from FK5 and FK6).
It also converts Az Al -> Ra De(Ha) and
Ha De -> Ra De(and Az Al).**

***It is a command line wrapper to a small subset of the AA+ class framework for Computational Astronomy.***

Example: ./ephem -t luna --traditional

2019-11-09 18:43:22 +01h06m04.52s +00°41m02.13s +21h33m35.03s +317°15m12.67s +28°34m38.76s

How to build on Ubuntu ? 

1. Compile AA+ v2.05 A class framework for Computational Astronomy
(see http://www.naughter.com/aa.html for source, documentation and copyright)
(unzip, cmake, make, make install and use LD_LIBRARY_PATH="/usr/local/lib")

2. Install Boost C++ libraries version >= 1.65.1 
(see https://www.boost.org/ for source, documentation and https://www.boost.org/users/license.html for license).
(use "sudo apt-get install libboost-all-dev")

3. Create a directory and run cmake ../ephem/src and make there.

4. Type ./bin/ephem -h or ./ephem -d to get more info.

```
Usage: ephem -options ...

Options:
  -h [ --help ]                     print help
  --lat arg (=54.321330555555562)   observer latitude (decimal degrees, south
                                    is negative).
  --long arg (=-10.134888888888888) observer longitude (decimal degrees, east
                                    is negative).
  --height arg (=7)                 observer height (meters).
  --UTC arg (=2019-Nov-09 18:42:11) observer date time UTC
                                    format "2019-Sep-15 17:55:39"
  -t [ --target ] arg (=sun)        ephemerides target:
                                    sun, mercury, venus, luna, mars, jupiter,
                                    saturn, uranus, neptune, pluto and rade,
                                    azal, hade, fk5, fk6 (requires additional
                                    inputs - see below).
  --stepsize arg (=86400)           step size in s.
  --steps arg (=1)                  number of steps.
  --traditional                     print in traditional form otherwise
                                    decimal.
  --ra arg (=0)                     RightAscension in decimal hours required
                                    for rade target.
  --de arg (=0)                     Declination in decimal degrees required for
                                    rade or hade target.
  --ha arg (=0)                     LocalHourAngle in decimal hours required
                                    for hade target.
  --az arg (=0)                     Azimuth in decimal degrees required for
                                    azal target.
  --al arg (=0)                     Altitude in decimal degrees required for
                                    azal target.
  -n [ --catn ] arg (=1)            Number in star catalog required for fk5 or
                                    fk6 target.
  -d [ --docu ]                     print documentation.
  -c [ --config ] arg               Load config file.
  ```
  
