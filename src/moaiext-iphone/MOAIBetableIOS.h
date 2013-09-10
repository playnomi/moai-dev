//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIBETABLEIOS_H
#define MOAIBETABLEIOS_H

#ifndef DISABLE_BETABLE

#import <Foundation/Foundation.h>
#import <moaicore/moaicore.h>

#import <Betable/Betable.h>

//================================================================//
// MOAIFlurryIOS
//================================================================//
/**	@name	MOAIFlurryIOS
 @text	Wrapper for Flurry integration on iOS devices.
 Flurry provides analytics and behaviour statistics.
 Exposed to lua via MOAIFlurry on
 all mobile platforms.
 
 */
//@class MOAIBetableDelegate;

class MOAIBetableIOS :
	public MOAIGlobalClass < MOAIBetableIOS, MOAILuaObject >,
	public MOAIGlobalEventSource {
private:
    
	Betable *mBetable;
	UIViewController *viewController;
	
	NSString* mToken;
	
	//MOAIBetableDelegate* mDelegate;
	
	UIWindow* window;
	UIViewController* rootVC;
	
	//----------------------------------------------------------------//
	static int _init				( lua_State* L );
	static int _authorize			( lua_State* L );
	static int _unbackedAuthorize	( lua_State* L );	
	static int _setToken			( lua_State* L );
	static int _getToken			( lua_State* L );
    
public:
    
	DECL_LUA_SINGLETON ( MOAIBetableIOS );
   
	enum {
		SESSION_DID_LOGIN,
		SESSION_DID_NOT_LOGIN,
	};
	
	MOAIBetableIOS		();
	~MOAIBetableIOS		();
	void	RegisterLuaClass	( MOAILuaState& state );
	
	void	HandleOpenURL ( NSURL* url );
	void	SessionDidLogin			();
	void	SessionDidNotLogin		();
	
	

	
};

//================================================================//
// MoaiChartBoostDelegate
//================================================================//
//@interface MOAIBetableDelegate : NSObject <NSArray> {

//@private
//}
//@end


#endif  //DISABLE_BETABLE

#endif // BETABLE_H