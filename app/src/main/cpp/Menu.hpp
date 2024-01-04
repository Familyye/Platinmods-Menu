#include <jni.h>
#include <string>

#define CATEGORY_NONE 1
#define CATEGORY_PLAYER 2
#define CATEGORY_PROFILE 3
#define CATEGORY_WEAPONS 4
#define CATEGORY_GAMEPLAY 5
#define CATEGORY_GAMEMODES 6
#define CATEGORY_EXTRAS 7
#define CATEGORY_CUSTOMIZATION 8

#define CATEGORY_TITLE_TEXT 1000
#define CATEGORY_MOD_TEXT 2000
#define CATEGORY_MOD_HIGHLIGHT 3000
#define CATEGORY_MENU_BACKGROUND 4000

#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_BLUE 2
#define COLOR_YELLOW 3
#define COLOR_ORANGE 4
#define COLOR_PINK 5
#define COLOR_PURPLE 6
#define COLOR_BLACK 7

int processID;

static jobject menu;
static jobject functionList;

static jobject title;
static jobject toggle1;
static jobject toggle2;
static jobject toggle3;
static jobject toggle4;
static jobject toggle5;
static jobject toggle6;
static jobject toggle7;
static jobject toggle8;
static jobject toggle9;
static jobject toggle10;

int COLOR_TITLE_TEXT;
int COLOR_MOD_TEXT;
int COLOR_MOD_HIGHLIGHT;
int COLOR_MENU_BG;

int getColor(int id, bool isDefault) {
    if (isDefault) {
        switch (id) {
            case 0:
                return -65536;

            case 1:
                return -16711936;

            case 2:
                return -16776961;

            case 3:
                return -256;

            case 4:
                return -35072;

            case 5:
                return -16181;

            case 6:
                return -65281;

            case 7:
                return -16777216;
        }
    } else {
        switch (id) {
            case 0:
                return -1725628416;

            case 1:
                return -1728043776;

            case 2:
                return -1728053211;

            case 3:
                return -1725618944;

            case 4:
                return -1725623808;

            case 5:
                return -1725622247;

            case 6:
                return -1725628379;

            case 7:
                return -1728053248;
        }
    }

    return 0;
}

jobject getWMParams(JNIEnv *env, jint width, jint height) {
    int VERSION_O = 26;
    int TRANSLUCENT = -3;
    int TYPE_PHONE = 2002;
    int FLAG_NOT_FOCUSABLE = 8;
    int TYPE_APPLICATION_OVERLAY = 2038;

    jclass Build$VERSION = env->FindClass("android/os/Build$VERSION");
    jint SDK_INT = env->GetStaticIntField(
            Build$VERSION,
            env->GetStaticFieldID(Build$VERSION, "SDK_INT", "I"));

    jclass WindowManager$LayoutParams = env->FindClass("android/view/WindowManager$LayoutParams");
    return env->NewObject(WindowManager$LayoutParams,
                          env->GetMethodID(WindowManager$LayoutParams,"<init>", "(IIIII)V"),
                          width, height, SDK_INT >= VERSION_O ? TYPE_APPLICATION_OVERLAY : TYPE_PHONE, FLAG_NOT_FOCUSABLE, TRANSLUCENT);
}

