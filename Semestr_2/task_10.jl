function transform_to_steps!(A::AbstractMatrix; epsilon = 1e-7, degenerate_exeption = true)
   # @inbounds - заметного ускорения здесь это не даёт!!!
   for k ∈ 1:size(A, 1)
        absval, Δk = findmax(abs, @view(A[k:end,k]))
        (degenerate_exeption && absval <= epsilon) && throw("Вырожденая матрица")
        Δk > 1 && swap!(@view(A[k,k:end]), @view(A[k+Δk-1,k:end]))
        for i ∈ k+1:size(A,1)
            t = A[i,k]/A[k,k]
            @. @views A[i,k:end] = A[i,k:end] - t * A[k,k:end]
            # макрос @. заменяет все "сквозные точки"
            # макрос @views заменяет многократное применение макроса @view
        end
    end
    return A
end

function swap!(A,B)
    for i in eachindex(A)
        A[i], B[i] = B[i], A[i]
    end
end

function swap_2!(A, i, iMax, k)
    A[i, k], A[iMax, k] = A[iMax, k], A[i, k]
end


function transform_to_steps_2!(a::Matrix)
    countSwaps = 1
    c = a
    eps = 0.000001
    for i = 1:size(a, 1)
        iMax = i
        for j = i:size(a, 1)
            if abs(c[j, i]) > abs(c[iMax, i])
                iMax = j
            end
        end
        if abs(c[iMax, i]) >= eps
            for k = 1:size(a, 2)
                swap_2!(c, i, iMax, k)
            end
            countSwaps = -countSwaps * (i != iMax ? 1 : -1)

            for j = i+1:size(a, 1)
                q = -c[j, i] / c[i, i]
                for k = size(a, 2):-1:i
                    c[j, k] += q*c[i, k]
                    if abs(c[j, k]) < eps
                        c[j, k] = 0
                    end
                end
            end
        end
    end
    if countSwaps > 0
        c * -1
    end
    c
end

function transform_to_steps_edit!(A::AbstractMatrix; epsilon = 1e-7, degenerate_exeption = true)
    ans = []
    for k ∈ 1:size(A, 1)
        absval, Δk = findmax(abs, @view(A[k:end,k]))
        (degenerate_exeption && absval <= epsilon) && throw("Вырожденая матрица")
        Δk > 1 && swap!(@view(A[k,k:end]), @view(A[k+Δk-1,k:end]))
        for i ∈ k+1:size(A,1)
            t = A[i,k]/A[k,k]
            @. @views A[i,k:end] = A[i,k:end] - t * A[k,k:end]
        end
    end
    for i = 1:size(A,1)
        for j = i:size(A,2)
            if abs(A[i, j]) > epsilon
                push!(ans, j)
                break;
            end
        end
    end
    return ans
end

function rank_(B::AbstractMatrix; epsilon = 1e-7, degenerate_exeption = true)
    ans = []
    A = copy(B)
    for k ∈ 1:size(A, 1)
        absval, Δk = findmax(abs, @view(A[k:end,k]))
        (degenerate_exeption && absval <= epsilon) && throw("Вырожденая матрица")
        Δk > 1 && swap!(@view(A[k,k:end]), @view(A[k+Δk-1,k:end]))
        for i ∈ k+1:size(A,1)
            t = A[i,k]/A[k,k]
            @. @views A[i,k:end] = A[i,k:end] - t * A[k,k:end]
        end
    end
    for i = 1:size(A,1)
        for j = i:size(A,2)
            if abs(A[i, j]) > epsilon
                push!(ans, j)
                break;
            end
        end
    end
    return length(ans)
end

function det_(a)
    ans = 1
    epsilon = 1e-7
    s = 1
    c = copy(a)
    for k ∈ 1:size(c, 1)
         absval, Δk = findmax(abs, @view(c[k:end,k]))
         Δk > 1 && swap!(@view(c[k,k:end]), @view(c[k+Δk-1,k:end]))
         if Δk > 1
             s*=-1
         end
         for i ∈ k+1:size(c,1)
             t = c[i,k]/c[k,k]
             @. @views c[i,k:end] = c[i,k:end] - t * c[k,k:end]
         end
    end
    for i = 1:size(c, 1)
        ans*=c[i, i]
    end
    ans*s
end

function slau(A, b)
    countSwaps = 1
    a = [A b]
    c = copy(a)
    eps = 0.000001
    for i = 1:size(a, 1)
        iMax = i
        for j = i:size(a, 1)
            if abs(c[j, i]) > abs(c[iMax, i])
                iMax = j
            end
        end
        if abs(c[iMax, i]) >= eps
            for k = 1:size(a, 2)
                swap_2!(c, i, iMax, k)
            end
            countSwaps = -countSwaps * (i != iMax ? 1 : -1)

            for j = i+1:size(a, 1)
                q = -c[j, i] / c[i, i]
                for k = size(a, 2):-1:i
                    c[j, k] += q*c[i, k]
                    if abs(c[j, k]) < eps
                        c[j, k] = 0
                    end
                end
            end
        end
    end
    if countSwaps > 0
        c * -1
    end
    c[size(a, 1), size(a, 1)+1] /= c[size(a, 1), size(a, 1)]
    c[size(a, 1), size(a, 1)] = 1
    v = []
    for i = size(a, 1):-1:1
        t = c[i, size(a, 1)+1]
        for j = i+1:size(a, 1)
            t-=c[j]*c[i,j]
        end
        c[size(a, 1), i] = t
    end
    c[size(a,1),1:size(a,1)]
end

function inv_(a)
    c = copy(a)
    for i = 1:size(c, 1)
        for j = i+1:size(c, 1)
            c[i,j], c[j,i] = c[j,i], c[i,j]
        end
    end
    c
end
function transform_to_low_steps!(A::AbstractMatrix; epsilon = 1e-7, degenerate_exeption = true)
   # @inbounds - заметного ускорения здесь это не даёт!!!
   for k ∈ size(A, 1):-1:1
        absval, Δk = findmax(abs, @view(A[k:end,k]))
        (degenerate_exeption && absval <= epsilon) && throw("Вырожденая матрица")
        Δk > 1 && swap!(@view(A[k,k:end]), @view(A[k+Δk-1,k:end]))
        for i ∈ k-1:-1:1
            t = A[i,k]/A[k,k]
            @. @views A[i,k:end] = A[i,k:end] - t * A[k,k:end]
            # макрос @. заменяет все "сквоные точки"
            # макрос @views заменяет многократное применение макроса @view
        end
    end
    return A
end
