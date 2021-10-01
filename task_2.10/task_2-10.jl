function goToDirect(r, side)
    sum = 0
    n = 0
    while !isborder(r, side)
        move!(r, side)
        if ismarker(r)
            sum+=temperature(r)
            n+=1
        end
    end
    return sum, n
end

function draw(r)
    sum = 0
    n = 0

    if ismarker(r)
        n+=1
        sum+=temperature(r)
    end

    k = 0
    directions = (Ost, West)

    while !isborder(r, Nord)
        sum1, n1 = goToDirect(r, directions[k%2+1])
        sum+=sum1
        n+=n1
        move!(r, Nord)
        if ismarker(r)
            n+=1
            sum+=temperature(r)
        end
        k += 1
    end
    sum1, n1 = goToDirect(r, directions[k%2+1])
    sum+=sum1
    n+=n1
    println(sum/7)
end