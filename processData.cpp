/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
#include "dbLib.h"
/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
    TDataset* p = (TDataset*)pData;
	string req = pRequest;
	string str;
	int *pI= new int;
	int count = 0, tmp = 0;
	int indexOfSpace = 0;
	indexOfSpace = req.find_first_of(" ");
	string stringInput = req.substr(indexOfSpace + 1);
	if ((!stringInput.length() || req.length() < 4) && req != "CL") pOutput = nullptr;
	else if (!req.find("CL")) {
		//Given namecity
		if (req.length() == 2)
			*pI = (int)p->Lines->getSize();
		else {
			tmp = -1;
			L1Item<TCity> *pCity = p->Cities->get_pHead();
			while (pCity) {
				if (pCity->data.name == req.substr(3)) {
					tmp = pCity->data.id;
					break;
				}
				pCity = pCity->pNext;
			}
			count = 0;
			if (tmp > -1) {
				L1Item<TLine>*pLine = p->Lines->get_pHead();
					while (pLine) {
						if (pLine->data.city_id == tmp) count++;
						pLine = pLine->pNext;
					}
			}
			else count = -1;
			*pI = count;
		}
		N = 1;
		pOutput = pI;
	}
	else if (!req.find("LSC")) {
		//Given namecity
		int* arr = new int[10000];
		N = 0;
		L1Item<TCity> *pCity = p->Cities->get_pHead();
		while (pCity) {
			if (pCity->data.name == req.substr(4)) {
				tmp = pCity->data.id;
				break;
			}
			pCity = pCity->pNext;
		}
		L1Item<TStation> *pStation = p->Stations->get_pHead();
		while (pStation) {
			if (pStation->data.city_id == tmp) {
				arr[N] = pStation->data.id;
				N++;
			}
			pStation = pStation->pNext;
		}
		pOutput = arr;
	}
	else if (!req.find("LLC")) {
		//Given namecity
		int* arr = new int[10000];
		N = 0;
		L1Item<TCity> *pCity = p->Cities->get_pHead();
		while (pCity) {
			if (pCity->data.name == req.substr(4)) { 
				tmp = pCity->data.id; 
				break; 
			}
			pCity = pCity->pNext;
		}
		L1Item<TLine>*pLine = p->Lines->get_pHead();
		while (pLine) {
			if (pLine->data.city_id == tmp) {
				arr[N] =pLine->data.id;
				N++;
			}
			pLine = pLine->pNext;
		}
		pOutput = arr;
	}
	else if (!req.find("LSL")) {
		//Given line_id
		int* arr = new int[10000];
		N = 0;
		L1Item<TStationLine> *pSLine = p->StationLines->get_pHead();
		while (pSLine) {
			if (pSLine->data.line_id == stoi(req.substr(4)))
			{
				arr[N] = pSLine->data.station_id;
				N++;
			}
			pSLine = pSLine->pNext;
		}
		pOutput = arr;
	}
	else if (!req.find("FC")) {
		//Given namecity
		tmp = 0;
		L1Item<TCity> *pCity = p->Cities->get_pHead();
		while (pCity) {
			if (pCity->data.name == req.substr(3)) { 
				tmp = pCity->data.id; 
				break; 
			}
			pCity = pCity->pNext;
		}
		if (!tmp) tmp = -1;
		*pI = tmp;
		pOutput = pI;
		N = 1;
	}
	else if (!req.find("FS")) {
		//Given name_station
		tmp = 0;
		L1Item<TStation> *pStation = p->Stations->get_pHead();
		while (pStation) {
			if (pStation->data.name == req.substr(3)) { 
				tmp = pStation->data.id; 
				break; 
			}
			pStation = pStation->pNext;
		}
		if (!tmp) tmp = -1;
		*pI = tmp;
		pOutput = pI;
		N = 1;
	}
	else if (!req.find("SLP")) {
		//Given station_id, track_id
		string tmpstr="";
		str = "";
		tmp = req.find_last_of(" ");
		str =(req.substr(0,tmp));
		if ((str.substr(4)).length() && (req.substr(tmp + 1)).length()) {
			L1Item<TStation> *pStation = p->Stations->get_pHead();
			while (pStation) {
				if (pStation->data.id == stoi(str.substr(4))) {
					tmpstr = pStation->data.geometry;
					break;
				}
				pStation = pStation->pNext;
			}
			L1Item<TTrack> *pTrack = p->Tracks->get_pHead();
			while (pTrack) {
				if (pTrack->data.id == stoi(req.substr(tmp + 1))) {
					str = pTrack->data.geometry;
					break;
				}
				pTrack = pTrack->pNext;
			}
		}
		else tmp = 0;
		//Return -1
		if (str.length() && tmpstr.length()) {
			tmp = tmpstr.find("(");
			tmpstr = tmpstr.substr(tmp);
			tmpstr.erase(tmpstr.begin());
			tmpstr.erase(tmpstr.end() - 1);
			tmp = str.find(tmpstr);
			if (tmp > str.length()) tmp = -1;
		}
		else tmp = 0; //if error
			count = -1;
			if (tmp > 0) {
				count++;
				for (int i = 10; i < tmp; i++) if (str[i] == ',') count++;
			}
			*pI = count;
			pOutput = pI;
			N = 1;
	}
	//id,name,geometry,buildstart,opening,closure,city_id
	
	else if (!req.find("US")) {
		int tmpIdx = -1;
		req = req.substr(3);
		tmp = req.find_first_of(" ");
		str = (req.substr(0, tmp));
		L1Item<TStation> *pStation = p->Stations->get_pHead();
		int i = 0;
		while (pStation) {
				if (pStation->data.id == stoi(str)) { 
					tmpIdx = i;	
					break; 
				}
			pStation = pStation->pNext;
			i++;
		}
	
		if (tmpIdx > -1) {
			str = req.substr(tmp + 1);
			//have comma
			//str = str.substr(1);
			//
			tmp = str.find(",");
			p->Stations->at(tmpIdx).name = str.substr(0, tmp);
			//have ""
			string s = p->Stations->at(tmpIdx).name;
			for (int i = 0; i < s.length(); i++) {
				if (s[i] == '\"') {
					s.erase(i, 1);
					i--;
				}
			}
			p->Stations->at(tmpIdx).name = s;
			//
			str = str.substr(tmp + 1);

			tmp = str.find(",");
			p->Stations->at(tmpIdx).geometry = str.substr(0, tmp);
			str = str.substr(tmp + 1);

			tmp = str.find(",");
			p->Stations->at(tmpIdx).buildstart = stoi(str.substr(0, tmp));
			str = str.substr(tmp + 1);


			tmp = str.find(",");
			p->Stations->at(tmpIdx).opening = stoi(str.substr(0, tmp));
			str = str.substr(tmp + 1);

			tmp = str.find(",");
			p->Stations->at(tmpIdx).closure = stoi(str.substr(0, tmp));
			*pI = 0;
		}
		else *pI = -1;
		pOutput = pI;
		N = 1;
	}
	else if (!req.find("ISL")) {
		string tmpstr;
		bool flag = 0;
		int tmpFound;
		str = req.substr(4);
		tmpFound = str.find_first_of(" ");
		tmpstr = str.substr(tmpFound+1);
		tmp = tmpstr.find(" ");
		TStationLine newStL;
		newStL.station_id = stoi(str.substr(0,tmpFound));
		newStL.line_id = stoi(tmpstr.substr(0, tmp));
		L1Item<TStationLine> *pSLine = p->StationLines->get_pHead();
		while (pSLine) {
			if (pSLine->data.station_id == newStL.station_id
				&& pSLine->data.line_id == newStL.line_id) {
				flag = 1;
				break;
			}
			pSLine = pSLine->pNext;
		}

		int pos = stoi(tmpstr.substr(tmp + 1));
		int index = 0;
		int i = 0;
		pSLine = p->StationLines->get_pHead();
		while (pSLine) {
			if (index < pos) i++;
			if (pSLine->data.line_id == newStL.line_id) {
					index++;
			}
			pSLine = pSLine->pNext;
		}
		if (index < pos || !index) flag = true;
		if (!flag) { 
			p->StationLines->insert(i, newStL); 
			*pI = 0;
		}
		else *pI = -1;
		pOutput = pI;
		N = 1;
	}
	else if (!req.find("RSL")){
		bool flag = 0;
		str = req.substr(4);
		tmp = str.find(" ");
		L1Item<TStationLine> *pSLine = p->StationLines->get_pHead();
		int i = 0;
		while (pSLine) {
			if (pSLine->data.station_id == stoi(str.substr(0, tmp))
				&& pSLine->data.line_id == stoi(str.substr(tmp + 1))) {
				flag = 1;
				tmp = i;
				break;
			}
			pSLine = pSLine->pNext;
			i++;
		}
		if (flag) { 
			p->StationLines->remove(tmp);
			*pI = 0;
		}
		else *pI = -1;
		pOutput = pI;
		N = 1;
	}
	else if (!req.find("IS")) {
		//Given station_id
		str = req.substr(3);
		//have comma
		//str = str.substr(1);
		//
		TStation newSt;
		tmp = str.find(",");
		newSt.name = str.substr(0, tmp);
		//have ""
		string s = newSt.name;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '\"') {
				s.erase(i, 1);
				i--;
			}
		}
		newSt.name = s;
		//
		str = str.substr(tmp + 1);

		tmp = str.find(",");
		newSt.geometry = str.substr(0, tmp);
		str = str.substr(tmp + 1);

		tmp = str.find(",");
		//newSt.buildstart = str.substr(0, tmp);
		str = str.substr(tmp + 1);


		tmp = str.find(",");
		//newSt.opening = stoi(str.substr(0, tmp));
		str = str.substr(tmp + 1);

		tmp = str.find(",");
		//newSt.closure = stoi(str.substr(0, tmp));
		tmp = 0;
		L1Item<TStation> *pStation = p->Stations->get_pHead();
		while (pStation) {
			if (tmp < pStation->data.id) tmp = pStation->data.id;
			pStation = pStation->pNext;
		}
		newSt.id = ++tmp;
		p->Stations->push_back(newSt);
		*pI = tmp;
		pOutput = pI;
		N = 1;
	}
	else if (!req.find("RS")) {
		tmp = -1;
		L1Item<TStation> *pStation = p->Stations->get_pHead();
		int i = 0;
		while (pStation) {
			if (stoi(req.substr(3)) == pStation->data.id) { 
				tmp = i; 
				break; 
			}
			pStation = pStation->pNext;
			i++;
		}
		L1Item<TStationLine> *pSLine = p->StationLines->get_pHead();
		i = 0;
		while (pSLine) {
			if (stoi(req.substr(3)) == pSLine->data.station_id) {
				pSLine = pSLine->pNext;
				p->StationLines->remove(i);
			}
			else {
				i++;
				pSLine = pSLine->pNext;
			}	
		}
		*pI = p->Stations->remove(tmp);
		pOutput = pI;
		N = 1;
	}
}

