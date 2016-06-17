-- @Author: Pedro Henrique
-- @Date:   2016-06-16 15:34:08
-- @Last Modified by:   Pedro Henrique
-- @Last Modified time: 2016-06-17 01:16:04

local Window = require "core.window"

function draw() 
	Window.draw(loadingscreen.backgroundSprite)
end

if loadingscreen.init then
	draw()
end