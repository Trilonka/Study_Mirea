function drawKrest(r)
    temper = temperature(r)
    list = (Nord, Sud, Nord,  Ost, West, Ost)
    pos = 0

    for el in list
        pos += 1
        
        while !isborder(r, el)

            if pos%3==0 && temperature(r) == temper
                break
            end

            putmarker!(r)
            move!(r, el)

        end

        putmarker!(r)       
    end
end