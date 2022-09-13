#ifndef _NMEAPARSERPACKET_H_
#define _NMEAPARSERPACKET_H_
#include <cstddef>
#include <stdint.h>
#include "NMEAParserData.h"
#include "ceSerial.h"

///
/// \class CNMEAParserPacket
/// \brief This class will parse NMEA data packet and call its virtual processor methods.
///
/// Below describes the ProcessNMEABuffer() methods state machine. It's whole goal is to connect data, build a command and call ProcessRxCommand robustly. 
///
/// \dot Receive Packet State Machine
///		digraph example{
///  		node[fontname = Helvetica, fontsize = 10];
///  		edge[fontname = Helvetica, fontsize = 10];
///
///			PARSE_STATE_SOM[label = "PARSE_STATE_SOM" URL = "\ref ProcessRxCommand"];
///			PARSE_STATE_CMD[label = "PARSE_STATE_CMD" URL = "\ref ProcessRxCommand"];
///			PARSE_STATE_DATA[label = "PARSE_STATE_DATA" URL = "\ref ProcessRxCommand"];
///			PARSE_STATE_CHECKSUM_1[label = "PARSE_STATE_CHECKSUM_1" URL = "\ref ProcessRxCommand"];
///			PARSE_STATE_CHECKSUM_2[label = "PARSE_STATE_CHECKSUM_2" URL = "\ref ProcessRxCommand"];
/// 
///			ProcessRxCommand[label = "Call Virtual ProcessRxCommand" shape="rectangle" URL = "\ref ProcessRxCommand"];
///
///			PARSE_STATE_SOM->PARSE_STATE_CMD[arrowhead = "normal", style = "solid"];
///			PARSE_STATE_CMD->PARSE_STATE_DATA[arrowhead = "normal", style = "solid"];
/// 
///			PARSE_STATE_DATA->PARSE_STATE_CHECKSUM_1[arrowhead = "normal", style = "solid"];
///			PARSE_STATE_DATA->PARSE_STATE_SOM[arrowhead = "normal", style = "solid", color = red, label="Checksum\nMismatch"];
///			PARSE_STATE_DATA->ProcessRxCommand [arrowhead = "normal", style = "solid", label="Sentence With\nNo Checksum"];
///			PARSE_STATE_DATA->PARSE_STATE_SOM[arrowhead = "normal", style = "solid", color = red, label="Buffer\nOverflow"];
/// 
///			PARSE_STATE_CHECKSUM_1->PARSE_STATE_CHECKSUM_2[arrowhead = "normal", style = "solid"];
///			PARSE_STATE_CHECKSUM_2->ProcessRxCommand [arrowhead = "normal", style = "solid"];
///			PARSE_STATE_CHECKSUM_2->PARSE_STATE_SOM [arrowhead = "normal", style = "solid", color = red, label="Checksum\nMismatch"];
///			ProcessRxCommand->PARSE_STATE_SOM [arrowhead = "normal", style = "solid"];
///		}
///  \enddot
///  

class CNMEAParserPacket {

private:

	enum PARSE_STATE {
		PARSE_STATE_SOM = 0,													///< Search for start of message
		PARSE_STATE_CMD,														///< Get command
		PARSE_STATE_DATA,														///< Get data
		PARSE_STATE_CHECKSUM_1,													///< Get first checksum character
		PARSE_STATE_CHECKSUM_2,													///< get second checksum character
	};


private:
	PARSE_STATE						m_nState;									///< Current NMEA parse state
	uint8_t							m_u8Checksum;								///< Calculated NMEA sentence checksum
	uint8_t							m_u8ReceivedChecksum;						///< Received NMEA sentence checksum (if exists)
	uint16_t						m_nIndex;									///< Index used for command and data
	char							m_pCommand[CNMEAParserData::c_uMaxCmdLen];	///< NMEA command
	char							m_pData[CNMEAParserData::c_uMaxDataLen];	///< NMEA data

public:
	CNMEAParserPacket();
	~CNMEAParserPacket();

	CNMEAParserData::ERROR_E ProcessNMEABuffer(ceSerial &com);

	/// A reset will restart the parser to start to look for the start of message.
	void Reset(void);

	///
	/// \brief This method is called whenever there is a parsing error.
	/// \param pCmd Pointer to NMEA command that caused the error. Please note that this parameter may be NULL of not completely defined. Use with caution.
	///
    virtual void OnError(CNMEAParserData::ERROR_E nError, char *pCmd) { UNUSED_PARAM(nError); UNUSED_PARAM(pCmd);}

protected:

	///
	/// \brief Redefine this method to process valid NMEA commands. Make sure that you honer the
	/// parameters below.
	///
	/// \param pCmd Pointer to the NMEA command string
	/// \param pData Comma separated data that belongs to the command
	/// \return Returns CNMEAParserData::ERROR_OK If successful
	///
	virtual CNMEAParserData::ERROR_E ProcessRxCommand(char *pCmd, char *pData) = 0;

	///
	/// \brief This method is called when receiving the start of message of the NMEA packet.
	///
	/// If you need to time tag your NMEA sentences, redefine this method to allow 
	/// you to capture when the SOM was received. You can then use the ProcessRxCommand()
	/// method to capture the NMEA command that this time-tag belongs to.
	///
	virtual void TimeTag(void) {}
};

#endif