void initIcon(JNIEnv *env, jobject thiz) {
    int TOP = 48;
    int LEFT = 3;
    int WRAP_CONTENT = -2;

    jclass Reborn = env->GetObjectClass(thiz);
    jobject iconOverlayParams = getWMParams(env, 320, 320);

    env->SetIntField(iconOverlayParams, env->GetFieldID(
            env->FindClass("android/view/WindowManager$LayoutParams"),
            "gravity",
            "I"), TOP | LEFT);

    env->SetObjectField(thiz,env->GetFieldID(
            Reborn,
            "iconOverlayParam",
            "Landroid/view/WindowManager$LayoutParams;"), iconOverlayParams);

    jclass RelativeLayout$LayoutParams = env->FindClass("android/widget/RelativeLayout$LayoutParams");
    jobject relativeLayoutParams = env->NewObject(RelativeLayout$LayoutParams, env->GetMethodID(
            RelativeLayout$LayoutParams,
            "<init>",
            "(II)V"), WRAP_CONTENT, WRAP_CONTENT);

    jclass RelativeLayout = env->FindClass("android/widget/RelativeLayout");
    jobject icon = env->NewObject(
            RelativeLayout,
            env->GetMethodID(RelativeLayout, "<init>", "(Landroid/content/Context;)V"),
            thiz);

    env->CallVoidMethod(
            icon,
            env->GetMethodID(RelativeLayout, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V"),
            relativeLayoutParams);

    jclass LinearLayout$LayoutParams = env->FindClass("android/widget/LinearLayout$LayoutParams");
    jobject pmtIconParams = env->NewObject(
            LinearLayout$LayoutParams,
            env->GetMethodID(LinearLayout$LayoutParams, "<init>", "(II)V"),
            274, 180);

    jclass ImageView = env->FindClass("android/widget/ImageView");
    jobject pmtIcon = env->NewObject(
            ImageView,
            env->GetMethodID(ImageView, "<init>", "(Landroid/content/Context;)V"),
            thiz);

    env->CallVoidMethod(
            pmtIcon,
            env->GetMethodID(ImageView, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V"),
            pmtIconParams);

    env->CallVoidMethod(icon,
                        env->GetMethodID(RelativeLayout, "addView", "(Landroid/view/View;)V"),
                        pmtIcon);

    env->SetObjectField(thiz, env->GetFieldID(
            Reborn,
            "pmtIcon",
            "Landroid/widget/ImageView;"), pmtIcon);

    env->SetObjectField(thiz, env->GetFieldID(
            Reborn,
            "icon",
            "Landroid/widget/RelativeLayout;"), icon);

    jobject windowManager = env->GetObjectField(thiz, env->GetFieldID(
            Reborn,
            "windowManager",
            "Landroid/view/WindowManager;"));

    jclass WindowManager = env->FindClass("android/view/WindowManager");
    env->CallVoidMethod(
            windowManager,
            env->GetMethodID(WindowManager, "addView", "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V"),
            icon, iconOverlayParams);
}

void initMenu(JNIEnv *env, jobject thiz) {
    int GONE = 8;
    int VERTICAL = 1;
    int MATCH_PARENT = -1;
    int WRAP_CONTENT = -2;

    jclass Reborn = env->GetObjectClass(thiz);
    jint width = env->GetIntField(thiz, env->GetFieldID(Reborn, "width", "I"));
    jint height = env->GetIntField(thiz, env->GetFieldID(Reborn, "height", "I"));

    jclass LinearLayout$LayoutParams = env->FindClass("android/widget/LinearLayout$LayoutParams");
    jobject mainParams = env->NewObject(LinearLayout$LayoutParams,
                                        env->GetMethodID(LinearLayout$LayoutParams, "<init>", "(II)V"),
                                        MATCH_PARENT, MATCH_PARENT);

    jclass LinearLayout = env->FindClass("android/widget/LinearLayout");

    functionList = env->NewGlobalRef(
            env->NewObject(LinearLayout,
                           env->GetMethodID(LinearLayout, "<init>", "(Landroid/content/Context;)V"),
                           thiz));

    env->CallVoidMethod(functionList,
                        env->GetMethodID(LinearLayout, "setOrientation", "(I)V"),
                        VERTICAL);

    env->CallVoidMethod(functionList,
                        env->GetMethodID(LinearLayout, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V"),
                        mainParams);

    jobject scrollParams = env->NewObject(LinearLayout$LayoutParams,
                                          env->GetMethodID(LinearLayout$LayoutParams, "<init>", "(II)V"),
                                          MATCH_PARENT, 514);

    jclass ScrollView = env->FindClass("android/widget/ScrollView");
    jobject scrollView = env->NewObject(ScrollView,
                                        env->GetMethodID(ScrollView, "<init>", "(Landroid/content/Context;)V"),
                                        thiz);

    env->CallVoidMethod(scrollView,
                        env->GetMethodID(ScrollView, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V"),
                        scrollParams);

    env->CallVoidMethod(scrollView,
                        env->GetMethodID(ScrollView, "addView", "(Landroid/view/View;)V"),
                        functionList);

    jclass RelativeLayout$LayoutParams = env->FindClass("android/widget/RelativeLayout$LayoutParams");
    jobject scrollBaseParams = env->NewObject(RelativeLayout$LayoutParams,
                                              env->GetMethodID(RelativeLayout$LayoutParams, "<init>", "(II)V"),
                                              WRAP_CONTENT, MATCH_PARENT);

    env->CallVoidMethod(scrollBaseParams,
                        env->GetMethodID(RelativeLayout$LayoutParams, "setMargins", "(IIII)V"),
                        0, 180, 0, 0);

    jclass RelativeLayout = env->FindClass("android/widget/RelativeLayout");
    jobject scrollBase = env->NewObject(RelativeLayout,
                                        env->GetMethodID(RelativeLayout, "<init>", "(Landroid/content/Context;)V"),
                                        thiz);

    env->CallVoidMethod(scrollBase,
                        env->GetMethodID(RelativeLayout, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V"),
                        scrollBaseParams);

    env->CallVoidMethod(scrollBase,
                        env->GetMethodID(RelativeLayout, "addView", "(Landroid/view/View;)V"),
                        scrollView);

    jobject menuParams = env->NewObject(RelativeLayout$LayoutParams,
                                        env->GetMethodID(RelativeLayout$LayoutParams, "<init>", "(II)V"),
                                        width, WRAP_CONTENT);

    menu = env->NewGlobalRef(
            env->NewObject(RelativeLayout,
                           env->GetMethodID(RelativeLayout, "<init>", "(Landroid/content/Context;)V"),
                           thiz));

    env->CallVoidMethod(menu,
                        env->GetMethodID(RelativeLayout, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V"),
                        menuParams);

    env->CallVoidMethod(menu,
                        env->GetMethodID(RelativeLayout, "setVisibility", "(I)V"),
                        GONE);

    env->CallVoidMethod(menu,
                        env->GetMethodID(RelativeLayout, "setBackgroundColor", "(I)V"),
                        COLOR_MENU_BG);

    env->CallVoidMethod(menu,
                        env->GetMethodID(RelativeLayout, "addView", "(Landroid/view/View;)V"),
                        scrollBase);

    env->SetObjectField(thiz,
                        env->GetFieldID(Reborn, "menu", "Landroid/widget/RelativeLayout;"),
                        menu);

    jobject menuParam = getWMParams(env, 640, height);

    env->SetObjectField(thiz,env->GetFieldID(
            Reborn,
            "menuParam",
            "Landroid/view/WindowManager$LayoutParams;"), menuParam);

    jobject windowManager = env->GetObjectField(thiz, env->GetFieldID(
            Reborn,
            "windowManager",
            "Landroid/view/WindowManager;"));

    jclass WindowManager = env->FindClass("android/view/WindowManager");
    env->CallVoidMethod(
            windowManager,
            env->GetMethodID(WindowManager, "addView", "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V"),
            menu, menuParam);
}

void setText(JNIEnv *env, jobject textView, const char *text) {
    if (!text)
        return;

    jclass TextView = env->FindClass("android/widget/TextView");
    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setText", "(Ljava/lang/CharSequence;)V"),
                        env->NewStringUTF(text));
}

void setVisibility(JNIEnv *env, jobject textView, bool visible) {
    int GONE = 8;
    int VISIBLE = 0;

    jclass TextView = env->FindClass("android/widget/TextView");
    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setVisibility", "(I)V"),
                        visible ? VISIBLE : GONE);
}

void setOnClick(JNIEnv *env, jobject thiz, jobject textView, int id) {
    jmethodID setOnClickListener = env->GetMethodID(env->GetObjectClass(thiz),
                                                    "setOnClickListener","(ZILandroid/widget/TextView;)V");

    env->CallVoidMethod(thiz, setOnClickListener, id == 0, id, textView);
}

void resetButtons(JNIEnv *env, jobject thiz, jint id) {
    auto showAll = [&]() -> void {
        setVisibility(env, toggle1, true);
        setVisibility(env, toggle2, true);
        setVisibility(env, toggle3, true);
        setVisibility(env, toggle4, true);
        setVisibility(env, toggle5, true);
        setVisibility(env, toggle6, true);
        setVisibility(env, toggle7, true);
        setVisibility(env, toggle8, true);
        setVisibility(env, toggle9, true);
        setVisibility(env, toggle10, true);
    };

    switch (id) {
        case CATEGORY_NONE:
            showAll();

            setText(env, title, "Platinmods<3\nMain Menu");
            setText(env, toggle1, "Player Menu");
            setText(env, toggle2, "Profile Menu");
            setText(env, toggle3, "Weapons Menu");
            setText(env, toggle4, "Gameplay Menu");
            setText(env, toggle5, "Gamemodes Menu");
            setText(env, toggle6, "Extras Menu");
            setText(env, toggle7, "Customization Menu");

            setVisibility(env, toggle8, false);
            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, CATEGORY_PLAYER);
            setOnClick(env, thiz, toggle2, CATEGORY_PROFILE);
            setOnClick(env, thiz, toggle3, CATEGORY_WEAPONS);
            setOnClick(env, thiz, toggle4, CATEGORY_GAMEPLAY);
            setOnClick(env, thiz, toggle5, CATEGORY_GAMEMODES);
            setOnClick(env, thiz, toggle6, CATEGORY_EXTRAS);
            setOnClick(env, thiz, toggle7, CATEGORY_CUSTOMIZATION);
            break;

        case CATEGORY_PLAYER:
            showAll();

            setText(env, title, "Platinmods<3\nPlayer Menu");
            setText(env, toggle1, "Infinite Ammo");
            setText(env, toggle2, "Rapid Fire");
            setText(env, toggle3, "No Spread");
            setText(env, toggle4, "No Recoil");
            setText(env, toggle5, "Field of View");
            setText(env, toggle6, "Wallhack");
            setText(env, toggle7, "Chams");
            setText(env, toggle8, "Back...");

            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, FUNCTION_INFINITE_AMMO);
            setOnClick(env, thiz, toggle2, FUNCTION_RAPID_FIRE);
            setOnClick(env, thiz, toggle3, FUNCTION_NO_SPREAD);
            setOnClick(env, thiz, toggle4, FUNCTION_NO_RECOIL);
            setOnClick(env, thiz, toggle5, FUNCTION_FIELD_OF_VIEW);
            setOnClick(env, thiz, toggle6, FUNCTION_WALLHACK);
            setOnClick(env, thiz, toggle7, FUNCTION_CHAMS);
            setOnClick(env, thiz, toggle8, CATEGORY_NONE);
            break;

        case CATEGORY_PROFILE:
            showAll();

            setText(env, title, "Platinmods<3\nProfile Menu");
            setText(env, toggle1, "Level Up");
            setText(env, toggle2, "Custom Name");
            setText(env, toggle3, "Double Xp");
            setText(env, toggle4, "Back...");

            setVisibility(env, toggle5, false);
            setVisibility(env, toggle6, false);
            setVisibility(env, toggle7, false);
            setVisibility(env, toggle8, false);
            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, FUNCTION_LVL_UP);
            setOnClick(env, thiz, toggle2, FUNCTION_CUSTOM_NAME);
            setOnClick(env, thiz, toggle3, FUNCTION_DOUBLE_XP);
            setOnClick(env, thiz, toggle4, CATEGORY_NONE);
            break;

        case CATEGORY_WEAPONS:
            showAll();

            setText(env, title, "Platinmods<3\nWeapons Menu");
            setText(env, toggle1, "No no no MR. Fish");
            setText(env, toggle2, "Back...");

            setVisibility(env, toggle3, false);
            setVisibility(env, toggle4, false);
            setVisibility(env, toggle5, false);
            setVisibility(env, toggle6, false);
            setVisibility(env, toggle7, false);
            setVisibility(env, toggle8, false);
            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, -1);
            setOnClick(env, thiz, toggle2, CATEGORY_NONE);
            break;

        case CATEGORY_GAMEPLAY:
            showAll();

            setText(env, title, "Platinmods<3\nGameplay Menu");
            setText(env, toggle1, "Super Speed");
            setText(env, toggle2, "Respawn");
            setText(env, toggle3, "Movement Always Allowed");
            setText(env, toggle4, "Firing Always Allowed");
            setText(env, toggle5, "Back...");

            setVisibility(env, toggle6, false);
            setVisibility(env, toggle7, false);
            setVisibility(env, toggle8, false);
            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, FUNCTION_SUPER_SPEED);
            setOnClick(env, thiz, toggle2, FUNCTION_RESPAWN);
            setOnClick(env, thiz, toggle3, FUNCTION_MOVEMENT_ALWAYS_ALLOWED);
            setOnClick(env, thiz, toggle4, FUNCTION_FIRING_ALWAYS_ALLOWED);
            setOnClick(env, thiz, toggle5, CATEGORY_NONE);
            break;

        case CATEGORY_GAMEMODES:
            showAll();

            setText(env, title, "Platinmods<3\nGamemodes Menu");
            setText(env, toggle1, "Level Up");
            setText(env, toggle2, "Level Down");
            setText(env, toggle3, "Add Money");
            setText(env, toggle4, "Always Hold Bomb");
            setText(env, toggle5, "Plant Anywhere");
            setText(env, toggle6, "Defuse Anywhere");
            setText(env, toggle7, "Back...");

            setVisibility(env, toggle8, false);
            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, FUNCTION_LEVEL_UP);
            setOnClick(env, thiz, toggle2, FUNCTION_LEVEL_DOWN);
            setOnClick(env, thiz, toggle3, FUNCTION_ADD_MONEY);
            setOnClick(env, thiz, toggle4, FUNCTION_ALWAYS_HOLD_BOMB);
            setOnClick(env, thiz, toggle5, FUNCTION_PLANT_ANYWHERE);
            setOnClick(env, thiz, toggle6, FUNCTION_DEFUSE_ANYWHERE);
            setOnClick(env, thiz, toggle7, CATEGORY_NONE);
            break;

        case CATEGORY_EXTRAS:
            showAll();

            setText(env, title, "Platinmods<3\nExtras Menu");
            setText(env, toggle1, "Respawn Before Die");
            setText(env, toggle2, "Spam Chat");
            setText(env, toggle3, "Jump Exploit");
            setText(env, toggle4, "Position Menu");
            setText(env, toggle5, "Telekill");
            setText(env, toggle6, "Aimbot");
            setText(env, toggle7, "Walking Nuke");
            setText(env, toggle8, "Back...");

            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, FUNCTION_RESPAWN_BEFORE_DIE);
            setOnClick(env, thiz, toggle2, FUNCTION_SPAM_CHAT);
            setOnClick(env, thiz, toggle3, FUNCTION_JUMP_EXPLOIT);
            setOnClick(env, thiz, toggle4, -1);
            setOnClick(env, thiz, toggle5, FUNCTION_TELEKILL);
            setOnClick(env, thiz, toggle6, FUNCTION_AIMBOT);
            setOnClick(env, thiz, toggle7, FUNCTION_WALKING_NUKE);
            setOnClick(env, thiz, toggle8, CATEGORY_NONE);
            break;

        case CATEGORY_CUSTOMIZATION:
            showAll();

            setText(env, title, "Platinmods<3\nCustomization Menu");
            setText(env, toggle1, "Title Text Color");
            setText(env, toggle2, "Mod Text Color");
            setText(env, toggle3, "Mod Highlight Color");
            setText(env, toggle4, "Menu Background Color");
            setText(env, toggle5, "Back...");

            setVisibility(env, toggle6, false);
            setVisibility(env, toggle7, false);
            setVisibility(env, toggle8, false);
            setVisibility(env, toggle9, false);
            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, CATEGORY_TITLE_TEXT);
            setOnClick(env, thiz, toggle2, CATEGORY_MOD_TEXT);
            setOnClick(env, thiz, toggle3, CATEGORY_MOD_HIGHLIGHT);
            setOnClick(env, thiz, toggle4, CATEGORY_MENU_BACKGROUND);
            setOnClick(env, thiz, toggle5, CATEGORY_NONE);
            break;

        case CATEGORY_TITLE_TEXT:
            showAll();

            setText(env, title, "Platinmods<3\nTitle Text");
            setText(env, toggle1, "Red Title");
            setText(env, toggle2, "Green Title");
            setText(env, toggle3, "Blue Title");
            setText(env, toggle4, "Yellow Title");
            setText(env, toggle5, "Orange Title");
            setText(env, toggle6, "Pink Title");
            setText(env, toggle7, "Purple Title");
            setText(env, toggle8, "Black Title");
            setText(env, toggle9, "Back...");

            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, CATEGORY_TITLE_TEXT + COLOR_RED);
            setOnClick(env, thiz, toggle2, CATEGORY_TITLE_TEXT + COLOR_GREEN);
            setOnClick(env, thiz, toggle3, CATEGORY_TITLE_TEXT + COLOR_BLUE);
            setOnClick(env, thiz, toggle4, CATEGORY_TITLE_TEXT + COLOR_YELLOW);
            setOnClick(env, thiz, toggle5, CATEGORY_TITLE_TEXT + COLOR_ORANGE);
            setOnClick(env, thiz, toggle6, CATEGORY_TITLE_TEXT + COLOR_PINK);
            setOnClick(env, thiz, toggle7, CATEGORY_TITLE_TEXT + COLOR_PURPLE);
            setOnClick(env, thiz, toggle8, CATEGORY_TITLE_TEXT + COLOR_BLACK);
            setOnClick(env, thiz, toggle9, CATEGORY_CUSTOMIZATION);
            break;

        case CATEGORY_MOD_TEXT:
            showAll();

            setText(env, title, "Platinmods<3\nMod Text");
            setText(env, toggle1, "Red Text");
            setText(env, toggle2, "Green Text");
            setText(env, toggle3, "Blue Text");
            setText(env, toggle4, "Yellow Text");
            setText(env, toggle5, "Orange Text");
            setText(env, toggle6, "Pink Text");
            setText(env, toggle7, "Purple Text");
            setText(env, toggle8, "Black Text");
            setText(env, toggle9, "Back...");

            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, CATEGORY_MOD_TEXT + COLOR_RED);
            setOnClick(env, thiz, toggle2, CATEGORY_MOD_TEXT + COLOR_GREEN);
            setOnClick(env, thiz, toggle3, CATEGORY_MOD_TEXT + COLOR_BLUE);
            setOnClick(env, thiz, toggle4, CATEGORY_MOD_TEXT + COLOR_YELLOW);
            setOnClick(env, thiz, toggle5, CATEGORY_MOD_TEXT + COLOR_ORANGE);
            setOnClick(env, thiz, toggle6, CATEGORY_MOD_TEXT + COLOR_PINK);
            setOnClick(env, thiz, toggle7, CATEGORY_MOD_TEXT + COLOR_PURPLE);
            setOnClick(env, thiz, toggle8, CATEGORY_MOD_TEXT + COLOR_BLACK);
            setOnClick(env, thiz, toggle9, CATEGORY_CUSTOMIZATION);
            break;

        case CATEGORY_MOD_HIGHLIGHT:
            showAll();

            setText(env, title, "Platinmods<3\nMod Highlight");
            setText(env, toggle1, "Red Highlight");
            setText(env, toggle2, "Green Highlight");
            setText(env, toggle3, "Blue Highlight");
            setText(env, toggle4, "Yellow Highlight");
            setText(env, toggle5, "Orange Highlight");
            setText(env, toggle6, "Pink Highlight");
            setText(env, toggle7, "Purple Highlight");
            setText(env, toggle8, "Black Highlight");
            setText(env, toggle9, "Back...");

            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, CATEGORY_MOD_HIGHLIGHT + COLOR_RED);
            setOnClick(env, thiz, toggle2, CATEGORY_MOD_HIGHLIGHT + COLOR_GREEN);
            setOnClick(env, thiz, toggle3, CATEGORY_MOD_HIGHLIGHT + COLOR_BLUE);
            setOnClick(env, thiz, toggle4, CATEGORY_MOD_HIGHLIGHT + COLOR_YELLOW);
            setOnClick(env, thiz, toggle5, CATEGORY_MOD_HIGHLIGHT + COLOR_ORANGE);
            setOnClick(env, thiz, toggle6, CATEGORY_MOD_HIGHLIGHT + COLOR_PINK);
            setOnClick(env, thiz, toggle7, CATEGORY_MOD_HIGHLIGHT + COLOR_PURPLE);
            setOnClick(env, thiz, toggle8, CATEGORY_MOD_HIGHLIGHT + COLOR_BLACK);
            setOnClick(env, thiz, toggle9, CATEGORY_CUSTOMIZATION);
            break;

        case CATEGORY_MENU_BACKGROUND:
            showAll();

            setText(env, title, "Platinmods<3\nBackground");
            setText(env, toggle1, "Red BG");
            setText(env, toggle2, "Green BG");
            setText(env, toggle3, "Blue BG");
            setText(env, toggle4, "Yellow BG");
            setText(env, toggle5, "Orange BG");
            setText(env, toggle6, "Pink BG");
            setText(env, toggle7, "Purple BG");
            setText(env, toggle8, "Black BG");
            setText(env, toggle9, "Back...");

            setVisibility(env, toggle10, false);

            setOnClick(env, thiz, toggle1, CATEGORY_MENU_BACKGROUND + COLOR_RED);
            setOnClick(env, thiz, toggle2, CATEGORY_MENU_BACKGROUND + COLOR_GREEN);
            setOnClick(env, thiz, toggle3, CATEGORY_MENU_BACKGROUND + COLOR_BLUE);
            setOnClick(env, thiz, toggle4, CATEGORY_MENU_BACKGROUND + COLOR_YELLOW);
            setOnClick(env, thiz, toggle5, CATEGORY_MENU_BACKGROUND + COLOR_ORANGE);
            setOnClick(env, thiz, toggle6, CATEGORY_MENU_BACKGROUND + COLOR_PINK);
            setOnClick(env, thiz, toggle7, CATEGORY_MENU_BACKGROUND + COLOR_PURPLE);
            setOnClick(env, thiz, toggle8, CATEGORY_MENU_BACKGROUND + COLOR_BLACK);
            setOnClick(env, thiz, toggle9, CATEGORY_CUSTOMIZATION);
            break;

        default:
            break;
    }
}

