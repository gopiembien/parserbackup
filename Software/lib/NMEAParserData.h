#ifndef _NMEAPARSERDATA_H_
#define _NMEAPARSERDATA_H_
#include <cstddef>
#include <stdint.h>
#include <time.h>

/// Used to identify unused function parameters. 
#define UNUSED_PARAM(x) (void)(x)

/// \class CNMEAParser
/// \brief This class will parse NMEA data, store its data and report that it has received data
namespace CNMEAParserData {

	/// Error types. Most methods will return one of the follow error types.
	enum ERROR_E {
		ERROR_OK = 0,															///< No error, operation successful
		ERROR_FAIL = 1,															///< Error, operation failed
		ERROR_TOO_MANY_SATELLITES = 2,											///< Error, could not process. Too many satellites to fit into database
		ERROR_CHECKSUM = 3,														///< Error, packet checksum mismatch
		ERROR_RX_BUFFER_OVERFLOW,												///< Error, receive packet buffer overflow
		ERROR_CMD_BUFFER_OVERFLOW,												///< Error, receive command buffer overflow
		ERROR_PORT_CLOSED,														///< Error, Port closed
		ERROR_FILE_OPEN_FAILED,													///< Error, File open failed
	};

	// Constants
	static const uint32_t		c_uMaxCmdLen = 32;								///< maximum command length (NMEA address)
	static const uint32_t		c_uMaxDataLen = 256;							///< maximum command length (NMEA address)
	static const int			c_nMaxConstellation = 64;						///< This is a max number if satellites for a constellation. NOTE: This does not reflect the actual constellation count for a given GPS/GNSS system
	static const int			c_nMaxGSASats = 12;								///< Maximum number of satellites in the GSA message
	static const int			c_nInvlidPRN = 0;								///< Invalid or non existing PRN

