#include "MYNMEAParser.h"

NMEAData *NMEAData::instance = NULL;

int main() 
{
	FILE *fileptr;
	fileptr = fopen("gpsdata.csv", "w");
	if(fileptr == NULL)
	{
		printf("Error Opening file.\n");
		return CNMEAParserData::ERROR_FILE_OPEN_FAILED;
	}
	fprintf(fileptr, "Type, Time, Epoch time,  Latitude, Longitude, Altitude, Satellites, Roll, Pitch, Heading\n");
	fclose(fileptr);

	while(1)
	{
		#ifdef ceWINDOWS
		ceSerial com("\\\\.\\COM11",115200,8,'N',1); // Windows
		#else
		ceSerial com("/dev/ttyUSB0",115200,8,'N',1); // Linux
		#endif

		printf("Opening port %s.\n",com.GetPort().c_str());
		if (com.Open() == 0) 
		{
			printf("OK.\n");
		}
		else 
		{
			printf("Error Opening port.\n");
			continue;
		}

		MyNMEAParser NMEAParser;
		CNMEAParserData::ERROR_E nErr;
		if ((nErr = NMEAParser.ProcessNMEABuffer(com)) != CNMEAParserData::ERROR_OK) 
		{
			printf("NMEA Parser ProcessNMEABuffer Failed and returned error: %d\n", nErr);
			continue;
		}
	}
	return 0;
}

