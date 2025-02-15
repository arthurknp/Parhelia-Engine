local ffi = require("ffi")

ffi.cdef[[
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;
Color parhelia_create_color_from_ints(int r, int g, int b, int a);
void parhelia_draw_rect(float x, float y, float w, float h, Color col);
void parhelia_clear_screen(Color col);
void parhelia_swap_buffers(void);
]]

C_Draw = {}
Color = {}
Color.__index = Color

function Color:new(r, g, b, a)
    local instance = setmetatable({}, self)
    instance._c = ffi.new("Color", {})
    instance._c = ffi.C.parhelia_create_color_from_ints(r, g, b, a)
    return instance
end

function Color.__tostring(a)
    return "(" .. a._c.r .. ", " .. a._c.g .. ", " .. a._c.b .. ", " .. a._c.a .. ")"
end

function C_Draw.draw_rect(pos, size, color)
    ffi.C.parhelia_draw_rect(pos.x, pos.y, size.x, size.y, color._c)
end

function C_Draw.clear_screen(color)
    ffi.C.parhelia_clear_screen(color._c)
end

function C_Draw.swap_buffers()
    ffi.C.parhelia_swap_buffers()
end

C_Draw.Color = Color


return C_Draw