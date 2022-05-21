function tryToMove(r, side, movesList)
    moves = 0
    localMoves = 0
    push!(movesList, 0)
    while !isborder(r, perSide(side))
        localMoves += 1
        move!(r, perSide(side))
        movesList[end] += 1

        if !isborder(r, side)
            moves = localMoves
            break
        end
    end
    return moves
end

function perSide(side::HorizonSide)::HorizonSide
    return HorizonSide((Integer(side)+1)%4)
end

function reverseSide(side)
    return HorizonSide((Integer(side)+2)%4)
end

function toSide(r, side, movesList)
    moves = 1
    while moves > 0
        push!(movesList, 0)
        while !isborder(r, side)
            movesList[end]+=1
            move!(r, side)
            putmarker!(r)
        end
        moves = tryToMove(r, side, movesList)
        if moves > 0
            moveAround(r, side, moves, movesList)
        end
    end
end

function moveAround(r, side, moves, movesList)
    reSide = reverseSide(perSide(side))
    push!(movesList, 0)
    movesList[end] += 1
    move!(r, side)
    while isborder(r, reSide)
        move!(r, side)
        movesList[end] += 1
        if !isborder(r, reSide)
            break
        end
    end
    push!(movesList, 0)
    for _ = 1:moves
        move!(r, reSide)
        movesList[end] += 1
    end
    putmarker!(r)
end

function goToStart(r, side, movesList)
    reverse!(movesList)
    for i = 1:length(movesList)
        if i%2 == 0
            for _ = 1:movesList[i]
                move!(r, reverseSide(side))
            end
        elseif i%4 == 3
            for _ = 1:movesList[i]
                move!(r, perSide(side))
            end
        else
            for _ = 1:movesList[i]
                move!(r, reverseSide(perSide(side)))
            end
        end
    end
end

function draw(r)
    putmarker!(r)
    for i = 0:3
        movesList = []
        toSide(r, HorizonSide(i), movesList)
        goToStart(r, HorizonSide(i), movesList)
    end
end