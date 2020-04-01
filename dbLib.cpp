/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void LoadData(void* & pData){	
	TDataset* DataSet = new TDataset();
	L1List<TCity>*p1 = new L1List<TCity>;
	DataSet->Cities = p1;
	string s;
	char c;
	int i = 0;
	ifstream file;
	TCity tCities;
    file.open("cities.csv");
	getline(file, s);
	while (!file.eof()){
		getline(file, s, ',');
		if (s == "\0") break;
		tCities.id = stoi(s);

		getline(file, s, ',');
		tCities.name = s;

		/*getline(file, s, ',');
		tCities.coords = s;

		getline(file, s, ',');
		if (s == "\0") s = "-1";
		tCities.start_year = stoi(s);

		getline(file, s,',');
		tCities.url_name = s;

		getline(file, s, ',');
		tCities.country = s;

		getline(file, s);
	    tCities.country_state = s;*/
		getline(file, s);

		DataSet->Cities->insertHead(tCities);		
	}

	file.close();
    //////////
	L1List<TLine> *p2 = new L1List<TLine>;
	DataSet->Lines = p2;
	TLine tLines;
	i = 0;
	file.open("lines.csv");
	getline(file, s);
	while (!file.eof()) {
		getline(file, s, ',');
		if (s == "\0") break;
		tLines.id = stoi(s);

		getline(file, s, ',');
		tLines.city_id = stoi(s);

		/*file >> c;
		if (c == '\"') { 
			getline(file, s, '\"');
			file >> c;
		}
		else getline(file, s, ',');
		
		if (c == ',') tLines.name = s;
		else tLines.name = c + s;

		getline(file, s,',');
		tLines.url_name = s;

		getline(file, s, ',');
		tLines.color = s;

		getline(file, s, ',');
	    tLines.system_id = stoi(s);

		getline(file, s);
		if (s == "\0") s = "-1";
		tLines.transport_mode_id = stoi(s);*/
		getline(file, s);

		DataSet->Lines->insertHead(tLines);
	}
	file.close();
    //////////
	L1List<TTrack> *p3 = new L1List<TTrack>;
	DataSet->Tracks = p3;
	TTrack tTracks;
	i = 0;
    file.open("tracks.csv");
	getline(file, s);
	while (!file.eof()) {
		getline(file, s, ',');
		if (s == "\0") break;
		tTracks.id = stoi(s);

		file >> c;
		if (c == '\"') {
			getline(file, s, '\"');
			file >> c;
		}
		else getline(file, s, ',');
		if (c != ',') s = s +c;
		tTracks.geometry = s;
		getline(file,s);
	
		/*
		getline(file, s, ',');
		if (s == "\0") s = "-1";
		tTracks.buildstart = stoi(s);

		getline(file, s, ',');
		if (s == "\0") s = "-1";
		tTracks.opening = stoi(s);

		getline(file, s,',');
		if (s == "\0") s = "-1";
		tTracks.closure = stoi(s);

		getline(file, s);
		if (s == "\0") s = "-1";
	    tTracks.city_id = stoi(s);
		*/
		DataSet->Tracks->insertHead(tTracks);
		
	}
	file.close();
	///////////
	TStationLine tSLines;
	L1List<TStationLine> *p4 = new L1List<TStationLine>;
	DataSet->StationLines = p4;
	file.open("station_lines.csv");
	getline(file, s);
	while (!file.eof()) {
		getline(file, s, ',');
		if (s == "\0") break;
		tSLines.id = stoi(s);
		getline(file, s, ',');
		tSLines.station_id = stoi(s);
		getline(file, s, ',');
		tSLines.line_id = stoi(s);
		getline(file, s, ',');
		tSLines.city_id = stoi(s);
		///////////////////////////
		/*getline(file, s, '-');
		tSLines.created_at.year = stoi(s);
		getline(file, s, '-');
		tSLines.created_at.month = stoi(s);
		getline(file, s, ' ');
		tSLines.created_at.day = stoi(s);
		getline(file, s, ':');
		tSLines.created_at.hour = stoi(s);
		getline(file, s, ':');
		tSLines.created_at.min = stoi(s);
		getline(file, s, ',');
		tSLines.created_at.sec = floorf(stof(s) + 0.5);
		/////////////////////
		getline(file, s, '-');
		tSLines.updated_at.year = stoi(s);
		getline(file, s, '-');
		tSLines.updated_at.month = stoi(s);
		getline(file, s, ' ');
		tSLines.updated_at.day = stoi(s);
		getline(file, s, ':');
		tSLines.updated_at.hour = stoi(s);
		getline(file, s, ':');
		tSLines.updated_at.min = stoi(s);
		getline(file, s);
		tSLines.updated_at.sec = floorf(stof(s) + 0.5);
		*/
		getline(file, s);

		DataSet->StationLines->insertHead(tSLines);
	}
	file.close();
	
	//////////////////////////////////
	TStation tStations;
	L1List<TStation> *p5 = new L1List<TStation>;
	DataSet->Stations = p5;
	file.open("stations.csv");
	getline(file, s);
	while (!file.eof()) {
		getline(file, s, ',');
		if (s == "\0") break;
		tStations.id = stoi(s);

		file >> c;
		if (c == '\"') {
			getline(file, s, '\"');
			file >> c;
		}
		else getline(file, s, ',');

		if (c != ',')  s = c + s;
		//remove "/n"
		/*for (int i = 0; i < s.length(); i++) {
			if (s[i] == '\n') {
				s.erase(i, 1);
				i--;
			}
		}*/
		tStations.name = s;

		getline(file, s, ',');
		if (s == "\0") s = "-1";
		tStations.geometry = s;

		getline(file, s, ',');
		/*if (s == "\0") s = "-1";
		tStations.buildstart = stoi(s);*/

		getline(file, s, ',');
		/*if (s == "\0") s = "-1";
		tStations.opening = stoi(s);*/

		getline(file, s, ',');
		/*if (s == "\0") s = "-1";
		tStations.closure = stoi(s);*/

		getline(file, s);
		if (s == "\0") s = "-1";
		tStations.city_id = stoi(s);

		DataSet->Stations->insertHead(tStations);
	}
	file.close();

	DataSet->Cities->reverse();
	DataSet->Lines->reverse();
	DataSet->StationLines->reverse();
	DataSet->Stations->reverse();
	DataSet->Tracks->reverse();
	pData = DataSet;


};
void ReleaseData(void* &){

};