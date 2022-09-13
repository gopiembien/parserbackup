#ifndef _NMEASENTENCEGPS_H_
#define _NMEASENTENCEGPS_H_

#include "NMEASentenceBase.h"
#include "NMEAParserData.h"

class CNMEASentenceGPS : public CNMEASentenceBase {
private:
	CNMEAParserData::GPS_DATA_T		m_SentenceData;

public:
	CNMEASentenceGPS();
	virtual ~CNMEASentenceGPS();
	virtual CNMEAParserData::ERROR_E ProcessSentence(char *pCmd, char *pData);
	virtual void ResetData(void);
	CNMEAParserData::GPS_DATA_T GetSentenceData(void) { return m_SentenceData; }
};

#endif /* _NMEASENTENCEGPS_H_ */