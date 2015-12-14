//
//  ImagePicker.h
//  SocialArcade
//
//  Created by Megan Peterson on 6/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef AKU_IMAGEPICKER_H
#define AKU_IMAGEPICKER_H

#include "MOAIImagePickerIOS.h"

#import <Foundation/Foundation.h>

#include <moaicore/moaicore.h>

@class MOAIImagePickerIOSDelegate;
@class MOAIImagePickerIOSTakeoverDelegate;

//================================================================//
// MOAIImagePickerIOS
//===============MOAIImagePickerIOS================================================//
/**	@name	MOAIImagePickerIOS
 @text	Wrapper for MOAIImagePickerIOS integration on iOS devices.

 */
class MOAIImagePickerIOS :
public MOAIGlobalClass < MOAIImagePickerIOS, MOAILuaObject >,
public MOAIGlobalEventSource {
private:
    
	MOAIImagePickerIOSDelegate*			mImagePickerDelegate;
	MOAIImagePickerIOSTakeoverDelegate*	mTakeoverDelegate;
	
	//----------------------------------------------------------------//
	//static int	_getDeviceID		( lua_State* L );
	static int	_init				( lua_State* L );
	static cc8*	_luaParseTable 		( lua_State* L, int idx );
	//static int	_playVideo			( lua_State* L );
	//static int	_videoReadyForZone	( lua_State* L );
	
public:
    
	DECL_LUA_SINGLETON ( MOAIImagePickerIOS );
	

    
	//NSString * 		mAppId;
	//NSDictionary * 	mZones;
	
    MOAIImagePickerIOS				();
    ~MOAIImagePickerIOS             ();
	void	NotifyTakeoverEventOccurred	( int event, cc8* zone );
	void	RegisterLuaClass			( MOAILuaState& state );
};


#endif
