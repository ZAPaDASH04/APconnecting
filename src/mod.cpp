

#include <apclient.hpp>
#include <apuuid.hpp>

#include <windows.h>
#include <fstream>
#include <shlobj.h> // For SHGetFolderPath


#ifdef __EMSCRIPTEN__
#define DATAPACKAGE_CACHE "/settings/datapackage.json"
#define UUID_FILE "/settings/uuid"
#else
#define DATAPACKAGE_CACHE "datapackage.json" // TODO: place in %appdata%
#define UUID_FILE "uuid" // TODO: place in %appdata%
#endif


void main() {

    // FILE* fp;
    // if (freopen_s(&fp, "a.txt", "a", stdout) != 0) {
    //     std::cerr << "Failed to redirect stdout\n";
    //     return 1;
    // }

    std::cout << "hello world" << std::endl;
    std::cerr << "error world" << std::endl;
    printf("does this work\n");
    std::cout << "ThreadProc started" << std::endl;

    // DWORD BASE_ADDR;// = (DWORD)GetModuleHandle(nullptr);
    
    // while ((BASE_ADDR = (DWORD)GetModuleHandle(nullptr)) == 0) {
    //     Sleep(50);
    // }

    // // Wait for LEGOBatman.exe to load.
    // HMODULE hModule = nullptr;
    // while (hModule == nullptr) {
    //     hModule = GetModuleHandleA("LEGOBatman.exe"); // use your exe's real name here
    //     Sleep(50);
    // }
    

    /*////////////////////////////////
    -////  Pre Loop Setup Begin  ////-
    ////////////////////////////////*/


    // AP testing.
    // TODO: This whole section should be broken out into its own cpp file & modularized. This is just an initial test.

    APClient* ap; //in dark souls, this variable is initialized outside of the function.
    /* I think this code below is used for first time connections to reset the datapackage_cache (which I think holds all locations completed & 
    items received that were completed), but if you disconnect from the server due to internet issues, the cache doesn't need to be reset*/
    if(ap != nullptr) 
        ap->reset(); 


    //TODO: will need to be fool-proofed, remove duplicate code, and probably can modularize this, but testing initial connection & proof of concept
    std::ifstream connectionFile("APConnect.txt");

    std::string serverURL {};
    std::getline(connectionFile, serverURL); //to skip pass the header line
    std::getline(connectionFile, serverURL);
    std::string serverPort {};
    std::getline(connectionFile, serverPort);
    std::string playerName {};
    std::getline(connectionFile, playerName);
    std::string password = ""; //TODO: to test how a password with an archi server works. Initial read through of the documentation appears to have the server tell the player?
    if(!connectionFile.eof())
        std::getline(connectionFile, password);   
    connectionFile.close();

    std::string URI = "ws://" + serverURL + ":" + serverPort; // {SERVER_IP}:{SERVER_PORT}
    std::string uuid = ap_get_uuid(UUID_FILE, URI); // UUID is a Unique identifier for player client. I believe it is 1 per player, doesn't change between seeds
    ap = new APClient(uuid, "Manual_LegoBatmanTheVideoGame_SnolidIce"/*"Lego Batman: The Videogame"*/, URI);
    std::cout << "connected? " << (int)ap->get_state() << std::endl;
        int counter = 0;
    while((int)ap->get_state() != 2){
        Sleep(500);
        counter++;
        if(counter == 100) break;
    }
    ap->set_socket_connected_handler([]() {
		});
	ap->set_socket_disconnected_handler([]() {
		});
    std::cout << "connected? " << (int)ap->get_state() << std::endl;
    //ap->set_slot_connected_handler([](const json& data){}); //this is the function where slot data is read and information passed back and forth

    bool connected = ap->ConnectSlot(playerName, password, 1); //TODO: see network protocol documentation for item handling flags. the library has ways to set them, which will implement later
    std::cout << "connected? " << (int)ap->get_state() << std::endl;

    //testing set up of uuid, URI & file read
    std::cout << "UUID is: " << uuid << std::endl;
    std::cout << "URI is: " << URI << std::endl;
    std::cout << "Player name is: " << playerName << std::endl;
    std::cout << "Password is: " << password << std::endl;
    std::cout << "Did the connection successfully work? " << connected << std::endl;



    /*//////////////////////////////
    -////  Pre Loop Setup End  ////-
    //////////////////////////////*/


    std::cout << "About to loop." << std::endl;
    file.close(); // close file before infinite loop.
    while (true) {

        // AP STUFF




        Sleep(500);
    }

    // Never reached but good practice
    FreeLibraryAndExitThread(hSelf, 0);
    return 0;
}