// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#import <moaiext-iphone/MOAIBetableIOS.h>
#import <moaiext-iphone/NSData+MOAILib.h>
#import <moaiext-iphone/NSDate+MOAILib.h>
#import <moaiext-iphone/NSDictionary+MOAILib.h>
#import <moaiext-iphone/NSError+MOAILib.h>
#import <moaiext-iphone/NSString+MOAILib.h>

#import <Betable/Betable.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	startSession
 @text	Start the Flurry session.
 
 @in	string apikey		The api key from Flurry.
 @out	nil
 */
int MOAIBetableIOS::_init( lua_State * L ) {
	
	MOAILuaState state ( L );
	
	cc8* clientId = state.GetValue < cc8* >( 1, "" );
	cc8* clientSecret = state.GetValue < cc8* >( 2, "" );
	cc8* redirectURI = state.GetValue < cc8* >( 3, "" );
	
	if ( clientId && clientId [ 0 ] != '\0' ) {

		printf("Init Betable: '%s'\n", clientId);
		
        Betable* betable = [[Betable alloc] initWithClientID:[ NSString stringWithUTF8String:clientId ]
                                       clientSecret:[ NSString stringWithUTF8String:clientSecret ]
                                        redirectURI:[ NSString stringWithUTF8String:redirectURI ]];
		
		MOAIBetableIOS::Get ().mBetable = betable;
		
	}
	return 0;
}

int MOAIBetableIOS::_authorize ( lua_State * L ) {
	
    UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
    UIViewController* rootVC = [ window rootViewController ];
    
    NSLog(@"%@", [rootVC class]);
    // NSLog(@"%@", [mBetable class]);
    
    [MOAIBetableIOS::Get ().mBetable authorizeInViewController:rootVC onClose:^{
        //[overlayView removeFromSuperview];
    }];

    return 0;
}

int MOAIBetableIOS::_unbackedAuthorize ( lua_State * L ) {
   
	/*
    authUnbacked = YES;
    [self.view addSubview:overlayView];
    [MOAIBetableIOS::Get ().betable unbackedToken:@"foobarbaz"
                onComplete:[^(NSString* accessToken){
        NSLog(@"accessToken: %@", accessToken);
        if (accessToken) {
            [self performSelectorOnMainThread:@selector(alertAuthorized) withObject:self waitUntilDone:NO];
        } else {
            [self performSelectorOnMainThread:@selector(alertAuthorizeFailed) withObject:self waitUntilDone:NO];
        }
    } autorelease]
                 onFailure:[^(NSURLResponse *response, NSString *responseBody, NSError *error){
        NSLog(@"%@", error);
    } autorelease]];
    */
	
		return 0;
}


//----------------------------------------------------------------//
void MOAIBetableIOS::HandleOpenURL ( NSURL* url ) {
		
    [MOAIBetableIOS::Get ().mBetable handleAuthorizeURL:url
        onAuthorizationComplete:[^(NSString* accessToken){
        NSLog(@"accessToken: %@", accessToken);
		
		mToken = accessToken;
		
        if (accessToken) {
			this->SessionDidLogin();
        } else {
			this->SessionDidNotLogin();
        }
    } autorelease]
                      onFailure:[^(NSURLResponse *response, NSString *responseBody, NSError *error){
        NSLog(@"%@", error);
    } autorelease]
     ];
	 
	 
    return YES;
}


//----------------------------------------------------------------//
/**	@name	getToken
 @text	Retrieve the Betable login token.
 
 @in		nil
 @out	string	token
 */
int MOAIBetableIOS::_getToken ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	//MOAIBetableIOS::Get ().mToken = [[ MOAIBetableIOS::Get ().mFacebook accessToken ] UTF8String ];
	if ( [MOAIBetableIOS::Get ().mToken UTF8String] != "") {
		
		lua_pushstring ( L, [MOAIBetableIOS::Get ().mToken UTF8String]);
	} else {
		
		lua_pushnil ( L );
	}
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	setToken
 @text	Set the Betable login token.
 
 @in		string	token			The login token. See Betable documentation.
 @out 	nil
 */
int MOAIBetableIOS::_setToken ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* token = state.GetValue < cc8* >( 1, "" );
	
	MOAIBetableIOS::Get ().mToken = [ NSString stringWithUTF8String:token ];
	//MOAIFacebookIOS::Get ().mFacebook.accessToken = [[ NSString alloc ] initWithUTF8String:token ];
	
	return 0;
}


//================================================================//
// MOAIBetableIOS
//================================================================//

//----------------------------------------------------------------//
MOAIBetableIOS::MOAIBetableIOS () {
	
	RTTI_SINGLE ( MOAILuaObject )
	RTTI_SINGLE ( MOAIGlobalEventSource )
	//mDelegate = [[ MoaiBetableDelegate alloc ] init ];
	
}

//----------------------------------------------------------------//
MOAIBetableIOS::~MOAIBetableIOS () {
	
}

//----------------------------------------------------------------//
void MOAIBetableIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	//printf("register Flurry '%s'\n", "test");
	state.SetField ( -1, "SESSION_DID_LOGIN", 		( u32 )SESSION_DID_LOGIN );
	state.SetField ( -1, "SESSION_DID_NOT_LOGIN", 	( u32 )SESSION_DID_NOT_LOGIN );
	
	
	luaL_Reg regTable [] = {
		{ "init",				_init },
		{ "authorize",			_authorize },
		{ "unbackedAuthorize",	_unbackedAuthorize },
		{ "setToken",	_setToken },
		{ "getToken",	_getToken },
		{ "setListener",			&MOAIGlobalEventSource::_setListener < MOAIBetableIOS > },		
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIBetableIOS::SessionDidLogin ( ) {
	
	MOAILuaStateHandle state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( SESSION_DID_LOGIN, state )) {
		
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIBetableIOS::SessionDidNotLogin ( ) {
	
	MOAILuaStateHandle state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( SESSION_DID_NOT_LOGIN, state )) {
		
		state.DebugCall ( 0, 0 );
	}
}







