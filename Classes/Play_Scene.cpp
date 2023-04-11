#include "Headers.h"
using namespace cocos2d;
using namespace CocosDenshion;

USING_NS_CC;
bool Play_Scene::reward = false;


extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_coinReward(JNIEnv* env, jobject thiz);
};


JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_coinReward(JNIEnv* env, jobject thiz)
{
    CCLOG("**** sExported JNI method called in  C++ +++++ ");
    Play_Scene::reward = true;
    CCLOG("**** sExported JNI method called in  C++ +++++ after ");
    
}
Scene* Play_Scene::createScene()
{
    Scene *scene = Scene::create();
    Play_Scene *layer = Play_Scene::create();
    scene->addChild(layer);
    return scene;
}

bool Play_Scene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(Play_Scene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    IS_TOUCH=true;
    
    REMOVE_BTN=true;
    NAME_BTN=true;
    
    CHAR_X=85;
    CHAR_Y=250;
    
    NAME_X=140;
    NAME_Y=450;
    
    STORE_TMP=0;
    LOOP_TMP=0;
    
    NT_STORE=0;
    RED_COUNT=0;
    
    COUNT=0;
    
    HINT_USE_ARE=0;
    Hint_TMP=0;
    
    IS_HINT_1=false;
    IS_HINT_2=false;
    
    ValueMap Coin_Map = FileUtils::getInstance()->getValueMapFromFile("Color_Code.plist");
    
    ADS_COIN_PLUS = Coin_Map.at("Show_ADS").asInt();
    HINT1_COIN_PLUS = Coin_Map.at("Hint_Use_1").asInt();
    HINT2_COIN_PLUS = Coin_Map.at("Hint_Use_2").asInt();
    COMP_COIN_PLUS = Coin_Map.at("Comp_Coin").asInt();
    
    for (int i=0; i<14; i++)
    {
        IS_ALPHA[i]=0;
        IS_BLANK[i]=false;
        IS_NAME[i]=0;
        RMV_LOOP[i]=false;
        RMV_2[i]=false;
        COMP_ARRAY[i]=false;
        STORE_STR[i]="";
        STR_STR[i]="";
    }
    
    //==============================================================
    
    PD_0 = FileUtils::getInstance()->getValueMapFromFile("Logo_Img.plist");
    
    PA_1 = PD_0.at(StringUtils::format("STEP_%d",CURRENT_STEP)).asValueVector();
    
    CHAR_IS = PA_1.at(0).asString();
    IMAGE_1 = PA_1.at(1).asString();
    IMAGE_2 = PA_1.at(2).asString();
    IMAGE_3 = PA_1.at(3).asString();
    IMAGE_4 = PA_1.at(4).asString();
    
    CCLOG("Name is = %s ",CHAR_IS.c_str());
    
    std::string text = CHAR_IS;
    for(size_t i = 0,k = 0; i < text.length();)
    {
        int cplen = 1;
        if((text[i] & 0xf8) == 0xf0) cplen = 4;
        else if((text[i] & 0xf0) == 0xe0) cplen = 3;
        else if((text[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > text.length()) cplen = 1;
        CCLOG("Char is = %s ",text.substr(i, cplen).c_str());
        CHAR_ARRAY[k++] = text.substr(i, cplen);
        // std::cout << text.substr(i, cplen) << "\n";
        i += cplen;
    }
    
    
    
    
    std::size_t Slength = 0;
    for (char c : CHAR_IS) {
        if ((c & 0xC0) != 0x80) {
            ++Slength;
        }
    }
    
    
    MAX_BLANK = Slength;
//    CCLOG("Length is = %d ",MAX_BLANK);
    
    if (MAX_BLANK==3)
    {
        NAME_X=284;
    }
    else if (MAX_BLANK==4)
    {
        NAME_X=230;
    }
    else if (MAX_BLANK==5)
    {
        NAME_X=185;
    }
    else if (MAX_BLANK==6)
    {
        NAME_X=140;
    }
    else
    {
        NAME_X=85;
    }
    
    for (int i=0; i<14; i++)
    {
        if (i<MAX_BLANK)
        {
            NAME_ARRAY[i]=CHAR_ARRAY[i];
        }
        else
        {
            PD_1 = FileUtils::getInstance()->getValueMapFromFile("Alphabets.plist");
            
            int Lower_Val = 1;
            int Upper_Val = PD_1.size();
            int ALFA_VAL = Lower_Val + arc4random() % (Upper_Val - Lower_Val);
            
            CHAR_IS = PD_1.at(StringUtils::format("Alphabets_%d",ALFA_VAL)).asString();
            CHAR_ARRAY[i]=CHAR_IS;
        }
        
    }
    
    
    std::random_shuffle(std::begin(CHAR_ARRAY), std::end(CHAR_ARRAY));
    for (int i=0; i< 14; i++)
    {
        RAND_ARRAY[i]=CHAR_ARRAY[i];
//        CCLOG("Rand SEQ -->  %s",RAND_ARRAY[i].c_str());
    }
    
    
    //====================== Ads ==================================//
    
    //============================================================//
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    scaleFactorx=visibleSize.width/768;
    scaleFactory=visibleSize.height/1024;
    
    BG=Sprite::create("playscreen_bg.png");
    BG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    BG->setScale(scaleFactorx,scaleFactory);
    this->addChild(BG);
    
    BG_frame=Sprite::create("Top_Frame.png");
    BG_frame->setAnchorPoint(Vec2(0.5,1.0));
    BG_frame->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(1024)));
    BG_frame->setScale(scaleFactorx,scaleFactory);
    this->addChild(BG_frame);
    
    LOGO_BG=Sprite::create("LOGO_BG.png");
    LOGO_BG->setPosition(Vec2(visibleSize.width/768*384,visibleSize.height/1024*710));
    LOGO_BG->setScale(scaleFactorx,scaleFactory);
    this->addChild(LOGO_BG);
//    LOGO_BG->setOpacity(100);
    
    LOGO_1=Sprite::create(IMAGE_1);
    LOGO_1->setAnchorPoint(Vec2(1.0,0.0));
    LOGO_1->setPosition(Vec2(visibleSize.width/768*379,visibleSize.height/1024*715));
    LOGO_1->setScale(scaleFactorx,scaleFactory);
    this->addChild(LOGO_1,5);
    
    LOGO_2=Sprite::create(IMAGE_2);
    LOGO_2->setAnchorPoint(Vec2(0.0,0.0));
    LOGO_2->setPosition(Vec2(visibleSize.width/768*389,visibleSize.height/1024*715));
    LOGO_2->setScale(scaleFactorx,scaleFactory);
    this->addChild(LOGO_2,5);
    
    LOGO_3=Sprite::create(IMAGE_3);
    LOGO_3->setAnchorPoint(Vec2(1.0,1.0));
    LOGO_3->setPosition(Vec2(visibleSize.width/768*379,visibleSize.height/1024*705));
    LOGO_3->setScale(scaleFactorx,scaleFactory);
    this->addChild(LOGO_3,5);
    
    LOGO_4=Sprite::create(IMAGE_4);
    LOGO_4->setAnchorPoint(Vec2(0.0,1.0));
    LOGO_4->setPosition(Vec2(visibleSize.width/768*389,visibleSize.height/1024*705));
    LOGO_4->setScale(scaleFactorx,scaleFactory);
    this->addChild(LOGO_4,5);
    
    BACK_BTN=Sprite::create("BACK_BTN.png");
    BACK_BTN->setPosition(Vec2(visibleSize.width/768*60,visibleSize.height/1024*975));
    BACK_BTN->setScale(scaleFactorx,scaleFactory);
    this->addChild(BACK_BTN,5);
    
    for (int i=0; i<MAX_BLANK; i++)
    {
        Hide_Name_Box[i]=Sprite::create("Blank_Box.png");
        Hide_Name_Box[i]->setPosition(Vec2(visibleSize.width/768*(NAME_X),visibleSize.height/1024*(NAME_Y)));
        Hide_Name_Box[i]->setScale(scaleFactorx,scaleFactory);
        this->addChild(Hide_Name_Box[i],4);
        
        Show_Hint_Char[i] = Label::createWithTTF(StringUtils::format("%s",NAME_ARRAY[i].c_str()),"arial.ttf", 60);
        Show_Hint_Char[i]->setPosition(Vec2(visibleSize.width/768*(NAME_X),visibleSize.height/1024*(NAME_Y)));
        Show_Hint_Char[i]->setScale(scaleFactorx,scaleFactory);
        this->addChild(Show_Hint_Char[i],4);
        Show_Hint_Char[i]->setOpacity(0);
        
        NAME_X=NAME_X+100;
        
        if (i==6)
        {
            NAME_X=85;
            NAME_Y=NAME_Y-100;
        }
    }
    
    for (int i=0; i<14; i++)
    {
        Hide_Char_Box[i]=Sprite::create("Name_Box.png");
        Hide_Char_Box[i]->setPosition(Vec2(visibleSize.width/768*(CHAR_X),visibleSize.height/1024*(CHAR_Y)));
        Hide_Char_Box[i]->setScale(scaleFactorx,scaleFactory);
        this->addChild(Hide_Char_Box[i],5);
        
        Disable_Box[i]=Sprite::create("Name_Box.png");
        Disable_Box[i]->setPosition(Vec2(visibleSize.width/768*(CHAR_X),visibleSize.height/1024*(CHAR_Y)));
        Disable_Box[i]->setScale(scaleFactorx,scaleFactory);
        Disable_Box[i]->setVisible(false);
        this->addChild(Disable_Box[i],5);
        
        Alphabet[i] = Label::createWithTTF(StringUtils::format("%s",CHAR_ARRAY[i].c_str()),"arial.ttf", 60);
        Alphabet[i]->setPosition(Vec2(visibleSize.width/768*(CHAR_X),visibleSize.height/1024*(CHAR_Y)));
        Alphabet[i]->setScale(scaleFactorx,scaleFactory);
        Alphabet[i]->setColor(Color3B(0,0,0));
        this->addChild(Alphabet[i],5);
        
        CHAR_X=CHAR_X+100;
        
        if (i==6)
        {
            CHAR_X=85;
            CHAR_Y=CHAR_Y-100;
        }
    }
    
    Name_Hint=Sprite::create("Name_Hint_BTN.png");
    Name_Hint->setAnchorPoint(Vec2(1.0,0.5));
    Name_Hint->setPosition(Vec2(visibleSize.width/768*768,visibleSize.height/1024*610));
    Name_Hint->setScale(scaleFactorx,scaleFactory);
    this->addChild(Name_Hint,5);
    
    Hint_2_lbl = Label::createWithTTF((StringUtils::format("%d",HINT2_COIN_PLUS)),"arial.ttf", 30);
    Hint_2_lbl->setPosition(Vec2(65,35));
    Name_Hint->addChild(Hint_2_lbl);
    
    Remove_Char=Sprite::create("Remove_Char_BTN.png");
    Remove_Char->setAnchorPoint(Vec2(1.0,0.5));
    Remove_Char->setPosition(Vec2(visibleSize.width/768*768,visibleSize.height/1024*810));
    Remove_Char->setScale(scaleFactorx,scaleFactory);
    this->addChild(Remove_Char,5);
    
    Hint_1_lbl = Label::createWithTTF((StringUtils::format("%d",HINT1_COIN_PLUS)),"arial.ttf", 30);
    Hint_1_lbl->setPosition(Vec2(65,35));
    Remove_Char->addChild(Hint_1_lbl);
    
    Free_BTN=Sprite::create("Free_BTN.png");
    Free_BTN->setAnchorPoint(Vec2(0.0,0.5));
    Free_BTN->setPosition(Vec2(visibleSize.width/768*0,visibleSize.height/1024*710));
    Free_BTN->setScale(scaleFactorx,scaleFactory);
    this->addChild(Free_BTN,5);
    
    Best_lvl = Label::createWithTTF(StringUtils::format("%d/%d",CURRENT_STEP,MAX_DATA),"arial.ttf", 50);
    Best_lvl->setPosition(Vec2(visibleSize.width/768*(384) , visibleSize.height/1024*(970) ));
    Best_lvl->setScale(scaleFactorx,scaleFactory);
    this->addChild(Best_lvl,3);
    Best_lvl->setColor(Color3B(R_C,G_C,B_C));
    
    Coin_Frame=Sprite::create("Coin_frame.png");
    Coin_Frame->setPosition(Vec2(visibleSize.width/768*(660),visibleSize.height/1024*(970)));
    Coin_Frame->setScale(scaleFactorx,scaleFactory);
    this->addChild(Coin_Frame,3);
    
    Show_Coin= Label::createWithTTF(StringUtils::format("%d",COIN_STORE),"arial.ttf", 40);
    Show_Coin->setPosition(Vec2(visibleSize.width/768*(690) , visibleSize.height/1024*(970) ));
    Show_Coin->setScale(scaleFactorx,scaleFactory);
    this->addChild(Show_Coin,3);
    Show_Coin->setColor(Color3B(R_C,G_C,B_C));
    
    
    
    
    
#pragma mark - ======== Popup
    
    SHP_Frame=Sprite::create("Popup_Frame_1.png");
    SHP_Frame->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    SHP_Frame->setScale(0.0*scaleFactorx,0.0*scaleFactory);
    this->addChild(SHP_Frame,10);
    
    SHP_Yes=Sprite::create("Popup_Yes.png");
    SHP_Yes->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    SHP_Yes->setScale(0.0*scaleFactorx,0.0*scaleFactory);
    this->addChild(SHP_Yes,10);
    
    SHP_No=Sprite::create("Popup_No.png");
    SHP_No->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    SHP_No->setScale(0.0*scaleFactorx,0.0*scaleFactory);
    this->addChild(SHP_No,10);
    
    
    Info_Frame=Sprite::create("Popup_Frame_2.png");
    Info_Frame->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    Info_Frame->setScale(0.0*scaleFactorx,0.0*scaleFactory);
    this->addChild(Info_Frame,10);
    
    Info_OK=Sprite::create("Popup_Ok.png");
    Info_OK->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    Info_OK->setScale(0.0*scaleFactorx,0.0*scaleFactory);
    this->addChild(Info_OK,10);
    
    
    
    
#pragma mark - ======== Level Screen
    
    LC_BG=Sprite::create("LC_BG.png");
    LC_BG->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    LC_BG->setScale(scaleFactorx,scaleFactory);
    this->addChild(LC_BG,9);
    LC_BG->setOpacity(230);
    
    LC_Coin_frame=Sprite::create("Coin_frame.png");
    LC_Coin_frame->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    LC_Coin_frame->setScale(scaleFactorx,scaleFactory);
    this->addChild(LC_Coin_frame,10);
    
    LC_NAME1= Label::createWithTTF("PERFECT !","arial.ttf", 60);
    LC_NAME1->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    LC_NAME1->setScale(scaleFactorx,scaleFactory);
    this->addChild(LC_NAME1,10);
    LC_NAME1->setColor(Color3B(255,255,255));
    
    LC_COIN = Label::createWithTTF((StringUtils::format("+%d",COMP_COIN_PLUS)),"arial.ttf", 40);
    LC_COIN->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    LC_COIN->setScale(scaleFactorx,scaleFactory);
    this->addChild(LC_COIN,10);
    LC_COIN->setColor(Color3B(255,255,255));
    
    LC_HOME=Sprite::create("Home_BTN.png");
    LC_HOME->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    LC_HOME->setScale(scaleFactorx,scaleFactory);
    this->addChild(LC_HOME,10);
    
    LC_PLAY=Sprite::create("Next_BTN.png");
    LC_PLAY->setPosition(Vec2(visibleSize.width/768*(500000),visibleSize.height/1024*(500000)));
    LC_PLAY->setScale(scaleFactorx,scaleFactory);
    this->addChild(LC_PLAY,10);
    
    
    Play_Scene::HINT_CHECK();
    
    this->scheduleUpdate();
    
    //==========================================================================//
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(Play_Scene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Play_Scene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Play_Scene::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //==========================================================================//
    
    
    
    return true;
}

void Play_Scene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        auto scene1 = HelloWorld::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene1));
    }
}

