#include <apclient.hpp>
#include <apuuid.hpp>

#include <windows.h>
#include <fstream>
#include <shlobj.h> // For SHGetFolderPath


#ifdef __EMSCRIPTEN__
//#define DATAPACKAGE_CACHE "/settings/datapackage.json"
#define UUID_FILE "/settings/uuid"
#else
//#define DATAPACKAGE_CACHE "datapackage.json" // TODO: place in %appdata%
#define UUID_FILE "uuid" // TODO: place in %appdata%
#endif



int main() {
    // FILE* fp;
    // if (freopen_s(&fp, "a.txt", "a", stdout) != 0) {
    //     std::cerr << "Failed to redirect stdout\n";
    //     return 1;
    // }
    std::cout << "ThreadProc started" << std::endl;
    printf("Testing printf\n");
    

    /*////////////////////////////////
    -////  Pre Loop Setup Begin  ////-
    ////////////////////////////////*/


    // AP testing.
    // TODO: This whole section should be broken out into its own cpp file & modularized. This is just an initial test.
    std::cout << "Creating AP Client" << std::endl;
    APClient* ap = nullptr; //in dark souls, this variable is initialized outside of the function.
    /* I think this code below is used for first time connections to reset the datapackage_cache (which I think holds all locations completed & 
    items received that were completed), but if you disconnect from the server due to internet issues, the cache doesn't need to be reset*/
    std::cout << "Successfully Created AP client" << std::endl;
    if(ap != nullptr) //for some reason, this was causing the exe to crash
        ap->reset(); 


    //TODO: will need to be fool-proofed, remove duplicate code, and probably can modularize this, but testing initial connection & proof of concept
    std::cout << "Opening Connection File" << std::endl;
    std::ifstream connectionFile("APConnect.txt");

    if(!connectionFile){
        std::cerr << "Error Opening Connection File" << std::endl;
        return -1;
    }

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

    std::cout << "Succesfully read file" << std::endl;

    std::string URI = serverURL + ":" + serverPort; // {SERVER_IP}:{SERVER_PORT}
    std::string uuid = ap_get_uuid(UUID_FILE, URI); // UUID is a Unique identifier for player client. I believe it is 1 per player, doesn't change between seeds
    ap = new APClient(uuid, "Manual_LegoBatmanTheVideoGame_SnolidIce"/*"Lego Batman: The Videogame"*/, URI);
    ap->set_socket_error_handler([](const std::string& error){
        std::cout << error << std::endl;
    });
    ap->set_room_info_handler([&]() {
		const int item_handling_flags_all = 1;

		ap->ConnectSlot(playerName, password, item_handling_flags_all, {}, {0, 6, 0});
	});
    std::cout << "connected? " << (int)ap->get_state() << std::endl;
        int counter = 0;
    while((int)ap->get_state() != 2){
        Sleep(500);
        counter++;
        if(counter == 60) break;
    }

    ap->set_socket_connected_handler([]() {
        std::cout << "Socket Connected" << std::endl;
		});
	ap->set_socket_disconnected_handler([]() {
        std::cout << "Socket Disconnected" << std::endl;
		});
    std::cout << "connected? " << (int)ap->get_state() << std::endl;
    //ap->set_slot_connected_handler([](const json& data){}); //this is the function where slot data is read and information passed back and forth

    //bool connected = ap->ConnectSlot(playerName, password, 1); //TODO: see network protocol documentation for item handling flags. I believe it will all be 7 once set up
    std::cout << "connected? " << (int)ap->get_state() << std::endl;

    //testing set up of uuid, URI & file read
    std::cout << "UUID is: " << uuid << std::endl;
    std::cout << "URI is: " << URI << std::endl;
    std::cout << "Player name is: " << playerName << std::endl;
    std::cout << "Password is: " << password << std::endl;
    //std::cout << "Did the connection successfully work? " << connected << std::endl;



    /*//////////////////////////////
    -////  Pre Loop Setup End  ////-
    //////////////////////////////*/


    // std::cout << "About to loop." << std::endl;

    //file.close(); // close file before infinite loop.
    // while (true) {

    //     // AP STUFF

    //     // keeps the console open.


    //     Sleep(500);
    // }

    // Never reached but good practice
    //FreeLibraryAndExitThread(hSelf, 0);
    return 0;
}