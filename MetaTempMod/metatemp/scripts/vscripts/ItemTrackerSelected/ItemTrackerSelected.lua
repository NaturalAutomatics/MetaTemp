-- item_tracker.lua

-- List of specific models to track (Cold)
local trackedModels = {
    "models/props/beer_bottle_1.vmdl",
    "models/breakable_props/bottle_o_gin.vmdl",
    "models/props/distillery/bottle_vodka.vmdl"
    -- Add more model paths as needed
}

print("ItemTrackerSelected Script Called!")

-- Function to call when an item is picked up
local function OnItemPickedUp(activator, caller)
    print("OnItemPickedUp Called!")
    if activator:IsPlayer() then
        local modelName = caller:GetModelName()
        if table.contains(trackedModels, modelName) then
            print("Player took " .. modelName .. " in hands")
            
            -- Call MetaTempDriver script
            -- Assuming MetaTempDriver.NotifyItemPickup is the function to call
            if MetaTempDriver and MetaTempDriver.NotifyItemPickup then
                MetaTempDriver.NotifyItemPickup(modelName)
            else
                print("Warning: MetaTempDriver.NotifyItemPickup not found")
            end
        end
    end
end

-- Helper function to check if a value is in a table
function table.contains(table, element)
    for _, value in pairs(table) do
        if value == element then
            return true
        end
    end
    return false
end

-- Find all prop_physics entities in the map
local allProps = Entities:FindAllByClassname("prop_physics")

-- Connect the OnPlayerPickup output to our function for each prop
for _, prop in pairs(allProps) do
    if table.contains(trackedModels, prop:GetModelName()) then
        prop:ConnectOutput("OnPlayerPickup", "OnItemPickedUp")
    end
end

print("Item tracker initialized for " .. #trackedModels .. " models")
