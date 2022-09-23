#include "NMEASentenceVEL.h"
#include <stdlib.h>

CNMEASentenceVEL::CNMEASentenceVEL() 
{
	// TODO Auto-generated constructor stub
}

CNMEASentenceVEL::~CNMEASentenceVEL() 
{
	// TODO Auto-generated destructor stub
}

CNMEAParserData::ERROR_E CNMEASentenceVEL::ProcessSentence(char *pCmd, char *pData) 
{
    UNUSED_PARAM(pCmd);
    char szField[c_nMaxField];
	// Vx
	if (GetField(pData, szField, 0, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_dVelocityXAxis = atof(szField);
	}
	// Vy
	if (GetField(pData, szField, 1, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_dVelocityYAxis = atof(szField);
	}
    // Vz
	if (GetField(pData, szField, 2, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dVelocityZAxis = atof(szField);
	}
    // Vn
	if (GetField(pData, szField, 3, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dVelocityNorth = atof(szField);
	}
    // Ve
	if (GetField(pData, szField, 4, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dVelocityEast = atof(szField);
	}
    // Vd
	if (GetField(pData, szField, 5, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_dVelocityDown = atof(szField);
	}
	m_uRxCount++;

	return CNMEAParserData::ERROR_OK;
}

void CNMEASentenceVEL::ResetData(void) 
{
	m_uRxCount = 0;
	m_SentenceData.m_dVelocityXAxis = 0.0;
	m_SentenceData.m_dVelocityYAxis = 0.0;
	m_SentenceData.m_dVelocityZAxis = 0.0;
	m_SentenceData.m_dVelocityNorth = 0.0;
	m_SentenceData.m_dVelocityEast = 0.0;
	m_SentenceData.m_dVelocityDown = 0.0;
}
