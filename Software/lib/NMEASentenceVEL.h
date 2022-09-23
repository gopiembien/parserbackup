#ifndef _NMEASENTENCEVEL_H_
#define _NMEASENTENCEVEL_H_

#include "NMEASentenceBase.h"
#include "NMEAParserData.h"

class CNMEASentenceVEL : public CNMEASentenceBase {
private:
	CNMEAParserData::VEL_DATA_T		m_SentenceData;

public:
	CNMEASentenceVEL();
	virtual ~CNMEASentenceVEL();
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData);
	virtual void ResetData(void);
	CNMEAParserData::VEL_DATA_T GetSentenceData(void) { return m_SentenceData; }
};

#endif /* NMEAPARSERLIB_NMEASENTENCEVEL_H_ */