#pragma once

#include <jni.h>
#include <vector>
#include "Hack.hpp"

enum category {
    icon = -1,
    none = 1000,
    player = 2000,
    profile = 3000,
    weapons = 4000,
    gameplay = 5000,
    gamemodes = 6000,
    extras = 7000,
    customization = 8000,
    customization_title_text = 9000,
    customization_mod_text = 10000,
    customization_mod_highlight = 11000,
    customization_menu_bg = 12000
};

enum color {
    red = 1,
    green = 2,
    blue = 3,
    yellow = 4,
    orange = 5,
    pink = 6,
    purple = 7,
    black = 8
};

struct Toggle {
    int onClickId;
    const char *text;
};

struct Callback {
    bool toggled;
    bool callToast;
    bool updateViews;
};

static jobject menu;
static jobject title;
static jobject functionList;

namespace NativeMenu {
    int processID;
    category selected_category;

    int COLOR_TITLE_TEXT;
    int COLOR_MOD_TEXT;
    int COLOR_MOD_HIGHLIGHT;
    int COLOR_MENU_BG;

    int getColor(int id, bool isDefault) {
        switch (id) {
            case color::red:
                return isDefault ? -65536 : -1725628416;

            case color::green:
                return isDefault ? -16711936 : -1728043776;

            case color::blue:
                return isDefault ? -16776961 : -1728053211;

            case color::yellow:
                return isDefault ? -256 : -1725618944;

            case color::orange:
                return isDefault ? -35072 : -1725623808;

            case color::pink:
                return isDefault ? -16181 : -1725622247;

            case color::purple:
                return isDefault ? -65281 : -1725628379;

            case color::black:
                return isDefault ? -16777216 : -1728053248;
        }

        return 0;
    }

