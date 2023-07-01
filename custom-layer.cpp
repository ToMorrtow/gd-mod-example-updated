#include "custom-layer.hpp"

void CustomLayer::customButtonCallBack(CCObject*) { // flalert uwu
    auto flalert = gd::FLAlertLayer::create(nullptr, "Creditos", "okay", nullptr, "Mod by: </c> ToMorritow\n<cg>Repositi by:</c> Matcool\n<co>Supporter by: </c> Jorgame, User666\n<co>");
    flalert->show();
}

CustomLayer* CustomLayer::create() {
    auto ret = new CustomLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool CustomLayer::init() {

    auto label = CCLabelBMFont::create("Hello World", "bigFont.fnt"); // Text Basic

    label->setPosition({292, 143});
    label->setRotation(0);

    addChild(label);

    auto CustomSprite = CCSprite::create("GJ_square05.png"); // Alert Flalert
    CustomSprite->setScale(0.6f);

    auto buttonMenu = CCMenu::create();
    auto CustomButton = gd::CCMenuItemSpriteExtra::create(CustomSprite, this, menu_selector(CustomLayer::customButtonCallBack));
    buttonMenu->setPosition({288 , 198});
    buttonMenu->addChild(CustomButton);
    this->addChild(buttonMenu);

    gd::GameManager::sharedState()->fadeInMusic("menuLoop2.mp3"); // change of song on layer

    auto backgroundSprite = CCSprite::create("GJ_gradientBG.png"); // bg ( background )
    
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = backgroundSprite->getContentSize();

    backgroundSprite->setScaleX(winSize.width / size.width);
    backgroundSprite->setScaleY(winSize.height / size.height);
    
    backgroundSprite->setAnchorPoint({0, 0});
    
    backgroundSprite->setColor({100, 100, 100});
    
    backgroundSprite->setZOrder(-1);
    addChild(backgroundSprite);

    auto button = gd::CCMenuItemSpriteExtra::create(

        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(CustomLayer::backButtonCallback)
    );

    auto menu = CCMenu::create();
    menu->addChild(button);

    menu->setPosition({25, winSize.height - 25});

    addChild(menu);

    setKeypadEnabled(true);

    return true;
}

void CustomLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

void CustomLayer::backButtonCallback(CCObject* object) {
    keyBackClicked();
}

void CustomLayer::switchToCustomLayerButton(CCObject* object) {

    auto layer = CustomLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    auto transition = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
}