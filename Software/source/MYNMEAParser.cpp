#include "MYNMEAParser.h"

NMEAData::NMEAData()
{
    m_latitude = 0.0;
    m_longitude = 0.0;
    m_altitude = 0.0;
    m_rollangle = 0.0;
    m_pitchangle = 0.0;
    m_headingangle = 0.0;
}

NMEAData* NMEAData::getInstance()
{
    if(instance == NULL)
    {
        instance = new NMEAData();
    }
    return instance;
}

CNMEAParserData::ERROR_E MyNMEAParser::ProcessRxCommand(char *pCmd, char *pData) 
{
    // Call base class to process the command
    CNMEAParser::ProcessRxCommand(pCmd, pData);
    FILE* fileptr;
    errno_t err;
    err = fopen_s(&fileptr, "gpsdata.csv", "a");
    if (err != 0)
	{
		printf("Error Opening file.\n");
		return CNMEAParserData::ERROR_FILE_OPEN_FAILED;
	}
    
    time_t my_time = time(NULL);
    char* ctime_no_newline;
    char dates[26];
    ctime_s(dates, sizeof(dates), &my_time);
    char* date = dates;
    ctime_no_newline = strtok_s(date, "\n", &date);
    NMEAData* nmeadata = NMEAData::getInstance();
    printf("Cmd: %s     time : %s \nData: %s\n", pCmd,ctime_no_newline, pData);

    // Check if this is the GPGGA command. If it is, then display some data
    if (strstr(pCmd, "GPGGA") != NULL) 
    {
        CNMEAParserData::GGA_DATA_T ggaData;
        if (GetGPGGA(ggaData) == CNMEAParserData::ERROR_OK) 
        {
            nmeadata->m_latitude = ggaData.m_dLatitude;
            nmeadata->m_longitude = ggaData.m_dLongitude;
            nmeadata->m_altitude = ggaData.m_dAltitudeMSL;
            fprintf(fileptr, "%s, %s, %ld, %f, %f, %0.01f, %d\n", pCmd, ctime_no_newline, my_time, ggaData.m_dLatitude, ggaData.m_dLongitude, ggaData.m_dAltitudeMSL, ggaData.m_nSatsInView);
        }
    }

    if (strstr(pCmd, "GPRMC") != NULL) 
    {
        CNMEAParserData::RMC_DATA_T rmcData;
        if (GetGPRMC(rmcData) == CNMEAParserData::ERROR_OK) 
        {
            nmeadata->m_latitude = rmcData.m_dLatitude;
            nmeadata->m_longitude = rmcData.m_dLongitude;
            fprintf(fileptr, "%s, %s, %ld, %f, %f\n", pCmd, ctime_no_newline, my_time, rmcData.m_dLatitude, rmcData.m_dLongitude);
        }
    }

    // if (strstr(pCmd, "AOVEL") != NULL) //Not used
    // {
    //     CNMEAParserData::VEL_DATA_T velData;
    //     if (GetAOVEL(velData) == CNMEAParserData::ERROR_OK) {
    //     }
    // }

    if (strstr(pCmd, "AOATT") != NULL) 
    {
        CNMEAParserData::ATT_DATA_T attData;
        if (GetAOATT(attData) == CNMEAParserData::ERROR_OK) {
            nmeadata->m_rollangle = attData.m_dRollAngle;
            nmeadata->m_pitchangle = attData.m_dPitchAngle;
            nmeadata->m_headingangle = attData.m_dHeadingAngle;
            fprintf(fileptr, "%s, %s, %ld, , , , , %.02f, %.02f, %.02f\n", pCmd, ctime_no_newline, my_time, attData.m_dRollAngle, attData.m_dPitchAngle, attData.m_dHeadingAngle);
        }
    }

    if (strstr(pCmd, "AOGPS") != NULL) 
    {
        CNMEAParserData::GPS_DATA_T gpsData;
        if (GetAOGPS(gpsData) == CNMEAParserData::ERROR_OK) {
            nmeadata->m_latitude = gpsData.m_dLatitude;
            nmeadata->m_longitude = gpsData.m_dLongitude;
            nmeadata->m_altitude = gpsData.m_dAltitude;
            fprintf(fileptr, "%s, %s, %ld, %f, %f, %0.01f, %d\n", pCmd, ctime_no_newline, my_time, gpsData.m_dLatitude, gpsData.m_dLongitude, gpsData.m_dAltitude, gpsData.m_nNoOfSatellites);
        }
    }
    fclose(fileptr);
    json gps;
    gps["Latitude"] = nmeadata->m_latitude;
    gps["Longitude"] = nmeadata->m_longitude;
    gps["Altitude"] = nmeadata->m_altitude;
    gps["RollAngle"] = nmeadata->m_rollangle;
    gps["PitchAngle"] = nmeadata->m_pitchangle;
    gps["HeadingAngle"] = nmeadata->m_headingangle;
    json gpsarray = json::array ({gps});
    std::fstream gpsptr;
    gpsptr.open("flashdata.json", std::ios::out | std::ios::trunc);
    gpsptr<<gpsarray.dump(1);
    gpsptr.close();
    return CNMEAParserData::ERROR_OK;
}