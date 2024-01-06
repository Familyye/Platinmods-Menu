#include "NativeMenu.hpp"

std::vector<Toggle> NativeMenu::getToggles() {
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
            toggles.push_back({ 1, "Infinite Ammo" });
            toggles.push_back({ 2, "Rapid Fire" });
            toggles.push_back({ 3, "No Spread" });
            toggles.push_back({ 4, "No Recoil" });
            toggles.push_back({ 5, "Field of View" });
            toggles.push_back({ 6, "Wallhack" });
            toggles.push_back({ 7, "Chams" });
            toggles.push_back({ category::none, "Back..." });
            break;

        case category::profile:
            toggles.push_back({ category::icon, "Platinmods<3\nProfile Menu" });
            toggles.push_back({ 1, "Level Up" });
            toggles.push_back({ 2, "Custom Name" });
            toggles.push_back({ 3, "Double Xp" });
            toggles.push_back({ category::none, "Back..." });
            break;

        case category::weapons:
            toggles.push_back({ category::icon, "Platinmods<3\nWeapons Menu" });
            toggles.push_back({ category::none, "Back..." });
            break;

        case category::gameplay:
            toggles.push_back({ category::icon, "Platinmods<3\nGameplay Menu" });
            toggles.push_back({ 1, "Super Speed" });
            toggles.push_back({ 2, "Respawn" });
            toggles.push_back({ 3, "Movement Always Allowed" });
            toggles.push_back({ 4, "Firing Always Allowed" });
            toggles.push_back({ category::none, "Back..." });
            break;

        case category::gamemodes:
            toggles.push_back({ category::icon, "Platinmods<3\nGamemodes Menu" });
            toggles.push_back({ 1, "Level Up" });
            toggles.push_back({ 2, "Level Down" });
            toggles.push_back({ 3, "Add Money" });
            toggles.push_back({ 4, "Always Hold Bomb" });
            toggles.push_back({ 5, "Plant Anywhere" });
            toggles.push_back({ 6, "Defuse Anywhere" });
            toggles.push_back({ category::none, "Back..." });
            break;

        case category::extras:
            toggles.push_back({ category::icon, "Platinmods<3\nExtras  Menu" });
            toggles.push_back({ 1, "Respawn Before Die" });
            toggles.push_back({ 2, "Spam Chat" });
            toggles.push_back({ 3, "Jump Exploit" });
            toggles.push_back({ 4, "Position Menu" });
            toggles.push_back({ 5, "Telekill" });
            toggles.push_back({ 6, "Aimbot" });
            toggles.push_back({ 7, "Walking Nuke" });
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

Callback NativeMenu::onToggle(int id) {
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

        case 1:
            return { true, false, true };

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
