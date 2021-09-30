function change(k)
    if k==1
        return 0
    else
        return 1
    end
end

function mark(r, k)
    if k==1
        putmarker!(r)
    end
end

function draw(r)
    k = 1
    right = 0
    bot = 0
    putmarker!(r)
    while !isborder(r, West)
        move!(r, West)
        k = change(k)
        right+=1
    end
    while !isborder(r, Nord)
        move!(r, Nord)
        k = change(k)
        bot+=1
    end

    mark(r, k)
    while !isborder(r, Ost)
        move!(r, Ost)
        k = change(k)
        mark(r, k)
    end

    while !isborder(r, Sud)
        move!(r, Sud)
        k = change(k)
        mark(r, k)

        while !isborder(r, West)
            move!(r, West)
            k = change(k)
            mark(r, k)
        end

        if !isborder(r, Sud) 
            move!(r, Sud)
            k = change(k)
            mark(r, k)
            while !isborder(r, Ost)
                move!(r, Ost)
                k = change(k)
                mark(r, k)
            end
        end
    end

    while !isborder(r, West)
        move!(r, West)
    end
    while !isborder(r, Nord)
        move!(r, Nord)
    end

    for _ = 1:right
        move!(r, Ost)
    end
    for _ = 1:bot
        move!(r, Sud)
    end
end