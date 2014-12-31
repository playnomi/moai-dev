//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef DISABLE_CHARTBOOST

#import <moaiext-iphone/MOAIChartBoostIOS.h>
#import <Chartboost/CBAnalytics.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
//----------------------------------------------------------------//
/**	@name	hasCachedInterstitial
 @text	returns whether a cached ad is available
 
 @out 	bool	True, if an ad is cached.
 */
int MOAIChartBoostIOS::_hasCachedInterstitial ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* location = lua_tostring ( state, 1 );
	
	bool isAdAvailable = [Chartboost hasInterstitial:[NSString stringWithUTF8String:location]];
	
	lua_pushboolean ( state, isAdAvailable );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	init
	@text	Initialize ChartBoost.
	
	@in		string	appId			Available in ChartBoost dashboard settings.
	@in 	string	appSignature	Available in ChartBoost dashboard settings.
	@out 	nil
*/
int MOAIChartBoostIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* identifier = lua_tostring ( state, 1 );
	cc8* signature = lua_tostring ( state, 2 );
	   
	[Chartboost startWithAppId:[ NSString stringWithUTF8String:identifier ]
				  appSignature:[ NSString stringWithUTF8String:signature ]
					  delegate:MOAIChartBoostIOS::Get ().mDelegate];
    
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	loadInterstitial
	@text	Request that an interstitial ad be cached for later display.
	
	@opt	string	locationId		Optional location ID.
	@out 	nil
*/
int MOAIChartBoostIOS::_loadInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );

	 cc8* location = state.GetValue < cc8* >( 1, "" );
	 
	 if ( location != nil ) {
	 	
         NSString* loc = [ NSString stringWithUTF8String:location ];
		
		 NSLog(@"MOAIChartBoostIOS::_loadInterstitial with location %@", loc);
		 
		 
		 UIWindow* mWindow = [[ UIWindow alloc ] initWithFrame:[ UIScreen mainScreen ].bounds ];
		 
		 [Chartboost cacheInterstitial:loc];
	 } else {
		
		 NSLog(@"Error: MOAIChartBoostIOS::_loadInterstitial is missing location");
	 }
			
	return 0;
}


int MOAIChartBoostIOS::_setCustomId ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* customId = state.GetValue < cc8* >( 1, "" );
	
	if ( customId != nil ) {
		
		NSString* cid = [ NSString stringWithUTF8String:customId ];
		
		[Chartboost setCustomId:cid];
	}
}


//----------------------------------------------------------------//
/**	@name	loadInterstitial
 @text	Request that an interstitial ad be cached for later display.
 
 @opt	string	locationId		Optional location ID.
 @out 	nil
 */
int MOAIChartBoostIOS::_loadRewardedVideo ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* location = state.GetValue < cc8* >( 1, "" );
	
	if ( location != nil ) {
	 	
		NSString* loc = [ NSString stringWithUTF8String:location ];
		
		NSLog(@"MOAIChartBoostIOS::_cacheRewardedVideo with location %@", loc);
		
	 	[ Chartboost cacheRewardedVideo:loc ];
	} 
	
	return 0;
}


//----------------------------------------------------------------//
/**	@name	loadInterstitial
 @text	Request that an interstitial ad be cached for later display.
 
 @opt	string	locationId		Optional location ID.
 @out 	nil
 */
int MOAIChartBoostIOS::_showRewardedVideo ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* location = state.GetValue < cc8* >( 1, "" );
	
	if ( location != nil ) {
	 	
		NSString* loc = [ NSString stringWithUTF8String:location ];
		
		NSLog(@"MOAIChartBoostIOS::_showRewardedVideo with location %@", loc);
		
	 	[ Chartboost showRewardedVideo:loc ];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	loadInterstitial
 @text	Request that an interstitial ad be cached for later display.
 
 @opt	string	locationId		Optional location ID.
 @out 	nil
 */
int MOAIChartBoostIOS::_hasRewardedVideo ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* location = state.GetValue < cc8* >( 1, "" );
	
	if ( location != nil ) {
	
		NSString* loc = [ NSString stringWithUTF8String:location ];
		
		bool isAdAvailable = [ Chartboost hasRewardedVideo:loc ];
	
		NSLog(@"MOAIChartBoostIOS::_hasRewardedVideo with location %@, %i", loc, isAdAvailable);
		
		
		lua_pushboolean ( state, isAdAvailable );

	}
	
	return 1;
}




//----------------------------------------------------------------//
int MOAIChartBoostIOS::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );
	
	if ( idx < TOTAL ) {
		
		MOAIChartBoostIOS::Get ().mListeners [ idx ].SetStrongRef ( state, 2 );
	}
	
	return 0;
}


int MOAIChartBoostIOS::_cacheMoreApps ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* location = state.GetValue < cc8* >( 1, "" );
	
	if ( location != nil ) {
		
		NSString* loc = [ NSString stringWithUTF8String:location ];
		
		[Chartboost cacheMoreApps:loc];
		
	}
	
}

int MOAIChartBoostIOS::_showMoreApps ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* location = state.GetValue < cc8* >( 1, "" );
	
	if ( location != nil ) {

		NSString* loc = [ NSString stringWithUTF8String:location ];
		
		[Chartboost showMoreApps:loc];
	
	}
		
}