void updateColors(JNIEnv *env, int id) {
    if (id >= CATEGORY_MENU_BACKGROUND) {
        COLOR_MENU_BG = getColor(id - CATEGORY_MENU_BACKGROUND, false);
    } else if (id >= CATEGORY_MOD_HIGHLIGHT) {
        COLOR_MOD_HIGHLIGHT = getColor(id - CATEGORY_MOD_HIGHLIGHT, true);
    } else if (id >= CATEGORY_MOD_TEXT) {
        COLOR_MOD_TEXT = getColor(id - CATEGORY_MOD_TEXT, true);
    } else {
        COLOR_TITLE_TEXT = getColor(id - CATEGORY_TITLE_TEXT, true);
    }

    jclass RelativeLayout = env->FindClass("android/widget/RelativeLayout");
    env->CallVoidMethod(menu,
                        env->GetMethodID(RelativeLayout, "setBackgroundColor", "(I)V"),
                        COLOR_MENU_BG);

    jclass TextView = env->FindClass("android/widget/TextView");
    auto setShadowLayer = [&](jobject textView, int color) {
        env->CallVoidMethod(textView,
                            env->GetMethodID(TextView, "setShadowLayer", "(FFFI)V"),
                            (jfloat) 12, (jfloat) 0, (jfloat) 0, color);
    };

    setShadowLayer(title, COLOR_TITLE_TEXT);
    setShadowLayer(toggle1, COLOR_MOD_TEXT);
    setShadowLayer(toggle2, COLOR_MOD_TEXT);
    setShadowLayer(toggle3, COLOR_MOD_TEXT);
    setShadowLayer(toggle4, COLOR_MOD_TEXT);
    setShadowLayer(toggle5, COLOR_MOD_TEXT);
    setShadowLayer(toggle6, COLOR_MOD_TEXT);
    setShadowLayer(toggle7, COLOR_MOD_TEXT);
    setShadowLayer(toggle8, COLOR_MOD_TEXT);
    setShadowLayer(toggle9, COLOR_MOD_TEXT);
    setShadowLayer(toggle10, COLOR_MOD_TEXT);
}

