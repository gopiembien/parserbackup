#ifndef _MYNMEAPARSER_H_
#define _MYNMEAPARSER_H_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include "NMEAParser.h"
#include "ceSerial.h"
using json = nlohmann::json;
class NMEAData
{
	private:
		static NMEAData* instance;
		NMEAData();
	public:
		static NMEAData* getInstance();
		double m_latitude;
		double m_longitude;
		double m_altitude;
		double m_rollangle;
		double m_pitchangle;
		double m_headingangle;
};

/// \class MyParser
/// \brief child class of CNMEAParser which will redefine notification calls from the parent class.
class MyNMEAParser : public CNMEAParser 
{
	virtual void OnError(CNMEAParserData::ERROR_E nError, char *pCmd) 
    {
		printf("ERROR for Cmd: %s, Number: %d\n", pCmd, nError);
	}

protected:
    virtual CNMEAParserData::ERROR_E ProcessRxCommand(char *pCmd, char *pData);
};

#endif