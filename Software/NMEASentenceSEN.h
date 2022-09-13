#ifndef _NMEASENTENCESEN_H_
#define _NMEASENTENCESEN_H_

#include "NMEASentenceBase.h"
#include "NMEAParserData.h"

class CNMEASentenceSEN : public CNMEASentenceBase {
private:
	CNMEAParserData::SEN_DATA_T		m_SentenceData;

public:
	CNMEASentenceSEN();
	virtual ~CNMEASentenceSEN();
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData);
	virtual void ResetData(void);
	CNMEAParserData::SEN_DATA_T GetSentenceData(void) { return m_SentenceData; }
};

#endif /* _NMEASENTENCESEN_H_ */