void Play_Scene::Coin_Rewarded()
{
    
    if(cocos2d::UserDefault::getInstance()->getIntegerForKey("ecoin") == ADS_COIN_PLUS){
        
        CCLOG("I am call now ");
        
        cocos2d::UserDefault::getInstance()->setIntegerForKey("ecoin",0);
        cocos2d::UserDefault::getInstance()->flush();
        
        cocos2d::UserDefault::getInstance()->setIntegerForKey("COIN_STORE_KEY",COIN_STORE+ADS_COIN_PLUS);
        cocos2d::UserDefault::getInstance()->flush();
    }
    else
    {
        CCLOG("I can't call now ");
    }
    Show_Coin->setString(StringUtils::format("%d",COIN_STORE));
}

void Play_Scene::update(float dt)
{
    cocos2d::UserDefault::getInstance()->setIntegerForKey("COIN_STORE_KEY", COIN_STORE);
    cocos2d::UserDefault::getInstance()->flush();
    
    //if this method call ? now it is ok don't comme dd
    if(Play_Scene::reward){
        
        COIN_STORE += ADS_COIN_PLUS;
        
        cocos2d::UserDefault::getInstance()->setIntegerForKey("COIN_STORE_KEY",COIN_STORE);
        cocos2d::UserDefault::getInstance()->flush();
        Play_Scene::reward = false;
        
    }
    
    Show_Coin->setString(StringUtils::format("%d",COIN_STORE));
    Play_Scene::HINT_CHECK();
}

