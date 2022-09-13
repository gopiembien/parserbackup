#ifndef _NMEASENTENCEATT_H_
#define _NMEASENTENCEATT_H_

#include "NMEASentenceBase.h"
#include "NMEAParserData.h"

class CNMEASentenceATT : public CNMEASentenceBase {
private:
	CNMEAParserData::ATT_DATA_T		m_SentenceData;

public:
	CNMEASentenceATT();
	virtual ~CNMEASentenceATT();
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData);
	virtual void ResetData(void);
	CNMEAParserData::ATT_DATA_T GetSentenceData(void) { return m_SentenceData; }
};

#endif /* _NMEASENTENCEATT_H_ */