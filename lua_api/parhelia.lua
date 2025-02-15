local Parhelia = {}

local vec = require("lua_api.vector")

Parhelia.Math = {}
Parhelia.Math.Vec2 = vec.Vec2

function Parhelia.load_texture()
    print("parhelia load bitmap")
end

function Parhelia.draw_texture(texture, x, y)
    print("draw texture at:", x, y)
end

package.loaded["Parhelia"] = Parhelia

return Parhelia