/* 
 * File:   main.cpp
 * Author: debdeep
 *
 * Created on 7 March 2015, 1:37 PM
 */

#include <cstdlib>
#include<iostream>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<cstdlib>
#include<cassert>
#include<ctime>
#include <cassert>
#include<cmath>
#include "stringutil.h"

using namespace std;

typedef std::pair<int, int> intpair;
typedef std::vector<int> intvector;
typedef std::vector< intvector > intmatrix;
typedef std::vector< std::vector< intpair> > intpairvectorvector;

class SatelliteProblemReader
{
public:
    
    std::stringstream domain_name;
    std::stringstream instance_name;
    
    int num_satellites;
    int num_instrument_types;
    int num_antenna_types;
    int num_ground_statiion;
    int num_timewindows;
    
    int instrument_max_on_time;
    int instrument_min_off_time;
    
    intvector inst_rate;
    intvector ant_rate;
    intvector ant_angular_speed;
    intvector inst_angular_speed;
    intvector inst_bat_rate;
    intvector ant_bat_rate;
    intvector sat_unit_recharge;
    
    intmatrix inst_sat_map;
    intmatrix ant_sat_map;
    intmatrix ant_gs_map;
    intmatrix gs_angular_distance;
    
    std::vector< std::vector< std::vector< intpair > > > satellite_groundstation_visibility;
    intpairvectorvector satellite_sun_visibility;
    
    int num_observations;
    intmatrix observations_inst_map;
    intvector observation_size;
    intmatrix observations_angualr_distances;
    
    std::vector< std::vector< std::vector< intpair > > > observation_satellite_time_windows;
 
    
    SatelliteProblemReader()
    {     
    }
    
