#include "Headers.h"

USING_NS_CC;

using namespace CocosDenshion;

int MUSIC=1;

int SELECTED_LEVEL=1;

int ONE_TIME_LOAD=0;

int LOGO_ARE=1;

int CURRENT_STEP=1;

int COIN_STORE=250;

int MAX_DATA=0;

int LOAD_ADD=0;

int R_C=0;
int G_C=0;
int B_C=0;
int F_SIZE=0;

unsigned int VocalSound;

static cocos2d::Size designResolutionSize = cocos2d::Size(768, 1024);


AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
    
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // set design size with fixed width
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(768, 1024, ResolutionPolicy::FIXED_HEIGHT);
    
    //
    //    if(Director::getInstance()->getVisibleSize().width >= 600 && Director::getInstance()->getVisibleSize().width <= 800)
    //    {
    //        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    //    }
    //
    //    else if(Director::getInstance()->getVisibleSize().width >= 950 && Director::getInstance()->getVisibleSize().width <= 1100)
    //    {
    //         director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    //    }
    //
    //    else if(Director::getInstance()->getVisibleSize().width >= 825 && Director::getInstance()->getVisibleSize().width <= 925)
    //    {
    //        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    //    }
    
    
    ONE_TIME_LOAD= cocos2d::UserDefault::getInstance()->getIntegerForKey("ONE_TIME_LOAD_KEY");
    
    if (ONE_TIME_LOAD==0)
    {
        ONE_TIME_LOAD=1;
        cocos2d::UserDefault::getInstance()->setIntegerForKey("ONE_TIME_LOAD_KEY", ONE_TIME_LOAD);
        cocos2d::UserDefault::getInstance()->flush();
        
        ValueMap Coin_Map = FileUtils::getInstance()->getValueMapFromFile("Color_Code.plist");
        COIN_STORE = Coin_Map.at("Total_Coin").asInt();
        
        cocos2d::UserDefault::getInstance()->setIntegerForKey("COIN_STORE_KEY", COIN_STORE);
        cocos2d::UserDefault::getInstance()->flush();
        
        
        cocos2d::UserDefault::getInstance()->setIntegerForKey("CURRENT_STEP_KEY", CURRENT_STEP);
        cocos2d::UserDefault::getInstance()->flush();
        
    }
    
    COIN_STORE = cocos2d::UserDefault::getInstance()->getIntegerForKey("COIN_STORE_KEY");
    CURRENT_STEP = cocos2d::UserDefault::getInstance()->getIntegerForKey("CURRENT_STEP_KEY");
    
    
    
    register_all_packages();
    
    if (MUSIC==1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BG.mp3", true);
    }
    
    ValueMap PData_1 = FileUtils::getInstance()->getValueMapFromFile("Logo_Img.plist");
    MAX_DATA=PData_1.size();
    
    ValueMap RGB_Map = FileUtils::getInstance()->getValueMapFromFile("Color_Code.plist");
    
    R_C = RGB_Map.at("R").asInt();
    G_C = RGB_Map.at("G").asInt();
    B_C = RGB_Map.at("B").asInt();
    
    F_SIZE = RGB_Map.at("Font_Size").asInt();
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    
    if(MUSIC==1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    }
}
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    
    if(MUSIC==1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    }
}

