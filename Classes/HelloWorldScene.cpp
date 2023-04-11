#include "Headers.h"

//#include "extensions/GUI/CCScrollView/CCScrollView.h"

USING_NS_CC;

using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    scalefactorx=visibleSize.width/768;
    scalefactory=visibleSize.height/1024;
    
    //==========================================================================//
    
    //==========================================================================//
    
    
    
    main_bg=Sprite::create("mainscreen_bg.png");
    main_bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    main_bg->setScaleX(scalefactorx);
    main_bg->setScaleY(scalefactory);
    this->addChild(main_bg);
    
    Title_1=Sprite::create("mainscreen_title.png");
    Title_1->setPosition(Vec2(visibleSize.width/768*384, visibleSize.height/1024*(820)));
    Title_1->setScaleX(scalefactorx);
    Title_1->setScaleY(scalefactory);
    this->addChild(Title_1,5);
    
    play_btn=Sprite::create("Play_BTN.png");
    play_btn->setPosition(Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(350)));
    play_btn->setScaleX(scalefactorx);
    play_btn->setScaleY(scalefactory);
    this->addChild(play_btn,5);
    
    more_btn=Sprite::create("More_BTN.png");
    more_btn->setPosition(Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(250)));
    more_btn->setScaleX(scalefactorx);
    more_btn->setScaleY(scalefactory);
    this->addChild(more_btn,5);
    
    rate_btn=Sprite::create("Rate_BTN.png");
    rate_btn->setPosition(Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(150)));
    rate_btn->setScaleX(scalefactorx);
    rate_btn->setScaleY(scalefactory);
    this->addChild(rate_btn,5);
    
    //==========================================================================//
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //==========================================================================//
    
    
    return true;
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
        
        AdCall_Jni::BackButtonClicked();
    }
}



bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    touchPoint = convertToNodeSpace(touchPoint);
    
    
    if (play_btn->getBoundingBox().containsPoint(touchPoint))
    {
        if (MUSIC==1)
        {
            SimpleAudioEngine::getInstance()->playEffect("Click_1.mp3");
        }
        
        play_btn->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scalefactorx,0.8*scalefactory),
                                             ScaleTo::create(0.2, 1.0*scalefactorx,1.0*scalefactory),NULL));
        
        auto scene1 = Play_Scene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene1));
    }
    
    if (more_btn->getBoundingBox().containsPoint(touchPoint))
    {
        if (MUSIC==1)
        {
            SimpleAudioEngine::getInstance()->playEffect("Click_3.mp3");
        }
        
        more_btn->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scalefactorx,0.8*scalefactory),
                                                  ScaleTo::create(0.2, 1.0*scalefactorx,1.0*scalefactory),NULL));
        
        AdCall_Jni::MoreGame();
        
    }
    
    if (rate_btn->getBoundingBox().containsPoint(touchPoint))
    {
        if (MUSIC==1)
        {
            SimpleAudioEngine::getInstance()->playEffect("Click_3.mp3");
        }
        
        rate_btn->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scalefactorx,0.8*scalefactory),
                                                ScaleTo::create(0.2, 1.0*scalefactorx,1.0*scalefactory),NULL));
        
        AdCall_Jni::RateGame();
    }
    
    return true;
}


void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    touchPoint = convertToNodeSpace(touchPoint);
    
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    touchPoint = convertToNodeSpace(touchPoint);
    
    CCLOG("x==>%f,y==>%f",touchPoint.x,touchPoint.y);
    
}


//void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
//{
//    cocos2d::log("touch cancelled");
//}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
