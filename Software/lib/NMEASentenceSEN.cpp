#include "NMEASentenceSEN.h"
#include <stdlib.h>

CNMEASentenceSEN::CNMEASentenceSEN() 
{
	// TODO Auto-generated constructor stub
}

CNMEASentenceSEN::~CNMEASentenceSEN() 
{
	// TODO Auto-generated destructor stub
}

CNMEAParserData::ERROR_E CNMEASentenceSEN::ProcessSentence(char *pCmd, char *pData) 
{
    UNUSED_PARAM(pCmd);
    char szField[c_nMaxField];
	// acceleration in X axis (in g)
	if (GetField(pData, szField, 0, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_dAX = atof(szField);
	}
	// acceleration in Y axis (in g)
	if (GetField(pData, szField, 1, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_dAY = atof(szField);
	}
    // acceleration in Z axis (in g)
	if (GetField(pData, szField, 2, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dAZ = atof(szField);
	}
    // Body rate in X axis (in rad/s)
	if (GetField(pData, szField, 3, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dBRX = atof(szField);
	}
    // Body rate in Y axis (in rad/s)
	if (GetField(pData, szField, 4, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dBRY = atof(szField);
	}
    // Body rate in Z axis (in rad/s)
	if (GetField(pData, szField, 5, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dBRZ = atof(szField);
	}
    // Euler Rate_Roll (in rad/s)
    if (GetField(pData, szField, 6, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dERR = atof(szField);
	}
    // Euler Rate_Pitch (in rad/s)
    if (GetField(pData, szField, 7, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dERP = atof(szField);
	}
    // Euler Rate_Yaw (in rad/s)
    if (GetField(pData, szField, 8, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dERY = atof(szField);
	}

	m_uRxCount++;

	return CNMEAParserData::ERROR_OK;
}

void CNMEASentenceSEN::ResetData(void) 
{
	m_uRxCount = 0;
	m_SentenceData.m_dAX = 0.0;
	m_SentenceData.m_dAY = 0.0;
	m_SentenceData.m_dAZ = 0.0;
	m_SentenceData.m_dBRX = 0.0;
	m_SentenceData.m_dBRY = 0.0;
	m_SentenceData.m_dBRZ = 0.0;
    m_SentenceData.m_dERR = 0.0;
    m_SentenceData.m_dERP = 0.0;
    m_SentenceData.m_dERY = 0.0;
}
