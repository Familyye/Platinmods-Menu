#pragma once

#include <string>
#include <unistd.h>

#include "Substrate/SubstrateHook.h"
#include "Substrate/CydiaSubstrate.h"

class map_t {
public:
    size_t length;
    unsigned long long startAddress;
    unsigned long long endAddress;

    map_t() : startAddress(-1), endAddress(-1), length(-1) {}

    inline bool isValid() const { return (startAddress && endAddress && length); }
};

map_t libil2cpp;

map_t getMap(const char *name) {
    map_t result {};

    FILE *file = fopen("/proc/self/maps", "r");
    if (file) {
        char line[512];

        while (fgets(line, sizeof(line), file)) {
            if (!strstr(line, name))
                continue;

            map_t map {};
            sscanf(line, "%llx-%llx",
                   &map.startAddress, &map.endAddress);

            map.length = map.endAddress - map.startAddress;

            if (map.isValid())
                result = map;
        }

        fclose(file);
    }

    return result;
}

void Hack() {
    do {
        libil2cpp = getMap("libil2cpp.so");

        if (libil2cpp.startAddress < 0) {
            sleep(1);
            continue;
        }

        break;
    } while (true);


}

/*
 * AimController.SetRotation
 * ArmsRaceRpcHelper.ctor
 * ArmsRaceRpcHelper.LevelDown
 * ArmsRaceRpcHelper.LevelUp
 * BombManager.CanDefuse
 * BombManager.CanPlantBomb
 * BombManager.IsBomberMe
 * BombManager.IsInBombSite
 * CameraScopeZoomer.Update
 * Camera.WorldToScreenPoint
 * Camera.get_main
 * ChatManager.SendToAll
 * ChatManager.ctor
 * Component.get_transform
 * CrouchState.OnStateEntered
 * DefuseController.AddMoney
 * DefuseController.ctor
 * GameController.SetPlayerWeapon
 * GameController.SpawnPlayer
 * GameController.ctor
 * GameManager.InitGame
 * GrenadeManager.ThrowGrenade
 * GrenadeManager.Update
 * GunController.IsFiring
 * GunController.accuracyMult
 * GunController.recoilMult
 * GunController.get_MagazineCapacity
 * NetworkingPeer.set_PlayerName
 * PhotonView.get_isMine
 * PhotonView.get_owner
 * PlayerController.GetHealth
 * PlayerController.Update
 * PlayerController.get_AimController
 * PlayerController.get_Player
 * PlayerControls.RequestFiringDisable
 * PlayerControls.RequestMovementDisable
 * PlayerTranslationData.IsVelocitySynchronized
 * PlayerTranslationData.WeaponSpeedMult
 * PlayerTranslationData.get_velocity
 * ProfileManager.AddLevelXp
 * ProfileManager.GetLevelID
 * ProfileManager.GetLevelUpXp
 * ProfileManager.ctor
 * Screen.get_height
 * Screen.get_width
 * String.CreateString
 * Transform.get_position_Injected
 * Transform.set_position_Injected
 * WeaponController.Initialize
 */