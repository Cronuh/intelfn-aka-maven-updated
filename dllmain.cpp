#include "stdafx.h"
#include "meni.h"

VOID Main() {
    //Util::CreateConsole();
    SettingsHelper::Initialize();

    if (!Util::Initialize()) {
        return;
    }

    if (!Offsets::Initialize()) {
        return;
    }

    if (!Core::Initialize()) {
        return;
    }

    if (!Render::Initialize()) {
        return;
    }
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        Main();
    }

    return TRUE;
}