Link do prezentacji dzialania - https://streamable.com/g1tnza

Google Drive: https://drive.google.com/drive/folders/18fraPfUdwoUg0n0sy9ytlppYf6Xo7oBR?usp=sharing

Github: https://github.com/AvajWiktor/SensorsNetworkSimulator


#ENG
Required C++20
With windows system application can be executed via .exe file which is attached to SensorNetworkSimulatorEXE.zip

Whereas second archive does not contain .exe file and can be compiled in any choosen env. Header files should be placed into "include" directory, and main.cpp is main entry point for application and should be in src dir.
For example on windows platform it can be compiled with developer command prompt by typing:
"cl -std:c++20 main.cpp"
and then run by:
"main.exe"

For linux might be necessary to add -pthread flag for compiler


#PL
Wymagany C++20
Na systemie windows program uruchomic mozna przy pomocy pliku .exe dolaczonego do archiwum SensorNetworkSimulatorEXE.zip

Natomiast druga paczka, nie zawiera pliku .exe i mozliwe jest jej skompilowanie w dowolnie wybranym srodowisku, wszystkie pliki mozna umiescic w jednym folderze i np. przy pomocy Developer Command Prompt for VS20XX wykonanie polecenie
"cl -std:c++20 main.cpp"
a nastepnie:
"main.exe"

Dla linuxa przy kompilacji moze byc wymagana flaga -pthread 
