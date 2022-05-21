include("task_func.jl")

function drawKrest(r)
    putmarker!(r)
    for side = (Nord, Ost, Sud, West)
        listOfShags = []
        while true
            push!(listOfShags, goToSide!(r, side, save = true, mark = true))
            if isRect(r, side)
                append!(listOfShags, aroundBorder!(r, side, save = true))
                putmarker!(r)
            else
                break
            end     
        end
        goToStart!(r, listOfShags)
    end
end