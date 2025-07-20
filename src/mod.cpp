#include "../inc/APCpp/Archipelago.h"
#include <iostream>

#include <windows.h>
#include <fstream>
#include <shlobj.h> // For SHGetFolderPath

int main() {

    std::cout << "Attempting initial connect" << std::endl;
    AP_Init("archipelago.gg:34565", "Manual_LegoBatmanTheVideoGame_SnolidIce", "Player1","");
    return 0;
}