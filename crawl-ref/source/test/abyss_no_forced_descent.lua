-- Test to verify that forced descent has been removed from the Abyss
-- This test checks that players are not forced deeper when teleporting in the Abyss

crawl.message("Testing that forced descent has been removed from the Abyss.")

-- Start in the Abyss at depth 1
debug.goto_place("Abyss:1")
test.regenerate_level()

-- Record initial depth
local initial_depth = you.depth()
crawl.message("Starting at Abyss depth: " .. initial_depth)

-- Try to trigger teleportation multiple times to see if forced descent occurs
for i = 1, 20 do
    local depth_before = you.depth()
    
    -- Force a teleport by moving to a random location
    you.teleport_to(68, 5 + crawl.random2(50))
    
    local depth_after = you.depth()
    
    -- Check if we were forced deeper
    if depth_after > depth_before then
        crawl.message("ERROR: Forced descent still occurs! Depth changed from " .. 
                     depth_before .. " to " .. depth_after)
        return false
    end
    
    -- Small delay to allow for any processing
    crawl.delay(10)
end

crawl.message("SUCCESS: No forced descent detected after 20 teleport attempts.")
crawl.message("Final depth: " .. you.depth() .. " (started at " .. initial_depth .. ")")
return true 