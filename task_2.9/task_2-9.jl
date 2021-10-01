function check(r) 
    return ismarker(r)
end
function draw(r) 
    k = 2
    a = (1,2,3,0)

    isCom = ismarker(r)
    while !isCom
        move!(r, Nord)
        move!(r, Ost)
        if check(r) break end
        for i = a
            for _ = 1:k
                move!(r, HorizonSide(i))
                if check(r) break end
            end
            if check(r) break end
        end   
        if check(r) break end   
        k+=2
    end
end