#pragma mark - ======== Method

void Play_Scene::TOUCH_PAUSE()
{
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    
    this->scheduleOnce(schedule_selector(Play_Scene::TOUCH_RESUME), 0.1f);
}

void Play_Scene::TOUCH_RESUME(float dt)
{
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
}

void Play_Scene::HINT_CHECK()
{
    if (COIN_STORE>=HINT2_COIN_PLUS)
    {
        IS_HINT_1=true;
        IS_HINT_2=true;
    }
    else if (COIN_STORE>=HINT1_COIN_PLUS)
    {
        IS_HINT_1=true;
        IS_HINT_2=false;
    }
    else
    {
        IS_HINT_1=false;
        IS_HINT_2=false;
    }
    
}


void Play_Scene::LEVEL_COMPLETE(float dt)
{
    if (MUSIC==1)
    {
        SimpleAudioEngine::getInstance()->playEffect("level_complete.mp3");
    }
    
    LOAD_ADD++;
    if (LOAD_ADD==2)
    {
        AdCall_Jni::showFullScreenAd();
        LOAD_ADD=0;
    }
    
    this->reorderChild(LOGO_BG, 9);
    this->reorderChild(LOGO_1, 9);
    this->reorderChild(LOGO_2, 9);
    this->reorderChild(LOGO_3, 9);
    this->reorderChild(LOGO_4, 9);
    
    for (int i=0; i<MAX_BLANK; i++)
    {
        this->reorderChild(Hide_Name_Box[i], 9);
    }
    
    for (int i=0; i<14; i++)
    {
        if (IS_ALPHA[i]==1)
        {
            Alphabet[i]->setColor(Color3B(0,0,255));
            this->reorderChild(Alphabet[i], 9);
            
            for (int k=0; k<14; k++)
            {
                if (i==k)
                {
                    auto J1 = JumpTo::create(1.0, Alphabet[i]->getPosition(), 10, 1);
                    auto D2 = DelayTime::create(1.0);
                    auto SEQ1 = Sequence::create(J1,D2, NULL);
                    Alphabet[i]->runAction(RepeatForever::create(SEQ1));
                }
            }
            
        }
    }
    
    LC_BG->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(512)));
    LC_Coin_frame->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(250)));
    LC_NAME1->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(960)));
    LC_COIN->setPosition(Vec2(visibleSize.width/768*(410),visibleSize.height/1024*(250)));
    LC_HOME->setPosition(Vec2(visibleSize.width/768*(184),visibleSize.height/1024*(150)));
    LC_PLAY->setPosition(Vec2(visibleSize.width/768*(584),visibleSize.height/1024*(150)));
    
    if (CURRENT_STEP>=MAX_DATA)
    {
        CURRENT_STEP=1;
        cocos2d::UserDefault::getInstance()->setIntegerForKey("CURRENT_STEP_KEY", CURRENT_STEP);
        cocos2d::UserDefault::getInstance()->flush();
    }
    else
    {
        CURRENT_STEP++;
        cocos2d::UserDefault::getInstance()->setIntegerForKey("CURRENT_STEP_KEY", CURRENT_STEP);
        cocos2d::UserDefault::getInstance()->flush();
    }
    
    COIN_STORE=COIN_STORE+COMP_COIN_PLUS;
    cocos2d::UserDefault::getInstance()->setIntegerForKey("COIN_STORE_KEY", COIN_STORE);
    cocos2d::UserDefault::getInstance()->flush();
    
    Show_Coin->setString(StringUtils::format("%d",COIN_STORE));
}

