include("task_func.jl")

function movements!(r, n)
    while !isborder(r, Ost)
        up = 0
        for _ = 1:n
            shag = goToSideWithShag!(r, Ost, n-1, save = true, checkBorder = true, mark = true)[1]
            goToSideWithShag!(r, West, shag)
            putmarker!(r)

            up += goToSideWithShag!(r, Nord, 1, save = true, checkBorder = true)[1]
        end
        goToSideWithShag!(r, Sud, up)
        goToSideWithShag!(r, Ost, 2*n, checkBorder = true)
    end

    goToSide!(r, West)
    goToSideWithShag!(r, Nord, n, checkBorder = true)
end

function draw!(r, n)
    listOfShags = []
    push!(listOfShags, goToSide!(r, Sud, save = true))
    push!(listOfShags, goToSide!(r, West, save = true))

    while !isborder(r, Nord)
        movements!(r, n)

        if isborder(r, Nord) && ismarker(r) break end
        goToSideWithShag!(r, Ost, n, checkBorder = true)

        movements!(r, n)
    end

    goToWestSud!(r)
    goToStart!(r, listOfShags)
end