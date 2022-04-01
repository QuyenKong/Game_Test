#ifndef MapScene_hpp
#define MapScene_hpp

#include "cocos2d.h"
#include "2d/CCNode.h"
using namespace cocos2d;
class MapScene : public Layer {
public:
	static MapScene* createMap(std::string s);

private:
	void loadMap();

}; 

#endif /* MapScene_hpp */