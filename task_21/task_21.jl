include("task_func.jl")

function hel(r, side, lockSide) 
    count = 0
    flag = 0
    while(!isborder(r, lockSide))
        listOfShags = []
        while(!isborder(r, side) || isRect(r, side))
            if(isRect(r, side)) 
                append!(listOfShags, aroundBorder!(r, side, save = true))
            else
                push!(listOfShags, goToSideWithShag!(r, side, 1, save = true))
            end
            if(flag == 0 && isborder(r, lockSide))
                flag = 1
                count += 1
            elseif(flag == 1 && !isborder(r, lockSide))
                flag = 0
            end
        end
        goToStart!(r, listOfShags)
        move!(r, lockSide)
    end
    return count
end

function draw(r)
    while !isborder(r, Nord) || !isborder(r, West)
        goToSide!(r, Nord)
        goToSide!(r, West)
    end
    answer = 0
    answer += hel(r, Ost, Sud)
    answer += hel(r, Nord, Ost)
    print(answer)
end