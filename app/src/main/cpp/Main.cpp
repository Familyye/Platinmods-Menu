#include "NativeMenu.hpp"

/*
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⡤⠤⠤⣤⣤⢤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⠟⣉⡤⠴⠀⣀⣈⣭⣁⠀⠙⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⠗⠋⣀⡤⠤⠒⢘⡥⠤⡀⠙⢦⡀⠈⢷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⠟⠁⡤⠚⠁⣠⠖⠛⠻⠧⢤⡈⠳⣄⠑⡄⠈⢿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⢻⣿⠋⣠⠞⠁⢠⠎⠀⡖⢀⠀⢀⡄⡵⡄⠘⢦⢣⠀⢻⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢫⡿⠃⣰⠏⠀⣳⡏⠀⣴⠁⠀⣸⣇⠙⡘⢿⡄⠈⠋⢧⠀⢻⣆⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣾⠁⢰⠏⠀⣠⣿⣟⢺⣟⣚⣿⡟⠘⣦⣷⡈⣿⡄⢀⡞⣧⠘⣿⡀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡏⢀⡿⠀⢸⣿⣿⣿⣿⡿⣶⡿⠁⠀⠈⢿⣷⣿⣷⠴⣷⣽⣇⣿⢇⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⣸⣇⢰⣿⢿⣾⣭⣿⠿⠋⢠⣐⡒⠀⠀⣹⣿⢃⠂⢸⣿⣿⣿⠎⣧⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣤⣿⣿⣿⡏⠀⠚⠉⠇⠀⠀⠙⢹⡿⡷⠦⡿⠙⢸⢠⣾⣿⣿⣿⣰⠏⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⣀⣿⣿⣏⣿⣧⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠈⣠⠞⠀⣰⣶⣿⣿⡧⠟⠟⠁⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠙⣟⢻⣿⣹⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⢿⣿⣾⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣿⣿⣿⣿⡟⠙⢦⡀⠀⠀⠀⣀⡤⢞⢏⡟⢼⡿⣿⣇⡉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⡀⠀⠀⠀⡀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣦⡼⣿⠓⣶⠟⠋⣠⣟⣉⣀⣤⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠰⠒⠉⣵⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠈⠉⢣⡤⠊⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⠀⠀⠀⠀
 * ⠀⢀⣈⡗⠀⣰⣾⡿⢿⣿⣿⣿⣿⣿⣿⠿⠿⠿⣿⣿⣿⣷⣾⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀
 * ⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣻⣶⣿⡿⣿⣿⢭⣭⣄⣆⠔⠬⢍⠉⢛⠛⠿⣿⣿⣿⣿⣿⡏⡀⠘⠿⡋⠙⢿⣿⡇⠀⠀
 * ⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣷⣧⣼⣾⣿⡻⠿⠿⢭⣭⣾⣽⣿⠃⠀⡠⠟⢠⣿⣿⣿⠀⠀
 * ⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣣⠞⠋⠐⠂⢭⣙⠛⠛⠿⣿⣿⣿⣿⣷⣶⣶⣦⣶⣾⣿⣿⣿⣶⣼⣁⣀⣼⣿⣿⣿⣇⠀
 * ⠀⢿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠙⢷⣶⣤⣤⣤⠤⠬⠉⠉⢭⣝⡛⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀
 * ⠀⢸⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀
 * ⠀⠀⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀
 * ⠀⠀⠈⣿⣿⣿⣿⣿⣧⠀⢀⠀⠀⠀⠀⠀⠀⢀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄
 * ⠀⠀⠀⠘⢿⣿⣿⣿⣿⣦⣄⠀⠀⠀⠀⠀⣠⠎⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
 * ⠀⠀⠀⠀⠀⠙⠻⠿⠿⠟⡊⠛⠶⠶⠖⠋⠁⠀⠀⠀⠈⢷⣄⠀⠀⠀⠀⠁⢀⣤⠏⢸⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⠶⠶⠶⠾⠉⠁⢀⡞⠁⠻⣿⣿⣿⣿⣿⣿⣿⣿⠏
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇⠀⠀⠙⢿⣿⣿⣿⣿⣿⠋⠀
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⠀⠀⠀⠀⠙⠛⠛⠋⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⢀⡴⡿⢱⠏⠣⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⢿⡷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⢀⡾⡿⠀⡇⣠⠗⢄⠉⠲⠦⠤⣀⣀⣀⣀⣀⣀⣀⡤⠶⠻⠋⢻⠀⠱⡹⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⢀⡞⣾⠇⣸⠁⠃⠀⠀⠉⢒⠦⠄⣀⣀⣀⠀⠀⣀⣀⣠⠴⠺⡀⠈⡇⠀⢻⡻⣄⠀⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⣼⣽⣿⢠⠃⠀⠀⢀⡆⠀⠈⠀⠀⠃⠀⠀⠃⠉⡏⠀⠀⡀⠀⡇⠀⢸⡄⠀⢳⠙⢆⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⢠⡿⢃⡇⢸⠀⠀⠀⣸⠀⠀⠀⠀⠘⠀⠀⠀⠀⠐⡇⠀⣄⡇⠀⢸⡀⠀⢣⠀⠈⢷⠈⢧⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⣼⠃⣼⠁⡜⠀⠀⢀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠘⣧⠀⠈⢧⠀⠘⣆⠀⠈⣧⠘⣧⠀⠀⠀⠀⠀
 * ⠀⠀⠀⢸⡟⠀⢻⠀⡇⠀⠀⣼⠀⠀⡇⠀⠀⡆⠀⠀⠀⠀⠀⡇⠀⠀⢹⡄⠀⢸⡀⠀⠹⡄⠀⢸⣦⠹⣇⠀⠀⠀⠀
 * ⠀⠀⢀⣿⠁⢸⡏⢰⠃⠀⡆⣿⠀⠀⠀⠀⠀⡇⠀⠀⡄⠀⠀⠇⠀⠀⠸⣷⠀⠀⣷⡀⠀⢷⠀⠀⣿⣆⣿⡄⠀⠀⠀
 * ⠀⠀⠈⣿⠿⢿⡇⣾⠀⠀⣇⣯⠀⢸⠀⠀⠀⡇⠀⠀⠃⠀⠀⢸⠀⠀⠀⣿⠀⠀⢸⡇⠀⢸⣦⣠⣼⡟⠋⠀⠀⠀⠀
 * ⠀⠀⠀⠁⠀⢸⣷⣿⣦⡀⣿⡇⠀⢸⠀⠀⠀⡇⠀⠀⡇⠀⠀⢸⡀⠀⠀⣿⡆⠀⠸⣧⣤⣤⣿⣿⣿⠃⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠘⣿⣿⣷⣭⣿⣷⡀⢸⠀⠀⠀⡇⠀⠀⡇⠀⠀⢸⡇⠀⠀⢸⡇⡤⣺⣿⠿⠻⣿⣿⡿⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⢸⣿⡇⠙⢻⠿⣬⣿⣯⣍⣒⣿⢦⡀⣿⡦⣄⢸⣿⣉⣐⢾⣿⣿⠟⠁⠀⠀⣿⣿⠃⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠈⣿⣿⠀⠀⠀⠙⠛⠈⠛⠿⢿⣿⣬⡿⣿⣶⣼⠿⡿⢿⠋⠀⠀⠀⠀⠀⢠⣿⡏⠀⠀⠀⠀⠀⠀⠀
 * ⠀⠀⠀⠀⠀⠀⠀⢻⣿⡄⠀⠀⠀⠀⠀⠀⣀⣁⣿⣿⣇⣈⣉⣇⣀⣆⡀⠀⠀⠀⠀⠀⠀⣸⡿⠁⠀⠀⠀⠀⠀⠀⠀
 */