void Play_Scene::Show_Hint_Popup()
{
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    
    SHP_Frame->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(512)));
    SHP_Yes->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(512)));
    SHP_No->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(512)));
    
    SHP_Frame->runAction(EaseBounceOut::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 1.0*scaleFactorx,1.0*scaleFactory),
                                                                           MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(512))))));
    SHP_Yes->runAction(EaseBounceOut::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 1.0*scaleFactorx,1.0*scaleFactory),
                                                                         MoveTo::create(1.0, Vec2(visibleSize.width/768*(264), visibleSize.height/1024*(400))))));
    SHP_No->runAction(EaseBounceOut::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 1.0*scaleFactorx,1.0*scaleFactory),
                                                                        MoveTo::create(1.0, Vec2(visibleSize.width/768*(504), visibleSize.height/1024*(400))))));
    
    scheduleOnce(schedule_selector(Play_Scene::Release_Popup), 1.0f);
}

void Play_Scene::Out_Hint_Popup()
{
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    
    SHP_Frame->runAction(EaseBounceIn::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 0.0*scaleFactorx,0.0*scaleFactory),
                                                                          MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(512))))));
    SHP_Yes->runAction(EaseBounceIn::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 0.0*scaleFactorx,0.0*scaleFactory),
                                                                        MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(512))))));
    SHP_No->runAction(EaseBounceIn::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 0.0*scaleFactorx,0.0*scaleFactory),
                                                                       MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(512))))));
    
    scheduleOnce(schedule_selector(Play_Scene::Release_Popup), 1.0f);
}


