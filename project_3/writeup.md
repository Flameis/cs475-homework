Project Requirements:

Start with this sample code, proj03.cpp. Left-click to look at it. Right-click to download it. Place it in the same folder as your USCities.data file.
Fill in the missing parts of the program, especially the #pragma that goes before the NUMCITIES for-loop.
The Makefile I used looks like this:

```
proj03:		proj03.cpp
	g++  proj03.cpp    -o  proj03    -lm  -fopenmp
```

Run the program for some combination of NUMT and NUMCAPITALS values..
Vary the number of threads (NUMT) and the number of capital cities (NUMCAPITALS). I ended up using a script that looked like this:

```
#!/bin/bash
for t in 1 2 4 6 8
do
  for n in 2 3 4 5 10 15 20 30 40 50
  do
     g++   proj03.cpp  -DNUMT=$t -DNUMCAPITALS=$n  -o proj03  -lm  -fopenmp
    ./proj03
  done
done
```

This is what I did, but, you can handle the requirements any way you please. 

For Those New to C/C++ -- What are those struct Things?

In the code, you will see constructs like:

```
struct city
{
    std::string     name;
    float           longitude;
    float           latitude;
    int             capitalnumber;
    float           mindistance;
};
```

Don't let that spook you. A struct is just a way to bundle a bunch of variables together under one name, city in this case. You get at each sub-element with a . (a period), like this:

```
struct city    corvallis;
corvallis.name =      "Corvallis, OR";
corvallis.longitude = 123.27;
corvallis.latitude =   44.57;
```

An array of structs works just like an array of any other variable type. The cities are all in an array called struct city Cities[ ] (which is in the USCities.data file). To, perhaps, do something with the longitude of city #100, we would write:


... Cities[100].longitude ...

Or, if processing the cities in a for-loop:


... Cities[i].longitude ...

Commentary:

Your commentary write-up (turned in as a PDF file) should include:

    Tell what machine you ran this on
    Tell what operating system you were using
    Tell what compiler you used
    Include the rectangular table of performance data.
    Include a graph of performance vs. NUMT with the colored curves being NUMCAPITALS.
    Include a graph of performance vs. NUMCAPITALS cities with the colored curves being NUMT.
    Tell us what you discovered by doing this. What patterns are you seeing in the graphs? 

Where Are The States Located?