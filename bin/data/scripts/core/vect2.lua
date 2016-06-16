-- @Author: Pedro Henrique
-- @Date:   2016-06-16 16:21:38
-- @Last Modified by:   Pedro Henrique
-- @Last Modified time: 2016-06-16 17:28:54
local Vect2 = {}
Vect2.x = 0
Vect2.y = 0

Vect2.MT = {
	__index = Vect2, 
	__call = function (_, ...)
		return Vect2.new(...)
	end,
	__tostring = function(self)
		return "Vect2(" .. self.x .. ", " .. self.y .. ")"
	end,
	-- TODO(Pedro): implement more operators
	-- __add
	-- __sub
	-- __mul
	-- __div
	-- __eq
	-- __lt
	-- __le
}

setmetatable(Vect2, Vect2.MT)

function Vect2.new(x, y)
	obj = setmetatable({}, Vect2.MT)
	obj.x = x or 0
	obj.y = y or 0
	return obj
end

return Vect2