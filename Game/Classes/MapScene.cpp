#include "MapScene.h"

MapScene* MapScene::createMap(std::string s)
{
    auto  tileMap =(MapScene*)(TMXTiledMap::create(s));
    if (tileMap) {
        tileMap->loadMap();

        return tileMap;
    }
    return nullptr;
}

void MapScene::loadMap()
{
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->setPosition(Director::getInstance()->getVisibleSize() / 2);
}
