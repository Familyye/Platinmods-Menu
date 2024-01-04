#include <jni.h>
#include <string>

#define FUNCTION_INFINITE_AMMO 100
#define FUNCTION_RAPID_FIRE 101
#define FUNCTION_NO_SPREAD 102
#define FUNCTION_NO_RECOIL 103
#define FUNCTION_FIELD_OF_VIEW 104
#define FUNCTION_WALLHACK 105
#define FUNCTION_CHAMS 106

#define FUNCTION_LVL_UP 200
#define FUNCTION_CUSTOM_NAME 201
#define FUNCTION_DOUBLE_XP 202

#define FUNCTION_SUPER_SPEED 300
#define FUNCTION_RESPAWN 301
#define FUNCTION_MOVEMENT_ALWAYS_ALLOWED 302
#define FUNCTION_FIRING_ALWAYS_ALLOWED 303

#define FUNCTION_LEVEL_UP 400
#define FUNCTION_LEVEL_DOWN 401
#define FUNCTION_ADD_MONEY 402
#define FUNCTION_ALWAYS_HOLD_BOMB 403
#define FUNCTION_PLANT_ANYWHERE 404
#define FUNCTION_DEFUSE_ANYWHERE 405

#define FUNCTION_RESPAWN_BEFORE_DIE 500
#define FUNCTION_SPAM_CHAT 501
#define FUNCTION_JUMP_EXPLOIT 502
#define FUNCTION_TELEKILL 503
#define FUNCTION_AIMBOT 504
#define FUNCTION_WALKING_NUKE 505

bool INFINITE_AMMO, RAPID_FIRE, NO_SPREAD, NO_RECOIL, FIELD_OF_VIEW, WALLHACK, CHAMS;

void showToast(JNIEnv *env, jobject thiz, const char *name, bool value) {
    char text[50];
    int LENGTH_LONG = 1;
    sprintf(text, "%s: %s", name, value ? "On" : "Off");

    jclass Toast = env->FindClass("android/widget/Toast");
    jmethodID makeText = env->GetStaticMethodID(Toast, "makeText",
                                                "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");

    jobject toast = env->CallStaticObjectMethod(Toast,
                                                makeText,
                                                thiz, env->NewStringUTF(text), LENGTH_LONG);

    env->CallVoidMethod(toast,
                        env->GetMethodID(Toast, "show", "()V"));
}

void toggleButton(JNIEnv *env, jobject thiz, [[maybe_unused]] int id) {
    switch (id) {
        case FUNCTION_INFINITE_AMMO:
            INFINITE_AMMO = !INFINITE_AMMO;
            showToast(env, thiz, "Infinite Ammo", INFINITE_AMMO);
            break;

        case FUNCTION_RAPID_FIRE:
            RAPID_FIRE = !RAPID_FIRE;
            showToast(env, thiz, "Rapid Fire", RAPID_FIRE);
            break;

        case FUNCTION_NO_SPREAD:
            NO_SPREAD = !NO_SPREAD;
            showToast(env, thiz, "No Spread", NO_SPREAD);
            break;

        case FUNCTION_NO_RECOIL:
            NO_RECOIL = !NO_RECOIL;
            showToast(env, thiz, "No Recoil", NO_RECOIL);
            break;

        case FUNCTION_FIELD_OF_VIEW:
            FIELD_OF_VIEW = !FIELD_OF_VIEW;
            showToast(env, thiz, "Field Of View", FIELD_OF_VIEW);
            break;

        case FUNCTION_WALLHACK:
            WALLHACK = !WALLHACK;
            showToast(env, thiz, "Wallhack", WALLHACK);
            break;

        case FUNCTION_CHAMS:
            CHAMS = !CHAMS;
            showToast(env, thiz, "Chams", CHAMS);
            break;
    }

}

/***** FUNCTIONS FROM STANDOFF2 *****/
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
 * and egl hook for chams
 */