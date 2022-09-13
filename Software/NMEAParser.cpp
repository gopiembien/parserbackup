#include <stdio.h>
#include <string.h>
#include "NMEAParser.h"

CNMEAParser::CNMEAParser()
{
	ResetData();
}

CNMEAParser::~CNMEAParser()
{
}

void CNMEAParser::ResetData(void)
{
	//
	// Lock access to data
	//
	DataAccessSemaphoreLock();
	m_GPGGA.ResetData();
	m_GPRMC.ResetData();
	m_AOVEL.ResetData();
	m_AOATT.ResetData();
	m_AOGPS.ResetData();
	m_AOSTS.ResetData();
	m_AOSEN.ResetData();
	//
	// Unlock access to data
	//
	DataAccessSemaphoreUnlock();
}

CNMEAParserData::ERROR_E CNMEAParser::GetGPGGA(CNMEAParserData::GGA_DATA_T & sentenseData)
{
	DataAccessSemaphoreLock();
	sentenseData = m_GPGGA.GetSentenceData();
	DataAccessSemaphoreUnlock();
	return CNMEAParserData::ERROR_OK;
}

CNMEAParserData::ERROR_E CNMEAParser::GetGPRMC(CNMEAParserData::RMC_DATA_T & sentenseData)
{
	DataAccessSemaphoreLock();
	sentenseData = m_GPRMC.GetSentenceData();
	DataAccessSemaphoreUnlock();
	return CNMEAParserData::ERROR_OK;
}

CNMEAParserData::ERROR_E CNMEAParser::GetAOVEL(CNMEAParserData::VEL_DATA_T & sentenseData)
{
	DataAccessSemaphoreLock();
	sentenseData = m_AOVEL.GetSentenceData();
	DataAccessSemaphoreUnlock();
	return CNMEAParserData::ERROR_OK;
}

CNMEAParserData::ERROR_E CNMEAParser::GetAOATT(CNMEAParserData::ATT_DATA_T & sentenseData)
{
	DataAccessSemaphoreLock();
	sentenseData = m_AOATT.GetSentenceData();
	DataAccessSemaphoreUnlock();
	return CNMEAParserData::ERROR_OK;
}

CNMEAParserData::ERROR_E CNMEAParser::GetAOGPS(CNMEAParserData::GPS_DATA_T & sentenseData)
{
	DataAccessSemaphoreLock();
	sentenseData = m_AOGPS.GetSentenceData();
	DataAccessSemaphoreUnlock();
	return CNMEAParserData::ERROR_OK;
}

CNMEAParserData::ERROR_E CNMEAParser::GetAOSTS(CNMEAParserData::STS_DATA_T & sentenseData)
{
	DataAccessSemaphoreLock();
	sentenseData = m_AOSTS.GetSentenceData();
	DataAccessSemaphoreUnlock();
	return CNMEAParserData::ERROR_OK;
}

CNMEAParserData::ERROR_E CNMEAParser::GetAOSEN(CNMEAParserData::SEN_DATA_T & sentenseData)
{
	DataAccessSemaphoreLock();
	sentenseData = m_AOSEN.GetSentenceData();
	DataAccessSemaphoreUnlock();
	return CNMEAParserData::ERROR_OK;
}

CNMEAParserData::ERROR_E CNMEAParser::ProcessRxCommand(char * pCmd, char * pData)
{
	// Grab the talker ID
	uint16_t u16TalkerID = (uint16_t)((uint8_t)pCmd[0]) << 8;
	u16TalkerID |= (uint16_t)((uint8_t)pCmd[1]);
	// Get the sentence ID, --XXX where XXX is the sentence ID
	char *lpszSentenceID = &pCmd[2];

	//printf("Cmd: %s, TalkerID:%c%c, Sentence ID: %s\n", pCmd, (u16TalkerID >> 8) & 0xFF, (u16TalkerID) & 0xFF, lpszSentenceID);

	//-----------------------------------------------------------------------------
	if (strcmp(pCmd, "GPGGA") == 0) {
		DataAccessSemaphoreLock();
		m_GPGGA.ProcessSentence(pCmd, pData);
		DataAccessSemaphoreUnlock();
	}
	else if (strcmp(pCmd, "GPRMC") == 0) {
		DataAccessSemaphoreLock();
		m_GPRMC.ProcessSentence(pCmd, pData);
		DataAccessSemaphoreUnlock();
	}
	else if (strcmp(pCmd, "AOVEL") == 0) {
		DataAccessSemaphoreLock();
		m_AOVEL.ProcessSentence(pCmd, pData);
		DataAccessSemaphoreUnlock();
	}
	else if (strcmp(pCmd, "AOATT") == 0) {
		DataAccessSemaphoreLock();
		m_AOATT.ProcessSentence(pCmd, pData);
		DataAccessSemaphoreUnlock();
	}
	else if (strcmp(pCmd, "AOGPS") == 0) {
		DataAccessSemaphoreLock();
		m_AOGPS.ProcessSentence(pCmd, pData);
		DataAccessSemaphoreUnlock();
	}
	else if (strcmp(pCmd, "AOSTS") == 0) {
		DataAccessSemaphoreLock();
		m_AOSTS.ProcessSentence(pCmd, pData);
		DataAccessSemaphoreUnlock();
	}
	else if (strcmp(pCmd, "AOSEN") == 0) {
		DataAccessSemaphoreLock();
		m_AOSEN.ProcessSentence(pCmd, pData);
		DataAccessSemaphoreUnlock();
	}

	return CNMEAParserData::ERROR_OK;
}

