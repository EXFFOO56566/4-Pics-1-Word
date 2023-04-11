#include "AdCall_Jni.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif

bool AdCall_Jni::isFull_PageAdAvailable() {

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	CCLOG( " Befor ..... AdCall-jni Method Called on .....");
	
			cocos2d::JniMethodInfo_ methodInfo;
	
			if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "isInterstitialAvailable", "()Z")){
		
				CCLOG("AdCall-jni Method Called on .....");

				bool returnValue = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);

				if (returnValue)
					CCLOG(" Full Page is Loaded ");


				methodInfo.env->DeleteLocalRef(methodInfo.classID);

			}
			else {

				CCLOG("Static Method Not Available in Java Class.. Plz Define ");

			}
			
	#endif

	return false;
}

void AdCall_Jni::showFullScreenAd() {
    
    CCLOG("show admob interstitial");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "showInterstitial", "()V")){
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
#endif
}

void AdCall_Jni::showRewardedAdmob() {
    
    CCLOG("show admob Rewarded Vide Ads");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "ShowReward", "()V")){
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
#endif
}

void AdCall_Jni::showSmallBanner() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	cocos2d::JniMethodInfo_ methodInfo;

	if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "bannerEnabled", "()V")) {

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);

	}

#endif

}

void AdCall_Jni::MoreGame() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "OpenMoreGame", "()V")) {
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
#endif
}

void AdCall_Jni::RateGame() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "openRateGame", "()V")) {
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
#endif
}




void AdCall_Jni::BackButtonClicked() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	cocos2d::JniMethodInfo_ methodInfo;

	if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "BackButtonClicked", "()V")) {

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);

	}

#endif
}
