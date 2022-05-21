function goToWest(r)
    counter = 0
    
    while !isborder(r, West)
        counter+=1
        move!(r, West)
    end
    putmarker!(r)

    return counter
end

function chooseDirect(r) 
    isborder(r, Sud) ? move!(r, Ost) : move!(r, Sud)
end

function putMarkers(r)
    directions = (Sud, Ost, Nord, West, Sud)

    for direct = directions
        while !isborder(r, direct) && !ismarker(r)
            putmarker!(r)
            move!(r, direct)
        end
    end
end

function goToStart(r, counter)
    for _ = 1:counter
        move!(r, Ost)
    end
end

function drawPerim(r) 
    counter = goToWest(r)

    chooseDirect(r)

    putMarkers(r)
    
    goToStart(r, counter)
end