	///
	/// All known talker IDs
	///
	enum TALKER_ID_E {
		TID_AB = (uint16_t)'A' << 8 | (uint16_t)'B',							///< AB Independent AIS Base Station
		TID_AD = (uint16_t)'A' << 8 | (uint16_t)'D',							///< AD Dependent AIS Base Station
		TID_AG = (uint16_t)'A' << 8 | (uint16_t)'G',							///< AG Autopilot - General
		TID_AP = (uint16_t)'A' << 8 | (uint16_t)'P',							///< AP Autopilot - Magnetic
		TID_BD = (uint16_t)'B' << 8 | (uint16_t)'D',							///< BD BeiDou(China)
		TID_BN = (uint16_t)'B' << 8 | (uint16_t)'N',							///< BN Bridge navigational watch alarm system
		TID_CC = (uint16_t)'C' << 8 | (uint16_t)'C',							///< CC Computer - Programmed Calculator(obsolete)
		TID_CD = (uint16_t)'C' << 8 | (uint16_t)'D',							///< CD Communications - Digital Selective Calling(DSC)
		TID_CM = (uint16_t)'C' << 8 | (uint16_t)'M',							///< CM Computer - Memory Data(obsolete)
		TID_CS = (uint16_t)'C' << 8 | (uint16_t)'S',							///< CS Communications - Satellite
		TID_CT = (uint16_t)'C' << 8 | (uint16_t)'T',							///< CT Communications - Radio - Telephone(MF / HF)
		TID_CV = (uint16_t)'C' << 8 | (uint16_t)'V',							///< CV Communications - Radio - Telephone(VHF)
		TID_CX = (uint16_t)'C' << 8 | (uint16_t)'X',							///< CX Communications - Scanning Receiver
		TID_DE = (uint16_t)'D' << 8 | (uint16_t)'E',							///< DE DECCA Navigation(obsolete)
		TID_DF = (uint16_t)'D' << 8 | (uint16_t)'F',							///< DF Direction Finder
		TID_DU = (uint16_t)'D' << 8 | (uint16_t)'U',							///< DU Duplex repeater station
		TID_EC = (uint16_t)'E' << 8 | (uint16_t)'C',							///< EC Electronic Chart Display & Information System(ECDIS)
		TID_EP = (uint16_t)'E' << 8 | (uint16_t)'P',							///< EP Emergency Position Indicating Beacon(EPIRB)
		TID_ER = (uint16_t)'E' << 8 | (uint16_t)'R',							///< ER Engine Room Monitoring Systems
		TID_GA = (uint16_t)'G' << 8 | (uint16_t)'A',							///< GA Galileo Positioning System
		TID_GB = (uint16_t)'G' << 8 | (uint16_t)'B',							///< GB BeiDou(China)
		TID_GL = (uint16_t)'G' << 8 | (uint16_t)'L',							///< GL GLONASS, according to IEIC 61162 - 1
		TID_GN = (uint16_t)'G' << 8 | (uint16_t)'N',							///< GN Mixed GPS and GLONASS data, according to IEIC 61162-1
		TID_GP = (uint16_t)'G' << 8 | (uint16_t)'P',							///< GP Global Positioning System(GPS)
		TID_HC = (uint16_t)'H' << 8 | (uint16_t)'C',							///< HC Heading - Magnetic Compass
		TID_HE = (uint16_t)'H' << 8 | (uint16_t)'E',							///< HE Heading - North Seeking Gyro
		TID_HN = (uint16_t)'H' << 8 | (uint16_t)'N',							///< HN Heading - Non North Seeking Gyro
		TID_II = (uint16_t)'I' << 8 | (uint16_t)'I',							///< II Integrated Instrumentation
		TID_IN = (uint16_t)'I' << 8 | (uint16_t)'N',							///< IN Integrated Navigation
		TID_LA = (uint16_t)'L' << 8 | (uint16_t)'A',							///< LA Loran A(obsolete)
		TID_LC = (uint16_t)'L' << 8 | (uint16_t)'C',							///< LC Loran C(obsolete)
		TID_MP = (uint16_t)'M' << 8 | (uint16_t)'P',							///< MP Microwave Positioning System(obsolete)
		TID_NL = (uint16_t)'N' << 8 | (uint16_t)'L',							///< NL Navigation light controller
		TID_OM = (uint16_t)'O' << 8 | (uint16_t)'M',							///< OM OMEGA Navigation System(obsolete)
		TID_OS = (uint16_t)'O' << 8 | (uint16_t)'S',							///< OS Distress Alarm System(obsolete)
		TID_QZ = (uint16_t)'Q' << 8 | (uint16_t)'Z',							///< QZ QZSS regional GPS augmentation system(Japan)
		TID_RA = (uint16_t)'R' << 8 | (uint16_t)'A',							///< RA RADAR and/or ARPA
		TID_SD = (uint16_t)'S' << 8 | (uint16_t)'D',							///< SD Sounder, Depth
		TID_SN = (uint16_t)'S' << 8 | (uint16_t)'N',							///< SN Electronic Positioning System, other / general
		TID_SS = (uint16_t)'S' << 8 | (uint16_t)'S',							///< SS Sounder, Scanning
		TID_TI = (uint16_t)'T' << 8 | (uint16_t)'I',							///< TI Turn Rate Indicator
		TID_TR = (uint16_t)'T' << 8 | (uint16_t)'R',							///< TR TRANSIT Navigation System
		TID_U0 = (uint16_t)'U' << 8 | (uint16_t)'0',							///< U# # is a digit 0 - 9; User Configured
		TID_U1 = (uint16_t)'U' << 8 | (uint16_t)'1',							///< U# # is a digit 0 - 9; User Configured
		TID_U2 = (uint16_t)'U' << 8 | (uint16_t)'2',							///< U# # is a digit 0 - 9; User Configured
		TID_U3 = (uint16_t)'U' << 8 | (uint16_t)'3',							///< U# # is a digit 0 - 9; User Configured
		TID_U4 = (uint16_t)'U' << 8 | (uint16_t)'4',							///< U# # is a digit 0 - 9; User Configured
		TID_U5 = (uint16_t)'U' << 8 | (uint16_t)'5',							///< U# # is a digit 0 - 9; User Configured
		TID_U6 = (uint16_t)'U' << 8 | (uint16_t)'6',							///< U# # is a digit 0 - 9; User Configured
		TID_U7 = (uint16_t)'U' << 8 | (uint16_t)'7',							///< U# # is a digit 0 - 9; User Configured
		TID_U8 = (uint16_t)'U' << 8 | (uint16_t)'8',							///< U# # is a digit 0 - 9; User Configured
		TID_U9 = (uint16_t)'U' << 8 | (uint16_t)'9',							///< U# # is a digit 0 - 9; User Configured
		TID_UP = (uint16_t)'U' << 8 | (uint16_t)'P',							///< UP Microprocessor controller
		TID_VD = (uint16_t)'V' << 8 | (uint16_t)'D',							///< VD Velocity Sensor, Doppler, other / general
		TID_DM = (uint16_t)'D' << 8 | (uint16_t)'M',							///< DM Velocity Sensor, Speed Log, Water, Magnetic
		TID_VW = (uint16_t)'V' << 8 | (uint16_t)'W',							///< VW Velocity Sensor, Speed Log, Water, Mechanical
		TID_WI = (uint16_t)'W' << 8 | (uint16_t)'I',							///< WI Weather Instruments
		TID_YC = (uint16_t)'Y' << 8 | (uint16_t)'C',							///< YC Transducer - Temperature(obsolete)
		TID_YD = (uint16_t)'Y' << 8 | (uint16_t)'D',							///< YD Transducer - Displacement, Angular or Linear(obsolete)
		TID_YF = (uint16_t)'Y' << 8 | (uint16_t)'F',							///< YF Transducer - Frequency(obsolete)
		TID_YL = (uint16_t)'Y' << 8 | (uint16_t)'L',							///< YL Transducer - Level(obsolete)
		TID_YP = (uint16_t)'Y' << 8 | (uint16_t)'P',							///< YP Transducer - Pressure(obsolete)
		TID_YR = (uint16_t)'Y' << 8 | (uint16_t)'R',							///< YR Transducer - Flow Rate(obsolete)
		TID_YT = (uint16_t)'Y' << 8 | (uint16_t)'T',							///< YT Transducer - Tachometer(obsolete)
		TID_YV = (uint16_t)'Y' << 8 | (uint16_t)'V',							///< YV Transducer - Volume(obsolete)
		TID_YX = (uint16_t)'Y' << 8 | (uint16_t)'X',							///< YX Transducer
		TID_ZA = (uint16_t)'Z' << 8 | (uint16_t)'A',							///< ZA Timekeeper - Atomic Clock
		TID_ZC = (uint16_t)'Z' << 8 | (uint16_t)'C',							///< ZC Timekeeper - Chronometer
		TID_ZQ = (uint16_t)'Z' << 8 | (uint16_t)'Q',							///< ZQ Timekeeper - Quartz
		TID_ZV = (uint16_t)'Z' << 8 | (uint16_t)'V',							///< ZV Timekeeper - Radio Update, WWV or WWVH
		TID_AO = (uint16_t)'A' << 8 | (uint16_t)'O',
	};

