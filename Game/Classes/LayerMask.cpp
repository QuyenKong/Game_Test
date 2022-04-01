#include "LayerMask.h"
#define MARGIN_ITEM Director::getInstance()->getVisibleSize().width/12
#define MARGIN_RIGHT 50
#define MARGIN_BOTTOM 30

LayerMask* LayerMask::createLayerMask()
{
    auto layer = new LayerMask();
    if (layer) {
        layer->autorelease();
        layer->loadLayerMask();
        return layer;
    }
    return nullptr;
}

void LayerMask::hideLayerMask()
{
    this->setVisible(false);
}

void LayerMask::loadLayerMask()
{
    //----------------Background LayerMask-----------------
    this->setContentSize(Director::getInstance()->getVisibleSize());
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->setPosition((Director::getInstance()->getVisibleSize() / 2));

    ImageView* logo = ImageView::create("Ui-Map/Layer 11.png");
    logo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    logo->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height*0.9 ));
    this->addChild(logo);

    ImageView* inforLeft = ImageView::create("Ui-Map/Group 17.png");
    inforLeft->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    inforLeft->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2-  MARGIN_ITEM, Director::getInstance()->getVisibleSize().height * 0.9));
    this->addChild(inforLeft);

    ImageView* inforRight = ImageView::create("Ui-Map/Group 2.png");
    inforRight->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    inforRight->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 +MARGIN_ITEM, Director::getInstance()->getVisibleSize().height * 0.9));
    this->addChild(inforRight);

    //---------score -------
    ImageView* scoreBorder = ImageView::create("Ui-Map/Rounded Rectangle 1.png");
    scoreBorder->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    scoreBorder->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - MARGIN_RIGHT, Director::getInstance()->getVisibleSize().height * 0.95));
    this->addChild(scoreBorder);

    ImageView* score = ImageView::create("Ui-Map/60_60.png");
    score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    score->setPosition(scoreBorder->getContentSize()/2);
    scoreBorder->addChild(score);

    //----------- type of soilder---------

    ImageView* soilder1 = ImageView::create("Ui-Map/Group 1.png");
    soilder1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    soilder1->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - MARGIN_RIGHT, Director::getInstance()->getVisibleSize().height * 0.8));
    this->addChild(soilder1);

    ImageView* soilder2 = ImageView::create("Ui-Map/Group 1 copy4.png");
    soilder2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    soilder2->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - MARGIN_RIGHT, Director::getInstance()->getVisibleSize().height * 0.7- MARGIN_BOTTOM));
    this->addChild(soilder2);

    ImageView* soilder3 = ImageView::create("Ui-Map/Group 1 copy3.png");
    soilder3->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    soilder3->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - MARGIN_RIGHT, Director::getInstance()->getVisibleSize().height * 0.6- MARGIN_BOTTOM*2));
    this->addChild(soilder3);

    //--------status--------

    ImageView* status = ImageView::create("Ui-Map/load.png");
    status->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    status->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - MARGIN_RIGHT, Director::getInstance()->getVisibleSize().height * 0.35 - MARGIN_BOTTOM * 3));
    this->addChild(status);


    ImageView* number100 = ImageView::create("Ui-Map/100_.png");
    number100->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    number100->setPosition(Vec2(status->getPosition().x - number100->getContentSize().width, status->getPosition().y + status->getContentSize().height / 2));
    this->addChild(number100);

    ImageView* number50 = ImageView::create("Ui-Map/50_.png");
    number50->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    number50->setPosition(Vec2(status->getPosition().x - number100->getContentSize().width, status->getPosition().y));
    this->addChild(number50);

    ImageView* number1 = ImageView::create("Ui-Map/1_.png");
    number1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    number1->setPosition(Vec2(status->getPosition().x- number100->getContentSize().width, status->getPosition().y - status->getContentSize().height / 2));
    this->addChild(number1);

    ImageView* sword = ImageView::create("Ui-Map/sword.png");
    sword->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sword->setPosition(Vec2(status->getPosition().x- sword->getContentSize().width/2, status->getPosition().y - status->getContentSize().height / 2 + status->getContentSize().height / 4));
    this->addChild(sword);
    
}
