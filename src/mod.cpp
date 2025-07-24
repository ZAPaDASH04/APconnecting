#include "../inc/APCpp/Archipelago.h"
#include <iostream>

#include <windows.h>
#include <fstream>
#include <shlobj.h> // For SHGetFolderPath

int main() {
    std::cout << "Attempting initial connect" << std::endl;
    AP_Init("archipelago.gg:34565", "Manual_LegoBatmanTheVideoGame_SnolidIce", "Player1","");
    AP_SetItemClearCallback([](){
        std::cout << "Calling ItemClearCallback Function" << std::endl;
    });

    AP_SetItemRecvCallback([&](int64_t itemID,bool notify){
        itemID = 0;
        notify = true;
        std::cout << "Calling SetItemRecvCallback" << std::endl;
    });
    //AP_SetLocationInfoCallback();
    AP_Start();
    while(true){};
    return 0;
}