	///
	/// GPS Quality that's used in the GGA sentence
	///
	enum GPS_QUALITY_E {
		GQ_FIX_NOT_AVAILABLE = 0,												///< fix not available,
		GQ_GPS_SPS_MODE = 1,													///< GPS fix,
		GQ_GPS_DIFFERENTIAL_SPS_MODE = 2,										///< Differential GPS fix(values above 2 are 2.3 features)
		GQ_GPS_PPS_MODE = 3,													///< GPS PPS Mode, fix valid
		GQ_REAL_TIME_KINEMATIC = 4,												///< Real Time Kinematic
		GQ_FLOAT_RTK = 5,														///< Float RTK
		GQ_ESTIMATED_DEAD_RECONING = 6,											///< estimated(dead reckoning)
		GQ_MANUAL_INPUT_MODE = 7,												///< Manual input mode
		GQ_SIMULATOR_MODE = 8,													///< Simulation mode
	};

	enum FIX_STATUS_E
	{
		NO_FIX = 0,
		FIX	= 1,
	};

	enum FIX_TYPE_E
	{
		GNSS_NO_FIX = 0,
		GNSS_FIX = 1,
		SBAC_FIX = 2,
	};

	///
	/// \brief GGA Data
	///
    typedef struct _GGA_DATA_T {
		int				m_nHour;												///< hour
		int				m_nMinute;												///< Minute
		int				m_nSecond;												///< Second
		double			m_dLatitude;											///< Latitude (Decimal degrees, S < 0 > N)
		double			m_dLongitude;											///< Longitude (Decimal degrees, W < 0 > E)
		double			m_dAltitudeMSL;											///< Altitude (Meters)
		GPS_QUALITY_E	m_nGPSQuality;											///< GPS Quality
		int				m_nSatsInView;											///< Number of satellites in view
		double			m_dHDOP;												///< Horizontal Dilution of Precision
		double			m_dGeoidalSep;											///< Geoidal separation, the difference between the WGS-84 earth ellipsoid and mean-sea-level (geoid), "-" means mean-sea-level below ellipsoid (meters)
		double			m_dDifferentialAge;										///< Age of differential GPS data, time in seconds since last SC104 type 1 or 9 update, null field when DGPS is not used 
		int				m_nDifferentialID;										///< Differential reference station ID, 0000-1023
		double			m_dVertSpeed;											///< Derived vertical speed (THIS IS NOT PART OF THE NMEA SPECIFICATION. It is derived during parsing)
	} GGA_DATA_T;

