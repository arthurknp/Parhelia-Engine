
-- TODO: Adicionar Vector3

Vector = {}

Vec2 = {}
Vec2.__index = Vec2

function Vec2:new(x, y)
    local instance = setmetatable({}, self)
    instance.x = x or 0
    instance.y = y or 0
    return instance
end

function Vec2.__add(a, b)
    return Vec2:new(a.x + b.x, a.y + b.y)
end

function Vec2.__sub(a, b)
    return Vec2:new(a.x - b.x, a.y - b.y)
end

function Vec2.__mul(a, b)
    if type(b) == "number" then
        return Vec2:new(a.x * b, a.y * b)
    elseif getmetatable(b) == Vec2 then
        return Vec2:new(a.x * b.x, a.y * b.y)
    end
end

function Vec2.__eq(a, b)
    return a.x == b.x and a.y == b.y
end

function Vec2:dot(other)
    if getmetatable(other) == Vec2 then
        return (self.x * other.x) + (self.y * other.y)
    else
        return Vec2:new()
    end
end

function Vec2:normalize()
    local magnitude = math.sqrt(self.x * self.x + self.y * self.y)
    if magnitude == 0 then
        return Vec2:new()
    else
        return Vec2:new(self.x / magnitude, self.y / magnitude)
    end
end

function Vec2.__tostring(a)
    return "(" .. a.x .. ", " .. a.y .. ")"
end

Vector.Vec2 = Vec2
return Vector