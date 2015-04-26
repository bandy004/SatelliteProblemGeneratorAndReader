all: SatelliteProblemReader.cpp SatelliteProblemGenerator.cpp
	g++ -o satellite_gen SatelliteProblemGenerator.cpp -I.
	g++ -o satellite_read SatelliteProblemReader.cpp -I.