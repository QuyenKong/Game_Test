#include "HouseBuilder.h"
#include <cocos/ui/UIButton.h>
#define MARGIN_TOP 30
#define MARGIN_ITEM 15
HouseBuilder* HouseBuilder::_houseBuilder;

HouseBuilder* HouseBuilder::getInstance()
{
    if (_houseBuilder == nullptr) {
        _houseBuilder = new HouseBuilder();
    }
    return _houseBuilder;
}
HouseBuilder* HouseBuilder::createHouseBuilder()
{
    _houseBuilder = new HouseBuilder();
    if (_houseBuilder) {
        _houseBuilder->loadHouseBuilder();
        return _houseBuilder;
    }
    return nullptr;
}

void HouseBuilder::hideHouseBuilder()
{
    _isShowing = false;
    _bgBorder->setVisible(false);
}

void HouseBuilder::showHouseBuilder()
{
    _isShowing = true;
    _bgBorder->setVisible(true);
}

float HouseBuilder::getHeight()
{
    return _bgBorder->getContentSize().height;
}

void HouseBuilder::setDelegate(HouseBuilder_Delegate* delegate)
{
    this->_delegate = delegate;
}

void HouseBuilder::loadHouseBuilder()
{
    //----------------Background houseBuilder-----------------
    /*this->setContentSize(Director::getInstance()->getVisibleSize());
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->setPosition((Director::getInstance()->getVisibleSize()/2));*/

    _bgBorder = ImageView::create("Ui-Map/khung.png");
    _bgBorder->setSize(Size(Director::getInstance()->getVisibleSize().width/10, Director::getInstance()->getVisibleSize().height * 2 /3 ));
    _bgBorder->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _bgBorder->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 10, Director::getInstance()->getVisibleSize().height * 3/7));
  
    //----------------Button name house builder-----------------
    ImageView* retangleButtonName = ImageView::create("Ui-Map/Rounded Rectangle 1-1.png");
    retangleButtonName->setSize(Size(Director::getInstance()->getVisibleSize().width / 10, Director::getInstance()->getVisibleSize().height * 2 / 3));
    retangleButtonName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    retangleButtonName->setPosition(Vec2(_bgBorder->getContentSize().width / 2, (_bgBorder->getContentSize().height - retangleButtonName->getContentSize().height/2- MARGIN_TOP)));
    

    ImageView* buttonName = ImageView::create("Ui-Map/Housebuilder.png");
    buttonName->setSize(Size(Director::getInstance()->getVisibleSize().width / 10, Director::getInstance()->getVisibleSize().height * 2 / 3));
    buttonName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    buttonName->setPosition(retangleButtonName->getContentSize()/2 );

    //----------------TOWER-----------------
    auto leftHeight = _bgBorder->getContentSize().height - retangleButtonName->getContentSize().height - MARGIN_TOP;
    leftHeight = leftHeight / 4 - MARGIN_TOP;
    ImageView* tower1 = ImageView::create("Ui-Map/Group 1 copy 2.png");
    tower1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tower1->setPosition(Vec2(_bgBorder->getContentSize().width / 2, leftHeight + MARGIN_ITEM));
    tower1->setTouchEnabled(true);
    tower1->setTag(1);
    tower1->addClickEventListener([=](Ref* sender) {
        _typeOfTower = 1;
        if (_delegate) {
            _delegate->onHouseBuilderClicked(this);
        }
        });

    ImageView* tower2 = ImageView::create("Ui-Map/Group 1 copy 5.png");
    tower2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tower2->setPosition(Vec2(_bgBorder->getContentSize().width / 2, leftHeight*2 + MARGIN_ITEM));
    tower2->setTouchEnabled(true);
    tower2->setTag(2);
    tower2->addClickEventListener([=](Ref* sender) {
        _typeOfTower = 2;
        if (_delegate) {
            _delegate->onHouseBuilderClicked(this);
        }
        });

    ImageView* tower3 = ImageView::create("Ui-Map/Group 1 copy.png");
    tower3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tower3->setPosition(Vec2(_bgBorder->getContentSize().width / 2, leftHeight * 3 + MARGIN_ITEM));
    tower3->setTouchEnabled(true);
    tower3->setTag(3);
    tower3->addClickEventListener([=](Ref* sender) {
        _typeOfTower = 3;
        if (_delegate) {
            _delegate->onHouseBuilderClicked(this);
        }
        });

    ImageView* tower4 = ImageView::create("Ui-Map/Group 1-1.png");
    tower4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tower4->setPosition(Vec2(_bgBorder->getContentSize().width / 2, leftHeight * 4 + MARGIN_ITEM));
    tower4->setTouchEnabled(true);
    tower4->setTag(4);
    tower4->addClickEventListener([=](Ref* sender) {
        _typeOfTower = 4;
        if (_delegate) {
            _delegate->onHouseBuilderClicked(this);
        }
        });

    this->addChild(_bgBorder);
    _bgBorder->addChild(tower1);
    _bgBorder->addChild(tower2);
    _bgBorder->addChild(tower3);
    _bgBorder->addChild(tower4);
    _bgBorder->addChild(retangleButtonName);
    retangleButtonName->addChild(buttonName);

}
