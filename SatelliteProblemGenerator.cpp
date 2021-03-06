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
typedef std::set<int> intset;

class SatelliteProblemDomainGenerator
{
public:

    std::stringstream domain_name;
    int num_satellites; //min 1 instrument 1 antenna
    int num_instrument_types; ///min 1
    int num_antenna_types; ///min 1
    int num_ground_statiion; //min 1 antenna is supported
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
    intvector sat_storage_total;
    intvector sat_battery_total;

    intmatrix inst_sat_map;
    intmatrix ant_sat_map;
    intmatrix ant_gs_map;
    intmatrix gs_angular_distance;


    intset antennaTotal;
    intset instrumentTotal;


    std::vector< std::vector< std::vector< intpair > > > satellite_groundstation_visibility;
    intpairvectorvector satellite_sun_visibility;

    SatelliteProblemDomainGenerator(int n_sat, int n_inst_type, int n_ant_type, int n_gs, int n_tw)
    : num_satellites(n_sat)
    , num_ground_statiion(n_gs)
    , num_antenna_types(n_ant_type)
    , num_instrument_types(n_inst_type)
    , num_timewindows(n_tw)
    , instrument_max_on_time(80)
    , instrument_min_off_time(5)
    {
        if (num_antenna_types < 1)
            num_antenna_types = 1;
        if (num_instrument_types < 1)
            num_instrument_types = 1;

        srand(time(NULL));


        for (int i = 0; i < num_antenna_types; i++)
        {
            ant_rate.push_back(get_rand_num(2, 5));
            ant_bat_rate.push_back(get_rand_num(2, 5));
            ant_angular_speed.push_back(get_rand_num(5, 10));
            ant_gs_map.push_back(intvector(num_ground_statiion, 0));
            ant_sat_map.push_back(intvector(num_satellites, 0));

            antennaTotal.insert(antennaTotal.end(), i);
        }
        //std::cout << "Antenna Total Size = " << antennaTotal.size() << std::endl;
        for (int i = 0; i < num_instrument_types; i++)
        {
            inst_rate.push_back(get_rand_num(3, 8));
            inst_bat_rate.push_back(get_rand_num(3, 8));
            inst_angular_speed.push_back(get_rand_num(5, 10));
            inst_sat_map.push_back(intvector(num_satellites, 0));

            instrumentTotal.insert(instrumentTotal.end(), i);
        }

        for (int i = 0; i < num_satellites; i++)
        {
            sat_unit_recharge.push_back(get_rand_num(15, 20));
            sat_storage_total.push_back(get_rand_num(150, 200));
            sat_battery_total.push_back(get_rand_num(350, 500));

            satellite_sun_visibility.push_back(std::vector<intpair>());
            int start = get_rand_num(0, 100);
            int length = get_rand_num(20, 30);
            for (int j = 0; j < num_timewindows; j++)
            {
                satellite_sun_visibility[i].push_back(std::make_pair<int, int>(start, start + length));
                start = start + length + 40;
            }

            /*
             * Each Satellite must support at least 2 instrument types
             */
            int instrumentNumber = get_rand_num(1, num_instrument_types);
            intset instsize = instrumentTotal;
            while (instrumentNumber > 0)
            {
                int selected = get_rand_num(0, instsize.size() - 1);
                intset::iterator itr = instsize.begin();
                int count = 0;
                while (itr != instsize.end())
                {
                    if (count == selected)
                    {
                        inst_sat_map[*itr][i] = 1;
                        //std::cout << "Satellite " << i << " will have instrument " << *itr << " = " << inst_sat_map[*itr][i] << std::endl;
                        instsize.erase(itr);
                        instrumentNumber--;
                        break;
                    }
                    itr++;
                    count++;
                }

            }


            /*
             * Each Satellite must support at least 2 antenna types;
             */
            int antNumber = get_rand_num(1, num_antenna_types);
            intset antsize = antennaTotal;
            while (antNumber > 0)
            {
                int selected = get_rand_num(0, antsize.size() - 1);
                intset::iterator itr = antsize.begin();
                int count = 0;
                while (itr != antsize.end())
                {
                    if (count == selected)
                    {
                        ant_sat_map[*itr][i] = 1;
                        //std::cout << "Satellite " << i << " will have antenna " << *itr << " = " << ant_sat_map[*itr][i] << std::endl;
                        antsize.erase(itr);
                        antNumber--;
                        break;
                    }
                    itr++;
                    count++;
                }

            }


            satellite_groundstation_visibility.push_back(std::vector< std::vector<intpair> >());
            for (int j = 0; j < num_ground_statiion; j++)
            {
                satellite_groundstation_visibility[i].push_back(std::vector<intpair>());
                int start = get_rand_num(0, 100);
                int length = get_rand_num(20, 30);
                for (int k = 0; k < num_timewindows; k++)
                {
                    satellite_groundstation_visibility[i][j].push_back(std::make_pair<int, int>(start, start + length));
                    start = start + length + 60;
                }
            }
        }


        for (int i = 0; i < num_ground_statiion; i++)
        {
            gs_angular_distance.push_back(intvector());
            for (int j = 0; j < num_ground_statiion; j++)
            {
                gs_angular_distance[i].push_back(0);
                if (i != j)
                {
                    gs_angular_distance[i][j] = get_manhattan_dist(get_rand_num(0, 100), get_rand_num(0, 100), get_rand_num(0, 100), get_rand_num(0, 100));
                }
            }

            /*
             * Each Ground Station must support at least 1 antenna type
             */
            int antNumber = get_rand_num(1, num_antenna_types);
            intset antsize = antennaTotal;
            while (antNumber > 0)
            {
                int selected = get_rand_num(0, antsize.size() - 1);
                intset::iterator itr = antsize.begin();
                int count = 0;
                while (itr != antsize.end())
                {
                    if (count == selected)
                    {
                        ant_gs_map[*itr][i] = 1;
                        //std::cout << "Ground Station " << i << " will have antenna " << *itr << " = " << ant_gs_map[*itr][i] << std::endl;
                        antsize.erase(itr);
                        antNumber--;
                        break;
                    }
                    itr++;
                    count++;
                }

            }
        }

        domain_name << "Sat-" << n_sat << "-GS-" << n_gs << "-Inst-" << n_inst_type << "-Ant-" << n_ant_type;
    }