    std::vector<Toggle> getToggles() {
        std::vector<Toggle> toggles;

        switch (selected_category) {
            case category::none:
                toggles.push_back({ category::icon, "Platinmods<3\nMain Menu" });
                toggles.push_back({ category::player, "Player Menu" });
                toggles.push_back({ category::profile, "Profile Menu" });
                toggles.push_back({ category::weapons, "Weapons Menu" });
                toggles.push_back({ category::gameplay, "Gameplay Menu" });
                toggles.push_back({ category::gamemodes, "Gamemodes Menu" });
                toggles.push_back({ category::extras, "Extras Menu" });
                toggles.push_back({ category::customization, "Customization Menu" });
                break;

            case category::player:
                toggles.push_back({ category::icon, "Platinmods<3\nPlayer Menu" });
                toggles.push_back({ category::player + 1, "Infinite Ammo" });
                toggles.push_back({ category::player + 2, "Rapid Fire" });
                toggles.push_back({ category::player + 3, "No Spread" });
                toggles.push_back({ category::player + 4, "No Recoil" });
                toggles.push_back({ category::player + 5, "Field of View" });
                toggles.push_back({ category::player + 6, "Wallhack" });
                toggles.push_back({ category::player + 7, "Chams" });
                toggles.push_back({ category::none, "Back..." });
                break;

            case category::profile:
                toggles.push_back({ category::icon, "Platinmods<3\nProfile Menu" });
                toggles.push_back({ category::profile + 1, "Level Up" });
                toggles.push_back({ category::profile + 2, "Custom Name" });
                toggles.push_back({ category::profile + 3, "Double Xp" });
                toggles.push_back({ category::none, "Back..." });
                break;

            case category::weapons:
                toggles.push_back({ category::icon, "Platinmods<3\nWeapons Menu" });
                toggles.push_back({ category::none, "Back..." });
                break;

            case category::gameplay:
                toggles.push_back({ category::icon, "Platinmods<3\nGameplay Menu" });
                toggles.push_back({ category::gameplay + 1, "Super Speed" });
                toggles.push_back({ category::gameplay + 2, "Respawn" });
                toggles.push_back({ category::gameplay + 3, "Movement Always Allowed" });
                toggles.push_back({ category::gameplay + 4, "Firing Always Allowed" });
                toggles.push_back({ category::none, "Back..." });
                break;

            case category::gamemodes:
                toggles.push_back({ category::icon, "Platinmods<3\nGamemodes Menu" });
                toggles.push_back({ category::gamemodes + 1, "Level Up" });
                toggles.push_back({ category::gamemodes + 2, "Level Down" });
                toggles.push_back({ category::gamemodes + 3, "Add Money" });
                toggles.push_back({ category::gamemodes + 4, "Always Hold Bomb" });
                toggles.push_back({ category::gamemodes + 5, "Plant Anywhere" });
                toggles.push_back({ category::gamemodes + 6, "Defuse Anywhere" });
                toggles.push_back({ category::none, "Back..." });
                break;

            case category::extras:
                toggles.push_back({ category::icon, "Platinmods<3\nExtras  Menu" });
                toggles.push_back({ category::extras + 1, "Respawn Before Die" });
                toggles.push_back({ category::extras + 2, "Spam Chat" });
                toggles.push_back({ category::extras + 3, "Jump Exploit" });
                toggles.push_back({ category::extras + 4, "Position Menu" });
                toggles.push_back({ category::extras + 5, "Telekill" });
                toggles.push_back({ category::extras + 6, "Aimbot" });
                toggles.push_back({ category::extras + 7, "Walking Nuke" });
                toggles.push_back({ category::none, "Back..." });
                break;

            case category::customization:
                toggles.push_back({ category::icon, "Platinmods<3\nCustomization Menu" });
                toggles.push_back({ category::customization_title_text, "Title Text Color" });
                toggles.push_back({ category::customization_mod_text, "Mod Text Color" });
                toggles.push_back({ category::customization_mod_highlight, "Mod Highlight Color" });
                toggles.push_back({ category::customization_menu_bg, "Menu Background Color" });
                toggles.push_back({ category::none, "Back..." });
                break;

            case category::customization_title_text:
                toggles.push_back({ category::icon, "Platinmods<3\nTitle Text" });
                toggles.push_back({ category::customization_title_text + (int) color::red, "Red Title" });
                toggles.push_back({ category::customization_title_text + (int) color::green, "Green Title" });
                toggles.push_back({ category::customization_title_text + (int) color::blue, "Blue Title" });
                toggles.push_back({ category::customization_title_text + (int) color::yellow, "Yellow Title" });
                toggles.push_back({ category::customization_title_text + (int) color::orange, "Orange Title" });
                toggles.push_back({ category::customization_title_text + (int) color::pink, "Pink Title" });
                toggles.push_back({ category::customization_title_text + (int) color::purple, "Purple Title" });
                toggles.push_back({ category::customization_title_text + (int) color::black, "Black Title" });
                toggles.push_back({ category::customization, "Back..." });
                break;

            case category::customization_mod_text:
                toggles.push_back({ category::icon, "Platinmods<3\nMod Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::red, "Red Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::green, "Green Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::blue, "Blue Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::yellow, "Yellow Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::orange, "Orange Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::pink, "Pink Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::purple, "Purple Text" });
                toggles.push_back({ category::customization_mod_text + (int) color::black, "Black Text" });
                toggles.push_back({ category::customization, "Back..." });
                break;

            case category::customization_mod_highlight:
                toggles.push_back({ category::icon, "Platinmods<3\nMod Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::red, "Red Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::green, "Green Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::blue, "Blue Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::yellow, "Yellow Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::orange, "Orange Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::pink, "Pink Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::purple, "Purple Highlight" });
                toggles.push_back({ category::customization_mod_highlight + (int) color::black, "Black Highlight" });
                toggles.push_back({ category::customization, "Back..." });
                break;

            case category::customization_menu_bg:
                toggles.push_back({ category::icon, "Platinmods<3\nBackground" });
                toggles.push_back({ category::customization_menu_bg + (int) color::red, "Red BG" });
                toggles.push_back({ category::customization_menu_bg + (int) color::green, "Green BG" });
                toggles.push_back({ category::customization_menu_bg + (int) color::blue, "Blue BG" });
                toggles.push_back({ category::customization_menu_bg + (int) color::yellow, "Yellow BG" });
                toggles.push_back({ category::customization_menu_bg + (int) color::orange, "Orange BG" });
                toggles.push_back({ category::customization_menu_bg + (int) color::pink, "Pink BG" });
                toggles.push_back({ category::customization_menu_bg + (int) color::purple, "Purple BG" });
                toggles.push_back({ category::customization_menu_bg + (int) color::black, "Black BG" });
                toggles.push_back({ category::customization, "Back..." });
                break;

            default:
                break;
        }

        return toggles;
    }

    Callback onToggle(int id) {
        switch (id) {
            case category::none:
                return { false, false, true };

            case category::player:
                return { false, false, true };

            case category::profile:
                return { false, false, true };

            case category::weapons:
                return { false, false, true };

            case category::gameplay:
                return { false, false, true };

            case category::gamemodes:
                return { false, false, true };

            case category::extras:
                return { false, false, true };

            case category::customization:
                return { false, false, true };

            case category::customization_title_text:
                return { false, false, true };

            case category::customization_mod_text:
                return { false, false, true };

            case category::customization_mod_highlight:
                return { false, false, true };

            case category::customization_menu_bg:
                return { false, false, true };

            default:
                if (id > category::customization_menu_bg) {
                    COLOR_MENU_BG = getColor(id - category::customization_menu_bg, false);
                } else if (id > category::customization_mod_highlight) {
                    COLOR_MOD_HIGHLIGHT = getColor(id - category::customization_mod_highlight, true);
                } else if (id > category::customization_mod_text) {
                    COLOR_MOD_TEXT = getColor(id - category::customization_mod_text, true);
                } else if (id > category::customization_title_text) {
                    COLOR_TITLE_TEXT = getColor(id - category::customization_title_text, true);
                }

                if (id > category::customization_title_text) {
                    return { true, false, true };
                }

                return {};
        }
    }
}