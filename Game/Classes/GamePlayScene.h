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

#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include <cocos/editor-support/cocostudio/WidgetCallBackHandlerProtocol.h>
#include <castle.h>
#include <HouseBuilder.h>

class GamePlayScene : public cocos2d::Scene,cocostudio::WidgetCallBackHandlerProtocol,Castle_Delegate, HouseBuilder_Delegate
{
private:
public:
    cocos2d::ui::Layout* _mainLayout;
    static GamePlayScene* createGamePlayScene();

    virtual bool init();

    void onCastleClicked(cocos2d::Ref* sender) override;

    void onHouseBuilderClicked(cocos2d::Ref* sender) override;

    void buildTower(Castle* castle);

    void generateSoldier(Castle* castle);

    Castle* _selectedCastle;
    Castle* _castle1;
    Castle* _castle2;
    Castle* _castle3;
    Castle* _castle4;
    std::vector< Castle*> vectorCastle;

    Castle* _castleAttack;
    Castle* _castleDefend;

    int _selectedCastleConvertToNumber;
    int _selectedTypeOfTower;
    bool _mouseEventOneTimeClickDown;
    bool _mouseEventOneTimeClickUP =false;
    Point _startPoint;
    Point _endPoint;

    void onMouseDown(Event* event);

    void onMouseMove(Event* event);

    void onMouseUp(Event* event);

    void checkCastleStartAndEnd();

    void MoveSoldier();

    void loadAnimation();

    CREATE_FUNC(GamePlayScene);
};

#endif // __GAMEPLAY_SCENE_H__
