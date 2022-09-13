#ifndef _MYNMEAPARSER_H_
#define _MYNMEAPARSER_H_

#include <stdio.h>
#include <string.h>
#include "NMEAParser.h"
#include "ceSerial.h"

/// \class MyParser
/// \brief child class of CNMEAParser which will redefine notification calls from the parent class.
class MyNMEAParser : public CNMEAParser 
{
	virtual void OnError(CNMEAParserData::ERROR_E nError, char *pCmd) 
    {
		printf("ERROR for Cmd: %s, Number: %d\n", pCmd, nError);
	}

protected:
    virtual CNMEAParserData::ERROR_E ProcessRxCommand(char *pCmd, char *pData);
};

#endif