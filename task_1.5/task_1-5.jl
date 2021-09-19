function goToBot!(r)
    moves = []
    pushMoves!(r, moves)
    while moves[end] != 0 && moves[end-1] != 0
        pushMoves!(r, moves)
    end 
    return moves
end

function pushMoves!(r, moves)
    push!(moves, goToWall!(r, Sud))
    push!(moves, goToWall!(r, West))
end

function goToWall!(r, side)
    k = 0
    while !isborder(r, side)
        k+=1
        move!(r, side)
    end
    return k
end

function setMarkers(r)
    sides = [Nord, Ost, Sud, West]
    for side = sides 
        putmarker!(r)
        goToAllLine!(r, side)
    end
end

function goToAllLine!(r, side)
    while !isborder(r, side)
        move!(r, side)
    end
end

function goToStart!(r, moves)
    reverse!(moves)
    for n = 1:length(moves)
        if n%2==1
            moves!(r, Ost, moves[n])
        else
            moves!(r, Nord, moves[n])
        end
    end
end
            

function moves!(r, side, move)
    for _ = 1:move
        move!(r, side)
    end
end

function drawCorners(r)
    moves = goToBot!(r)

    setMarkers(r)

    goToStart!(r, moves)
end 