/////   ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
/////   ⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡀⢉⣉⠉⠉⠋⠐⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠰⠒⠒⠂⠀⠄⠀⠀⠀⠀⠀⠀⠀
/////   ⠀⠀⠀⠀⠀⣠⣾⣿⣿⡿⠿⠿⣶⣶⣥⣴⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢊⡀⢤⣤⣤⣶⣶⣶⣖⠃⠀⠀⠀⠀⠀
/////   ⠀⠀⠠⢴⣾⣿⡿⠋⠀⠀⠀⣴⣾⣿⣿⣿⣗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣥⣾⣿⣟⠉⠉⠙⠻⣿⣿⣦⣀⠀⠀⠀
/////   ⠀⠀⣠⣾⣿⠋⠀⠀⠀⠀⠠⣿⣜⢶⡗⣹⡯⠣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣟⢭⣛⢹⣧⠀⠀⠀⠀⠻⣿⣧⡀⠀⠀
/////   ⠲⠿⠿⠿⣿⡀⠀⠀⠀⠀⠀⠻⠿⣷⡼⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣯⣫⣼⡏⠀⠀⠀⠀⠀⣹⣿⠿⠷⠦
/////   ⠀⠀⠀⠀⠈⠉⠒⠀⠀⡀⢀⣠⠶⠖⠒⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠭⢭⢥⣄⠀⠀⠀⠀⠊⠁⠀⠀⠀⠀
/////    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

