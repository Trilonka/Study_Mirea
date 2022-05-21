using HorizonSideRobots

function goToSide!(r::Robot, side::HorizonSide; save::Bool=false, mark::Bool = false)::Union{Tuple{Int, HorizonSide}, Nothing}
    if save
        shags = 0
        while !isborder(r, side)
            move!(r, side)
            if mark putmarker!(r) end
            shags+=1
        end
        return (shags, reverseSide(side))
    else
        while !isborder(r, side)
            move!(r, side)
            if mark putmarker!(r) end
        end
    end
end

function goToSideWithShag!(r::Robot, side::HorizonSide, shags::Int; save::Bool = false, checkBorder::Bool = false, mark::Bool = false)::Union{Tuple{Int, HorizonSide}, Nothing}
    if save
        shag = 0
        for _ = 1:shags
            if checkBorder && isborder(r, side) break end
            move!(r, side)
            if mark putmarker!(r) end
            shag+=1
        end
        return (shag, reverseSide(side))
    else
        for _ = 1:shags
            if checkBorder && isborder(r, side) break end
            move!(r, side)
            if mark putmarker!(r) end
        end
    end
end

function aroundBorder!(r::Robot, side::HorizonSide; save::Bool=false)
    listOfShags = []
    k = 0
    while isborder(r, side)
        push!(listOfShags, goToSideWithShag!(r, perSide(side), 1, save = true))
        k+=1
    end
    push!(listOfShags, goToSideWithShag!(r, side, 1, save = true))
    while isborder(r, reverseSide(perSide(side)))
        push!(listOfShags, goToSideWithShag!(r, side, 1, save = true))
    end
    for _ = 1:k
        push!(listOfShags, goToSideWithShag!(r, reverseSide(perSide(side)), 1, save = true))
    end
    if save
        return listOfShags
    end
end

function isRect(r::Robot, side::HorizonSide)::Bool
    result = false
    k = 0
    while !isborder(r, perSide(side))
        move!(r, perSide(side))
        k+=1
        if !isborder(r, side)
            result = true
            break
        end
    end
    for _ = 1:k
        move!(r, reverseSide(perSide(side)))
    end
    return result
end

function reverseSide(side::HorizonSide)::HorizonSide
    return HorizonSide(
        (Integer(side)+2) % 4
    )
end

function perSide(side::HorizonSide)::HorizonSide
    return HorizonSide(
        (Integer(side)+1) % 4
    ) 
end

function goToStart!(r::Robot, listOfShags)::Nothing
    reverse!(listOfShags)
    for tup = listOfShags
        for _ = 1:tup[1]
            move!(r, tup[2])
        end
    end
end

function goToWestSud!(r::Robot)::Nothing
    goToSide!(r, Sud)
    goToSide!(r, West)
end