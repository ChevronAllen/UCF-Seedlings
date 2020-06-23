name_table = {}

function tick()
    
end

function get_gameobject_properties(id)
    if(name_table[id] != nil) then
        obj = {x=0,y=0,xscale=0,yscale=0,angle=0}
        -- TODO: API function which converts a game object into a table
        return obj
    end
    return nil
end

function create_gameobject(id)
    obj = {} 
    
end