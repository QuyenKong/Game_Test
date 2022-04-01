#include "Soldier.h"

Soldier* Soldier::createSoldier(std::string path)
{
    auto  soldier = new Soldier();
    if (soldier) {
        soldier->autorelease();
        soldier->loadSoldier(path);
        return soldier;
    }
    return nullptr;
}

Sprite* Soldier::getSoilderSprite()
{
    return _soilderSprite;
}

void Soldier::loadSoldier(std::string path)
{
    //auto _soilder = Sprite::create(path);
    _soilderSprite = Sprite::create("Ui-Map/troops-unpack/1-idle-front-1.png");
    _soilderSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _soilderSprite->setScale(0.2);
    this->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    this->setContentSize(_soilderSprite->getContentSize());

    this->addChild(_soilderSprite);

}

