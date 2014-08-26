//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAICHARTBOOSTIOS_H
#define	MOAICHARTBOOSTIOS_H

#ifndef DISABLE_CHARTBOOST

#include <moaicore/moaicore.h>
#import <Chartboost.h>

@class MoaiChartBoostDelegate;

//================================================================//
// MOAIChartBoostIOS
//================================================================//
class MOAIChartBoostIOS :
	public MOAIGlobalClass < MOAIChartBoostIOS, MOAILuaObject > {
private:

	MoaiChartBoostDelegate*	mDelegate;

	//----------------------------------------------------------------//
	static int	_hasCachedInterstitial	( lua_State* L );
	static int	_init					( lua_State* L );
	static int	_loadInterstitial		( lua_State* L );
	static int	_setListener			( lua_State* L );
	static int	_showInterstitial		( lua_State* L );
		
	static int	_loadRewardedVideo		( lua_State* L );
	static int	_showRewardedVideo		( lua_State* L );
	static int  _hasRewardedVideo		( lua_State* L );
		
	static int  _setCustomId			( lua_State* L );
	static int  _getCustomId			( lua_State* L );
		
	static int	_cacheMoreApps			( lua_State* L );
	static int	_showMoreApps			( lua_State* L );
	
	static int	_trackInAppPurchaseEvent ( lua_State* L );
		
public:

	DECL_LUA_SINGLETON ( MOAIChartBoostIOS );

	enum {
		CB_LOCATION_STARTUP,
		CB_LOCATION_HOME_SCREEN,
		CB_LOCATION_MAIN_MENU,
		CB_LOCATION_GAME_SCREEN,
		CB_LOCATION_ACHIEVEMENTS,
		CB_LOCATION_QUESTS,
		CB_LOCATION_PAUSE,
		CB_LOCATION_LEVEL_START,
		CB_LOCATION_LEVEL_COMPLETE,
		CB_LOCATION_TURN_COMPLETE,
		CB_LOCATION_IAP_STORE,
		CB_LOCATION_ITEM_STORE,
		CB_LOCATION_GAME_OVER,
		CB_LOCATION_LEADERBOARD,
		CB_LOCATION_SETTINGS,
		CB_LOCATION_QUIT,
	};
	
	enum {
		INTERSTITIAL_LOAD_FAILED,
		INTERSTITIAL_DISMISSED,
		DID_COMPLETE_REWARDED_VIDEO,
		TOTAL
	};
	
	MOAILuaRef		mListeners [ TOTAL ];
	
					MOAIChartBoostIOS				();
					~MOAIChartBoostIOS				();
	void 			NotifyInterstitialDismissed		();
	void 			NotifyInterstitialLoadFailed	();
	void 			NotifiyDidCompleteRewardedVideo	(int reward, cc8* location);
	void			RegisterLuaClass				( MOAILuaState& state );
};

//================================================================//
// MoaiChartBoostDelegate
//================================================================//
@interface MoaiChartBoostDelegate : NSObject < ChartboostDelegate > {
@private
}
@end

#endif  //DISABLE_CHARTBOOST

#endif  //MOAICHARTBOOSTIOS_H