#pragma mark - ======== Video AD ==========

void Play_Scene::YES_METHOD(float dt)
{
    AdCall_Jni::showRewardedAdmob();
    
}

void Play_Scene::Release_Popup(float dt)
{
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
    
    if (IS_TOUCH==true)
    {
        IS_TOUCH=false;
    }
    else
    {
        IS_TOUCH=true;
    }
}

void Play_Scene::GET_HINT(float dt)
{
    if (HINT_USE_ARE==1)
    {
        COIN_STORE=COIN_STORE-HINT1_COIN_PLUS;
        
        Play_Scene::Remove_Char_Method();
        Remove_Char->setOpacity(100);
    }
    else if (HINT_USE_ARE==2)
    {
        COIN_STORE=COIN_STORE-HINT2_COIN_PLUS;
        
        Play_Scene::Name_Hint_Method();
    }
    
    cocos2d::UserDefault::getInstance()->setIntegerForKey("COIN_STORE_KEY", COIN_STORE);
    cocos2d::UserDefault::getInstance()->flush();
    
    Show_Coin->setString(StringUtils::format("%d",COIN_STORE));
    
    Play_Scene::HINT_CHECK();
}




void Play_Scene::Show_Info_Popup()
{
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    
    Info_Frame->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(512)));
    Info_OK->setPosition(Vec2(visibleSize.width/768*(384),visibleSize.height/1024*(512)));
    
    Info_Frame->runAction(EaseBounceOut::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 1.0*scaleFactorx,1.0*scaleFactory),
                                                                            MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(512))))));
    Info_OK->runAction(EaseBounceOut::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 1.0*scaleFactorx,1.0*scaleFactory),
                                                                         MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(400))))));
    
    scheduleOnce(schedule_selector(Play_Scene::Release_Popup), 1.0f);
}

