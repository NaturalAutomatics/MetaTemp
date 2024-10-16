-- BeerBottleTracker.lua

print("BeerBottleTracker.lua has been loaded!")

local beerBottleModel = "models/props/beer_bottle_1.vmdl"

local function OnBeerBottlePickedUp(activator, caller)
    if activator:IsPlayer() then
        local modelName = caller:GetModelName()
        if modelName == beerBottleModel then
            print("Cheers! The player just picked up a beer bottle!")
        end
    end
end

-- Find all beer bottles in the map and hook up the pickup event
function InitializeBeerBottleTracker()
    print("InitializeBeerBottleTracker function called")
    local ents = Entities:FindAllByModel(beerBottleModel)
    for _, ent in ipairs(ents) do
        ent:ConnectOutput("OnPlayerPickup", "OnBeerBottlePickedUp")
    end
    print("Beer bottle tracker initialized. Found " .. #ents .. " beer bottles.")
end

-- Expose the function to the global scope
if not _G.BeerBottleTracker then
    _G.BeerBottleTracker = {}
end
_G.BeerBottleTracker.Initialize = InitializeBeerBottleTracker

-- Connect the pickup function
Entities:GetLocalPlayer():ConnectOutput("OnBeerBottlePickedUp", "OnBeerBottlePickedUp")

print("BeerBottleTracker.lua has finished loading")
