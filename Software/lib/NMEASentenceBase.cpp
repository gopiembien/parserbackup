#include "NMEASentenceBase.h"



CNMEASentenceBase::CNMEASentenceBase() :
	m_uRxCount(0)
{
}


CNMEASentenceBase::~CNMEASentenceBase()
{
}

CNMEAParserData::ERROR_E CNMEASentenceBase::GetField(char * pData, char * pField, int nFieldNum, int nMaxFieldLen)
{
	//
	// Validate parameters
	//
	if (pData == NULL || pField == NULL || nMaxFieldLen <= 0)
	{
		return CNMEAParserData::ERROR_FAIL;
	}

	//
	// Go to the beginning of the selected field
	//
	int i = 0;
	int nField = 0;
	while (nField != nFieldNum && pData[i])
	{
		if (pData[i] == ',')
		{
			nField++;
		}

		i++;

		if (pData[i] == 0)
		{
			pField[0] = '\0';
			return CNMEAParserData::ERROR_FAIL;
		}
	}

	if (pData[i] == ',' || pData[i] == '*')
	{
		pField[0] = '\0';
		return CNMEAParserData::ERROR_FAIL;
	}

	//
	// copy field from pData to Field
	//
	int i2 = 0;
	while (pData[i] != ',' && pData[i] != '*' && pData[i])
	{
		pField[i2] = pData[i];
		i2++; i++;

		//
		// check if field is too big to fit on passed parameter. If it is,
		// crop returned field to its max length.
		//
		if (i2 >= nMaxFieldLen)
		{
			i2 = nMaxFieldLen - 1;
			break;
		}
	}
	pField[i2] = '\0';

	return CNMEAParserData::ERROR_OK;
}
