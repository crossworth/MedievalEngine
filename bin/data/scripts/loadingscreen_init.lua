-- @File: loadingscreen_init.lua
-- @Author: Pedro Henrique
-- @Date:   2016-06-16 15:34:27
-- @Last Modified by:   Pedro Henrique
-- @Last Modified time: 2016-06-17 09:16:51

local Vect2  = require "core.vect2"
local Sprite = require "core.sprite"
local Window = require "core.window"

loadingscreen = {}


-- -- Sprite(sprite_name, texture_location)
loadingscreen.backgroundSprite = Sprite("loading_background", "states/loading/background.png")
loadingscreen.backgroundSprite:set_position(Vect2(0.0, 0.0))


loadingscreen.init = true

print("loadingscreen_init.lua")

Window.set_title("$fps")