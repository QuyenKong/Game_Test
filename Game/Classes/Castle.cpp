#include "Castle.h"
#include <HouseBuilder.h>

Castle* Castle::CreateCastle(std::string path)
{
    auto  castle = new Castle();
    if (castle) {
        castle->autorelease();
        castle->loadCastle(path);
        return castle;
    }
    return nullptr;
}

void Castle::setDelegate(Castle_Delegate* delegate)
{
    this->_delegate = delegate;
}

void Castle::loadCastle(std::string path)
{
    _castle = ImageView::create("Ui-Map/actors/3-flat.png");
    _castle->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    this->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    this->setContentSize(_castle->getContentSize());
 /*   this->setBackGroundColor(Color3B::RED);
    this->setBackGroundImageOpacity(100);
    this->setBackGroundColorType(BackGroundColorType::SOLID);*/

    this->setContentSize(_castle->getContentSize());

    _touchLayout = cocos2d::ui::Layout::create();
    _touchLayout->setContentSize(_castle->getContentSize());
    _touchLayout->setTouchEnabled(true);

    this->addChild(_castle,9);

    this->addChild(_touchLayout, 10);


    _touchLayout->addClickEventListener([=](cocos2d::Ref* sender) {
        if (_delegate) {
            _delegate->onCastleClicked(this);
        }
        });
}
