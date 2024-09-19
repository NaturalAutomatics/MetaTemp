-- item_tracker.lua

-- Function to call when the item is picked up
local function OnItemPickedUp(activator, caller)
    if activator:IsPlayer() then
        print("Player picked up the special item!")
        -- You can add more custom logic here
        -- For example, you might want to trigger other events or update a score
    end
end

-- Find our special item in the map
local special_item = Entities:FindByName(nil, "special_item")

if special_item then
    -- Connect the OnPlayerPickup output to our function
    special_item:ConnectOutput("OnPlayerPickup", "OnItemPickedUp")
else
    print("Warning: special_item not found in the map!")
end
