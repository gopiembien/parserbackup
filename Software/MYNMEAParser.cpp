#include "MYNMEAParser.h"

CNMEAParserData::ERROR_E MyNMEAParser::ProcessRxCommand(char *pCmd, char *pData) 
{
    // Call base class to process the command
    CNMEAParser::ProcessRxCommand(pCmd, pData);
    FILE *fileptr;
    fileptr = fopen("outfile.csv", "a");
    if(fileptr == NULL)
	{
		printf("Error Opening file.\n");
		return CNMEAParserData::ERROR_FILE_OPEN_FAILED;
	}
    time_t my_time = time(NULL);
    char *ctime_no_newline;
    ctime_no_newline = strtok(ctime(&my_time), "\n");

    printf("Cmd: %s\nData: %s\n", pCmd, pData);

    // Check if this is the GPGGA command. If it is, then display some data
    if (strstr(pCmd, "GPGGA") != NULL) {
        CNMEAParserData::GGA_DATA_T ggaData;
        if (GetGPGGA(ggaData) == CNMEAParserData::ERROR_OK) 
        {
            // printf("GPGGA Parsed!\n");
            // printf("   Time:                %02d:%02d:%02d\n", ggaData.m_nHour, ggaData.m_nMinute, ggaData.m_nSecond);
            // printf("   Latitude:            %f\n", ggaData.m_dLatitude);
            // printf("   Longitude:           %f\n", ggaData.m_dLongitude);
            // printf("   Altitude:            %.01f\n", ggaData.m_dAltitudeMSL);
            // printf("   GPS Quality:         %d\n", ggaData.m_nGPSQuality);
            // printf("   Satellites in view:  %d\n", ggaData.m_nSatsInView);
            // printf("   HDOP:                %.02f\n", ggaData.m_dHDOP);
            // printf("   Differential ID:     %d\n", ggaData.m_nDifferentialID);
            // printf("   Differential age:    %f\n", ggaData.m_dDifferentialAge);
            // printf("   Geoidal Separation:  %f\n", ggaData.m_dGeoidalSep);
            // printf("   Vertical Speed:      %.02f\n", ggaData.m_dVertSpeed);
            fprintf(fileptr, "%s, %s, %ld, %f, %f, %0.01f, %d\n", pCmd, ctime_no_newline, my_time, ggaData.m_dLatitude, ggaData.m_dLongitude, ggaData.m_dAltitudeMSL, ggaData.m_nSatsInView);
        }
    }

    if (strstr(pCmd, "GPRMC") != NULL) 
    {
        CNMEAParserData::RMC_DATA_T rmcData;
        if (GetGPRMC(rmcData) == CNMEAParserData::ERROR_OK) {
            // printf("GPRMC Parsed!\n");
            // printf("   Time:                %02d:%02d:%02d\n", rmcData.m_nHour, rmcData.m_nMinute, rmcData.m_nSecond);
            // printf("   Status:              %c\n", rmcData.m_nStatus);
            // printf("   Latitude:            %f\n", rmcData.m_dLatitude);
            // printf("   Longitude:           %f\n", rmcData.m_dLongitude);
            // printf("   SOG knots:           %.02f\n", rmcData.m_dSpeedKnots);
            // printf("   Course:              %.02f\n", rmcData.m_dTrackAngle);
            // printf("   Date:                %02d:%02d:%02d\n", rmcData.m_nDay, rmcData.m_nMonth, rmcData.m_nDay);
            // printf("   Magnetic Variation:  %.02f\n", rmcData.m_dMagneticVariation);
            fprintf(fileptr, "%s, %s, %ld, %f, %f\n", pCmd, ctime_no_newline, my_time, rmcData.m_dLatitude, rmcData.m_dLongitude);
        }
    }

    if (strstr(pCmd, "AOVEL") != NULL) 
    {
        CNMEAParserData::VEL_DATA_T velData;
        if (GetAOVEL(velData) == CNMEAParserData::ERROR_OK) {
            // printf("AOVEL Parsed!\n");
            // printf("   Velocity X-axis:     %.02f\n", velData.m_dVelocityXAxis);
            // printf("   Velocity Y-axis:     %.02f\n", velData.m_dVelocityYAxis);
            // printf("   Velocity Z-axis:     %.02f\n", velData.m_dVelocityZAxis);
            // printf("   Velocity North:      %.02f\n", velData.m_dVelocityNorth);
            // printf("   Velocity East:       %.02f\n", velData.m_dVelocityEast);
            // printf("   Velocity Down:       %.02f\n", velData.m_dVelocityDown);
        }
    }

    if (strstr(pCmd, "AOATT") != NULL) 
    {
        CNMEAParserData::ATT_DATA_T attData;
        if (GetAOATT(attData) == CNMEAParserData::ERROR_OK) {
            // printf("AOATT Parsed!\n");
            // printf("   Roll Angle:       %.02f\n", attData.m_dRollAngle);
            // printf("   Pitch Angle:      %.02f\n", attData.m_dPitchAngle);
            // printf("   Heading Angle:    %.02f\n", attData.m_dHeadingAngle);
            // printf("   Q0:               %.02f\n", attData.m_dQ0);
            // printf("   Q1:               %.02f\n", attData.m_dQ1);
            // printf("   Q2:               %.02f\n", attData.m_dQ2);
            // printf("   Q3:               %.02f\n", attData.m_dQ3);
            // printf("   Ins Mode:         %02d\n", attData.m_nInsMode);
            fprintf(fileptr, "%s, %s, %ld, , , , , %.02f, %.02f, %.02f\n", pCmd, ctime_no_newline, my_time, attData.m_dRollAngle, attData.m_dPitchAngle, attData.m_dHeadingAngle);
        }
    }

    if (strstr(pCmd, "AOGPS") != NULL) 
    {
        CNMEAParserData::GPS_DATA_T gpsData;
        if (GetAOGPS(gpsData) == CNMEAParserData::ERROR_OK) {
            // printf("AOGPS Parsed!\n");
            // printf("   Fix Status:       	%d\n", gpsData.m_nFixStatus);
            // printf("   Fix Type:            %d\n", gpsData.m_nFixType);
            // printf("   Satellites in view:	%02d\n", gpsData.m_nNoOfSatellites);
            // printf("   GPS Latitue:	    	%.06lf\n", gpsData.m_dLatitude);
            // printf("   GPS Longitude:    	%.06lf\n", gpsData.m_dLongitude);
            // printf("   GPS Altitude:     	%.03lf\n", gpsData.m_dAltitude);
            // printf("   Speed Over Ground:	%.03f\n", gpsData.m_dSpeedOverGround);
            // printf("   Course Over Ground:	%.03f\n", gpsData.m_dCourseOverGround);
            // printf("   PDOP:                %.03f\n", gpsData.m_dDilutionOfPrecision);
            fprintf(fileptr, "%s, %s, %ld, %f, %f, %0.01f, %d\n", pCmd, ctime_no_newline, my_time, gpsData.m_dLatitude, gpsData.m_dLongitude, gpsData.m_dAltitude, gpsData.m_nNoOfSatellites);
        }
    }
    fclose(fileptr);
    return CNMEAParserData::ERROR_OK;
}