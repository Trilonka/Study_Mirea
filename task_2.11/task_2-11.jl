function movesCounter!(r, list)
    push!(list, goToWall!(r, Sud))
    push!(list, goToWall!(r, West))
    while list[end] != 0 && list[end-1] != 0
        push!(list, goToWall!(r, Sud))
        push!(list, goToWall!(r, West))
    end
end

function goToWall!(r, side)
    k = 0
    while !isborder(r, side)
        k+=1
        move!(r, side)
    end
    return k
end

function countXY(list)
    return sum(list[2:2:end]), sum(list[1:2:end])
end

function rightSide!(r, x, y)
    sides = [Ost, Nord]
    xy = [x, y]
    result = [0, 0]

    for el = 1:2
        makeMove(r, sides[el], xy[el])
        putmarker!(r)
        while !isborder(r, sides[el])
            result[el]+=1
            move!(r, sides[el])
        end
    end

    return result[1], result[2]
end

function leftSide!(r, kx, ky) 
    sides = [West, Sud]
    kxy = [kx, ky]

    for el = 1:2
        makeMove(r, sides[el], kxy[el])
        putmarker!(r)
        while !isborder(r, sides[el])
            move!(r, sides[el])
        end
    end
end

function goToHome!(r, list)
    reverse!(list)
    for n = 1:length(list)
        if n%2==1
            makeMove(r, Ost, list[n])
        else
            makeMove(r, Nord, list[n])
        end
    end
end

function makeMove(r, side, mov)
    for _ = 1:mov
        move!(r, side)
    end
end

function draw!(r)
    list = []

    movesCounter!(r, list)

    x, y = countXY(list)

    kx, ky = rightSide!(r, x, y)

    leftSide!(r, kx, ky) 

    goToHome!(r, list)
end