void Play_Scene::Out_Info_Popup()
{
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    
    Info_Frame->runAction(EaseBounceIn::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 0.0*scaleFactorx,0.0*scaleFactory),
                                                                           MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(512))))));
    Info_OK->runAction(EaseBounceIn::create(Spawn::createWithTwoActions(ScaleTo::create(1.0, 0.0*scaleFactorx,0.0*scaleFactory),
                                                                        MoveTo::create(1.0, Vec2(visibleSize.width/768*(384), visibleSize.height/1024*(512))))));
    
    scheduleOnce(schedule_selector(Play_Scene::Release_Popup), 1.0f);
}

void Play_Scene::Name_Compare()
{
    
    if (RED_COUNT==MAX_BLANK)
    {
        for (int i=0; i<14; i++)
        {
            if (IS_ALPHA[i]==1)
            {
                if (MUSIC==1)
                {
                    SimpleAudioEngine::getInstance()->stopEffect(VocalSound);
                    VocalSound = SimpleAudioEngine::getInstance()->playEffect("wrong.mp3");
                }
                
                Alphabet[i]->setColor(Color3B(255,0,0));
            }
            else if (IS_ALPHA[i]==0)
            {
                Alphabet[i]->setColor(Color3B(0,0,0));
            }
        }
    }
    
    
    COUNT=0;
    
    for (int i=0; i<MAX_BLANK; i++)
    {
        if (NAME_ARRAY[i].compare(STR_STR[i]))
        {
            
        }
        else
        {
            COUNT++;
            
            if (COUNT==MAX_BLANK)
            {
                for (int g=0; g<14; g++)
                {
                    if (IS_ALPHA[g]==1)
                    {
                        if (MUSIC==1)
                        {
                            SimpleAudioEngine::getInstance()->stopEffect(VocalSound);
                            VocalSound = SimpleAudioEngine::getInstance()->playEffect("right.mp3");
                        }
                        
                        Alphabet[g]->setColor(Color3B(0,0,255));
                    }
                }
                
                IS_TOUCH=false;
                
                Comp_Part=ParticleSystemQuad::create("Complete_Part.plist");
                Comp_Part->setPosition(Vec2(visibleSize.width/768*384, visibleSize.height/1024*512));
                this->addChild(Comp_Part,100);
                
                this->scheduleOnce(schedule_selector(Play_Scene::LEVEL_COMPLETE), 1.0f);
            }
        }
    }
}

void Play_Scene::Name_Method()
{
    for (int i=0; i<MAX_BLANK; i++)
        {
            if (IS_BLANK[i]==false)
            {
                if (LOOP_TMP==0)
                {
                    if (MUSIC==1)
                    {
                        SimpleAudioEngine::getInstance()->playEffect("Click_3.mp3");
                    }
                    
                    LOOP_TMP=1;
                    IS_BLANK[i]=true;
                    IS_ALPHA[STORE_TMP]=1;
                    
                    Hide_Char_Box[STORE_TMP]->setVisible(false);
                    Disable_Box[STORE_TMP]->setPosition(Hide_Name_Box[i]->getPosition());
                    Alphabet[STORE_TMP]->setPosition(Hide_Name_Box[i]->getPosition());
                    
                    STORE_STR[STORE_TMP]=CHAR_ARRAY[STORE_TMP];
                    STR_STR[i]=CHAR_ARRAY[STORE_TMP];
                    
                    RED_COUNT++;
                    Play_Scene::Name_Compare();
                }
            }
    }
}

