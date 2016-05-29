local mousePos = getMouseLocalPosition()
local recSize = rectangleGetSize("test1")


rectangleSetPosition("test1", mousePos["x"],  mousePos["y"])

rectangleRotate("test1", 3)