#pragma once

#include <string>
#include <unistd.h>

/*
 * FUCK SUBSTRATE
 * ALL MY HOMIES USE
 * DOBBY HOOK
 */

#include "Dobby/dobby.h"
#include "Includes/Utils.hpp"
#include "Includes/Struct.hpp"

map_t libil2cpp;

#define import(function, offset) *(void **)(&function) = (void *)(libil2cpp.startAddress + offset)
#define hook(offset, fake, orig) DobbyHook((void *) (libil2cpp.startAddress + offset), (void *) fake, (void **) orig)

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