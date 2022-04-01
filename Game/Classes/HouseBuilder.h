#ifndef HouseBuilder_hpp
#define HouseBuilder_hpp

#include "cocos2d.h"
#include <cocos/ui/UIImageView.h>
#include "2d/CCNode.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;
class HouseBuilder_Delegate {
public:
	virtual void onHouseBuilderClicked(cocos2d::Ref* sender) {};
};

class HouseBuilder : Layout {
public:
	static HouseBuilder* getInstance();
	static HouseBuilder* createHouseBuilder();
	void hideHouseBuilder();
	void showHouseBuilder();
	float getHeight();
	void setDelegate(HouseBuilder_Delegate* delegate);

	bool _isShowing =true;
	int _typeOfTower = 0;
private:
	ImageView* _bgBorder;
	static HouseBuilder* _houseBuilder;
	HouseBuilder_Delegate* _delegate;

	void loadHouseBuilder();

};
#endif /* HouseBuilder_hpp */