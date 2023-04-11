#ifndef _AdCall_Jni_H_
#define _AdCall_Jni_H_

#include "cocos2d.h"

class AdCall_Jni : public cocos2d::Ref
{
public :

	static bool isFull_PageAdAvailable();
	static void showSmallBanner();
    static void showFullScreenAd();
    static void showRewardedAdmob();
   
	static void BackButtonClicked();
    
    static void MoreGame();
    static void RateGame();
};

#endif // _Tiles_H_
