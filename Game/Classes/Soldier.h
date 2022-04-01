#ifndef Soldier_hpp
#define Soldier_hpp

#include "cocos2d.h"
#include "2d/CCNode.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;


class  Soldier :public Layout {
public:
	static Soldier* createSoldier(std::string path);
	int _currentRotate;
	int _nextRotate;
	Sprite* getSoilderSprite();
private:
	Sprite* _soilderSprite;


	void loadSoldier(std::string path);
};
#endif /* Soldier_hpp */