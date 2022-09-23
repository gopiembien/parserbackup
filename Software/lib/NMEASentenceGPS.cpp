#include "NMEASentenceGPS.h"
#include <stdlib.h>

CNMEASentenceGPS::CNMEASentenceGPS() 
{
	// TODO Auto-generated constructor stub
}

CNMEASentenceGPS::~CNMEASentenceGPS() 
{
	// TODO Auto-generated destructor stub
}

CNMEAParserData::ERROR_E CNMEASentenceGPS::ProcessSentence(char *pCmd, char *pData) 
{
    UNUSED_PARAM(pCmd);
    char szField[c_nMaxField];
	// FixStatus
	if (GetField(pData, szField, 0, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_nFixStatus = (CNMEAParserData::FIX_STATUS_E)atoi(szField);
	}
	else {
		m_SentenceData.m_nFixStatus = CNMEAParserData::NO_FIX;
	}
	// FixType
	if (GetField(pData, szField, 1, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_nFixType = (CNMEAParserData::FIX_TYPE_E)atoi(szField);
	}
	else {
		m_SentenceData.m_nFixType = CNMEAParserData::GNSS_NO_FIX;
	}
    // No Of Satellites
	if (GetField(pData, szField, 2, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_nNoOfSatellites = atoi(szField);
	}
    // Vn
	if (GetField(pData, szField, 3, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dLatitude = atof(szField);
	}
    // Ve
	if (GetField(pData, szField, 4, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dLongitude = atof(szField);
	}
    // Vd
	if (GetField(pData, szField, 5, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dAltitude = atof(szField);
	}
    //
    if (GetField(pData, szField, 6, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dSpeedOverGround = atof(szField);
	}
    //
    if (GetField(pData, szField, 7, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dCourseOverGround = atof(szField);
	}
    //
    if (GetField(pData, szField, 8, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dDilutionOfPrecision = atof(szField);
	}
	m_uRxCount++;

	return CNMEAParserData::ERROR_OK;
}

void CNMEASentenceGPS::ResetData(void) 
{
	m_uRxCount = 0;
	m_SentenceData.m_nFixStatus = CNMEAParserData::NO_FIX;
	m_SentenceData.m_nFixType = CNMEAParserData::GNSS_NO_FIX;
	m_SentenceData.m_nNoOfSatellites = 0;
	m_SentenceData.m_dLatitude = 0.0;
	m_SentenceData.m_dLongitude = 0.0;
	m_SentenceData.m_dAltitude = 0.0;
    m_SentenceData.m_dSpeedOverGround = 0.0;
    m_SentenceData.m_dCourseOverGround = 0.0;
    m_SentenceData.m_dDilutionOfPrecision = 0.0;
}
