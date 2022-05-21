using HorizonSideRobots

function goToSide!(r::Robot, side::HorizonSide; save::Bool=false)::Union{Tuple{Int, HorizonSide}, Nothing}
    if save
        shags = 0
        while !isborder(r, side)
            move!(r, side)
            shags+=1
        end
        return (shags, reverseSide(side))
    else
        while !isborder(r, side)
            move!(r, side)
        end
    end
end

function goToSideWithShag!(r::Robot, side::HorizonSide, shags::Int; save::Bool=false, checkBorder::Bool = false)::Union{Tuple{Int, HorizonSide}, Nothing}
    if save
        shag = 0
        for _ = 1:shags
            if checkBorder && isborder(r, side) break end
            move!(r, side)
            shag+=1
        end
        return (shag, reverseSide(side))
    else
        for _ = 1:shags
            if checkBorder && isborder(r, side) break end
            move!(r, side)
        end
    end
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