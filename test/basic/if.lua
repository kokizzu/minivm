
local v = 1
while true do
    local x = if v == 1 then
        "v == 1"
    elseif v == 2 then
        "v == 2"
    elseif v == 3 then
        "v == 3"
    else
        break
    end
    print(x)
    v = v + 1
end