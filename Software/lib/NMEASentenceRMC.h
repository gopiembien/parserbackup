#ifndef _NMEASENTENCERMC_H_
#define _NMEASENTENCERMC_H_

#include "NMEASentenceBase.h"
#include "NMEAParserData.h"

class CNMEASentenceRMC : public CNMEASentenceBase {
private:
	CNMEAParserData::RMC_DATA_T		m_SentenceData;								///< Sentence specific data

public:
	CNMEASentenceRMC();
	virtual ~CNMEASentenceRMC();

	///
	/// \brief Process the data from the specific NMEA sentence.
	///
	/// This method was made into a pure virtual to force the child class to define
	/// the sentense processor. You must redefine this method to process the
	/// specific data. See CNMEASentenceGGA::ProcessSentence() child class method
	/// for an example.
	///
	/// \param pCmd Talker command
	/// \param pData Comma separated talker data string.
	/// \return ERROR_OK if successful
	///
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData);

	///
	/// \brief Clears the sentense specific data to a default value
	///
	/// This method was made into a pure virtual to force the child class to define
	/// the sentense processor. You must redefine this method to process the
	/// specific data. See CNMEASentenceGGA::ResetData() child class method
	/// for an example.
	///
	virtual void ResetData(void);

	///
	/// \brief Returns the NMEA sentence data structure
	///
	CNMEAParserData::RMC_DATA_T GetSentenceData(void) { return m_SentenceData; }
};

#endif /* _NMEASENTENCERMC_H_ */