void Play_Scene::Alphabet_Method()
{
    for (int i=0; i<MAX_BLANK; i++)
    {
        if (IS_BLANK[NT_STORE]==true)
        {
            if (LOOP_TMP==0)
            {
                if (MUSIC==1)
                {
                    SimpleAudioEngine::getInstance()->playEffect("Click_3.mp3");
                }
                
                LOOP_TMP=1;
                IS_BLANK[NT_STORE]=false;
                IS_ALPHA[STORE_TMP]=0;
                
                STR_STR[NT_STORE]="";
                
                Hide_Char_Box[STORE_TMP]->setVisible(true);
                
                RED_COUNT--;
                Alphabet[STORE_TMP]->setColor(Color3B(0,0,0));
                
                Disable_Box[STORE_TMP]->setPosition(Hide_Char_Box[STORE_TMP]->getPosition());
                Alphabet[STORE_TMP]->setPosition(Hide_Char_Box[STORE_TMP]->getPosition());
            }
        }
    }
    
    for (int i=0; i<14; i++)
    {
        if (IS_ALPHA[i]==2)
        {
            
        }
        else
        {
            Alphabet[i]->setColor(Color3B(0,0,0));
        }
    }
    
}


void Play_Scene::Name_Hint_Method()
{
    for (int k=0; k<14; k++)
    {
        Hide_Char_Box[k]->setVisible(true);
        IS_ALPHA[k]=10;
        
        Alphabet[k]->setColor(Color3B(0,0,0));
        Disable_Box[k]->setPosition(Hide_Char_Box[k]->getPosition());
        Alphabet[k]->setPosition(Hide_Char_Box[k]->getPosition());
    }
    
    for (int j=0; j<MAX_BLANK; j++)
    {
        int R_Loop=0;
        
        for (int i=0; i<14; i++)
        {
            if (RMV_LOOP[i]==false)
            {
                if (R_Loop==0)
                {
                    if (NAME_ARRAY[j].compare(CHAR_ARRAY[i]))
                    {
                        
                    }
                    else
                    {
                        R_Loop=1;
                        RMV_LOOP[i]=true;
                        IS_ALPHA[i]=1;
                        
                        if (MUSIC==1)
                        {
                            SimpleAudioEngine::getInstance()->stopEffect(VocalSound);
                            VocalSound = SimpleAudioEngine::getInstance()->playEffect("right.mp3");
                        }
                        
                        Hide_Char_Box[i]->setPosition(Vec2(visibleSize.width/768*(5000000),visibleSize.height/1024*(5000000)));
                        Alphabet[i]->setPosition(Show_Hint_Char[j]->getPosition());
                        Alphabet[i]->setColor(Color3B(0,0,255) );
                    }
                }
            }
        }
    }
    
    IS_TOUCH=false;
    CCLOG("***** level complete *****");
    Comp_Part=ParticleSystemQuad::create("Complete_Part.plist");
    Comp_Part->setPosition(Vec2(visibleSize.width/768*384, visibleSize.height/1024*512));
    this->addChild(Comp_Part,100);
    
    this->scheduleOnce(schedule_selector(Play_Scene::LEVEL_COMPLETE), 2.0f);
}

void Play_Scene::Remove_Char_Method()
{
    for (int i=0; i<14; i++)
    {
        if (RMV_2[i]==false)
        {
            if (NAME_ARRAY[Hint_TMP].compare(CHAR_ARRAY[i]))
            {
                
            }
            else
            {
                if (Hint_TMP<MAX_BLANK)
                {
                    Hint_TMP++;
                    RMV_2[i]=true;
                    return Remove_Char_Method();
                }
            }
        }
    }
    
    for (int i=0; i<14; i++)
    {
        if (RMV_2[i]==false)
        {
            RED_COUNT=0;
            STR_STR[i]="";
            IS_BLANK[i]=false;
            IS_ALPHA[i]=0;
            Disable_Box[i]->setPosition(Vec2(visibleSize.width/768*(5000000),visibleSize.height/1024*(5000000)));
            Hide_Char_Box[i]->setPosition(Vec2(visibleSize.width/768*(5000000),visibleSize.height/1024*(5000000)));
            Alphabet[i]->setPosition(Vec2(visibleSize.width/768*(5000000),visibleSize.height/1024*(5000000)));
        }
        else
        {
            RED_COUNT=0;
            STR_STR[i]="";
            Hide_Char_Box[i]->setVisible(true);
            IS_ALPHA[i]=0;
            IS_BLANK[i]=false;
            
            Alphabet[i]->setColor(Color3B(0,0,0));
            Disable_Box[i]->setPosition(Hide_Char_Box[i]->getPosition());
            Alphabet[i]->setPosition(Hide_Char_Box[i]->getPosition());
        }
        
        if (IS_ALPHA[i]==2)
        {
            
        }
        else
        {
           Alphabet[i]->setColor(Color3B(0,0,0));
        }
    }
    
    
}

