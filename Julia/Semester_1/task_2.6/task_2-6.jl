function goToStart(r, side2, side1, second, first)
    for _ = 1:second
        move!(r, reverseSide(side2))
    end

    for _ = 1:first
        move!(r, reverseSide(side1))
    end
end

function reverseSide(side)
    return HorizonSide((Integer(side)+2)%4)
end

function isFigur(r, side1, side2)
    println(side1, side2)
    first = 0
    second = 0
    isFigure = false
    while !isborder(r, side1)
        first+=1
        move!(r, side1)
    end
    while !isborder(r, side2)
        second+=1
        move!(r, side2)
    end
    if !isborder(r, side1) 
        println(side1)
        isFigure = true
    end
    goToStart(r, side2, side1, second, first)
    return isFigure
end

function toSide(side, r)
    return HorizonSide((Integer(side)+r)%4)
end

function around(r, side)
    k = 0
    while !isborder(r, side)
        move!(r, side)
        k+=1
    end
    putmarker!(r)
    while isborder(r, side)
        putmarker!(r)
        move!(r, toSide(side, 1))
    end
    move!(r, side)
    putmarker!(r)
    while isborder(r, toSide(side, -1))
        putmarker!(r)
        move!(r, side)
    end
    move!(r, toSide(side, -1))
    putmarker!(r)
    while isborder(r, reverseSide(side))
        putmarker!(r)
        move!(r, toSide(side, -1))
    end
    move!(r, reverseSide(side))
    putmarker!(r)
    while isborder(r, toSide(side, 1))
        putmarker!(r)
        move!(r, reverseSide(side))
    end

    move!(r, toSide(side, 1))
    while !ismarker(r)
        putmarker!(r)
        move!(r, toSide(side, 1))
    end
    return k
end


function draw(r) 

    k = 0
    for i = 0:3
        if (isFigur(r, HorizonSide(i), HorizonSide((i+1)%4)))
            k = i
            break
        end
    end

    kk = around(r, HorizonSide(k))

    println(HorizonSide(k))
    println(reverseSide(HorizonSide(k)))
    for _ = 1:kk
        move!(r, reverseSide(HorizonSide(k)))
    end


end