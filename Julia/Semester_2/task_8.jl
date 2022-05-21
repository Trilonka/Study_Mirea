function eyler(n)
    s = 0.0
    a = 1.0
    for k in 1:n+1
    # границы значений индекса k по отношению к прежнему варианту теперь смещены на 1 вправо
        s += a
        a /= k
    end
    s
end # сложность O(n)

function eyler_2()
    s = 0
    a = 1
    k = 0
    while s + a != s
        k += 1
        s += a
        a /= k
    end
    return s
end
#при вычислении `s+a` должны будут складываться соответствующие 53-х битные
# мантиссы (здесь речь идет о формате типа Float64). Но сначала порядок меньшего
# слагаемого должен быть приведен к порядку большего слагаемого путем "сдвига" его
#мантиссы вправо с заменой "освобождающихся" битов нулями. Таким образом, если сдвиг
#составит 53 бита или больше, то мантисса меньшего числа окажется полностью замененной нулями.


function sin_(x)
    a = x
    s = 0
    e = 0.000000001
    k = 1
    while abs(a) > e
        s += a
        k += 1
        a *= -x*x/(2*k-1)/(2*k-2)
    end
    s
end

function sin_(x)
    xx=x^2
    a=x
    m=2
    s=typeof(x)(0)
    while s+a != s
        s+=a
        a=-a*xx/m/(m+1)
        m+=2
    end
    #УТВ: |sin(x)-s| <= 1е-16
    return s
end
#цикл завершится, как только разность двоитчных порядков величин `s` и `a` достигнет
# `53` (что примерно соответствует шестнадцати десятичный порядков).

function exp_(x, eps)
    sum = 1;
    f = x
    k = 2
    while f > eps
        sum += f
        f *= x/k
        k += 1
    end
    sum
end

function harmonic_sum()
    s=0.0
    k=1
    a=1.0
    while s+a != s
        a=1/k
        s+=a
        k+=1
    end
    return s
end

function cos_(x, n)
    mx2 = -x*x
    part = 1
    sum = 1
    for i = 2:2:n
        part *= mx2/((i-1)*i)
        sum += part
    end
    sum
end

function cos_m(x, e = 0.0000000000001)
    s = 0
    an = 1
    n = 0
    while abs(an) > e
        s += an
        n += 1
        an *= -x*x/(2*n-1)/(2*n)
    end
    s
end

#########################

using Plots

#
x = 0:0.1:10
plot(x, cos_.(x, 4))
#
p = plot() # получена ссылка на пустой график
for n in 2:2:8
    plot!(p, x, cos_.(x,n)) # в текущий график добавлена новая кривая
end
display(p)
#
