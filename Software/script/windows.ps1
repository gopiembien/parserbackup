#cd .\Software
#g++ main.cpp MYNMEAParser.cpp ceSerial.cpp NMEAParserPacket.cpp NMEAParser.cpp NMEASentenceBase.cpp NMEASentenceGGA.cpp 
#NMEASentenceRMC.cpp NMEASentenceVEL.cpp NMEASentenceATT.cpp NMEASentenceGPS.cpp NMEASentenceSTS.cpp NMEASentenceSEN.cpp -o parser.exe -std=c++11

cd ..\
$Folder = '.\build\'
if (Test-Path -Path $Folder) 
{
    Write-Host "Path exists!"
    Remove-Item '.\build\' -Recurse
    mkdir build
} 
else
{
    Write-Host "Path doesn't exist."
    mkdir build
}

cd .\build\
Write-Host "Running cmake"
cmake -S ../ -B . -G "Visual Studio 17 2022"
cmake --build .

cd ../

$Out = '.\Output\'
if (Test-Path -Path $Out) 
{
    Write-Host "Output Path exists!"
    Remove-Item '.\Output\' -Recurse
    mkdir Output
    Copy-Item .\build\source\Debug\GPSParser.exe .\Output\
} 
else
{
    Write-Host "Path doesn't exist."
    mkdir Output
    Copy-Item .\build\source\Debug\GPSParser.exe .\Output\
}

# Copy-Item .\script\compile.txt .\build\







