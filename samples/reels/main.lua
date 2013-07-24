----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 640, 384 )

layer = MOAILayer2D.new ()
MOAISim.pushRenderPass ( layer )

viewport = MOAIViewport.new ()
viewport:setSize ( 640, 384 )
viewport:setScale ( 640, -384 )
viewport:setOffset ( -1, 1 )
layer:setViewport ( viewport )

deck = MOAITileDeck2D.new ()
deck:setTexture ( "numbers.png" )
deck:setSize ( 8, 8 )
deck:setRect ( -0.5, 0.5, 0.5, -0.5 )

--============================================================--
-- MOAIAnimCurve
--============================================================--
MOAIAnimCurve.extend (

	'MOAIAnimCurve',
	
	----------------------------------------------------------------
	function ( interface, class, superInterface, superClass )
		
		-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
		function interface.prepare ( self )
			
			if self.keys then
				self:reserveKeys ( #self.keys )
				local time = 0
				for n, key in ipairs ( self.keys ) do
					time = time + key.time
					self:setKey ( n, time, key.value, key.mode, key.weight )
				end
				self.keys = nil
			end
		end
		
		-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
		function interface.pushKey ( self, time, value, mode, weight )
			
			self.keys = self.keys or {}
			
			print ( time, value )
			
			local key = {
				value = value,
				time = time,
				mode = mode,
				weight = weight,
			}
			
			table.insert ( self.keys, key )
		end
		
		-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
		--TODO: move this capability to C++; get rid of piecewise linear
		function interface.pushSpline ( self, t1, v1, t2, v2, resolution, mode, weight )
			
			local lastKey = self.keys [ #self.keys ]
			local t0 = lastKey.time
			local v0 = lastKey.value
			
			local step = ( t1 + t2 ) / resolution
			local t = 0
			
			for n = 1, ( resolution - 1 ) do
				
				t = t + ( 1 / resolution )
				
				local vA = v0 + (( v1 - v0 ) * t )
				local vB = v1 + (( v2 - v1 ) * t )
				local vC = vA + (( vB - vA ) * t )
			
				self:pushKey ( step, vC, MOAIEaseType.LINEAR )
			end
			
			self:pushKey ( step, v2, mode )
		end
	end
)

--==============================================================
-- machine face setup
--==============================================================

----------------------------------------------------------------
local function makeReelProp ( iconWidth, iconHeight, reel, deck )

	local grid = MOAIGrid.new ()
	grid:setSize ( 1, #reel, iconWidth, iconHeight )
	grid:setRepeat ( false, true )
	
	for n, v in ipairs ( reel ) do
		grid:setTile ( 1, n, v )
	end

	local prop = MOAIProp.new ()
	prop:setDeck ( deck )
	prop:setGrid ( grid )
	return prop
end

----------------------------------------------------------------
local function makeReelCurve ( iconHeight, reel, cycles, startIndex, finishIndex, windUpTime, iconTime, snapTime )

	finishIndex = finishIndex + ( cycles * #reel )
	
	local time = math.abs (( finishIndex - startIndex ) * iconTime )
	local startOffset = startIndex * iconHeight
	local finishOffset = finishIndex * iconHeight
	
	local windUp = iconHeight
	local snap = iconHeight * 0.0625
	
	-- TODO: better curve
	local curve = MOAIAnimCurve.new ()
	
	curve:pushKey ( 0.0, -startOffset )
	
	windUpTime = windUpTime * 0.5
	curve:pushSpline (
		windUpTime,			-( startOffset - windUp ),
		windUpTime,			-startOffset,
		6
	)
	
	time = time * 0.5
	local a = -startOffset
	local b = -finishOffset
	
	curve:pushSpline (
		time,				a + (( b - a ) * 0.95 ),
		time,				b,
		20,
		MOAIEaseType.EASE_OUT
	)
	
	snapTime = snapTime * 0.5
	curve:pushSpline (
		snapTime,			-( finishOffset + snap ),
		snapTime,			-finishOffset,
		4
	)
	curve:prepare ()
	
	return curve
end

----------------------------------------------------------------
local function makeMachineFace ( iconWidth, iconHeight, reels, deck, cycles, windUpTime, iconTime, snapTime )
	
	local props = {}
	
	local anim = MOAIAnim.new ()
	anim:reserveLinks ( #reels )
	
	for n, reel in ipairs ( reels ) do
	
		local prop = makeReelProp ( iconWidth, iconHeight, reel, deck )
		prop:setLoc ( iconWidth * ( n - 1 ), -iconHeight )
		table.insert ( props, prop )
		
		local curve = makeReelCurve ( iconHeight, reel, cycles, 1, #reel - 4, windUpTime, iconTime, snapTime )
		anim:setLink ( n, curve, prop, MOAIProp.ATTR_Y_LOC )
	end
	
	return props, anim
end

--==============================================================
-- sample
--==============================================================

local reels = {
	{ 1, 2, 3, 4, 5, 6, 7, },
	{ 1, 2, 3, 4, 5, 6, 7, 8, },
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
}

props, anim = makeMachineFace ( 128, 128, reels, deck, 1, 0.35, 0.08, 0.1 )

for n, prop in ipairs ( props ) do
	layer:insertProp ( prop )
end

local function mainLoop ()
	while true do
		if MOAIInputMgr.device.mouseLeft:isDown () then
			MOAIThread.blockOnAction ( anim:start ())
		end
		coroutine.yield ()
	end
end

thread = MOAICoroutine.new ()
thread:run ( mainLoop )
