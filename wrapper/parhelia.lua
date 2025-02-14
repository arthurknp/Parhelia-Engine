local Parhelia = {}

function Parhelia.load_texture()
    print("parhelia load bitmap")
end

function Parhelia.draw_texture(texture, x, y)
    print("draw texture at:", x, y)
end

package.loaded["Parhelia"] = Parhelia

return Parhelia