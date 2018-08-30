02-13-2018
last update: 08-29-2018
written by Derek Huang

08-29-2018

Fixed some typos in the file, and made the package part of the prog_proj github repo. Also, I capitalize my words now. Wow. 

background:I couldn't figure out which dorm I wanted to live in next year, so I wrote a program to rank them for me. Uses a simple four-factor model, and was only tested for a few NYU dorms, although I'm sure the code could be adapted pretty easily.

Written in Java, in a NetBeans environment; hopefully one of the last times I will ever use Java. Might as well use C for any general purpose programming.

02-13-2018

dorm selection program: based on quantifiable travel times to Stern, the nearest dining hall, the nearest gym, and the nearest quiet study space, these times will be aggregated into a total "elapsed time" quantifiable, with the lower score signifying a better hall. capitalized coefficients adjust for relative weighting of each particular category of time. 

formula:

 - s: time to stern
 - g: time to nearest gym with weights and cardio machines
 - d: time to nearest dining hall
 - q: time to nearest quiet study location
 
T(s, g, d, q) = Ss + Gg + Dd + Qq

results of initial run with arbitrary weights 1.2, 0.7, 0.8, 1.1
1. t_util:	31.10	Alumni Hall
2. t_util:	32.20	Second Street
3. t_util:	33.60	Coral Tower
4. t_util:	36.00	Palladium
5. t_util:	41.20	Carlyle Court
6. t_util:	59.10	Gramercy Green
7. t_util:	77.70	Lafayette Hall

results of run with even weights 1, 1, 1, 1
1. t_util:	30.00	Alumni Hall
2. t_util:	31.00	Coral Tower
3. t_util:	32.00	Palladium
4. t_util:	34.00	Second Street
5. t_util:	41.00	Carlyle Court
6. t_util:	57.00	Gramercy Green
7. t_util:	82.00	Lafayette Hall

results of run with heavier weights 1.4, 1.1, 0.9, 1.2
1. t_util:	37.00	Alumni Hall
2. t_util:	38.20	Second Street
3. t_util:	39.20	Coral Tower
4. t_util:	41.00	Palladium
5. t_util:	48.70	Carlyle Court
6. t_util:	69.40	Gramercy Green
7. t_util:	93.60	Lafayette Hall


