# ephem

ephem is a minimalistic astrometry tool which returns

| date and time string | RightAscension | Declination | LocalHourAngle | LocalAzimuth | LocalAltitude |

to stdout for a given target (sun, luna, planets, stars from FK5 and FK6), observer location at UTC date and time.
RightAscension and Declination are in Jnow reference frame. Times all in UTC.

*It is a command line wrapper to a small subset of the AA+ class framework for Computational Astronomy.*

# Whats the idea behind ?

ephem is a part of a DIY telescope mount library. So is it designed to be compact and fits into midsized controller designs
like ST F476.

# Example

Where is luna right now seen from the city Kiel of Germany? 

./ephem -t luna --traditional

2019-11-09 18:43:22 +01h06m04.52s +00°41m02.13s +21h33m35.03s +317°15m12.67s +28°34m38.76s

which are | date and time string | RightAscension | Declination | LocalHourAngle | LocalAzimuth | LocalAltitude .


# How to build on Ubuntu? 

1. Compile AA+ >= v2.05  A class framework for Computational Astronomy
(see http://www.naughter.com/aa.html for source, documentation and copyright)
(unzip, cmake, make, make install and use LD_LIBRARY_PATH="/usr/local/lib")

2. Install Boost C++ libraries version >= 1.65.1 
(see https://www.boost.org/ for source, documentation and https://www.boost.org/users/license.html for license).
(use "sudo apt-get install libboost-all-dev")

3. Create a directory, cd directory, run cmake pathto/ephem/src and make there.

4. Type ./bin/ephem -h or ./ephem -d to get more info.

# How to use?

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

Example:	Get some ephemerides of the sun at Kiel/germany in december 2019.

./ephem -t  sun --steps 24 --UTC "2019-12-10 11:20:0"  --traditional

```
2019-12-10 11:20:00 +17h08m12.85s -22°54m18.16s +00h09m05.18s +002°08m43.06s +12°49m14.26s
2019-12-11 11:20:00 +17h12m36.66s -22°59m30.29s +00h08m37.93s +002°02m09.90s +12°44m12.56s
2019-12-12 11:20:00 +17h17m00.86s -23°04m15.14s +00h08m10.29s +001°55m32.65s +12°39m37.65s
2019-12-13 11:20:00 +17h21m25.42s -23°08m32.59s +00h07m42.30s +001°48m51.59s +12°35m29.63s
2019-12-14 11:20:00 +17h25m50.32s -23°12m22.50s +00h07m13.97s +001°42m07.01s +12°31m48.62s
2019-12-15 11:20:00 +17h30m15.51s -23°15m44.74s +00h06m45.34s +001°35m19.21s +12°28m34.71s
2019-12-16 11:20:00 +17h34m40.98s -23°18m39.18s +00h06m16.43s +001°28m28.48s +12°25m48.00s
2019-12-17 11:20:00 +17h39m06.69s -23°21m05.74s +00h05m47.28s +001°21m35.14s +12°23m28.58s
2019-12-18 11:20:00 +17h43m32.62s -23°23m04.30s +00h05m17.91s +001°14m39.51s +12°21m36.52s
2019-12-19 11:20:00 +17h47m58.73s -23°24m34.78s +00h04m48.36s +001°07m41.94s +12°20m11.89s
2019-12-20 11:20:00 +17h52m24.99s -23°25m37.11s +00h04m18.65s +001°00m42.79s +12°19m14.75s
2019-12-21 11:20:00 +17h56m51.37s -23°26m11.24s +00h03m48.83s +000°53m42.44s +12°18m45.13s
2019-12-22 11:20:00 +18h01m17.83s -23°26m17.14s +00h03m18.92s +000°46m41.28s +12°18m43.07s
2019-12-23 11:20:00 +18h05m44.34s -23°25m54.79s +00h02m48.98s +000°39m39.73s +12°19m08.55s
2019-12-24 11:20:00 +18h10m10.85s -23°25m04.20s +00h02m19.02s +000°32m38.23s +12°20m01.59s
2019-12-25 11:20:00 +18h14m37.34s -23°23m45.38s +00h01m49.11s +000°25m37.20s +12°21m22.16s
2019-12-26 11:20:00 +18h19m03.75s -23°21m58.35s +00h01m19.26s +000°18m37.10s +12°23m10.24s
2019-12-27 11:20:00 +18h23m30.05s -23°19m43.16s +00h00m49.53s +000°11m38.35s +12°25m25.79s
2019-12-28 11:20:00 +18h27m56.19s -23°16m59.87s +00h00m19.95s +000°04m41.39s +12°28m08.77s
2019-12-29 11:20:00 +18h32m22.15s -23°13m48.53s +23h59m50.55s +359°57m46.64s +12°31m19.12s
2019-12-30 11:20:00 +18h36m47.88s -23°10m09.24s +23h59m21.38s +359°50m54.51s +12°34m56.76s
2019-12-31 11:20:00 +18h41m13.34s -23°06m02.09s +23h58m52.47s +359°44m05.40s +12°39m01.62s
2020-01-01 11:20:00 +18h45m38.51s -23°01m27.20s +23h58m23.86s +359°37m19.68s +12°43m33.59s
2020-01-02 11:20:00 +18h50m03.36s -22°56m24.72s +23h57m55.56s +359°30m37.73s +12°48m32.56s
```

  
# How to use a config file?

Where is polaris right now seen from Kiel/Germany?

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
