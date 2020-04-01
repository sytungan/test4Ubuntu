/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct TCity {
    // The structure to store city information
    int id, start_year;
    string name, url_name, country, country_state, coords;
};

struct TLine {
    // The structure to store line information
    int id, system_id, transport_mode_id, city_id;
    string name, url_name, color;
};

struct TTrack {
    // The structure to store track information
    int id, buildstart, opening, closure, length, city_id;
    string geometry;
};

struct TStation
{
	int id, buildstart, opening, closure, city_id;
	string name, geometry;
};

struct date
{
	int sec, min, hour, day, month, year;
};
struct TStationLine
{
	int id, station_id, line_id, city_id;
	date created_at, updated_at;
};

class TDataset {
public:
	L1List<TCity> *Cities;
	L1List<TLine> *Lines;
	L1List<TTrack> *Tracks;
	L1List<TStation> *Stations;
	L1List<TStationLine> *StationLines;	
	TDataset() {
		Cities = nullptr;
		Lines = nullptr;
		Tracks = nullptr;
		Stations = nullptr;
		StationLines = nullptr;
	}

	~TDataset() {}
};

// Please add more or modify as needed

void LoadData(void* &pData);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H
