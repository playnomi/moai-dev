// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef DISABLE_CHARTBOOST

#include "pch.h"

#include <jni.h>

#include <moaiext-android/moaiext-jni.h>
#include <moaiext-android/MOAIChartBoostAndroid.h>

extern JavaVM* jvm;


//----------------------------------------------------------------//
//----------------------------------------------------------------//
/**	@name	hasCachedInterstitial
 @text	returns whether a cached ad is available
 
 @out 	bool	True, if an ad is cached.
 */
int MOAIChartBoostAndroid::_hasCachedInterstitial ( lua_State* L ) {
    
    MOAILuaState state ( L );
    
	cc8* location = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );
	
	jclass javaClass = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( javaClass == NULL ) {
        
		USLog::Print ( "MoaiChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID javaMethod = env->GetStaticMethodID ( javaClass, "hasCachedInterstitial", "(Ljava/lang/String;)V" );
    	if ( javaMethod == NULL ) {
            
			USLog::Print ( "MoaiChartBoostAndroid: Unable to find static java method %s", "isConnected" );
    	} else {
            
			bool result = env->CallStaticObjectMethod ( javaClass, javaMethod, jlocation );
            
            lua_pushboolean(state, result);
            
            return 1;
		}
	}
    
    lua_pushnil ( state );
    
	return 1;
    
}



//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	init
	@text	Initialize ChartBoost.
	
	@in		string	appId			Available in ChartBoost dashboard settings.
	@in 	string	appSignature	Available in ChartBoost dashboard settings.
	@out 	nil
*/
int MOAIChartBoostAndroid::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* identifier = lua_tostring ( state, 1 );
	cc8* signature = lua_tostring ( state, 2 );

	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( identifier, jidentifier );
	JNI_GET_JSTRING ( signature, jsignature );

	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {

		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {

    	jmethodID init = env->GetStaticMethodID ( chartboost, "init", "(Ljava/lang/String;Ljava/lang/String;)V" );
    	if ( init == NULL ) {

			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "init" );
    	} else {

			env->CallStaticVoidMethod ( chartboost, init, jidentifier, jsignature );				
		}
	}
			
	return 0;
}

//----------------------------------------------------------------//
/**	@name	loadInterstitial
	@text	Request that an interstitial ad be cached for later display.
	
	@opt	string	locationId		Optional location ID.
	@out 	nil
*/
int MOAIChartBoostAndroid::_loadInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* location = lua_tostring ( state, 1 ); 

	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );

	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {

		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {

    	jmethodID loadInterstitial = env->GetStaticMethodID ( chartboost, "loadInterstitial", "(Ljava/lang/String;)V" );
    	if ( loadInterstitial == NULL ) {

			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "loadInterstitial" );
    	} else {

			env->CallStaticVoidMethod ( chartboost, loadInterstitial, jlocation );			
		}
	}
			
	return 0;
}


int MOAIChartBoostAndroid::_setCustomId ( lua_State* L ) {

    MOAILuaState state ( L );
    
	cc8* customId = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( customId, jcustomId );
    
	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {
        
		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID method = env->GetStaticMethodID ( chartboost, "setCustomId", "(Ljava/lang/String;)V" );
    	if ( method == NULL ) {
            
			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "setCustomId" );
    	} else {
            
			env->CallStaticVoidMethod ( chartboost, method, jcustomId );
		}
	}
    
	return 0;
    
}


//----------------------------------------------------------------//
/**	@name	_loadRewardedVideo
 @text	Request that an interstitial ad be cached for later display.
 
 @opt	string	locationId		Optional location ID.
 @out 	nil
 */
int MOAIChartBoostAndroid::_loadRewardedVideo ( lua_State* L ) {
	
	MOAILuaState state ( L );
    
	cc8* location = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );
    
	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {
        
		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID loadInterstitial = env->GetStaticMethodID ( chartboost, "loadRewardedVideo", "(Ljava/lang/String;)V" );
    	if ( loadInterstitial == NULL ) {
            
			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "cacheRewardeVideo" );
    	} else {
            
			env->CallStaticVoidMethod ( chartboost, loadInterstitial, jlocation );
		}
	}
    
	return 0;
}


//----------------------------------------------------------------//
/**	@name	showRewardedVideo
 @text	Request that an interstitial ad be cached for later display.
 
 @opt	string	locationId		Optional location ID.
 @out 	nil
 */