#pragma mark - ======== Touch Begin


bool Play_Scene::onTouchBegan(Touch* touch, Event* event)
{
    locationPoint = touch->getLocationInView();
    locationPoint = Director::getInstance()->convertToGL(locationPoint);
    locationPoint = convertToNodeSpace(locationPoint);
    
    Play_Scene::TOUCH_PAUSE();
    
    if (IS_TOUCH==true)
    {
        
        if (BACK_BTN->getBoundingBox().containsPoint(locationPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
            }
            
            BACK_BTN->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                 ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
            
            auto scene1 = HelloWorld::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene1));
        }
        
        if (Name_Hint->getBoundingBox().containsPoint(locationPoint))
        {
            if (NAME_BTN==true)
            {
                if (MUSIC==1)
                {
                    SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
                }
                
                Name_Hint->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                      ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
                
                if (IS_HINT_2==true)
                {
                    NAME_BTN=false;
                    HINT_USE_ARE=2;
                    scheduleOnce(schedule_selector(Play_Scene::GET_HINT), 0.5f);
                }
                else
                {
                    Play_Scene::Show_Info_Popup();
                }
            }
        }
        
        if (Remove_Char->getBoundingBox().containsPoint(locationPoint))
        {
            if (REMOVE_BTN==true)
            {
                if (MUSIC==1)
                {
                    SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
                }
                
                Remove_Char->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                        ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
                
                if (IS_HINT_1==true)
                {
                    REMOVE_BTN=false;
                    HINT_USE_ARE=1;
                    scheduleOnce(schedule_selector(Play_Scene::GET_HINT), 0.5f);
                }
                else
                {
                    Play_Scene::Show_Info_Popup();
                }
                
            }
        }
        
        if (Free_BTN->getBoundingBox().containsPoint(locationPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
            }
            
            Free_BTN->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                 ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
            
            Play_Scene::Show_Hint_Popup();
        }
        
        for (int k=0; k<MAX_BLANK; k++)
        {
            if(Hide_Name_Box[k]->getBoundingBox().containsPoint(locationPoint))
            {
                NT_STORE=k;
            }
        }
        
        for (int i=0; i<14; i++)
        {
            if(Disable_Box[i]->getBoundingBox().containsPoint(locationPoint))
            {
                LOOP_TMP=0;
                STORE_TMP=i;
                
                if (IS_ALPHA[i]==0)
                {
                    Play_Scene::Name_Method();
                }
                else if (IS_ALPHA[i]==1)
                {
                    Play_Scene::Alphabet_Method();
                }
            }
        }
        
        
    }
    
    else if (IS_TOUCH==false)
    {
        if (LC_PLAY->getBoundingBox().containsPoint(locationPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
            }
            
            LC_PLAY->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
            
            
            auto scene1 = Play_Scene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene1));
            
        }
        
        if (LC_HOME->getBoundingBox().containsPoint(locationPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
            }
            
            LC_HOME->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
            
            auto scene1 = HelloWorld::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene1));
        }
        
        
        if (SHP_Yes->getBoundingBox().containsPoint(locationPoint))
        {
            
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
            }
            
            SHP_Yes->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
            
            Play_Scene::Out_Hint_Popup();
            scheduleOnce(schedule_selector(Play_Scene::YES_METHOD), 1.0f);
            
        }
        
        if (SHP_No->getBoundingBox().containsPoint(locationPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
            }
            
            SHP_No->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                               ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
            
            Play_Scene::Out_Hint_Popup();
        }
        
        if (Info_OK->getBoundingBox().containsPoint(locationPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Click_2.mp3");
            }
            
            Info_OK->runAction(Sequence::create(ScaleTo::create(0.2, 0.8*scaleFactorx,0.8*scaleFactory),
                                                ScaleTo::create(0.2, 1.0*scaleFactorx,1.0*scaleFactory),NULL));
            
            Play_Scene::Out_Info_Popup();
        }
    }
    
    return true;
}

#pragma mark - ======== Touch Move

void Play_Scene::onTouchMoved(Touch* touch, Event* event)
{
    locationPoint = touch->getLocationInView();
    locationPoint = Director::getInstance()->convertToGL(locationPoint);
    locationPoint = convertToNodeSpace(locationPoint);
    
}

#pragma mark - ======== Touch Ended

void Play_Scene::onTouchEnded(Touch* touch, Event* event)
{
    locationPoint = touch->getLocationInView();
    locationPoint = Director::getInstance()->convertToGL(locationPoint);
    locationPoint = convertToNodeSpace(locationPoint);
    
    //    CCLOG("X==>%f,Y==%f",locationPoint.x,locationPoint.y);
    
    
}

