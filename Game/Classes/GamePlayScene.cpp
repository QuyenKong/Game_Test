/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "MapScene.h"
#include <HouseBuilder.h>
#include <cocos/ui/UIButton.h>
#include <LayerMask.h>
#include <Castle.h>
#include <Soldier.h>
#define MAX_TOWER_IN_A_CASTLE 4
#define MARGIN_TOWER_WITH_SOLDIER 4
#define MAX_TYPE_OF_SOLDIER 2
#define SPEED_OF_SOLDIER 20
#define TIME_SPAW 1
USING_NS_CC;

GamePlayScene* GamePlayScene::createGamePlayScene()
{
    GamePlayScene* obj = new GamePlayScene();
    if (obj->init())
    {
        obj->autorelease();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return nullptr;
}

// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    loadAnimation();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto a = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

     _mainLayout = cocos2d::ui::Layout::create();
    _mainLayout->setContentSize(this->getContentSize());
    this->addChild(_mainLayout);
  /*  this->setTouchEnabled(true);
   
    _rooLayout = cocos2d::ui::Layout::create();
    _rooLayout->setContentSize(a);
    this->addChild(_rooLayout, 5);*/

    //add map
    auto _map = MapScene::createMap("Ui-Map/maps/map-1.tmx");
    _mainLayout->addChild(_map,1);
    _mainLayout->setTouchEnabled(true);

    //layout houseBuilder
    auto _houseBuilder = HouseBuilder::createHouseBuilder();
    _houseBuilder->setDelegate(this);
    _houseBuilder->hideHouseBuilder();
    _mainLayout->addChild((Node*)_houseBuilder, 6);

    //button surrender
    Button* surrenderButton = Button::create("Ui-Map/bt Surrender.png", "Ui-Map/bt Surrender cover.png", "Ui-Map/bt Surrender.png");
    surrenderButton->setContentSize(this->getContentSize());
    surrenderButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    surrenderButton->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 10 -10, Director::getInstance()->getVisibleSize().height*9/10));
    surrenderButton->addClickEventListener([=](cocos2d::Ref* sender) {
        Director::getInstance()->end();
        });
    _mainLayout->addChild(surrenderButton, 2);
    
    //maskLayer : name,avatar , infor
    auto _maskLayer = LayerMask::createLayerMask();
    this->addChild((Node*)(_maskLayer), 3);
    _maskLayer->hideLayerMask();


     _castle1 = Castle::CreateCastle("");
    _mainLayout->addChild(_castle1, 4);
    _castle1->setPosition(Director::getInstance()->getVisibleSize() / 2);
    _castle1->setDelegate(this);
    _castle1->setTag(1);
    _castle1->schedule([=](float dt_) {
        generateSoldier(_castle1);
    }, TIME_SPAW,true,0 ,"generate_soldier_1");

    _castle2 = Castle::CreateCastle("");
    _castle2->setTouchEnabled(true);
    _mainLayout->addChild(_castle2, 3);
    _castle2->setTag(2);
    _castle2->setPosition(Vec2(Director::getInstance()->getVisibleSize().width* 1/ 7, Director::getInstance()->getVisibleSize().height *0.6));
    _castle2->setDelegate(this);
    _castle2->schedule([=](float dt_) {
        generateSoldier(_castle2);
        }, TIME_SPAW,true,0, "generate_soldier_2");

   _castle3 = Castle::CreateCastle("");
    _castle3->setTouchEnabled(true);
    _castle3->setDelegate(this);
    _castle3->setTag(3);
    _mainLayout->addChild(_castle3, 3);
    _castle3->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*0.7, Director::getInstance()->getVisibleSize().height/4));
    _castle3->schedule([=](float dt_) {
        generateSoldier(_castle2);
        }, TIME_SPAW, true, 0, "generate_soldier_3");
    
    _castle4 = Castle::CreateCastle("");
    _castle4->setTouchEnabled(true);
    _castle4->setDelegate(this);
    _castle4->setTag(3);
    _mainLayout->addChild(_castle4, 3);
    _castle4->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.3, Director::getInstance()->getVisibleSize().height / 4));
    _castle4->schedule([=](float dt_) {
        generateSoldier(_castle2);
        }, TIME_SPAW, true, 0, "generate_soldier_3");

    vectorCastle.push_back(_castle1);
    vectorCastle.push_back(_castle2);
    vectorCastle.push_back(_castle3);
    vectorCastle.push_back(_castle4);

   /* auto soldier = Soldier::createSoldier("");
    soldier->setContentSize(_castle1->getContentSize() / 10);
    
    soldier->setPosition(Vec2(_castle1->getPosition().x + _castle1->getContentSize().width / 2 + MARGIN_TOWER_WITH_SOLDIER, _castle1->getPosition().y - MARGIN_TOWER_WITH_SOLDIER));
    Animate* animate = Animate::create(AnimationCache::getInstance()->getAnimation("soilder1AnimationFront"));

    soldier->getSoilderSprite()->runAction(animate);
    auto soldier1 = Soldier::createSoldier("");
    soldier1->setContentSize(_castle1->getContentSize() / 10);
    soldier1->setPosition(Vec2(soldier->getPosition().x + soldier->getContentSize().width*2 + MARGIN_TOWER_WITH_SOLDIER, soldier->getPosition().y + soldier->getContentSize().height*2 + MARGIN_TOWER_WITH_SOLDIER));
    this->addChild(soldier, 4);
    this->addChild(soldier1, 4);*/

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(GamePlayScene::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(GamePlayScene::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(GamePlayScene::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    return true;
}

void GamePlayScene::onCastleClicked(cocos2d::Ref* sender)
{
    if (_mouseEventOneTimeClickDown) {
        _castleAttack = static_cast<Castle*>(sender);
    }
    _selectedCastleConvertToNumber = static_cast<Castle*>(sender)->getTag();
    _selectedCastle = static_cast<Castle*>(sender);
    if (HouseBuilder::getInstance()) {
        if (HouseBuilder::getInstance()->_isShowing) {
            return;
        }
        else {
            HouseBuilder::getInstance()->showHouseBuilder();
        }

    }
}

void GamePlayScene::onHouseBuilderClicked(cocos2d::Ref* sender)
{

    _selectedTypeOfTower = static_cast<HouseBuilder*>(sender)->_typeOfTower;//static_cast<HouseBuilder *>(sender);
    buildTower(_selectedCastle);
}

void GamePlayScene::buildTower(Castle *castle)
{
    std::string nameOfSchedule = "generate_soldier_"+ std::to_string(_selectedCastleConvertToNumber);
    castle->unschedule(nameOfSchedule);
    castle->schedule([=](float dt_) {
        generateSoldier(castle);
        }, TIME_SPAW, nameOfSchedule);

    if (castle) {
        auto widthOfCastle = castle->getContentSize().width;
        auto  heightOfCastle = castle->getContentSize().height;
        std::vector<std::string> pathOfTower = { "Ui-Map/Group 1 copy 2.png","Ui-Map/Group 1 copy 5.png","Ui-Map/Group 1 copy.png","Ui-Map/Group 1-1.png" };
        std::vector<Point> pointPositonOf4Tower = { Vec2(0,0), Vec2(widthOfCastle / 2,0), Vec2(castle->getContentSize() / 2), Vec2(0,heightOfCastle / 2) };

        ImageView* tower = ImageView::create(pathOfTower.at(_selectedTypeOfTower - 1));
        tower->setContentSize(castle->getContentSize() / 4);
        if (castle->_numberTower < MAX_TOWER_IN_A_CASTLE) {
            if (_selectedTypeOfTower == 1) {
                castle->_tower1 = true;
            }
            if (_selectedTypeOfTower == 2) {
                castle->_tower2 = true;
            }
            tower->setPosition(pointPositonOf4Tower.at(castle->_numberTower));
            castle->_numberTower++;
            castle->addChild(tower, 11);
        }
    }
}

void GamePlayScene::generateSoldier(Castle* castle)
{  //bot 2 = Vec2(soldier->getPosition().x + soldier->getContentSize().width + MARGIN_TOWER_WITH_SOLDIER, soldier->getPosition().y + soldier->getContentSize().height + MARGIN_TOWER_WITH_SOLDIER)
    auto soldier = Soldier::createSoldier("");
    soldier->setContentSize(castle->getContentSize() / 10);

    auto p1 = Point(castle->getPosition().x + castle->getContentSize().width / 2 + MARGIN_TOWER_WITH_SOLDIER, castle->getPosition().y - MARGIN_TOWER_WITH_SOLDIER);
    auto p2 = Point(p1.x + soldier->getContentSize().width     + MARGIN_TOWER_WITH_SOLDIER, p1.y + soldier->getContentSize().height     + MARGIN_TOWER_WITH_SOLDIER);
    auto p3 = Point(p1.x + soldier->getContentSize().width * 2 + MARGIN_TOWER_WITH_SOLDIER, p1.y + soldier->getContentSize().height * 2 + MARGIN_TOWER_WITH_SOLDIER);
    auto p4 = Point(p1.x + soldier->getContentSize().width * 3 + MARGIN_TOWER_WITH_SOLDIER, p1.y + soldier->getContentSize().height * 3 + MARGIN_TOWER_WITH_SOLDIER);

    std::vector<Point> pointPositonOfSoldier = {p1,p2,p3,p4};

    if (castle->_tower1) {
        if (castle->_numberSoldier1 < MAX_TYPE_OF_SOLDIER) {
            if (castle->_numberSoldier1 == 1) {
                auto soldier = Soldier::createSoldier("Ui-Map/troops-unpack/1-idle-front-1.png");//1
                soldier->setContentSize(castle->getContentSize() / 10);
                soldier->setPosition(p2);
                this->addChild(soldier, 4);
                castle->listSoldier.push_back(soldier);
                castle->_numberSoldier1++;
            }
            if (castle->_numberSoldier1 == 0) {
                auto soldier = Soldier::createSoldier("Ui-Map/troops-unpack/1-idle-front-1.png");//1
                soldier->setContentSize(castle->getContentSize() / 10);
                soldier->setPosition(p1);
                this->addChild(soldier, 4);
                castle->listSoldier.push_back(soldier);
                castle->_numberSoldier1++;

            }
        }
    }

    if (castle->_tower2) {
        if (castle->_numberSoldier2 < MAX_TYPE_OF_SOLDIER) {
            if (castle->_numberSoldier2 == 1) {
                auto soldier = Soldier::createSoldier("Ui-Map/troops-unpack/2-walk-front-1.png");//1
                soldier->setContentSize(castle->getContentSize() / 10);
                soldier->setPosition(p4);
                this->addChild(soldier, 4);
                castle->listSoldier.push_back(soldier);
                castle->_numberSoldier2++;
            }
            if (castle->_numberSoldier2 == 0) {
                auto soldier = Soldier::createSoldier("Ui-Map/troops-unpack/2-walk-front-1.png");//1
                soldier->setContentSize(castle->getContentSize() / 10);
                soldier->setPosition(p3);
                this->addChild(soldier, 4);
                castle->listSoldier.push_back(soldier);
                castle->_numberSoldier2++;
            }
        }
    }

}

void GamePlayScene::onMouseDown(Event* event)
{
    _mouseEventOneTimeClickDown = true;
    EventMouse* e = (EventMouse*)event;
    CCLOG("----------onMouseDown x: %f - y: %f ---------------", e->getCursorX(), e->getCursorY());
    _startPoint = Point(e->getCursorX(), e->getCursorY());

}

void GamePlayScene::onMouseMove(Event* event) {
    EventMouse* e = (EventMouse*)event;
    CCLOG("x: %f - y: %f ", e->getCursorX(), e->getCursorY());
}

void GamePlayScene::onMouseUp(Event* event) {
    if (_mouseEventOneTimeClickDown) {
        _mouseEventOneTimeClickDown = false;
    }
    EventMouse* e = (EventMouse*)event;
    CCLOG("----------onMouseUp x: %f - y: %f ---------------", e->getCursorX(), e->getCursorY());
    _endPoint = Point(e->getCursorX(), e->getCursorY());
    if (_startPoint.x != _endPoint.x || _startPoint.y != _endPoint.y) {
        checkCastleStartAndEnd();
        if (_castleDefend !=NULL && _castleAttack != NULL) {
            if (_castleAttack->listSoldier.size() > 0) {
                MoveSoldier();

            }
            CCLOG("_castleAttack %d", _castleAttack->getTag());
            CCLOG("_castleDefend %d", _castleDefend->getTag());
        }

    }
    else {
        for (auto castle : vectorCastle) {
            if (castle->getBoundingBox().containsPoint(_startPoint)) {
                return;
            }         
        }
        HouseBuilder::getInstance()->hideHouseBuilder();
    }
}

void GamePlayScene::checkCastleStartAndEnd()
{
    for (auto castle : vectorCastle) {
        if (castle->getBoundingBox().containsPoint(_startPoint)) {
            _castleAttack = castle;
        }
    }
    for (auto castle : vectorCastle) {
        if (castle->getBoundingBox().containsPoint(_endPoint)) {
            _castleDefend = castle;
        }
    }
}

void GamePlayScene::MoveSoldier()
{
    for (auto x : _castleAttack->listSoldier) {
        if (_castleAttack->getPosition().y > _castleDefend->getPosition().y) {
            if (_castleAttack->getPosition().x > _castleDefend->getPosition().x) {
                x->setRotation3D(Vec3(-180, 0, 0));
            }
            else {
                //x->setRotation3D(Vec3(-180, 0, 0));
            }
            Animate* animate = Animate::create(AnimationCache::getInstance()->getAnimation("soilder1AnimationFront"));
            x->getSoilderSprite()->runAction(animate);
            x->runAction(Sequence::create(
                MoveBy::create(5, Vec2(_castleDefend->getPosition().x - _castleAttack->getPosition().x, _castleDefend->getPosition().y - _castleAttack->getPosition().y)),
                [=]() {
                },
                NULL));
        }
        else {
            if (_castleAttack->getPosition().x > _castleDefend->getPosition().x) {
                x->setRotation3D(Vec3(0, 180, 0));
            }
            else {
                x->setRotation3D(Vec3(0,-360,0));
            }

                Animate* animate = Animate::create(AnimationCache::getInstance()->getAnimation("soilder1AnimationBack"));
                x->getSoilderSprite()->runAction(animate);
                x->runAction(Sequence::create(
                    MoveBy::create(5, Vec2(_castleDefend->getPosition().x - _castleAttack->getPosition().x, _castleDefend->getPosition().y - _castleAttack->getPosition().y)),
                    [=]() {
                    },
                    NULL));
            
        }
        
    }

}
void GamePlayScene::loadAnimation()
{
    //animation1  Back
    auto soilder1AnimationBack = Animation::create();
    soilder1AnimationBack->setDelayPerUnit(0.15f);
    soilder1AnimationBack->setLoops(-1);

    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-1.png")->getSpriteFrame());
    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-2.png")->getSpriteFrame());
    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-3.png")->getSpriteFrame());
    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-4.png")->getSpriteFrame());
    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-1.png")->getSpriteFrame());
    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-2.png")->getSpriteFrame());
    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-3.png")->getSpriteFrame());
    soilder1AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-back-4.png")->getSpriteFrame());

    AnimationCache::getInstance()->addAnimation(soilder1AnimationBack, "soilder1AnimationBack");

    //animation1 front
    auto soilder1AnimationFront = Animation::create();
    soilder1AnimationFront->setDelayPerUnit(0.15f);
    soilder1AnimationFront->setLoops(-1);

    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-1.png")->getSpriteFrame());
    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-2.png")->getSpriteFrame());
    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-3.png")->getSpriteFrame());
    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-4.png")->getSpriteFrame());
    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-1.png")->getSpriteFrame());
    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-2.png")->getSpriteFrame());
    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-3.png")->getSpriteFrame());
    soilder1AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/1-walk-front-4.png")->getSpriteFrame());

    AnimationCache::getInstance()->addAnimation(soilder1AnimationFront, "soilder1AnimationFront");


    //animation2 back
    auto soilder2AnimationBack = Animation::create();
    soilder2AnimationBack->setDelayPerUnit(0.15f);
    soilder2AnimationBack->setLoops(1/4);

    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-1.png")->getSpriteFrame());
    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-2.png")->getSpriteFrame());
    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-3.png")->getSpriteFrame());
    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-3.png")->getSpriteFrame());
    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-1.png")->getSpriteFrame());
    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-2.png")->getSpriteFrame());
    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-3.png")->getSpriteFrame());
    soilder2AnimationBack->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-back-3.png")->getSpriteFrame());

    AnimationCache::getInstance()->addAnimation(soilder2AnimationBack, "soilder2AnimationBack");

    //animation2 back
    auto soilder2AnimationFront = Animation::create();
    soilder2AnimationFront->setDelayPerUnit(0.15f);
    soilder2AnimationFront->setLoops(1/4);

    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-1.png")->getSpriteFrame());
    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-2.png")->getSpriteFrame());
    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-3.png")->getSpriteFrame());
    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-4.png")->getSpriteFrame());
    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-1.png")->getSpriteFrame());
    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-2.png")->getSpriteFrame());
    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-3.png")->getSpriteFrame());
    soilder2AnimationFront->addSpriteFrame(Sprite::create("Ui-Map/troops-unpack/2-walk-front-4.png")->getSpriteFrame());

    AnimationCache::getInstance()->addAnimation(soilder2AnimationFront, "soilder2AnimationFront");
}



