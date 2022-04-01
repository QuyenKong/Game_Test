#pragma once
#ifndef LayerMask_hpp
#define LayerMask_hpp

#include "cocos2d.h"
#include <cocos/ui/UIImageView.h>
#include "2d/CCNode.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class LayerMask: Layer
{
public:
	static LayerMask* createLayerMask();
	void hideLayerMask();
private:
	void loadLayerMask();


};

#endif /* LayerMask_hpp_hpp */