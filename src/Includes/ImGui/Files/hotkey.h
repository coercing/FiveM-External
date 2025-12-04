#pragma once
#include <Windows.h>
#include <string>

class Hotkey {
public:
    static Hotkey& hot();

    void start();

    int aimKey = 2;
    int silentEnableKey = 0;
    int GodmodeEnableKey = 0;
    int silentKey = 6;
    int rageKey = 2;
    int triggerKey = 5;
    int triggerEnableKey = 0;
    int aimEnableKey = 0;
    int rageEnableKey = 0;
    int visualsEnableKey = 0;
    int vehiclesVisualsEnableKey = 0;
    int tpPlayerKey = 90;
    int friendPlayerKey = 4;
    int fillAmmoKey = 0;
    int fillHealthKey = 0;
    int fillArmorKey = 0;
    int unlockKey = 0;
    int menuSwitchKey = 45;
    int noclipKey = 164;
    int magicEnableKey = 0; // Adiciona magicEnableKey
    int magicKey = 0; // Adiciona magicKey

    int aimbotKey;
    int silentHotKey;
    int silentEnableHotKey;
    int GodmodeEnableHotKey;
    int ragebotKey;
    int triggerBotkey;
    int triggerBotEnablekey;
    int aimbotEnableKey;
    int rageBotEnableKey;
    int visualsEspEnableKey;
    int vehiclesVisualsEspEnableKey;
    int teleportPlayerKey;
    int friendSwitchPlayerKey;
    int fillAmmoHotKey;
    int fillHealthHotKey;
    int fillArmorHotKey;
    int unlockHotKey;
    int menuSwitchHotKey;
    int noclipHotKey;
    int magicHotKey; // Adiciona magicHotKey
    int magicEnableHotKey; // Adiciona magicEnableHotKey
};