    void writeSatelliteDomain(std::ofstream& writer)
    {
        writer << "Domain Description :" << domain_name.str() << std::endl;
        writer << "Satellite : " << num_satellites << std::endl;
        writer << "Ground Stations : " << num_ground_statiion << std::endl;
        writer << "Instrument Types : " << num_instrument_types << std::endl;
        writer << "Antenna Types : " << num_antenna_types << std::endl;
        writer << "Instrument ON Max : " << instrument_max_on_time << std::endl;
        writer << "Instrument OFF Min : " << instrument_min_off_time << std::endl;
        writer << "Instrument Rate : " << std::endl;

        for (int i = 0; i < num_instrument_types; i++)
        {
            writer << i << ":" << inst_rate[i] << std::endl;
        }

        writer << "Instrument Battery Consumption Rate : " << std::endl;
        for (int i = 0; i < num_instrument_types; i++)
        {
            writer << i << ":" << inst_bat_rate[i] << std::endl;
        }

        writer << "Instrument Angular Speed : " << std::endl;
        for (int i = 0; i < num_instrument_types; i++)
        {
            writer << i << ":" << inst_angular_speed[i] << std::endl;
        }

        writer << "Antenna Rate : " << std::endl;
        for (int i = 0; i < num_antenna_types; i++)
        {
            writer << i << ":" << ant_rate[i] << std::endl;
        }

        writer << "Antenna Battery Consumption Rate : " << std::endl;
        for (int i = 0; i < num_antenna_types; i++)
        {
            writer << i << ":" << ant_bat_rate[i] << std::endl;
        }

        writer << "Antenna Angular Speed : " << std::endl;
        for (int i = 0; i < num_antenna_types; i++)
        {
            writer << i << ":" << ant_angular_speed[i] << std::endl;
        }

        writer << "Instrument Satellite Map" << std::endl;
        for (int i = 0; i < num_instrument_types; i++)
        {
            writer << i << ":";
            for (int j = 0; j < num_satellites; j++)
            {
                if (inst_sat_map[i][j])
                {
                    writer << j << "\t";
                }
            }
            writer << std::endl;
        }
        writer << "Antenna Satellite Map" << std::endl;
        for (int i = 0; i < num_antenna_types; i++)
        {
            writer << i << ":";
            for (int j = 0; j < num_satellites; j++)
            {
                if (ant_sat_map[i][j])
                {
                    writer << j << "\t";
                }
            }
            writer << std::endl;
        }
        writer << "Antenna Ground Station Map" << std::endl;
        for (int i = 0; i < num_antenna_types; i++)
        {
            writer << i << ":";
            for (int j = 0; j < num_ground_statiion; j++)
            {
                if (ant_gs_map[i][j])
                {
                    writer << j << "\t";
                }
            }
            writer << std::endl;
        }

        writer << "Satellite Unit Recharge" << std::endl;
        for (int i = 0; i < num_satellites; i++)
        {
            writer << i << ":" << sat_unit_recharge[i] << std::endl;
        }

        writer << "Satellite Storage" << std::endl;
        for (int i = 0; i < num_satellites; i++)
        {
            writer << i << ":" << sat_storage_total[i] << std::endl;
        }

        writer << "Satellite Battery" << std::endl;
        for (int i = 0; i < num_satellites; i++)
        {
            writer << i << ":" << sat_battery_total[i] << std::endl;
        }

        writer << "Satellite Sun Visibility" << std::endl;
        for (int i = 0; i < num_satellites; i++)
        {
            writer << i << ":";
            for (int j = 0; j < satellite_sun_visibility[i].size(); j++)
            {
                writer << "[" << satellite_sun_visibility[i][j].first << "," << satellite_sun_visibility[i][j].second << "]\t";
            }
            writer << std::endl;
        }
        writer << "Satellite Ground Station Visibility" << std::endl;
        for (int i = 0; i < num_satellites; i++)
        {
            writer << i << ":\n";
            for (int j = 0; j < satellite_groundstation_visibility[i].size(); j++)
            {
                writer << j << ":";
                for (int k = 0; k < satellite_groundstation_visibility[i][j].size(); k++)
                {
                    writer << "[" << satellite_groundstation_visibility[i][j][k].first << "," << satellite_groundstation_visibility[i][j][k].second << "]\t";
                }
                writer << std::endl;
            }
            //writer<< std::endl;
        }
        writer << "Ground Station Angular Distances" << std::endl;
        for (int i = 0; i < num_ground_statiion; i++)
        {
            writer << i << ":";
            for (int j = 0; j < num_ground_statiion; j++)
            {
                writer << gs_angular_distance[i][j] << "\t";
            }
            writer << std::endl;
        }
    }

