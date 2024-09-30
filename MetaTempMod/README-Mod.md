# VR Object Tracking in Half-Life: Alyx

This guide explains how to track specific VR objects when a player interacts with them in Half-Life: Alyx.

## Implementation Steps

1. **Identify the specific model**
   - Determine the exact name or class of the model you want to track.
   - For this example, we'll use a unique item called "special_item".
    
    The models to track:
    - `"models/props/example_model1.vmdl"`
    - `"models/props/example_model2.vmdl"`
    - `"models/props/example_model3.vmdl"`



2. **Create a script**
   - Create a Lua script named "item_tracker.lua" to handle the tracking.

3. **Use entity outputs**
   - Utilize Half-Life: Alyx's entity system, which allows objects to have outputs that fire on certain events.
   - We'll focus on the event when the player picks up the item.

4. **Implement in the map**
   To use the script in your map:
   - Place your special item in the map and give it a unique name (e.g., "special_item").
   - Create a logic_script entity in your map.
   - Set the script file for the logic_script to "item_tracker.lua".
   - Ensure the script runs when the map loads (use the map's logic_auto entity to trigger the script on map start).

5. **Testing**
   - When the player picks up the special item in VR, the OnItemPickedUp function will be called.
   - You'll see a message in the console.
   - Expand this function to implement custom behavior when the event occurs.

## Additional Considerations

- Track item release: Use the "OnPlayerDrop" output to monitor when the player drops the item.
- Multiple item tracking: Modify the script to handle a list of items or create multiple script instances.
- Customization: Adjust the implementation based on your mod or custom map requirements.

## Script Example

```lua
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