	///
	/// RMC Status field
	///
	enum RMC_STATUS_E {
		RMC_STATUS_ACTIVE = 'A',
		RMC_STATUS_VOID = 'V',
	};

	///
	/// RMC Recommended minimum data for GPS
	///
	typedef struct _RMC_DATA_T {
		time_t			m_timeGGA;												///< Time in GGA sentence
		int				m_nHour;												///< hour
		int				m_nMinute;												///< Minute
		int				m_nSecond;												///< Second
		double			m_dSecond;												///< Fractional second
		double			m_dLatitude;											///< Latitude (Decimal degrees, S < 0 > N)
		double			m_dLongitude;											///< Longitude (Decimal degrees, W < 0 > E)
		double			m_dAltitudeMSL;											///< Altitude (Meters)
		RMC_STATUS_E	m_nStatus;												///< Status
		double			m_dSpeedKnots;											///< Speed over the ground in knots
	    double			m_dTrackAngle;											///< Track angle in degrees True North
	    int				m_nMonth;												///< Month
	    int				m_nDay;													///< Day
	    int				m_nYear;												///< Year
	    double			m_dMagneticVariation;									///< Magnetic Variation

	} RMC_DATA_T;

	typedef struct _VEL_DATA_T 
	{
		double m_dVelocityXAxis;
		double m_dVelocityYAxis;
		double m_dVelocityZAxis;
		double m_dVelocityNorth;
		double m_dVelocityEast;
		double m_dVelocityDown;
	} VEL_DATA_T;
	
	typedef struct _ATT_DATA_T
	{
		double m_dRollAngle;
		double m_dPitchAngle;
		double m_dHeadingAngle;
		double m_dQ0;
		double m_dQ1;
		double m_dQ2;
		double m_dQ3;
		int	m_nInsMode;
	}ATT_DATA_T;

	typedef struct _GPS_DATA_T
	{
		FIX_STATUS_E  m_nFixStatus;
		FIX_TYPE_E  m_nFixType;
		int m_nNoOfSatellites;
		double m_dLatitude;
		double m_dLongitude;
		double m_dAltitude;
		double m_dSpeedOverGround;
		double m_dCourseOverGround;
		double m_dDilutionOfPrecision;
	}GPS_DATA_T;

	typedef struct _STS_DATA_T
	{
		time_t m_timeSeconds;
		int m_nMSEC;
		long m_lInsStatus;
		long m_lHardwareStatus;
	}STS_DATA_T;

	typedef struct _SEN_DATA_T
	{
		double m_dAX;
		double m_dAY;
		double m_dAZ;
		double m_dBRX;
		double m_dBRY;
		double m_dBRZ;
		double m_dERR;
		double m_dERP;
		double m_dERY;
	}SEN_DATA_T;
};

#endif