/////   pasted shit code xd

void submitPID(JNIEnv *env, jobject thiz, jint process_id) {
    processID = process_id;
}

void Initialize(JNIEnv *env, jclass clazz, jobject context) {
    COLOR_TITLE_TEXT = getColor(COLOR_RED, true);
    COLOR_MOD_TEXT = getColor(COLOR_RED, true);
    COLOR_MOD_HIGHLIGHT = getColor(COLOR_RED, true);
    COLOR_MENU_BG = getColor(COLOR_RED, false);

    // Settings.Secure.getString(context.getContentResolver(), "ANDROID_ID");
    // get android id, make request and check output (valid = "Authentication Succeeded!")
}

void createWindowParams(JNIEnv *env, jobject thiz) {
    initIcon(env, thiz);
    initMenu(env, thiz);
}

jobject createToggle(JNIEnv *env, jobject thiz, const char *text, int id) {
    int MATCH_PARENT = -1;
    int WRAP_CONTENT = -2;
    int CENTER_HORIZONTAL = 1;
    int TEXT_ALIGNMENT_CENTER = 4;

    bool isTitle = id == 0;

    jclass RelativeLayout$LayoutParams = env->FindClass("android/widget/RelativeLayout$LayoutParams");
    jobject params = env->NewObject(RelativeLayout$LayoutParams,
                                    env->GetMethodID(RelativeLayout$LayoutParams, "<init>", "(II)V"),
                                    MATCH_PARENT, WRAP_CONTENT);

    jclass TextView = env->FindClass("android/widget/TextView");
    jobject textView = env->NewObject(TextView,
                                      env->GetMethodID(TextView, "<init>", "(Landroid/content/Context;)V"),
                                      thiz);

    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V"),
                        params);

    setText(env, textView, text);

    env->CallVoidMethod(textView, env->GetMethodID(
            TextView,
            "setGravity",
            "(I)V"), CENTER_HORIZONTAL);

    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setTextAlignment", "(I)V"),
                        TEXT_ALIGNMENT_CENTER);

    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setShadowLayer", "(FFFI)V"),
                        (jfloat) 12, (jfloat) 0, (jfloat) 0, isTitle ? COLOR_TITLE_TEXT : COLOR_MOD_TEXT);

    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setTextColor", "(I)V"),
                        -1);

    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setTextSize", "(IF)V"),
                        2, isTitle ? (jfloat) 23 : (jfloat) 19);

    jclass LinearLayout = env->FindClass("android/widget/LinearLayout");

    env->CallVoidMethod(isTitle ? menu : functionList,
                        env->GetMethodID(LinearLayout, "addView", "(Landroid/view/View;)V"),
                        textView);

    setVisibility(env, textView, text != NULL);

    if (isTitle) {
        env->SetObjectField(thiz,
                            env->GetFieldID(env->GetObjectClass(thiz), "menuTitle", "Landroid/widget/TextView;"),
                            textView);
    }

    setOnClick(env, thiz, textView, id);

    return textView;
}

