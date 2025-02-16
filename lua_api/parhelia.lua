local Parhelia = {}

local vec = require("lua_api.vector")
local draw = require("lua_api.c_draw")
local rend = require("lua_api.renderer")
local input = require("lua_api.input")

Parhelia.Renderer = rend
Parhelia.Math = {}
Parhelia.Math.Vec2 = vec.Vec2
Parhelia.Color = draw.Color
Parhelia.Input = input
Parhelia.Texture = draw.Texture

function Parhelia.load_texture()
    print("parhelia load bitmap")
end

package.loaded["Parhelia"] = Parhelia

return Parhelia