include("task_func.jl")
function drawAll(r)
    listOfShags = []
    while !isborder(r, West) || !isborder(r, Sud)
        push!(listOfShags, goToSide!(r, West, save = true))
        push!(listOfShags, goToSide!(r, Sud, save = true))
    end
    side = Ost
    putmarker!(r)
    goToSide!(r, Ost, mark = true)
    side = reverseSide(side)
    while !isborder(r, Nord)
        move!(r, Nord)
        putmarker!(r)
        while true
            goToSide!(r, side, mark = true)
            if isRect(r, side)
                aroundBorder!(r, side)
                putmarker!(r)
            else
                break
            end
        end
        side = reverseSide(side)
    end
    goToSide!(r, West)
    goToSide!(r, Sud)
    goToStart!(r, listOfShags)
end