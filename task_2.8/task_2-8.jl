function draw(r) 
    k = 1
    isExit = !isborder(r, Nord)
    while !isExit
        for _ = 1:k
            move!(r, West)
            if (!isborder(r, Nord)) break end
        end
        if (!isborder(r, Nord)) break end
        k+=1
        for _ = 1:k
            move!(r, Ost)
            if (!isborder(r, Nord)) break end
        end
        if (!isborder(r, Nord)) break end
        k+=1
    end
end