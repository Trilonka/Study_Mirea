function paint(r, counter, k)
    if (counter%2)==1
        while !isborder(r, West)
            move!(r, West)
            putmarker!(r)
        end
    else
        putmarker!(r) 
        for _ = 1:((k-1)-counter)
            move!(r, Ost)
            putmarker!(r)
        end
    end
end

function goToHome(r, bot, right)
    while !isborder(r, West)
        move!(r, West)
    end
    for _ = 1:bot
        move!(r, Nord)
    end
    for _ = 1:right
        move!(r, Ost)
    end
end

function drawPir(r)
    right = 0

    while !isborder(r, West)               
        right += 1
        move!(r, West)       
    end
    
    k = 1
    counter = 1
    bot = 0
    if !isborder(r, Sud) 
        move!(r, Sud)
        bot+=1
        putmarker!(r)
        while !isborder(r, Ost)
            k+=1
            move!(r, Ost)
            putmarker!(r)
        end
        move!(r, Sud)
        bot+=1
    end

    while !isborder(r, Sud)
        if counter==k
            break
        end

        paint(r, counter, k)

        counter+=1
        move!(r, Sud)
        bot+=1
    end

    paint(r, counter, k)

    goToHome(r, bot, right)

end