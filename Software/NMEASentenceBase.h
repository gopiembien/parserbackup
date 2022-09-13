#ifndef _NMEASENTENCEBASE_H_
#define _NMEASENTENCEBASE_H_

#include <string>
#include "NMEAParserData.h"

///
/// \class CNMEASentenceBase
/// \brief This is the base class for every NMEA sentence
///
class CNMEASentenceBase
{
public:
	static const int				c_nMaxField = 256;							///< Maximum field length

private:
	std::string						m_strSentenceID;							///< Sentence ID, ie: GGA, RMC, etc...
	CNMEAParserData::TALKER_ID_E	m_nTalkerID;								///< Talker ID, ie: GP, GN, etc...

protected:
	unsigned int					m_uRxCount;									///< Receive count

public:
	CNMEASentenceBase();
	~CNMEASentenceBase();

	/// \brief Process the data from the specific NMEA sentence. 
	/// \param pCmd Talker command
	/// \param pData Comma separated talker data string.
	/// \return ERROR_OK if successful
	///
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData) = 0;

	/// \brief Clears the sentence specific data to a default value
	virtual void ResetData(void) = 0;

	/// \brief Returns the receive count for this sentence
	unsigned int GetRxCount(void) {	return m_uRxCount;	}
protected:

	/// This function will get the specified field in a NMEA string.
	/// \param	pData -		Pointer to NMEA string
	///	\param	pField -		pointer to returned field
	///	\param	nFieldNum -		Field offset to get
	///	\param	nMaxFieldLen -	Maximum of bytes pFiled can handle
	///
	CNMEAParserData::ERROR_E GetField(char * pData, char * pField, int nFieldNum, int nMaxFieldLen);

};

#endif