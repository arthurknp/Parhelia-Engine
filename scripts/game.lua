local Parhelia = require("Parhelia")

Game = {}

local texture
local draw_msg = true

local pos = Parhelia.Math.Vec2:new(100, 100)

function Game.load_content()
    texture = Parhelia.load_texture("teste.bmp")
end

function Game.update(dt)
    print(pos)
end

function Game.draw()
    if draw_msg then
        Parhelia.draw_texture(texture, 100, 100)
        draw_msg = false
    end
end