NativeMenu nativeMenu;

void submitPID(JNIEnv *env, jobject thiz, jint processID) {
    nativeMenu.submitPID(env, thiz, processID);
}

void Initialize(JNIEnv *env, jclass clazz, jobject context) {
    nativeMenu.Initialize(env, clazz, context);
}

void createWindowParams(JNIEnv *env, jobject thiz) {
    nativeMenu.createWindowParams(env, thiz);
}

void createViews(JNIEnv *env, jobject thiz) {
    nativeMenu.createViews(env, thiz);
}

void toggleMenu(JNIEnv *env, jobject thiz) {
    nativeMenu.toggleMenu(env, thiz);
}

void changingMenu(JNIEnv *env, jobject thiz, jobject textView) {
    nativeMenu.changingMenu(env, thiz, textView);
}

void resetMenu(JNIEnv *env, jobject thiz, jint id, jobject textView) {
    nativeMenu.resetMenu(env, thiz, id, textView);
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_OK) {
        nativeMenu = NativeMenu();

        JNINativeMethod methods[] = {
                { "submitPID", "(I)V", (void *) submitPID },
                { "Initialize", "(Landroid/content/Context;)V", (void *) Initialize },
                { "createWindowParams", "()V", (void *) createWindowParams },
                { "createViews", "()V", (void *) createViews },
                { "toggleMenu", "()V", (void *) toggleMenu },
                { "changingMenu", "(Landroid/widget/TextView;)V", (void *) changingMenu },
                { "resetMenu", "(ILandroid/widget/TextView;)V", (void *) resetMenu }
        };

        env->RegisterNatives(env->FindClass("platinmods/menu/pmt/Reborn"), methods, sizeof(methods) / sizeof(methods[0]));
    }

    return JNI_VERSION_1_6;
}