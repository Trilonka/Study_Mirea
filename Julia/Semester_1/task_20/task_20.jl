include("task_func.jl")

function draw(r)
    goToSide!(r, West)
    goToSide!(r, Nord)
    count = 0
    flag = 0
    while(!isborder(r, Sud))
        while(!isborder(r, Ost))
            move!(r, Ost)
            if(flag == 0 && isborder(r, Sud))
                flag = 1
                count += 1
            elseif(flag == 1 && !isborder(r, Sud))
                flag = 0
            end
        end
        move!(r, Sud)
        goToSide!(r, West)
    end
    print(count)
end