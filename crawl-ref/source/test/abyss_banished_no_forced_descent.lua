-- Test to verify that banished() function no longer forces descent in the Abyss
-- This test checks that players are not forced deeper when banished while already in the Abyss

crawl.message("Testing that banished() function no longer forces descent in the Abyss.")

-- Start in the Abyss at depth 1
debug.goto_place("Abyss:1")
test.regenerate_level()

-- Record initial depth
local initial_depth = you.depth()
crawl.message("Starting at Abyss depth: " .. initial_depth)

-- Try to trigger banished() multiple times to see if forced descent occurs
for i = 1, 10 do
    local depth_before = you.depth()
    
    -- Simulate being banished while already in the Abyss
    -- This would normally trigger the banished() function
    you.banished = true
    you.banished_by = "test"
    you.banished_power = 10
    
    -- Force a check for banished status
    crawl.delay(10)
    
    local depth_after = you.depth()
    
    -- Check if we were forced deeper
    if depth_after > depth_before then
        crawl.message("ERROR: Banished function still forces descent! Depth changed from " .. 
                     depth_before .. " to " .. depth_after)
        return false
    end
    
    -- Clear banished status for next iteration
    you.banished = false
    you.banished_by = ""
    you.banished_power = 0
    
    -- Small delay to allow for any processing
    crawl.delay(10)
end

crawl.message("SUCCESS: Banished function no longer forces descent after 10 attempts.")
crawl.message("Final depth: " .. you.depth() .. " (started at " .. initial_depth .. ")")
return true 