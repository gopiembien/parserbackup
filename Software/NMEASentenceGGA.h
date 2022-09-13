#ifndef _NMEASENTENCEGGA_H_
#define _NMEASENTENCEGGA_H_

#include <string>
#include "NMEAParserData.h"
#include "NMEASentenceBase.h"
#include "NMEAParserData.h"

///
/// \class CNMEASentenceGGA
/// \brief --GGA Data class
///
class CNMEASentenceGGA : public CNMEASentenceBase
{
private:
	CNMEAParserData::GGA_DATA_T		m_SentenceData;								///< Sentence specific data
	int								m_nOldVSpeedSeconds;						///< Used to calculate vertical speed
	double							m_dOldVSpeedAlt;							///< Used to calculate vertical speed

public:
	CNMEASentenceGGA();
	virtual ~CNMEASentenceGGA();
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData);

	virtual void ResetData(void);

	///
	/// \brief Returns the NMEA sentence data structure
	///
	CNMEAParserData::GGA_DATA_T GetSentenceData(void) { return m_SentenceData; }

};

#endif 