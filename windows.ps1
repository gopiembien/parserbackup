cd .\Software

g++ main.cpp MYNMEAParser.cpp ceSerial.cpp NMEAParserPacket.cpp NMEAParser.cpp NMEASentenceBase.cpp NMEASentenceGGA.cpp NMEASentenceRMC.cpp NMEASentenceVEL.cpp NMEASentenceATT.cpp NMEASentenceGPS.cpp NMEASentenceSTS.cpp NMEASentenceSEN.cpp -o parser.exe -std=c++11