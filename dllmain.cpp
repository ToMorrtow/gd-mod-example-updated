#include "includes.h"
#include "custom-layer.hpp"

bool (__thiscall* CreatorLayer_init)(CCLayer* self);
bool __fastcall CreatorLayer_init_H(CCLayer* self, void*) {

    if (!CreatorLayer_init(self)) return false;

    // button pw 

    auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_gauntletsBtn_001.png");
    
    auto button = gd::CCMenuItemSpriteExtra::create(
        buttonSprite,
        self,
        menu_selector(CustomLayer::switchToCustomLayerButton)
    );

    auto menu = CCMenu::create();
    menu->addChild(button);
    menu->setPosition({91, 233});
    menu->setScale({0.85f});

    self->addChild(menu);

    // change button on Creator Layer

    auto allBtns = dynamic_cast<CCNode*>(self->getChildren()->objectAtIndex(1));

    auto CreateBtn = dynamic_cast<CCNode*>(allBtns->getChildren()->objectAtIndex(0));

    auto SaveBtn = dynamic_cast<CCNode*>(allBtns->getChildren()->objectAtIndex(1));

    auto ScoresBtn = dynamic_cast<CCNode*>(allBtns->getChildren()->objectAtIndex(2));

    auto QuestsBtn = dynamic_cast<CCNode*>(allBtns->getChildren()->objectAtIndex(3));

    auto DailyBtn = dynamic_cast<CCNode*>(allBtns->getChildren()->objectAtIndex(4));

    auto WeeklyBtn = dynamic_cast<CCNode*>(allBtns->getChildren()->objectAtIndex(5));

    auto SearchBtn = dynamic_cast<CCNode*>(allBtns->getChildren()->objectAtIndex(9));
    
    //Moving buttons

    ScoresBtn->setPosition(150, 97); 

    SaveBtn->setPosition(50, 97);

    CreateBtn->setPosition(-50, 97);

    return true;
}

// text ramdon pwxdd

bool (__thiscall* MenuLayer_init)(CCLayer* self);
bool __fastcall MenuLayer_init_H(CCLayer* self, void*) {

    if (!MenuLayer_init(self)) return false;

    auto textlabelpw = CCLabelBMFont::create("Developer mods by: ToMorritow", "chatFont.fnt");
    textlabelpw->setPosition({283, 310});
    textlabelpw->setScale({ 0.5f });

    return true;
}

DWORD WINAPI thread_func(void* hModule) {
    MH_Initialize();

    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));

    MH_CreateHook( // MenuLayer
        reinterpret_cast<void*>(base + 0x1907b0),
        reinterpret_cast<void*>(&MenuLayer_init_H),
        reinterpret_cast<void**>(&MenuLayer_init)
    );

    MH_CreateHook( // Creator Layer
        reinterpret_cast<void*>(base + 0x4DE40),
        reinterpret_cast<void*>(&CreatorLayer_init_H),
        reinterpret_cast<void**>(&CreatorLayer_init)
    );

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}