    void writeDomain()
    {
        std::ofstream writer;
        std::stringstream name;
        name << domain_name.str() << ".txt";
        std::cout << "Creating instance  " << name.str() << std::endl;

        writer.open(name.str().c_str());

        writeSatelliteDomain(writer);

        writer.close();

    }
};

class SatelliteProblemInstanceGenerator
{
public:
    SatelliteProblemDomainGenerator* domain;
    int instance_id;
    std::stringstream instance_name;
    int num_observations;
    intmatrix observations_inst_map;
    intvector observation_size;
    intmatrix observations_angualr_distances;

    std::vector< std::vector< std::vector< intpair > > > observation_satellite_time_windows;

    SatelliteProblemInstanceGenerator(int id, int n_obs, SatelliteProblemDomainGenerator* domain)
    : instance_id(id)
    , num_observations(n_obs)
    , domain(domain)
    {
        //srand(time(NULL));
        //num_observations = get_rand_num()
        for (int i = 0; i < num_observations; i++)
        {
            observations_inst_map.push_back(intvector(domain->num_instrument_types, 0));

            /*
             * Each Observation must support at least 2 instrument types
             */
            int instrumentNumber = get_rand_num(1, std::min(domain->num_instrument_types, 2));
            intset instsize = domain->instrumentTotal;
            while (instrumentNumber > 0)
            {
                int selected = get_rand_num(0, instsize.size() - 1);
                intset::iterator itr = instsize.begin();
                int count = 0;
                while (itr != instsize.end())
                {
                    if (count == selected)
                    {
                        observations_inst_map[i][*itr] = 1;
                        //std::cout << "Observation " << i << " will have instrument " << *itr << " = " << observations_inst_map[i][*itr] << std::endl;
                        instsize.erase(itr);
                        instrumentNumber--;
                        break;
                    }
                    itr++;
                    count++;
                }

            }


            observation_size.push_back(get_rand_num(30, 50));

            //srand(time(NULL));
            //for (int i = 0; i < num_observations; i++)
            {
                observation_satellite_time_windows.push_back(std::vector< std::vector<intpair> >());
                for (int j = 0; j < domain->num_satellites; j++)
                {
                    observation_satellite_time_windows[i].push_back(std::vector<intpair>());
                    int start = get_rand_num(0, 100);
                    int length = get_rand_num(20, 30);
                    for (int k = 0; k < domain->num_timewindows; k++)
                    {
                        observation_satellite_time_windows[i][j].push_back(std::make_pair<int, int>(start, start + length));
                        start = start + length + 60;
                    }
                }
            }
            //srand(time(NULL));
            //for (int i = 0; i < num_observations; i++)
            {
                observations_angualr_distances.push_back(intvector());
                for (int j = 0; j < num_observations; j++)
                {
                    observations_angualr_distances[i].push_back(0);
                    if (i != j)
                    {
                        observations_angualr_distances[i][j] = get_manhattan_dist(get_rand_num(0, 100), get_rand_num(0, 100), get_rand_num(0, 100), get_rand_num(0, 100));
                    }
                }
            }
        }

        instance_name << "ID-" << instance_id << "-Observations-" << num_observations;
    }

