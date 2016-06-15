-- MedievalEngine
-- You can set every file that you will be using on the game here
-- it will be loaded at the loading screen

-- resource_load("music_one_menu.wav")
-- to use on your game you call local menu_m = resource_get("music_one_menu.wave")
-- or maybe something like local m = resource_get("music_file.wav") m.play()
-- music_play(menu_m)

local test_message = "This is a log call from the Loader.lua"

-- for i=1,500000 do 
--     print(test_message) 
-- end



function load()
    for i=1,500000 do 
        print(test_message) 
    end  
end