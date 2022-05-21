struct Residue{T, M}
    value::T
    Residue{T,M}(value) where {T,M} = new(value % M)
    Base. +(a::Residue{T,M}, b::Residue{T,M}) where{T,M} = (a.value + b.value) % M
    Base. *(a::Residue{T,M}, b::Residue{T,M}) where{T,M} = (a.value * b.value) % M
    function Base.inv(a::Residue{T,M})::Union{Nothing, Residue{T,M}} where{T,M}
        a,b,c = gcdx(a.value, M)
        if a != 1
            return nothing
        else
            if b>0
                return b
            else
                return M+b
            end
        end
    end
    Base. /(a::Residue{T,M}, b::Residue{T,M}) where{T,M} = a * inv(b)
    Base. -(a::Residue{T,M}) where{T,M} = Residue{T,M}(M - a.value)
    Base. -(a::Residue{T,M}, b::Residue{T,M}) where{T,M} = a + (-b)
end

struct Polynomial{T}
    coeff::Vector{T}
    function Polynomial{T}(coeff) where {T}
        i, n = lastindex(coeff), 0
        while i > 0 && coeff[i] == 0
            n += 1
            i -= 1
        end
        # n = число нулей в конце массива coeff, соответсвующих старшим степеням
        resize!(coeff, length(coeff)-n)
        new(coeff[1:end-n])
    end
    deg(p::Polynomial{T}) where{T} = length(p.coeff) - 1
    function Base. +(p::Polynomial{T}, q::Polynomial{T})::Polynomial{T} where {T}
        np, nq = length(p.coeff), length(q.coeff)
        if  np >= nq
            coeff = similar(p.coeff)
            coeff[1:nq] .= (@view(p.coeff[1:nq]) .+ q.coeff)
        else
            coeff = similar(q.coeff)
            coeff[1:np] .= (p.coeff .+ @view(q.coeff[1:np]))
        end
        # При сложении некоторые старшие коэфициенты могли обратиться в 0
        i, n = lastindex(coeff), 0
        while i > 0 && coeff[i] == 0
            n += 1
            i -= 1
        end
        # n = число нулей в конце массива coeff, соответсвующих старшим степеням
        resize!(coeff, length(coeff)-n)
        return Polynomial{T}(coeff)
    end
    function Base. -(p::Polynomial{T}, q::Polynomial{T})::Polynomial{T} where {T}
        np, nq = length(p.coeff), length(q.coeff)
        if  np >= nq
            coeff = similar(p.coeff)
            coeff[1:nq] .= (@view(p.coeff[1:nq]) .- q.coeff)
        else
            coeff = similar(q.coeff)
            coeff[1:np] .= (p.coeff .- @view(q.coeff[1:np]))
        end
        # При вычитании некоторые старшие коэфициенты могли обратиться в 0
        i, n = lastindex(coeff), 0
        while i > 0 && coeff[i] == 0
            n += 1
            i -= 1
        end
        # n = число нулей в конце массива coeff, соответсвующих старшим степеням
        resize!(coeff, length(coeff)-n)
        return Polynomial{T}(coeff)
    end
    function Base. *(p::Polynomial{T}, q::Polynomial{T})::Polynomial{T} where {T}
        coeff = zeros(T, deg(p) + deg(q)+1)
        for i in eachindex(p.coeff), j in eachindex(q.coeff)
                coeff[i+j - 1] += p.coeff[i]*q.coeff[j]
        end
        i, n = lastindex(coeff), 0
        while i > 0 && coeff[i] == 0
            n += 1
            i -= 1
        end
        # n = число нулей в конце массива coeff, соответсвующих старшим степеням
        resize!(coeff, length(coeff)-n)
        return Polynomial{T}(coeff)
    end
    Base. +(p::Polynomial{T}, c::T) where {T} = +(p, Polynomial{T}([c]))
    Base. +(c::T, p::Polynomial{T}) where {T} = +(Polynomial{T}([c]), p)

    Base. -(p::Polynomial{T}, c::T) where {T} = -(p, Polynomial{T}([c]))
    Base. -(c::T, p::Polynomial{T}) where {T} = -(Polynomial{T}([c]), p)

    Base. *(p::Polynomial{T}, c::T) where {T} = *(p, Polynomial{T}([c]))
    Base. *(c::T, p::Polynomial{T}) where {T} = *(Polynomial{T}([c]), p)

    Base.div(p::Polynomial{T}, q::Polynomial{T}) where {T} = divrem(p,q)[1]
    Base.rem(p::Polynomial{T}, q::Polynomial{T}) where {T} = divrem(p,q)[2]

    (p::Polynomial)(x) = polyval(reverse(p.coeff), x)
    function Base.display(p::Polynomial)
        if isempty(p.coeff)
            return ""
        end
        n = length(p.coeff)
        if p.coeff[1]!=0
            n-=1
        end
        str = "$(p.coeff[1])" # $(...) - означает "интерполяцию стоки", т.е. вставку в строку некоторого вычисляемого значения
        for i in 2:length(p.coeff)
            if p.coeff[i]!=0
                n-=1
                if i > 2
                    s = " + $(p.coeff[i])x^$(i-1)"
                else
                    s = " + $(p.coeff[i])x"
                end
                str *= s
            end
        end
        if n==length(p.coeff)
            println(0)
        else
            println(str)
        end
    end
end
