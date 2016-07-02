-- @Author: Pedro Henrique
-- @Date:   2016-06-16 19:50:59
-- @Last Modified by:   Pedro Henrique
-- @Last Modified time: 2016-06-17 01:32:50

local Window = {}

function Window.draw(resource)
	window_draw(resource.name)
end


function Window.set_title(title)
	window_set_title(title)
end

return Window