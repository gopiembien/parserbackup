#include "NMEASentenceSTS.h"
#include <stdlib.h>

CNMEASentenceSTS::CNMEASentenceSTS() 
{
	// TODO Auto-generated constructor stub
}

CNMEASentenceSTS::~CNMEASentenceSTS() 
{
	// TODO Auto-generated destructor stub
}

CNMEAParserData::ERROR_E CNMEASentenceSTS::ProcessSentence(char *pCmd, char *pData) 
{
    UNUSED_PARAM(pCmd);
    char szField[c_nMaxField];
    char *ptr;
	// Epoch time in seconds
	if (GetField(pData, szField, 0, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_timeSeconds = strtol(szField, &ptr , 16);
	}
	// Microseconds since last second
	if (GetField(pData, szField, 1, c_nMaxField) == CNMEAParserData::ERROR_OK) {
		m_SentenceData.m_nMSEC = atoi(szField);
	}
    // INS STS
	if (GetField(pData, szField, 2, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_lInsStatus = strtol(szField, &ptr , 16);
	}
    // Hardware STS
	if (GetField(pData, szField, 3, c_nMaxField) == CNMEAParserData::ERROR_OK)
	{
		m_SentenceData.m_lHardwareStatus = strtol(szField, &ptr , 16);
	}
	m_uRxCount++;

	return CNMEAParserData::ERROR_OK;
}

void CNMEASentenceSTS::ResetData(void) 
{
	m_uRxCount = 0;
	m_SentenceData.m_timeSeconds = 0;
	m_SentenceData.m_nMSEC = 0;
	m_SentenceData.m_lInsStatus = 0;
	m_SentenceData.m_lHardwareStatus = 0;
}
