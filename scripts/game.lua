local Parhelia = require("Parhelia")

Game = {}

local texture
local draw_msg = true

function Game.load_content()
    -- carregar a porra das textura
    texture = Parhelia.load_texture("teste.bmp")
end

function Game.update(dt)
    -- aqui a buceta da logica da porra do jogo
end

function Game.draw()
    if draw_msg then
        Parhelia.draw_texture(texture, 100, 100)
        draw_msg = false
    end
end