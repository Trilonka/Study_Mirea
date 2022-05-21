include("sorted.jl")
function sortkey(key_values, a)
    indperm = sortperm(key_values)
    return a[indperm]
end

function sortkey(f::Function, a)
    key_values = []
    for i in a
        append!(key_values, f(i))
    end
    sortkey(key_values, a)
end

function sortkeymatrix(A::Matrix)
    vec_of_colons = [@view A[:,j] for j in 1:size(A,2)]
    sorted1_vec_of_colons = sortkey(a -> sum(a), vec_of_colons)
    sorted2_vec_of_colons = sortkey(a -> sum(map(iszero, a)), vec_of_colons)
    hcat(sorted1_vec_of_colons...)
    hcat(sorted2_vec_of_colons...)
end

function calcsort(values, array) 
    pom = zeros(values[length(values)])
    for i in 1:length(array)
        pom[array[i]] += 1
    end
    pos = 1
    for i in 1:length(values)
        for _ in 1:pom[i]
            array[pos] = values[i]
            pos += 1
        end
    end
    return array
end

function calcsort(head, tail, array) 
    values = []
    for i in head:tail
        append!(values, i)
    end
    return calcsort(values, array)
end

function insertsortperm(A)
    indecies = []
    for i in 1:length(A)
        append!(indecies, i)
    end
    for j = 2:length(A)
        key = A[j]
        ikey = indecies[j]
        i = j-1
        while (i > 0 && A[i] > key)
            A[i + 1] = A[i]
            indecies[i + 1] = indecies[i]
            i = i - 1
        end
        A[i+1] = key
        indecies[i+1] = ikey
    end
    println(A)
end

function insertsort(A)
    for j = 2:length(A)
        key = A[j]
        i = j-1
        while (i > 0 && A[i] > key)
            A[i + 1] = A[i]
            i = i - 1
        end
        A[i+1] = key
    end
    println(A)
end

function insertsortbinary(A)
    for j = 2:length(A)
        key = A[j]
        i = searchsortedfirst(A[1:j-1], key)
        for k in j-1:-1:i
            A[k + 1] = A[k]
        end
        A[i] = key
    end
    println(A)
end