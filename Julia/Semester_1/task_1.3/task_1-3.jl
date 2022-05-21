function goToDirect(r, side)
    while !isborder(r, side)
        move!(r, side)
        putmarker!(r)
    end
end

function goToStart(r)
    while !isborder(r, Sud)
        move!(r, Sud)
    end
    while !isborder(r, West)
        move!(r, West)
    end
end
function drawAll(r)
    top = 0
    right = 0

    while !isborder(r, Sud) || !isborder(r, West)
        if !isborder(r, Sud)
            top += 1
            move!(r, Sud)
        end
        if !isborder(r, West)
            right += 1
            move!(r, West)
        end
    end
    putmarker!(r)


    k = 0
    directions = (Ost, West)

    while !isborder(r, Nord)
        goToDirect(r, directions[k%2+1])
        move!(r, Nord)
        putmarker!(r)
        k += 1
    end
    goToDirect(r, directions[k%2+1])

    goToStart(r)

    for _  = 1:top
        move!(r, Nord)
    end
    for _ = 1:right
        move!(r, Ost)
    end
end