//----------------------------------------------------------------//
/**	@name	showInterstitial
	@text	Request an interstitial ad display if a cached ad is available.
	
	@opt	string	locationId		Optional location ID.
	@out 	bool					True, if an ad is cached and will be displayed.
*/
int MOAIChartBoostIOS::_showInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );

	 cc8* location = state.GetValue < cc8* >( 1, "" );
	 
	 if ( location != nil ) {
	 	
         NSString* loc = [ NSString stringWithUTF8String:location ];
         
         NSLog(@"MOAIChartBoostIOS::_showInterstitial with location %@", loc);
		 
	 		[Chartboost showInterstitial:loc];
	 		lua_pushboolean ( state, true );
	 		
	 		return 1;
	 } else {
		
		NSLog(@"Error: MOAIChartBoostIOS::_showInterstitial without location");
	
	}
			
	lua_pushboolean ( state, false );

	return 1;
}


int	MOAIChartBoostIOS::_trackInAppPurchaseEvent ( lua_State* L ) {

	// do the translation here
	MOAILuaState state ( L );

	// get the receipt url if it is support else use the receipt value
	cc8* receipt		= state.GetValue < cc8* >( 1, "" );
	cc8* title			= state.GetValue < cc8* >( 2, "" );
	cc8* description	= state.GetValue < cc8* >( 3, "" );
	u32 price			= state.GetValue < u32 >( 4, 0 );
	cc8* currency		= state.GetValue < cc8* >( 5, "" );
	cc8* identifier 	= state.GetValue < cc8* >( 6, "" );
	
	NSData* receiptData = [[ NSString stringWithUTF8String:receipt ] dataUsingEncoding:NSUTF8StringEncoding];
	
	[CBAnalytics trackInAppPurchaseEvent: receiptData
							productTitle: [ NSString stringWithUTF8String:title ]
					  productDescription: [ NSString stringWithUTF8String:description ]
							productPrice: [ NSNumber numberWithInt:price]
						 productCurrency: [ NSString stringWithUTF8String:currency ]
					   productIdentifier: [ NSString stringWithUTF8String:identifier ]];
	
	return 1;
}



//================================================================//
// MOAIChartBoostIOS
//================================================================//

//----------------------------------------------------------------//
MOAIChartBoostIOS::MOAIChartBoostIOS () {

	RTTI_SINGLE ( MOAILuaObject )	

	mDelegate = [[ MoaiChartBoostDelegate alloc ] init ];
	
	
}

//----------------------------------------------------------------//
MOAIChartBoostIOS::~MOAIChartBoostIOS () {

	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIChartBoostIOS::RegisterLuaClass ( MOAILuaState& state ) {

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

	luaL_Reg regTable [] = {
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
		{ "trackInAppPurchaseEvent", _trackInAppPurchaseEvent },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIChartBoostIOS::NotifyInterstitialDismissed () {	
	
	MOAILuaRef& callback = this->mListeners [ INTERSTITIAL_DISMISSED ];
	
	if ( callback ) {
		
		MOAILuaStateHandle state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIChartBoostIOS::NotifyInterstitialLoadFailed () {	
	
	MOAILuaRef& callback = this->mListeners [ INTERSTITIAL_LOAD_FAILED ];
	
	if ( callback ) {
		
		MOAILuaStateHandle state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}


void MOAIChartBoostIOS::NotifiyDidCompleteRewardedVideo (int reward, cc8* location) {
	
	MOAILuaRef& callback = this->mListeners [ DID_COMPLETE_REWARDED_VIDEO ];
	
	if (callback) {
		
		MOAILuaStateHandle state = callback.GetSelf ();
		
		// location is the first param
		lua_pushstring ( state, location );
		lua_pushinteger ( state, reward );
		
		state.DebugCall ( 2, 0 );
	}

}


//================================================================//
// MoaiChartBoostDelegate
//================================================================//
@implementation MoaiChartBoostDelegate

	//================================================================//
	#pragma mark -
	#pragma mark Protocol MoaiChartBoostDelegate
	//================================================================//

	//- ( BOOL ) shouldRequestInterstitial {
		
	//	return YES;
	//}

	- ( void ) didFailToLoadInterstitial {
		
		MOAIChartBoostIOS::Get ().NotifyInterstitialLoadFailed ();
	}

	//- ( BOOL ) shouldDisplayInterstitial:( UIView * )interstitialView {
		
	//	return YES;
	//}

	- ( void ) didDismissInterstitial:( UIView * )interstitialView {
		
		MOAIChartBoostIOS::Get ().NotifyInterstitialDismissed ();
	}

	//- ( BOOL ) shouldDisplayMoreApps:( UIView * )moreAppsView {
		
	//	return YES;
	//}

	//- (void)didDismissMoreApps {
		//[[Chartboost sharedChartboost] cacheMoreApps];
	//}

	- (void)didCompleteRewardedVideo:(CBLocation)location withReward:(int)reward {
		
		 NSLog(@"MOAIChartBoostIOS::_didComplete Rewarded Video location %i %@", reward, location);
		
		MOAIChartBoostIOS::Get ().NotifiyDidCompleteRewardedVideo (reward, [location UTF8String ]);
	}


@end

#endif