    void readInstrumentRate(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_instrument_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            inst_rate.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    
    void readInstrumentBatConRate(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_instrument_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            inst_bat_rate.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    
    void readInstrumentAngularSpeed(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_instrument_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            inst_angular_speed.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    void readAntennaRate(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_antenna_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            ant_rate.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    
    void readAntennaBatConRate(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_antenna_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            ant_bat_rate.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    
    void readAntennaAngularSpeed(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_antenna_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            ant_angular_speed.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    
    
    void readInstrumentSatelliteMap(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_instrument_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(atoi(tokens[0].c_str()) == i);
            inst_sat_map.push_back(intvector());
            if( tokens.size() > 1 )
            {
                line = tokens[1];
                tokens.clear();
                tokenize(line, tokens, std::string("\t"));
                
                for(int j = 0; j < tokens.size(); j++)
                {
                    inst_sat_map[i].push_back(atoi(tokens[j].c_str()));
                }
            }
        }
    }
    void readAntennaSatelliteMap(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_antenna_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(atoi(tokens[0].c_str()) == i);
            ant_sat_map.push_back(intvector());
            if( tokens.size() > 1 )
            {
                line = tokens[1];
                tokens.clear();
                tokenize(line, tokens, std::string("\t"));
                
                for(int j = 0; j < tokens.size(); j++)
                {
                    ant_sat_map[i].push_back(atoi(tokens[j].c_str()));
                }
            }
        }
        
        std::cout<<"Done"<<std::endl;
    }
    void readAntennaGroundStationMap(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_antenna_types; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(atoi(tokens[0].c_str()) == i);
            ant_gs_map.push_back(intvector());
            if( tokens.size() > 1 )
            {
                line = tokens[1];
                tokens.clear();
                tokenize(line, tokens, std::string("\t"));
                
                for(int j = 0; j < tokens.size(); j++)
                {
                    ant_gs_map[i].push_back(atoi(tokens[j].c_str()));
                }
            }
        }
    }
    void readSatelliteUnitRecharge(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_satellites; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            sat_unit_recharge.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    void readSatelliteSunVisibility(std::ifstream& reader)
    {
        for(int i = 0; i < num_satellites; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            line = tokens[1];
            tokens.clear();
            tokenize(line, tokens, std::string("\t"));
            satellite_sun_visibility.push_back( std::vector<intpair>() );
            for(int j = 0; j < tokens.size(); j++)
            {
                std::string pairstr = tokens[j];
                std::vector<std::string> pairtokens;
                tokenize(pairstr, pairtokens, std::string("[,]"));
                assert(pairtokens.size() == 2);
                satellite_sun_visibility[i].push_back(std::make_pair<int, int>(atoi(pairtokens[0].c_str()), atoi(pairtokens[1].c_str())));
            }
        }
    }
    void readSatelliteGroundStationVisibility(std::ifstream& reader)
    {
        for(int i = 0; i < num_satellites; i++)
        {
            std::string line1;
            std::getline(reader, line1);
            satellite_groundstation_visibility.push_back( std::vector< std::vector< intpair > >() );
            for(int k = 0; k < num_ground_statiion; k++)
            {
                satellite_groundstation_visibility[i].push_back( std::vector<intpair>());
                std::string line;
                std::vector<std::string> tokens;
                std::getline(reader, line);
                tokenize(line, tokens, std::string(":"));
                assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == k);
                line = tokens[1];
                tokens.clear();
                tokenize(line, tokens, std::string("\t"));

                for(int j = 0; j < tokens.size(); j++)
                {
                    std::string pairstr = tokens[j];
                    std::vector<std::string> pairtokens;
                    tokenize(pairstr, pairtokens, std::string("[,]"));
                    assert(pairtokens.size() == 2);
                    satellite_groundstation_visibility[i][k].push_back(std::make_pair<int, int>(atoi(pairtokens[0].c_str()), atoi(pairtokens[1].c_str())));
                }
            }
        }
    }
    void readGroundStationAngularDistance(std::ifstream& reader)
    {
        for(int i = 0; i < num_ground_statiion; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            line = tokens[1];
            tokens.clear();
            tokenize(line, tokens, std::string("\t"));
            assert(tokens.size() == num_ground_statiion);
            gs_angular_distance.push_back( intvector() );
            for(int j = 0; j < tokens.size(); j++)
            {
                gs_angular_distance[i].push_back(atoi(tokens[j].c_str()));
            }
        }
    }
    void readObservationSize(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_observations; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            observation_size.push_back(atoi(tokens[1].c_str()));
            
        }
    }
    void readObservationInstrumentMap(std::ifstream& reader)
    {
        for(int i = 0 ; i < num_observations; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(atoi(tokens[0].c_str()) == i);
             observations_inst_map.push_back(intvector());
            if( tokens.size() > 1 )
            {
                line = tokens[1];
                tokens.clear();
                tokenize(line, tokens, std::string("\t"));
               
                for(int j = 0; j < tokens.size(); j++)
                {
                    observations_inst_map[i].push_back(atoi(tokens[j].c_str()));
                }
            }
        }
    }
    void readObservationSatelliteVisibility(std::ifstream& reader)
    {
        for(int i = 0; i < num_observations; i++)
        {
            std::string line1;
            std::getline(reader, line1);
            observation_satellite_time_windows.push_back( std::vector< std::vector< intpair > >() );
            for(int k = 0; k < num_satellites; k++)
            {
                observation_satellite_time_windows[i].push_back( std::vector<intpair>());
                std::string line;
                std::vector<std::string> tokens;
                std::getline(reader, line);
                tokenize(line, tokens, std::string(":"));
                assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == k);
                line = tokens[1];
                tokens.clear();
                tokenize(line, tokens, std::string("\t"));
                
                for(int j = 0; j < tokens.size(); j++)
                {
                    std::string pairstr = tokens[j];
                    std::vector<std::string> pairtokens;
                    tokenize(pairstr, pairtokens, std::string("[,]"));
                    assert(pairtokens.size() == 2);
                    observation_satellite_time_windows[i][k].push_back(std::make_pair<int, int>(atoi(pairtokens[0].c_str()), atoi(pairtokens[1].c_str())));
                }
            }
        }
    }
    void readObservationAngularDistance(std::ifstream& reader)
    {
        for(int i = 0; i < num_observations; i++)
        {
            std::string line;
            std::vector<std::string> tokens;
            std::getline(reader, line);
            tokenize(line, tokens, std::string(":"));
            assert(tokens.size() == 2 and atoi(tokens[0].c_str()) == i);
            line = tokens[1];
            tokens.clear();
            tokenize(line, tokens, std::string("\t"));
            assert(tokens.size() == num_observations);
            observations_angualr_distances.push_back( intvector() );
            for(int j = 0; j < tokens.size(); j++)
            {
                observations_angualr_distances[i].push_back(atoi(tokens[j].c_str()));
            }
        }
    }
    
    void readProblem(std::string filename)
    {
        std::cout <<"reading problem " << filename << std::endl;
        std::ifstream reader(filename.c_str());
        
        std::string line;
        std::vector<std::string> tokens;
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->domain_name << tokens[1];
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->num_satellites = atoi(tokens[1].c_str());
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->num_ground_statiion = atoi(tokens[1].c_str());
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->num_instrument_types = atoi(tokens[1].c_str());
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->num_antenna_types = atoi(tokens[1].c_str());
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->instrument_max_on_time = atoi(tokens[1].c_str());
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->instrument_min_off_time = atoi(tokens[1].c_str());
    
        std::cout<<"readInstrumentRate"<<std::endl;
        std::getline(reader, line);
        readInstrumentRate(reader);
        
        std::cout<<"readInstrumentBatConRate"<<std::endl;
        std::getline(reader, line);
        readInstrumentBatConRate(reader);
        
        
        std::cout<<"readInstrumentAngularSpeed"<<std::endl;
        std::getline(reader, line);
        readInstrumentAngularSpeed(reader);
        
        
        std::cout<<"readAntennaRate"<<std::endl;
        std::getline(reader, line);
        readAntennaRate(reader);
        
        std::cout<<"readAntennaBatConRate"<<std::endl;
        std::getline(reader, line);
        readAntennaBatConRate(reader);
        
        std::cout<<"readAntennaAngularSpeed"<<std::endl;
        std::getline(reader, line);
        readAntennaAngularSpeed(reader);
        
        
        std::cout<<"readInstrumentSatelliteMap"<<std::endl;
        std::getline(reader, line);
        readInstrumentSatelliteMap(reader);
        
        
        std::cout<<"readAntennaSatelliteMap"<<std::endl;
        std::getline(reader, line);
        readAntennaSatelliteMap(reader);
        
        std::cout<<"readAntennaGroundStationMap"<<std::endl;
        std::getline(reader, line);
        readAntennaGroundStationMap(reader);
        
        std::cout<<"readSatelliteRechargeRate"<<std::endl;
        std::getline(reader, line);
        readSatelliteUnitRecharge(reader);
        
        std::cout<<"readSatelliteSunVisibility"<<std::endl;
        std::getline(reader, line);
        readSatelliteSunVisibility(reader);
        
        
        std::cout<<"readSatelliteGroundStationVisibility"<<std::endl;
        std::getline(reader, line);
        readSatelliteGroundStationVisibility(reader);
        
        
        std::cout<<"readGroundStationAngularDistance"<<std::endl;
        std::getline(reader, line);
        readGroundStationAngularDistance(reader);
        //======================================================================================
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->instance_name << tokens[1];
        
        std::getline( reader, line );
        tokens.clear();
        tokenize(line, tokens, std::string(":"));
        assert(tokens.size() == 2);
        this->num_observations = atoi(tokens[1].c_str() );
        
        std::cout<<"readObservationSize"<<std::endl;
        std::getline(reader, line);
        readObservationSize(reader);
        
        std::cout<<"readObservationInstrumentMap"<<std::endl;
        std::getline(reader, line);
        readObservationInstrumentMap(reader);
        
        std::cout<<"readObservationSatelliteVisibility"<<std::endl;
        std::getline(reader, line);
        readObservationSatelliteVisibility(reader);
        
        std::cout<<"readObservationAngularDistance"<<std::endl;
        std::getline(reader, line);
        readObservationAngularDistance(reader);
        
        for( int i = 0; i < num_satellites; i++)
        {
            std::cout <<"Satellite "<< i << " has following instruments" << std::endl;
            
            for( int s = 0 ; s < num_instrument_types; s++)
            {
                for( int j = 0 ; j < inst_sat_map[s].size(); j++)
                {
                    if( inst_sat_map[s][j] == i )
                    {
                        std::cout << "Instrument: " << s << std::endl;
                    }
                }
            }
            
            std::cout <<"Satellite "<< i << " has following antennas" << std::endl;
            
            for( int s = 0 ; s < num_antenna_types; s++)
            {
                for( int j = 0 ; j < ant_sat_map[s].size(); j++)
                {
                    if( ant_sat_map[s][j] == i )
                    {
                        std::cout << "Antenna: " << s << std::endl;
                    }
                }
            }
            
        }
    }
};
    


int main(int argc, char** argv)
{
    if( argc == 2 )
    {
        SatelliteProblemReader* reader = new SatelliteProblemReader();
        std::string name = argv[1];
        reader->readProblem(name);
        delete reader;
    }
    else
    {
        std::cout <<"Usage ./satellite_read <problem_file_name>" << std::endl;
    }
    return 0;
}

