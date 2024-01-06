#pragma once

#include <jni.h>
#include <vector>

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

class NativeMenu {
private:
    int processID;
    category selected_category;

    int COLOR_TITLE_TEXT;
    int COLOR_MOD_TEXT;
    int COLOR_MOD_HIGHLIGHT;
    int COLOR_MENU_BG;

    std::vector<Toggle> getToggles();

    Callback onToggle(int id);

    void showToast(JNIEnv *env, jobject thiz, const char *function, bool toggled) {
        int LENGTH_LONG = 1;

        char text[256];
        sprintf(text, "%s: %s",
                function,
                toggled ? "On" : "Off");

        jclass Toast = env->FindClass("android/widget/Toast");
        jobject toast = env->CallStaticObjectMethod(Toast,
                                                    env->GetStaticMethodID(Toast, "makeText", "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"),
                                                    thiz, env->NewStringUTF(text), LENGTH_LONG);

        env->CallVoidMethod(toast,
                            env->GetMethodID(Toast, "show", "()V"));
    }

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

    void createToggle(JNIEnv *env, jobject thiz, Toggle toggle) {
        int MATCH_PARENT = -1;
        int WRAP_CONTENT = -2;
        int CENTER_HORIZONTAL = 1;
        int TEXT_ALIGNMENT_CENTER = 4;

        bool isTitle = toggle.onClickId < 0;

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

        env->CallVoidMethod(textView,
                            env->GetMethodID(TextView, "setText", "(Ljava/lang/CharSequence;)V"),
                            env->NewStringUTF(toggle.text));

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

        env->CallVoidMethod(isTitle ? menu : functionList,
                            env->GetMethodID(env->FindClass("android/view/ViewGroup"), "addView", "(Landroid/view/View;)V"),
                            textView);

        if (isTitle) {
            env->SetObjectField(thiz,
                                env->GetFieldID(env->GetObjectClass(thiz), "menuTitle", "Landroid/widget/TextView;"),
                                textView);

            title = env->NewGlobalRef(textView);
        }

        env->CallVoidMethod(thiz,
                            env->GetMethodID(env->GetObjectClass(thiz), "setOnClickListener","(ZILandroid/widget/TextView;)V"),
                            isTitle, toggle.onClickId, textView);
    }
public:
    void submitPID(JNIEnv *env, jobject thiz, jint _processID) {
        processID = _processID;
    }

    void Initialize(JNIEnv *env, jclass clazz, jobject context) {
        COLOR_TITLE_TEXT = getColor(color::red, true);
        COLOR_MOD_TEXT = getColor(color::red, true);
        COLOR_MOD_HIGHLIGHT = getColor(color::red, true);
        COLOR_MENU_BG = getColor(color::red, false);

        selected_category = category::none;

        // Settings.Secure.getString(context.getContentResolver(), "ANDROID_ID");
        // get android id, make request and check output (valid = "Authentication Succeeded!")
    }

    void createWindowParams(JNIEnv *env, jobject thiz) {
        initIcon(env, thiz);
        initMenu(env, thiz);
    }

    void createViews(JNIEnv *env, jobject thiz) {
        for (Toggle toggle : getToggles()) {
            createToggle(env, thiz, toggle);
        }
    }

    void toggleMenu(JNIEnv *env, jobject thiz) {
        int GONE = 8;
        int VISIBLE = 0;

        jclass RelativeLayout = env->FindClass("android/widget/RelativeLayout");
        env->CallVoidMethod(menu,
                            env->GetMethodID(RelativeLayout, "setVisibility", "(I)V"),
                            GONE);

        jobject icon = env->GetObjectField(thiz,
                                           env->GetFieldID(env->GetObjectClass(thiz), "icon", "Landroid/widget/RelativeLayout;"));

        env->CallVoidMethod(icon,
                            env->GetMethodID(RelativeLayout, "setVisibility", "(I)V"),
                            VISIBLE);

        env->CallVoidMethod(menu,
                            env->GetMethodID(env->FindClass("android/widget/RelativeLayout"), "removeView", "(Landroid/view/View;)V"),
                            title);

        env->CallVoidMethod(functionList,
                            env->GetMethodID(env->FindClass("android/widget/LinearLayout"), "removeAllViews", "()V"));

        selected_category = category::none;

        createViews(env, thiz);
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

        Callback callback = onToggle(id);

        if (callback.updateViews) {
            env->CallVoidMethod(menu,
                                env->GetMethodID(env->FindClass("android/widget/RelativeLayout"), "removeView", "(Landroid/view/View;)V"),
                                title);

            env->CallVoidMethod(functionList,
                                env->GetMethodID(env->FindClass("android/widget/LinearLayout"), "removeAllViews", "()V"));

            if (callback.toggled) {
                jclass RelativeLayout = env->FindClass("android/widget/RelativeLayout");
                env->CallVoidMethod(menu,
                                    env->GetMethodID(RelativeLayout, "setBackgroundColor", "(I)V"),
                                    COLOR_MENU_BG);
            } else {
                selected_category = (category) id;
            }

            createViews(env, thiz);
        }

        if (callback.callToast) {
            jstring text = (jstring) env->CallObjectMethod(textView,
                                                           env->GetMethodID(TextView, "getText", "()Ljava/lang/CharSequence;"));

            showToast(env, thiz, env->GetStringUTFChars(text, JNI_FALSE), callback.toggled);
        }
    }
};