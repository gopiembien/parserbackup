#pragma once
#include <cstddef>
#include <stdint.h>
#include <map>
#include <time.h>
#include <stdlib.h>

#include "NMEAParserData.h"
#include "NMEAParserPacket.h"
#include "NMEASentenceGGA.h"
#include "NMEASentenceRMC.h"
#include "NMEASentenceVEL.h"
#include "NMEASentenceATT.h"
#include "NMEASentenceGPS.h"
#include "NMEASentenceSTS.h"
#include "NMEASentenceSEN.h"
///
/// \class CNMEAParser
/// \brief This class will parse NMEA data, store its data and report that it has received data
///
class CNMEAParser : public CNMEAParserPacket {

private:

	// GPS
	CNMEASentenceGGA	m_GPGGA;												///< GPGGA Specific sentence data
	CNMEASentenceRMC	m_GPRMC;												///< GPRMC Recommended minimum data for GPS
	// AO
	CNMEASentenceVEL	m_AOVEL;
	CNMEASentenceATT	m_AOATT;
	CNMEASentenceGPS	m_AOGPS;
	CNMEASentenceSTS	m_AOSTS;
	CNMEASentenceSEN	m_AOSEN;
	
public:
	CNMEAParser();
	virtual ~CNMEAParser();

	///
	/// \brief Resets or clears all NMEA data to a known default value
	///
	void ResetData(void);

	///
	/// \brief Places a copy of the GPGGA data into sentenseData
	/// \param sentenseData reference to a CNMEASentenceGGA object to place the data into.
	/// \return Returns ERROR_OK if successful.
	///
	CNMEAParserData::ERROR_E GetGPGGA(CNMEAParserData::GGA_DATA_T & sentenseData);
	///
	/// \brief Places a copy of the GPRMC data into sentenseData
	/// \param sentenseData reference to a CNMEASentenceGMC object to place the data into.
	/// \return Returns ERROR_OK if successful.
	///
	CNMEAParserData::ERROR_E GetGPRMC(CNMEAParserData::RMC_DATA_T & sentenseData);
	/// 
	CNMEAParserData::ERROR_E GetAOVEL(CNMEAParserData::VEL_DATA_T & sentenseData);
	CNMEAParserData::ERROR_E GetAOATT(CNMEAParserData::ATT_DATA_T & sentenseData);
	CNMEAParserData::ERROR_E GetAOGPS(CNMEAParserData::GPS_DATA_T & sentenseData);
	CNMEAParserData::ERROR_E GetAOSTS(CNMEAParserData::STS_DATA_T & sentenseData);
	CNMEAParserData::ERROR_E GetAOSEN(CNMEAParserData::SEN_DATA_T & sentenseData);

protected:
	///
	/// \brief This method is redefined from CNMEAParserPacket::ProcessRxCommand(char *pCmd, char *pData)
	///
	/// \param pCmd Pointer to the NMEA command string
	/// \param pData Comma separated data that belongs to the command
	/// \return Returns CNMEAParserData::ERROR_OK If successful
	///
	virtual CNMEAParserData::ERROR_E ProcessRxCommand(char *pCmd, char *pData);

	///
	/// \brief This method will invoke a semaphore lock (mutex) for data access.
	///
	///	Redefine this method if you will be access this class from different threads.
	///
	virtual void DataAccessSemaphoreLock(void) {}

	///
	/// \brief This method will invoke a semaphore unlock (mutex) for data access.
	///
	///	Redefine this method if you will be access this class from different threads.
	///
	virtual void DataAccessSemaphoreUnlock(void) {}

};
