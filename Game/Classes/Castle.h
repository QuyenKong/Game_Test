#ifndef Castle_hpp
#define Castle_hpp

#include "Soldier.h"
#include "cocos2d.h"
#include "2d/CCNode.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class Castle_Delegate {
public:
	virtual void onCastleClicked(cocos2d::Ref* sender) {};
};

class Castle: public Layout {
public:
	int _numberTower = 0;
	bool _tower1 = false;
	bool _tower2 = false;

	int _numberSoldier1 = 0;
	int _numberSoldier2 = 0;
	std::vector<Soldier*> listSoldier;

	static Castle* CreateCastle(std::string path);
	void setDelegate(Castle_Delegate* delegate);
private:
	cocos2d::ui::Layout* _touchLayout;
	ImageView* _castle;
	Castle_Delegate* _delegate = nullptr;

	void onClickItem(Ref* sender);
	void loadCastle(std::string path);

};
#endif /* Castle_hpp_hpp */