int MOAIChartBoostAndroid::_showRewardedVideo ( lua_State* L ) {
	
	MOAILuaState state ( L );
    
	cc8* location = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );
    
	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {
        
		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID showInterstitial = env->GetStaticMethodID ( chartboost, "showRewardedVideo", "(Ljava/lang/String;)V" );
    	if ( showInterstitial == NULL ) {
            
			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "showRewardedVideo" );
    	} else {
            
			env->CallStaticVoidMethod ( chartboost, showInterstitial, jlocation );
		}
	}
    
	return 0;
}

//----------------------------------------------------------------//
/**	@name	loadInterstitial
 @text	Request that an interstitial ad be cached for later display.
 
 @opt	string	locationId		Optional location ID.
 @out 	nil
 */
int MOAIChartBoostAndroid::_hasRewardedVideo ( lua_State* L ) {
	
    MOAILuaState state ( L );
    
	cc8* location = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );
	
	jclass javaClass = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( javaClass == NULL ) {
        
		USLog::Print ( "MoaiChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID javaMethod = env->GetStaticMethodID ( javaClass, "hasRewardedVideo", "(Ljava/lang/String;)Z" );
    	if ( javaMethod == NULL ) {
            
			USLog::Print ( "MoaiChartBoostAndroid: Unable to find static java method %s", "hasRewardedVideo" );
    	} else {
            
			bool result = env->CallStaticObjectMethod ( javaClass, javaMethod, jlocation );
            
            lua_pushboolean(state, result);
            
            return 1;
		}
	}
    
    lua_pushnil ( state );
    
	return 1;
    
}




//----------------------------------------------------------------//
int MOAIChartBoostAndroid::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );

	if ( idx < TOTAL ) {
		
		MOAIChartBoostAndroid::Get ().mListeners [ idx ].SetStrongRef ( state, 2 );
	}
	
	return 0;
}

int MOAIChartBoostAndroid::_cacheMoreApps ( lua_State* L ) {
	
    MOAILuaState state ( L );
    
	cc8* location = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );
	
	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {
        
		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID cacheMoreApps = env->GetStaticMethodID ( chartboost, "cacheMoreApps", "(Ljava/lang/String;)V" );
    	if ( cacheMoreApps == NULL ) {
            
			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "cacheMoreApps" );
    	} else {
            
			env->CallStaticVoidMethod ( chartboost, cacheMoreApps, jlocation );
		}
	}
    
	return 0;
    
}

int MOAIChartBoostAndroid::_showMoreApps ( lua_State* L ) {
	
    MOAILuaState state ( L );
    
	cc8* location = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );
	
	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {
        
		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID showMoreApps = env->GetStaticMethodID ( chartboost, "showMoreApps", "(Ljava/lang/String;)V" );
    	if ( showMoreApps == NULL ) {
            
			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "showMoreApps" );
    	} else {
            
			env->CallStaticVoidMethod ( chartboost, showMoreApps, jlocation );
		}
	}
    
	return 0;
    
}

//----------------------------------------------------------------//
/**	@name	showInterstitial
	@text	Request an interstitial ad display if a cached ad is available.
	
	@opt	string	locationId		Optional location ID.
	@out 	nil
*/
int MOAIChartBoostAndroid::_showInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* location = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( location, jlocation );

	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {

		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {

    	jmethodID showInterstitial = env->GetStaticMethodID ( chartboost, "showInterstitial", "(Ljava/lang/String;)V" );
    	if ( showInterstitial == NULL ) {

			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "showInterstitial" );
    	} else {

			env->CallStaticVoidMethod ( chartboost, showInterstitial, jlocation );				
		}
	}

	return 0;
}

