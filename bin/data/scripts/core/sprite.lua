-- @Author: Pedro Henrique
-- @Date:   2016-06-16 16:04:10
-- @Last Modified by:   Pedro Henrique
-- @Last Modified time: 2016-06-16 23:37:23
local Sprite = {}

local Call_proto = {
	__call = function(_, ...)
		return Sprite.new(...)
	end
}

local Sprite_proto = {
	__index = Sprite,
	__tostring = function(self) 
		return "Sprite: " .. self.name
	end,
	-- TODO(Pedro): implement more operators
	-- __eq
	-- __lt
	-- __le
}

setmetatable(Sprite, Call_proto)

function Sprite:set_position(first_arg, second_arg)
	local x = 0
	local y = 0

	if type(first_arg) == "table" then
		x = first_arg.x
		y = first_arg.y
	else
		x = tonumber(first_arg)
		y = tonumber(second_arg)
	end
	
	sprite_set_position(self.name, x, y)
end 


function Sprite.new(name, texture_name)
	local self        = {}
	self.name         = name
	self.type         = "sprite"
	self.texture_name = texture_name or ""

	if texture_name then
		load_texture(texture_name)   
		create_sprite(name, texture_name)
	end

	return setmetatable(self, Sprite_proto)
end


return Sprite