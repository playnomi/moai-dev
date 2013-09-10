// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <aku/AKU-betable.h>
#include <moaiext-iphone/MOAIBetableIOS.h>

//================================================================//
// AKU-chartboost
//================================================================//

//----------------------------------------------------------------//
void AKUBetableInit () {
	
	MOAIBetableIOS::Affirm();
	REGISTER_LUA_CLASS ( MOAIBetableIOS );
}