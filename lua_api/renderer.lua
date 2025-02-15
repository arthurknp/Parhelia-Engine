local Vec2 = require("lua_api.vector").Vec2
local c_draw = require("lua_api.c_draw")

local Color = c_draw.Color

local Renderer = {}

Renderer.__index = Renderer

function Renderer:new()
    local instance = setmetatable({}, self)
    return instance
end

function Renderer:clear_background(color)
    c_draw.clear_screen(color)
end

function Renderer:draw_rect(pos, size, color)
    c_draw.draw_rect(pos, size, color)
end

function Renderer:swap_buffers()
    c_draw.swap_buffers()
end

return Renderer