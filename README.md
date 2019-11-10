# ephem

ephem is a minimalistic astrometry tool which returns

| date and time string | RightAscension | Declination | LocalHourAngle | LocalAzimuth | LocalAltitude |

to stdout for a given target (sun, luna, planets, stars from FK5 and FK6), observer location at UTC date and time.

*It is a command line wrapper to a small subset of the AA+ class framework for Computational Astronomy.*

# Example

Where is luna right now in the city Kiel of Germany? 

./ephem -t luna --traditional

2019-11-09 18:43:22 +01h06m04.52s +00°41m02.13s +21h33m35.03s +317°15m12.67s +28°34m38.76s

which are | date and time string | RightAscension | Declination | LocalHourAngle | LocalAzimuth | LocalAltitude .


# How to build on Ubuntu? 

1. Compile AA+ v2.05 A class framework for Computational Astronomy
(see http://www.naughter.com/aa.html for source, documentation and copyright)
(unzip, cmake, make, make install and use LD_LIBRARY_PATH="/usr/local/lib")

2. Install Boost C++ libraries version >= 1.65.1 
(see https://www.boost.org/ for source, documentation and https://www.boost.org/users/license.html for license).
(use "sudo apt-get install libboost-all-dev")

3. Create a directory, cd <directory>, run cmake <pathto>/ephem/src and make there.

4. Type ./bin/ephem -h or ./ephem -d to get more info.

#How to use?

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

Example:	Get ephemerides of the sun at Phuket  2020-12-24 0:0:0 UTC in steps of one hour.

./ephem -t sun --traditional --UTC "2020-12-24 0:0:0" --steps 24 --stepsize 3600 --lat 7.878978 --long -98.398392

```
2020-12-24 00:00:00 +18h11m28.39s -23°24m41.08s +18h35m12.82s +294°28m35.28s +05°01m15.32s
2020-12-24 01:00:00 +18h11m39.44s -23°24m38.89s +19h35m11.63s +297°53m13.93s +18°15m03.03s
2020-12-24 02:00:00 +18h11m50.45s -23°24m36.56s +20h35m10.48s +303°26m31.40s +31°01m44.62s
2020-12-24 03:00:00 +18h12m01.43s -23°24m34.03s +21h35m09.36s +312°24m02.35s +42°46m56.84s
2020-12-24 04:00:00 +18h12m12.38s -23°24m31.26s +22h35m08.26s +326°58m14.96s +52°28m34.15s
2020-12-24 05:00:00 +18h12m23.31s -23°24m28.21s +23h35m07.19s +349°08m46.00s +58°08m17.61s
2020-12-24 06:00:00 +18h12m34.24s -23°24m24.88s +00h35m06.11s +015°07m45.83s +57°34m11.56s
2020-12-24 07:00:00 +18h12m45.17s -23°24m21.26s +01h35m05.04s +036°01m40.51s +51°02m37.38s
2020-12-24 08:00:00 +18h12m56.13s -23°24m17.37s +02h35m03.94s +049°27m17.16s +40°53m22.28s
2020-12-24 09:00:00 +18h13m07.11s -23°24m13.25s +03h35m02.82s +057°42m22.99s +28°54m28.95s
2020-12-24 10:00:00 +18h13m18.12s -23°24m08.94s +04h35m01.66s +062°49m51.53s +16°00m56.51s
2020-12-24 11:00:00 +18h13m29.18s -23°24m04.49s +05h35m00.46s +065°57m04.44s +02°47m59.76s
2020-12-24 12:00:00 +18h13m40.28s -23°23m59.97s +06h34m59.21s +067°34m43.12s -10°21m55.09s
2020-12-24 13:00:00 +18h13m51.42s -23°23m55.43s +07h34m57.93s +067°48m23.00s -24°07m07.84s
2020-12-24 14:00:00 +18h14m02.60s -23°23m50.94s +08h34m56.60s +066°16m28.51s -37°48m46.19s
2020-12-24 15:00:00 +18h14m13.82s -23°23m46.55s +09h34m55.24s +061°44m10.09s -51°11m56.28s
2020-12-24 16:00:00 +18h14m25.06s -23°23m42.31s +10h34m53.85s +050°20m25.95s -63°37m27.52s
2020-12-24 17:00:00 +18h14m36.32s -23°23m38.24s +11h34m52.45s +020°31m24.62s -72°36m42.35s
2020-12-24 18:00:00 +18h14m47.58s -23°23m34.36s +12h34m51.05s +332°39m42.72s -71°38m01.78s
2020-12-24 19:00:00 +18h14m58.84s -23°23m30.67s +13h34m49.65s +307°00m00.27s -61°44m09.88s
2020-12-24 20:00:00 +18h15m10.08s -23°23m27.14s +14h34m48.26s +297°12m38.30s -49°04m07.52s
2020-12-24 21:00:00 +18h15m21.29s -23°23m23.76s +15h34m46.91s +293°18m46.84s -35°36m19.95s
2020-12-24 22:00:00 +18h15m32.47s -23°23m20.47s +16h34m45.59s +292°07m00.08s -21°53m18.58s
2020-12-24 23:00:00 +18h15m43.60s -23°23m17.21s +17h34m44.31s +292°34m48.67s -08°08m21.44s
```
  
#How to use a config file?

Run ./ephem -c config.ini . 


```
# example config file 

# set topocentric observer location in decimal degrees and meters  

ObserverLatitude		= 54.321330555555562
ObserverLongitude		= -10.134888888888888
ObserverHeight			= 7.0

# set initial date and time (string) of observer in UTC
# if not given it is UTC from system date ant time

# DateTimeUTC			= 2029-11-04 19:12:51

# set the observation target

Target					= fk5

# configure steps to calculate

StepSize				= 86400
Steps					= 1

# configure output to print date and time in traditional form 
PrintTraditional		= true		

# additional inputs according to target,
# if target is rade so set 

# RightAscension	= 0
# Declination		= 0

# if target is hade so set 
# LocalHourAngle	= 0

# if target is azal so set 

# LocalAzimuth	= 0
# LocalAltitude	= 0

# if target is fk5 or fk6 so set 

CatalogNumber			= 907	# polaris
#CatalogNumber			= 906	# 2Umi
#CatalogNumber			= 932	# Yildun
```
