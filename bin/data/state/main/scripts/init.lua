window = getWindowInfo()


-- musicLoad("menu", "state/main/music.ogg")
-- musicPlay("menu")

textureCreate("bg_txt", "state/main/bg.jpg")
spriteCreate("bg_sprite", "bg_txt")
spriteSetPosition("bg_sprite", 0, 0)
fadeIn("bg_sprite", 1)

local bgSize = spriteGetSize("bg_sprite")
spriteSetScale("bg_sprite", window["width"]/bgSize["x"], window["height"]/bgSize["y"])




rectangleCreate("test1", 100, 100, true)
rectangleSetFillColor("test1", 255, 255, 255)
rectangleSetOrigin("test1", 50, 50)
mRotate = 0