int MOAIChartBoostAndroid::_trackInAppGooglePlayPurchaseEvent ( lua_State* L ) {
	
   	MOAILuaState state ( L );
    
	cc8* title = lua_tostring ( state, 1 );
    cc8* description = lua_tostring ( state, 1 );
    cc8* price = lua_tostring ( state, 1 );
    cc8* currency = lua_tostring ( state, 1 );
    cc8* productID = lua_tostring ( state, 1 );
    cc8* purchaseData = lua_tostring ( state, 1 );
    cc8* purchaseSignature = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( title, jtitle );
    JNI_GET_JSTRING ( description, jdescription );
    JNI_GET_JSTRING ( price, jprice );
    JNI_GET_JSTRING ( currency, jcurrency );
    JNI_GET_JSTRING ( productID, jproductID );
    JNI_GET_JSTRING ( purchaseData, jpurchaseData );
    JNI_GET_JSTRING ( purchaseSignature, jpurchaseSignature );
    
	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {
        
		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID method = env->GetStaticMethodID ( chartboost, "trackInAppGooglePlayPurchaseEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
    	if ( method == NULL ) {
            
			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "trackInAppGooglePlayPurchaseEvent" );
    	} else {
            
			env->CallStaticVoidMethod ( chartboost, method, jtitle, jdescription, jprice, jcurrency, jproductID, jpurchaseData, jpurchaseSignature);
		}
	}
    
	return 0;
}

