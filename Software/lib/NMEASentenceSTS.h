#ifndef _NMEASENTENCESTS_H_
#define _NMEASENTENCESTS_H_

#include "NMEASentenceBase.h"
#include "NMEAParserData.h"

class CNMEASentenceSTS : public CNMEASentenceBase {
private:
	CNMEAParserData::STS_DATA_T		m_SentenceData;

public:
	CNMEASentenceSTS();
	virtual ~CNMEASentenceSTS();
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData);
	virtual void ResetData(void);
	CNMEAParserData::STS_DATA_T GetSentenceData(void) { return m_SentenceData; }
};

#endif /* _NMEASENTENCESTS_H_ */