void createViews(JNIEnv *env, jobject thiz) {
    title = env->NewGlobalRef(createToggle(env, thiz, "Platinmods<3\nMain Menu", 0));

    toggle1 = env->NewGlobalRef(createToggle(env, thiz, "Player Menu", CATEGORY_PLAYER));
    toggle2 = env->NewGlobalRef(createToggle(env, thiz, "Profile Menu", CATEGORY_PROFILE));
    toggle3 = env->NewGlobalRef(createToggle(env, thiz, "Weapons Menu", CATEGORY_WEAPONS));
    toggle4 = env->NewGlobalRef(createToggle(env, thiz, "Gameplay Menu", CATEGORY_GAMEPLAY));
    toggle5 = env->NewGlobalRef(createToggle(env, thiz, "Gamemodes Menu", CATEGORY_GAMEMODES));
    toggle6 = env->NewGlobalRef(createToggle(env, thiz, "Extras Menu", CATEGORY_EXTRAS));
    toggle7 = env->NewGlobalRef(createToggle(env, thiz, "Customization Menu", CATEGORY_CUSTOMIZATION));
    toggle8 = env->NewGlobalRef(createToggle(env, thiz, NULL, 8));
    toggle9 = env->NewGlobalRef(createToggle(env, thiz, NULL, 9));
    toggle10 = env->NewGlobalRef(createToggle(env, thiz, NULL, 10));
}