int MOAIChartBoostAndroid::_trackInAppAmazonStorePurchaseEvent ( lua_State* L ) {
	
   	MOAILuaState state ( L );
    
	cc8* title = lua_tostring ( state, 1 );
    cc8* description = lua_tostring ( state, 1 );
    cc8* price = lua_tostring ( state, 1 );
    cc8* currency = lua_tostring ( state, 1 );
    cc8* productID = lua_tostring ( state, 1 );
    cc8* userID = lua_tostring ( state, 1 );
    cc8* purchaseToken = lua_tostring ( state, 1 );
    
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( title, jtitle );
    JNI_GET_JSTRING ( description, jdescription );
    JNI_GET_JSTRING ( price, jprice );
    JNI_GET_JSTRING ( currency, jcurrency );
    JNI_GET_JSTRING ( productID, jproductID );
    JNI_GET_JSTRING ( userID, juserID );
    JNI_GET_JSTRING ( purchaseToken, jpurchaseToken );
    
	jclass chartboost = env->FindClass ( "com/ziplinegames/moai/MoaiChartBoost" );
    if ( chartboost == NULL ) {
        
		USLog::Print ( "MOAIChartBoostAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiChartBoost" );
    } else {
        
    	jmethodID method = env->GetStaticMethodID ( chartboost, "trackInAppAmazonStorePurchaseEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
    	if ( method == NULL ) {
            
			USLog::Print ( "MOAIChartBoostAndroid: Unable to find static java method %s", "trackInAppGooglePlayPurchaseEvent" );
    	} else {
            
			env->CallStaticVoidMethod ( chartboost, method, jtitle, jdescription, jprice, jcurrency, jproductID, juserID, jpurchaseToken);
		}
	}
    
	return 0;
}


//================================================================//
// MOAIChartBoostAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIChartBoostAndroid::MOAIChartBoostAndroid () {

	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIChartBoostAndroid::~MOAIChartBoostAndroid () {

}

//----------------------------------------------------------------//
void MOAIChartBoostAndroid::RegisterLuaClass ( MOAILuaState& state ) {

    state.SetField ( -1, "CB_LOCATION_STARTUP",( u32 )CB_LOCATION_STARTUP );
	state.SetField ( -1, "CB_LOCATION_HOME_SCREEN",( u32 )CB_LOCATION_HOME_SCREEN );
	state.SetField ( -1, "CB_LOCATION_MAIN_MENU",( u32 )CB_LOCATION_MAIN_MENU );
	state.SetField ( -1, "CB_LOCATION_GAME_SCREEN",( u32 )CB_LOCATION_GAME_SCREEN );
	state.SetField ( -1, "CB_LOCATION_ACHIEVEMENTS",( u32 )CB_LOCATION_ACHIEVEMENTS );
	state.SetField ( -1, "CB_LOCATION_QUESTS",( u32 )CB_LOCATION_QUESTS );
	state.SetField ( -1, "CB_LOCATION_PAUSE",( u32 )CB_LOCATION_PAUSE );
	state.SetField ( -1, "CB_LOCATION_LEVEL_START",( u32 )CB_LOCATION_LEVEL_START );
	state.SetField ( -1, "CB_LOCATION_LEVEL_COMPLETE",( u32 )CB_LOCATION_LEVEL_COMPLETE );
	state.SetField ( -1, "CB_LOCATION_TURN_COMPLETE",( u32 )CB_LOCATION_TURN_COMPLETE );
	state.SetField ( -1, "CB_LOCATION_IAP_STORE",( u32 )CB_LOCATION_IAP_STORE );
	state.SetField ( -1, "CB_LOCATION_ITEM_STORE",( u32 )CB_LOCATION_ITEM_STORE );
	state.SetField ( -1, "CB_LOCATION_GAME_OVER",( u32 )CB_LOCATION_GAME_OVER );
	state.SetField ( -1, "CB_LOCATION_LEADERBOARD",( u32 )CB_LOCATION_LEADERBOARD );
	state.SetField ( -1, "CB_LOCATION_SETTINGS",( u32 )CB_LOCATION_SETTINGS );
	state.SetField ( -1, "CB_LOCATION_QUIT",( u32 )CB_LOCATION_QUIT );
	
	state.SetField ( -1, "DID_COMPLETE_REWARDED_VIDEO",	( u32 )DID_COMPLETE_REWARDED_VIDEO );
	state.SetField ( -1, "INTERSTITIAL_LOAD_FAILED",	( u32 )INTERSTITIAL_LOAD_FAILED );
	state.SetField ( -1, "INTERSTITIAL_DISMISSED", 		( u32 )INTERSTITIAL_DISMISSED );
    
	state.SetField ( -1, "INTERSTITIAL_LOAD_FAILED",	( u32 )INTERSTITIAL_LOAD_FAILED );
	state.SetField ( -1, "INTERSTITIAL_DISMISSED", 		( u32 )INTERSTITIAL_DISMISSED );

	luaL_Reg regTable [] = {
		{ "trackInAppAmazonStorePurchaseEvent",	_trackInAppAmazonStorePurchaseEvent },
		{ "trackInAppGooglePlayPurchaseEvent",	_trackInAppGooglePlayPurchaseEvent },
		{ "hasCachedInterstitial",	_hasCachedInterstitial },
		{ "init",					_init },
		{ "loadInterstitial",		_loadInterstitial },
		{ "setListener",			_setListener },
		{ "showInterstitial",		_showInterstitial },
		{ "cacheMoreApps",		_cacheMoreApps },
		{ "showMoreApps",		_showMoreApps },
		{ "hasRewardedVideo",    _hasRewardedVideo },
		{ "showRewardedVideo",    _showRewardedVideo },
		{ "loadRewardedVideo",    _loadRewardedVideo },
		{ "setCustomId",		   _setCustomId},
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIChartBoostAndroid::NotifyInterstitialDismissed () {	
	
	MOAILuaRef& callback = this->mListeners [ INTERSTITIAL_DISMISSED ];
	
	if ( callback ) {
		
		MOAILuaStateHandle state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIChartBoostAndroid::NotifyInterstitialLoadFailed () {	
	
	MOAILuaRef& callback = this->mListeners [ INTERSTITIAL_LOAD_FAILED ];
	
	if ( callback ) {
		
		MOAILuaStateHandle state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIChartBoostAndroid::NotifiyDidCompleteRewardedVideo (cc8* location, int reward) {
	
	MOAILuaRef& callback = this->mListeners [ DID_COMPLETE_REWARDED_VIDEO ];
	
    if (callback) {
		
		MOAILuaStateHandle state = callback.GetSelf ();
		
		lua_pushstring ( state, location );
        lua_pushinteger ( state, reward );
        
		state.DebugCall ( 2, 0 );
	}
}

//================================================================//
// ChartBoost JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiChartBoost_AKUNotifyChartBoostInterstitialDismissed ( JNIEnv* env, jclass obj ) {

	MOAIChartBoostAndroid::Get ().NotifyInterstitialDismissed ();
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiChartBoost_AKUNotifyChartBoostInterstitialLoadFailed ( JNIEnv* env, jclass obj ) {

	MOAIChartBoostAndroid::Get ().NotifyInterstitialLoadFailed ();
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiChartBoost_AKUNotifyChartBoostDidCompleteRewardedVideo ( JNIEnv* env, jclass obj, jstring location, jint reward ) {
    
    const char* nativeLocationString = env->GetStringUTFChars(location, 0);
    
	 MOAIChartBoostAndroid::Get ().NotifiyDidCompleteRewardedVideo (nativeLocationString, reward);
}





#endif