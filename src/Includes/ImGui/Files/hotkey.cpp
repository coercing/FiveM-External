#include "hotkey.h"
#include <iostream>
#include "keys.hpp"


Hotkey& Hotkey::hot()
{
    static Hotkey ins;
    return ins;
}

int getKey(int keyIndex)
{
    if (keyIndex >= 0 && keyIndex < sizeof(KeyCodes) / sizeof(KeyCodes[0])) {
        return KeyCodes[keyIndex];
    }
    return 0;
}

void Hotkey::start()
{
    aimbotKey = getKey(aimKey);
    ragebotKey = getKey(rageKey);
    triggerBotkey = getKey(triggerKey);
    aimbotEnableKey = getKey(aimEnableKey);
    visualsEspEnableKey = getKey(visualsEnableKey);
    triggerBotEnablekey = getKey(triggerEnableKey);
    rageBotEnableKey = getKey(rageEnableKey);
    teleportPlayerKey = getKey(tpPlayerKey);
    friendSwitchPlayerKey = getKey(friendPlayerKey);
    fillAmmoHotKey = getKey(fillAmmoKey);
    fillHealthHotKey = getKey(fillHealthKey);
    fillArmorHotKey = getKey(fillArmorKey);
    unlockHotKey = getKey(unlockKey);
    vehiclesVisualsEspEnableKey = getKey(vehiclesVisualsEnableKey);
    menuSwitchHotKey = getKey(menuSwitchKey);
    noclipHotKey = getKey(noclipKey);
    silentHotKey = getKey(silentKey);
    silentEnableHotKey = getKey(silentEnableKey);
    GodmodeEnableHotKey = getKey(GodmodeEnableKey);
    magicHotKey = getKey(magicKey); 
    magicEnableHotKey = getKey(magicEnableKey); 

    //if ((GetAsyncKeyState(aimbotEnableKey) & 1) || (GetAsyncKeyState(visualsEspEnableKey) & 1) || (GetAsyncKeyState(triggerBotEnablekey) & 1) || (GetAsyncKeyState(rageBotEnableKey) & 1) || (GetAsyncKeyState(vehiclesVisualsEspEnableKey) & 1) || (GetAsyncKeyState(silentEnableHotKey) & 1) || (GetAsyncKeyState(magicEnableHotKey) & 1)) {
    //    if (aimbotEnableKey != 0 && (GetAsyncKeyState(aimbotEnableKey) != 0) || aimbotEnableKey != 0 && (GetAsyncKeyState(aimbotEnableKey) & 1)) {
    //        aimAssist::aim().enable = !aimAssist::aim().enable;
    //        //rageAim::rage().enable = false;
    //    }
    //    if (visualsEspEnableKey != 0 && (GetAsyncKeyState(visualsEspEnableKey) != 0) || visualsEspEnableKey != 0 && (GetAsyncKeyState(visualsEspEnableKey) & 1)) {
    //        i_esp::esp().enable = !i_esp::esp().enable;
    //    }
    //    if (triggerBotEnablekey != 0 && (GetAsyncKeyState(triggerBotEnablekey) != 0) || triggerBotEnablekey != 0 && (GetAsyncKeyState(triggerBotEnablekey) & 1)) {
    //        triggerBot::trigger().enable = !triggerBot::trigger().enable;
    //    }
    //    if (silentEnableHotKey != 0 && (GetAsyncKeyState(silentEnableHotKey) != 0) || silentEnableHotKey != 0 && (GetAsyncKeyState(silentEnableHotKey) & 1)) {
    //        silentAim::silent().enable = !silentAim::silent().enable;
    //    }
    //    if (rageBotEnableKey != 0 && (GetAsyncKeyState(rageBotEnableKey) != 0) || rageBotEnableKey != 0 && (GetAsyncKeyState(rageBotEnableKey) & 1)) {
    //        //rageAim::rage().enable = !rageAim::rage().enable;
    //        aimAssist::aim().enable = false;
    //    }
    //    if (vehiclesVisualsEspEnableKey != 0 && (GetAsyncKeyState(vehiclesVisualsEspEnableKey) != 0) || vehiclesVisualsEspEnableKey != 0 && (GetAsyncKeyState(vehiclesVisualsEspEnableKey) & 1)) {
    //        i_esp::esp().vehiclesEsp = !i_esp::esp().vehiclesEsp;
    //    }
    //    if (magicEnableHotKey != 0 && (GetAsyncKeyState(magicEnableHotKey) != 0) || magicEnableHotKey != 0 && (GetAsyncKeyState(magicEnableHotKey) & 1)) {
    //        Magicbullet::magic().enable = !Magicbullet::magic().enable;
    //    }
    //}
}
