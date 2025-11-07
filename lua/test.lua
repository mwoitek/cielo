local cielo = require("cielo")

local violet_hex = "#EE82EE"
local violet_rgb = cielo.rgb_from_hex(violet_hex)
assert(type(violet_rgb) == "table")

print(string.format("Violet: Red   = %.5f", violet_rgb.r))
print(string.format("Violet: Green = %.5f", violet_rgb.g))
print(string.format("Violet: Blue  = %.5f", violet_rgb.b))

local invalid_hex = "61de2a"
local ok, msg = pcall(cielo.rgb_from_hex, invalid_hex)
assert(not ok)
print(msg)
