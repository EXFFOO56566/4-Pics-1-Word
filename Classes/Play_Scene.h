//
//  Play_Scene.h
//  Make My Barbie
//
//  Created by Mehul on 02/03/15.
//
//

#ifndef __Make_My_Barbie__Play_Scene__
#define __Make_My_Barbie__Play_Scene__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

class Play_Scene : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    cocos2d::Point locationPoint;
    cocos2d::Size visibleSize;
    
    float scaleFactorx;
    float scaleFactory;
    
    bool IS_TOUCH;
    
    //////////////////////////////////////////////////
    
    cocos2d::Sprite *BG;
    cocos2d::Sprite *BG_frame;
    
    cocos2d::Sprite *LOGO_BG;
    cocos2d::Sprite *LOGO_1;
    cocos2d::Sprite *LOGO_2;
    cocos2d::Sprite *LOGO_3;
    cocos2d::Sprite *LOGO_4;
    cocos2d::Sprite *BACK_BTN;
    
    cocos2d::Sprite *Free_BTN;
    
    int ADS_COIN_PLUS;
    int HINT1_COIN_PLUS;
    int HINT2_COIN_PLUS;
    int COMP_COIN_PLUS;
    
    cocos2d::Sprite *Name_Hint;
    cocos2d::Sprite *Remove_Char;
    
    bool NAME_BTN;
    bool REMOVE_BTN;
    
    cocos2d::Sprite *Disable_Box[15];
    
    cocos2d::Sprite *Hide_Char_Box[15];
    cocos2d::Sprite *Hide_Name_Box[15];
    cocos2d::Label *Alphabet[15];
    
    cocos2d::Label *Show_Hint_Char[15];
    
    void update(float dt);
    
    int IS_NAME[15];
    int IS_ALPHA[15];
    
    int CHAR_X;
    int CHAR_Y;
    int NAME_X;
    int NAME_Y;
    
    int MAX_BLANK;
    
    
    void Name_Method();
    void Alphabet_Method();
    int LOOP_TMP;
    
    int STORE_TMP;
    int RED_COUNT;
    
    void Name_Compare();
    int COUNT;
    
    
    std::string LENGTH_STR;
    std::string RAND_ARRAY[14];
    std::string CHAR_ARRAY[14];
    std::string NAME_ARRAY[14];
    std::string CHAR_IS;
    std::string STORE_STR[14];
    
    ValueMap PD_1;
    ValueVector PA_1;
    ValueMap PD_0;
    
    int Hint_TMP;
    bool RMV_LOOP[14];
    bool RMV_2[14];
    
    bool COMP_ARRAY[14];
    bool IS_BLANK[14];
    
    //-----======================
    int NT_STORE;
    
    std::string STR_STR[14];
    
    std::string IMAGE_1;
    std::string IMAGE_2;
    std::string IMAGE_3;
    std::string IMAGE_4;
    
    //-----======================
    
    
    
    cocos2d::ParticleSystemQuad *Comp_Part;
    
    void GET_HINT(float dt);
    
    void Name_Hint_Method();
    void Remove_Char_Method();
    
    void Coin_Rewarded();
    static bool reward;
    
    cocos2d::Sprite *Coin_Frame;
    cocos2d::Label *Best_lvl;
    cocos2d::Label *Show_Coin;
    
    cocos2d::Label *Hint_1_lbl;
    cocos2d::Label *Hint_2_lbl;
    
    
    void LEVEL_COMPLETE(float dt);
    cocos2d::Sprite *LC_BG;
    cocos2d::Sprite *LC_Coin_frame;
    cocos2d::Label *LC_NAME1;
    cocos2d::Label *LC_COIN;
    cocos2d::Sprite *LC_PLAY;
    cocos2d::Sprite *LC_HOME;
    
    void Show_Hint_Popup();
    void Out_Hint_Popup();
    void Release_Popup(float dt);
    
    cocos2d::Sprite *SHP_Frame;
    cocos2d::Sprite *SHP_Yes;
    cocos2d::Sprite *SHP_No;
    
    void YES_METHOD(float dt);
    int HINT_USE_ARE;
    
    bool IS_HINT_1;
    bool IS_HINT_2;
    
    void HINT_CHECK();
    
    void Show_Info_Popup();
    void Out_Info_Popup();
    
    cocos2d::Sprite *Info_Frame;
    cocos2d::Sprite *Info_OK;
    
    void TOUCH_PAUSE();
    void TOUCH_RESUME(float dt);
    
    /////////////////////////////////////////////////
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    CREATE_FUNC(Play_Scene);
    
private:
    cocos2d::Vect getAnimation(const char *format, int count);
    
};

#endif /* defined(__Make_My_Barbie__Play_Scene__) */
