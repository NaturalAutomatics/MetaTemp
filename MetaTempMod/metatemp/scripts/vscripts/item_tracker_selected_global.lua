-- item_tracker_selected.lua

ItemTracker = {}  -- Global table to store our functions

local trackedItems = {}

function ItemTracker.Initialize()
    print("Item Tracker Script Initialized")
    -- Add any initialization code here
end

function ItemTracker.AddTrackedItem(item)
    table.insert(trackedItems, item)
    print("Added item to track: " .. item:GetName())
end

function ItemTracker.RemoveTrackedItem(item)
    for i, trackedItem in ipairs(trackedItems) do
        if trackedItem == item then
            table.remove(trackedItems, i)
            print("Removed item from tracking: " .. item:GetName())
            return
        end
    end
end

function ItemTracker.Think()
    -- This function can be called regularly if needed
    for _, item in ipairs(trackedItems) do
        print("Checking item: " .. item:GetName())
    end
end
