local Parhelia = require("Parhelia")

Game = {}

local pos = Parhelia.Math.Vec2:new(0, 0)
local size = Parhelia.Math.Vec2:new(32, 32)
local col = Parhelia.Color:new(255, 0, 0, 255)

local speed = 10

local renderer = Parhelia.Renderer:new()

function Game.load_content()
end

function Game.update(dt)

    local move = Parhelia.Math.Vec2:new(0, 0)

    if Parhelia.Input.is_key_pressed(Parhelia.Input.Keys.KEY_W) then
         move.y = -1
    end
    if Parhelia.Input.is_key_pressed(Parhelia.Input.Keys.KEY_S) then
        move.y = 1
   end
   if Parhelia.Input.is_key_pressed(Parhelia.Input.Keys.KEY_A) then
        move.x = -1
    end
    if Parhelia.Input.is_key_pressed(Parhelia.Input.Keys.KEY_D) then
        move.x = 1
    end

    move = move:normalize() * speed
    pos = pos + move

end

function Game.draw()
    renderer:clear_background(Parhelia.Color:new(255, 255, 255, 255))

    renderer:draw_rect(pos, size, col)

    renderer:swap_buffers()

end