#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    cocos2d::Point touchPoint;
    cocos2d::Size visibleSize;
    
    float scalefactorx;
    float scalefactory;
    
    //cocos2d::Director::getInstance()->purgeCachedData();
    
    virtual bool init();
    
    //=========== Sprites ===========//
    
    cocos2d::Sprite *main_bg;
    cocos2d::Sprite *Title_1;
    cocos2d::Sprite *Title_2;
    
    //=========== Buttons ===========//
 
    cocos2d::Sprite *play_btn;
    
    cocos2d::Sprite *more_btn;
    cocos2d::Sprite *rate_btn;
    
    //=========== Methods ===========//
    
    void play_method();
    
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
private:
    cocos2d::Label* labelTouchInfo;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
