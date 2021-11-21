include("task_func.jl")

function aroundBorder!(r::Robot, side::HorizonSide; save = false)
    k = 0
    kk = 0
    while isborder(r, side)
        goToSideWithShag!(r, perSide(side), 1)
        k+=1
    end
    goToSideWithShag!(r, side, 1)
    while isborder(r, reverseSide(perSide(side)))
        goToSideWithShag!(r, side, 1)
        kk+=1
    end
    for _ = 1:k
        goToSideWithShag!(r, reverseSide(perSide(side)), 1)
    end
    if save 
        return kk
    end
end

function drawPir(r)
    listOfShags = []
    side = West
    while true
        push!(listOfShags,goToSide!(r, side, save = true))
        if isRect(r, side)
            aroundBorder!(r, side)
        else
            break
        end
    end

    topCount = 0
    k = 0
    while !isborder(r, Nord)
        move!(r, Nord)
        topCount+=1
    end
    while !isborder(r, Ost)
        move!(r, Ost)
    end
    while !isborder(r, West)
        move!(r, West)
        k+=1
    end
    k+=1
    for _ = 1:topCount
        move!(r, Sud)
    end

    botCount = 0
    while !isborder(r, Sud)
        move!(r, Sud)
        botCount+=1
        localK = 0
        if k>0
            localK = 1
            putmarker!(r)
        end
        side = Ost
        while true
            while !isborder(r, side) && localK<k
                move!(r, side)
                putmarker!(r)
                localK+=1
            end
    
            if localK<k
                if isRect(r, side)
                    localK += aroundBorder!(r, side, save = true)
                    putmarker!(r)
                    localK+=1
                else
                    break
                end
            else
                break
            end
        end
        k-=1
        side = West
        while true
            while !isborder(r, side)
                move!(r, side)
            end
    
            if isRect(r, side)
                aroundBorder!(r, side)
            else
                break
            end
        end
    end

    for _ = 1:botCount
        move!(r, Nord)
    end

    for el = listOfShags
        goToSideWithShag!(r, Ost, el[1])
        if isborder(r, Ost)
            aroundBorder!(r, Ost)
        end
    end
end