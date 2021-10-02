include("task_func.jl")

function draw(r)
    putmarker!(r)
    for side = (Nord, Sud) 
        listOfShags = []
        k = 1
        k2, k3, lastk2, lastk3 = 0, 0, 0, 0
        while !isborder(r, side)
            push!(listOfShags, goToSideWithShag!(r, side, 1, save=true))

            lastk2 = k2
            k2 = goToSideWithShag!(r, West, k, save = true, checkBorder = true)[1]
            if lastk2!=k2 putmarker!(r) end

            lastk3 = k3
            k3 = goToSideWithShag!(r, Ost, k+k2, save = true, checkBorder = true)[1]
            if lastk3!=k3 putmarker!(r) end

            goToSideWithShag!(r, West, k3-k2, save = false, checkBorder = false)
            k+=1
        end
        goToStart!(r, listOfShags)
    end
end