void toggleMenu(JNIEnv *env, jobject thiz) {
    int GONE = 8;
    int VISIBLE = 0;

    resetButtons(env, thiz, CATEGORY_NONE);

    jclass RelativeLayout = env->FindClass("android/widget/RelativeLayout");
    env->CallVoidMethod(menu,
                        env->GetMethodID(RelativeLayout, "setVisibility", "(I)V"),
                        GONE);

    jobject icon = env->GetObjectField(thiz,
                                       env->GetFieldID(env->GetObjectClass(thiz), "icon", "Landroid/widget/RelativeLayout;"));

    env->CallVoidMethod(icon,
                        env->GetMethodID(RelativeLayout, "setVisibility", "(I)V"),
                        VISIBLE);
}

void changingMenu(JNIEnv *env, jobject thiz, jobject textView) {
    jclass TextView = env->GetObjectClass(textView);

    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setBackgroundColor", "(I)V"),
                        COLOR_MOD_HIGHLIGHT);
}

void resetMenu(JNIEnv *env, jobject thiz, jint id, jobject textView) {
    jclass TextView = env->GetObjectClass(textView);

    env->CallVoidMethod(textView,
                        env->GetMethodID(TextView, "setBackgroundColor", "(I)V"),
                        0); // transparent

    resetButtons(env, thiz, id);

    if (id < CATEGORY_TITLE_TEXT) {
        toggleButton(id);
    } else {
        updateColors(env, id);
    }
}