    void writeSatelliteInstance(std::ofstream& writer)
    {
        writer << "Instance Description : " << instance_name.str() << std::endl;
        writer << "Observation : " << num_observations << std::endl;
        writer << "Observation Size:" << std::endl;
        for (int i = 0; i < num_observations; i++)
        {
            writer << i << ":" << observation_size[i] << std::endl;
        }
        writer << "Observation Instrument map" << std::endl;
        for (int i = 0; i < num_observations; i++)
        {
            writer << i << ":";
            for (int j = 0; j < domain->num_antenna_types; j++)
            {
                if (observations_inst_map[i][j])
                    writer << j << "\t";
            }
            writer << std::endl;
        }
        writer << "Observation Satellite Visibility" << std::endl;
        for (int i = 0; i < num_observations; i++)
        {
            writer << i << ":\n";
            for (int j = 0; j < observation_satellite_time_windows[i].size(); j++)
            {
                writer << j << ":";
                for (int k = 0; k < observation_satellite_time_windows[i][j].size(); k++)
                {
                    writer << "[" << observation_satellite_time_windows[i][j][k].first << "," << observation_satellite_time_windows[i][j][k].second << "]\t";
                }
                writer << std::endl;
            }
            //writer<< std::endl;
        }
        writer << "Observation Angular Distances" << std::endl;
        for (int i = 0; i < num_observations; i++)
        {
            writer << i << ":";
            for (int j = 0; j < num_observations; j++)
            {
                writer << observations_angualr_distances[i][j] << "\t";
            }
            writer << std::endl;
        }

    }

    void writeInstance()
    {
        std::ofstream writer;
        std::stringstream name;
        name << domain->domain_name.str() << "-" << instance_name.str() << ".txt";
        std::cout << "Creating instance  " << name.str() << std::endl;

        writer.open(name.str().c_str());

        domain->writeSatelliteDomain(writer);
        this->writeSatelliteInstance(writer);

        writer.close();
    }
};

/*
 * 
 */
int main(int argc, char** argv)
{
    //SatelliteProblemDomainGenerator(int n_sat, int n_inst_type, int n_ant_type, int n_gs, int n_tw )
    /**
     * @param n_sat : number of satellites
     * @param n_inst_type: types of unique instruments
     * @param n_ant_type: types of unique antennas
     * @param n_gs : number of gs
     * @param n_tw : number of time windows for visibility between satellite/observation/ground stations/sun light
     * @param n_instance: number of instances that should be generated
     * @param n_observation: number of observation in that instance
     */
    std::cout << "argc " << argc << std::endl;

    if( argc == 8 )
    {
        int n_sat = atoi(argv[1]);
        int n_inst = atoi(argv[2]);
        int n_ant_type = atoi(argv[3]);
        int n_gs = atoi(argv[4]);
        int n_tw = atoi(argv[5]);

        int num_instance = atoi(argv[6]);
        int num_observations = atoi(argv[7]);

        SatelliteProblemDomainGenerator* gen = new SatelliteProblemDomainGenerator(n_sat, n_inst, n_ant_type, n_gs, n_tw);
        for (int i = 0; i < num_instance; i++)
        {
            SatelliteProblemInstanceGenerator* ins = new SatelliteProblemInstanceGenerator(i, num_observations, gen);
            ins->writeInstance();
            delete ins;
        }

        delete gen;
    }
    else
    {
        std::cout <<"Usage ./satellite_gen num_sat, num_instrument_type, num_antenna_type, num_ground_stations, num_timewindows, num_instance, num_observations" << std::endl;
    }

    return 0;
}

