/*
* MIT License
*
*  Copyright (c) 2018 VisualGPS, LLC
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*
*/
#include <stdio.h>
#include <string.h>
#include "NMEAParser.h"
#include "ceSerial.h"

///
/// \class MyParser
/// \brief child class of CNMEAParser which will redefine notification calls from the parent class.
///
class MyNMEAParser : public CNMEAParser {

	///
	/// \brief This method is called whenever there is a parsing error.
	///
	/// Redefine this method to capture errors.
	///
	/// \param pCmd Pointer to NMEA command that caused the error. Please note that this parameter may be NULL of not completely defined. Use with caution.
	///
	virtual void OnError(CNMEAParserData::ERROR_E nError, char *pCmd) {
		printf("ERROR for Cmd: %s, Number: %d\n", pCmd, nError);
	}

protected:
	///
	/// \brief This method is redefined from CNMEAParserPacket::ProcessRxCommand(char *pCmd, char *pData)
	///
	/// Here we are capturing the ProcessRxCommand to print out status. We also are looking for
	/// the GPGGA message and displaying some data from it.
	///
	/// \param pCmd Pointer to the NMEA command string
	/// \param pData Comma separated data that belongs to the command
	/// \return Returns CNMEAParserData::ERROR_OK If successful
	///
	virtual CNMEAParserData::ERROR_E ProcessRxCommand(char *pCmd, char *pData) {

		// Call base class to process the command
		CNMEAParser::ProcessRxCommand(pCmd, pData);

		printf("Cmd: %s\nData: %s\n", pCmd, pData);

		// Check if this is the GPGGA command. If it is, then display some data
		if (strstr(pCmd, "GPGGA") != NULL) {
			CNMEAParserData::GGA_DATA_T ggaData;
			if (GetGPGGA(ggaData) == CNMEAParserData::ERROR_OK) {
				printf("GPGGA Parsed!\n");
				printf("   Time:                %02d:%02d:%02d\n", ggaData.m_nHour, ggaData.m_nMinute, ggaData.m_nSecond);
				printf("   Latitude:            %f\n", ggaData.m_dLatitude);
				printf("   Longitude:           %f\n", ggaData.m_dLongitude);
				printf("   Altitude:            %.01fM\n", ggaData.m_dAltitudeMSL);
				printf("   GPS Quality:         %d\n", ggaData.m_nGPSQuality);
				printf("   Satellites in view:  %d\n", ggaData.m_nSatsInView);
				printf("   HDOP:                %.02f\n", ggaData.m_dHDOP);
				printf("   Differential ID:     %d\n", ggaData.m_nDifferentialID);
				printf("   Differential age:    %f\n", ggaData.m_dDifferentialAge);
				printf("   Geoidal Separation:  %f\n", ggaData.m_dGeoidalSep);
				printf("   Vertical Speed:      %.02f\n", ggaData.m_dVertSpeed);
			}
		}

		return CNMEAParserData::ERROR_OK;
	}
};

int main() 
{
	#ifdef ceWINDOWS
	ceSerial com("\\\\.\\COM7",9600,8,'N',1); // Windows
	#else
	ceSerial com("/dev/ttyUSB0",9600,8,'N',1); // Linux
	#endif

	printf("Opening port %s.\n",com.GetPort().c_str());
	if (com.Open() == 0) {
		printf("OK.\n");
	}
	else {
		printf("Error.\n");
		return 1;
	}

	MyNMEAParser NMEAParser;

	CNMEAParserData::ERROR_E nErr;
	if ((nErr = NMEAParser.ProcessNMEABuffer(com)) != CNMEAParserData::ERROR_OK) {
		printf("NMEA Parser ProcessNMEABuffer Failed and returned error: %d\n", nErr);
		return -1;
	}
	return 0;
}

