-- @Author: Pedro Henrique
-- @Date:   2016-06-16 15:34:27
-- @Last Modified by:   Pedro Henrique
-- @Last Modified time: 2016-06-16 16:07:28

local sprite = require "core.sprite"

loadingscreen = {}



sprite.set_name("teste class lua")
sprite.print_name()


sprite.set_name("teste class lua2")
sprite.print_name()

-- -- Example safe load texture and create sprite
-- if load_texture("states/loading/background.png") and create_sprite("loading_background", "states/loading/background.png") then
-- 	print("create sprite ok")
-- else
-- 	print("create sprite not ok")
-- end

-- loadingscreen.backgroundSprite = sprite.get("loading_background")

-- loadingscreen.backgroundSprite.setPosition(Vect2f(0.0, 0.0))
