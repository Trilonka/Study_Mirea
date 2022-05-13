using LinearAlgebra

function reverse_gauss_1(A,b)
    x = similar(b)
    N = size(A, 1)
    for k in 0:N-1
        x[N-k] = (b[N-k] - sum(@view(A[N-k,N-k+1:N]) .* @view(x[N-k+1:N])))/A[N-k,N-k]
    end
    return x
end

function reverse_gauss(Ab)
#Ab - транспонированная расширенная матрица
    N = size(Ab, 2)
    x = Vector{eltype(Ab)}(undef,N)

    for k in 0:N-1
        x[N-k] = (Ab[N-k, N] - dot(@view(Ab[N-k+1:N, N-k]), @view(x[N-k+1:N])))/Ab[N-k,N-k]
    end
    return x
end

function upper_triangular(N::Integer)
    A = randn(N, N)
    _, A = lu(A)
    return A
end

function upper_triangular_bad(N::Integer)
    A = zeros(N,N)
    for i in 1:N
        A[i,i+1:N] = randn(N-i)
        A[i,i] = 1.0
    end
    return A
end

######
N=10_000
A = upper_triangular(N)
b = ones(N)
Abt=[A b]

println("1:")
@time reverse_gauss_1(A,b);

println("2:")
@time reverse_gauss(Abt);
println("...................")
########


#######################################################
#---------------------------------------------------------------

function add_1(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A) == size(B)
    C = similar(A)
    for i in 1:size(A,1), j in 1:size(A,2) #
        C[i,j] = A[i,j] + B[i,j]
    end
    #= это эквивалентно:
    for i in 1:size(A,1)
        for j in 1:size(A,2)
            C[i,j] = A[i,j] + B[i,j]
        end
    end
    =#
    return C
end

function add_2(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A) == size(B)
    C = similar(A)
    for  j in 1:size(A,2), i in 1:size(A,1) # - это более педпочтиельный вариант (преимущество проявляется на больших матрицах)
        C[i,j] = A[i,j] + B[i,j]
    end
    return C
end

using LinearAlgebra

function mul(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    At=A'
    for j in 1:size(C,2), i in 1:size(C,1)
        p=0.0
        for k in 1:size(A,2) # size(A,2) == size(B, 1)
            p += At[k,i]*B[k,j]
        end
        C[i,j] = p
    end
    return C
end

function mul_1(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    for i in 1:size(C,1), j in 1:size(C,2)
        @views C[i,j] = dot(A[i,:],B[:,j])
    end
    #= это эквивалентно:
    for i in 1:size(C,1), j in 1:size(C,2)
        C[i,j] = T(0)
        for k in 1:size(A,2) # size(A,2) == size(B, 1)
            C[i,j] += A[i,k]*conj(B[k,j])
        end
    end
    =#
    return C
end

function mul_2(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    for j in 1:size(C,2), i in 1:size(C,1)
        @views C[i,j] = dot(A[i,:], B[:,j])
    end
    return C
end

function mul_3(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    At = A'
    for j in 1:size(C,2), i in 1:size(C,1)
        @views C[i,j] = dot(At[:,i], B[:,j])
    end
    return C
end
#----------------------------------------------------
print("N = ")
N = parse(Int, readline())
#=
При N=10_000 выигрыш примерно на порядок
при N=1000 он всего раза в два
=#
A = randn(N,N)
B = randn(N,N)
println("Варианты реализации сложения матриц:")
@time add_1(A,B);
@time add_2(A,B);
println("Варианты реализации перемножения матриц:")
@time mul(A,B);
#=
@time mul_1(A,B);
@time mul_2(A,B);
@time mul_3(A,B);
=#
println()
