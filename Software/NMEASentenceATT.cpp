#include "NMEASentenceATT.h"
#include <stdlib.h>

CNMEASentenceATT::CNMEASentenceATT() 
{
	// TODO Auto-generated constructor stub
}

CNMEASentenceATT::~CNMEASentenceATT() 
{
	// TODO Auto-generated destructor stub
}

CNMEAParserData::ERROR_E CNMEASentenceATT::ProcessSentence(char *pCmd, char *pData) 
{
    UNUSED_PARAM(pCmd);
    char szField[c_nMaxField];
	// Rollangle
	if (GetField(pData, szField, 0, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_dRollAngle = atof(szField);
	}
	// Vy
	if (GetField(pData, szField, 1, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_dPitchAngle = atof(szField);
	}
    // Vz
	if (GetField(pData, szField, 2, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dHeadingAngle = atof(szField);
	}
    // Vn
	if (GetField(pData, szField, 3, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dQ0 = atof(szField);
	}
    // Ve
	if (GetField(pData, szField, 4, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dQ1 = atof(szField);
	}
    // Vd
	if (GetField(pData, szField, 5, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dQ2 = atof(szField);
	}
    //
    if (GetField(pData, szField, 6, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dQ3 = atof(szField);
	}
    //
    if (GetField(pData, szField, 7, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_nInsMode = atoi(szField);
	}
	m_uRxCount++;

	return CNMEAParserData::ERROR_OK;
}

void CNMEASentenceATT::ResetData(void) 
{
	m_uRxCount = 0;
	m_SentenceData.m_dRollAngle = 0.0;
	m_SentenceData.m_dPitchAngle = 0.0;
	m_SentenceData.m_dHeadingAngle = 0.0;
	m_SentenceData.m_dQ0 = 0.0;
	m_SentenceData.m_dQ1 = 0.0;
	m_SentenceData.m_dQ2 = 0.0;
    m_SentenceData.m_dQ3 = 0.0;
    m_SentenceData.m_nInsMode = 0;
}
