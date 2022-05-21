library("lmtest")
library("rlms")
library("dplyr")
library("GGally")
library("car")
library("sandwich")


data <- rlms_read("C:\\GoogleDownloads\\r20i_os26c.sav")
glimpse(data)
data2 = select(data, pj13.2, p_age, ph5, p_educ, status, pj6.2, p_marst)
# pj13.2 - зарплата 
# p_age - возраст
# ph5 - пол (1 - мужчины, 2 - женщины)
# p_educ - образование 
# status - тип населенного пункта
# pj6.2 - часы в рабочей неделе
# p_marst - семейное положение

#исключаем строки с отсутствующими значениями NA
data2 = na.omit(data2)
glimpse(data2)

#семейное положение
data2["wed1"] = data2$p_marst # 1 если женат, 0 в противном случае
data2$wed1 = 0
data2$wed1[which(data2$p_marst==2)] <- 1

data2["wed2"] = data2$p_marst # 1 если разведен или вдовец, 0 в противном случае
data2$wed2 = 0
data2$wed2[which(data2$p_marst==4)] <- 1
data2$wed2[which(data2$p_marst==5)] <- 1

data2["wed3"] = data2$p_marst  # 1 если никогда в браке не состоял, 0 в противном случае
data2$wed3 = 0
data2$wed3[which(data2$p_marst==1)] <- 1

glimpse(data2)

# проверим на отсутствие зависимости введеные переменные
testmodel = lm(data = data2, p_marst~wed1 + wed2 + wed3)
vif(testmodel) # коэффициенты vif у каждого низкий (ниже 2.3), поэтому мультиколлинеарности нет, убедились

#пол
data2["sex"] = data2$ph5 # 1 если мужчина, 0 если женщина
data2$sex = 0
data2$sex[which(data2$ph5==1)] <- 1

glimpse(data2)

#населенный пункт
data2["city_status"] = data2$status # 1 если город или областной центр, 0 в противном случае
data2$city_status = 0
data2$city_status[which(data2$status==1)] <- 1
data2$city_status[which(data2$status==2)] <- 1

glimpse(data2)

#образование
data2["higher_educ"] = data2$p_educ # 1 если есть полное высшее образование, 0 в противном случае
data2["higher_educ"] = 0
data2$higher_educ[which(data2$p_educ==21)] <- 1
data2$higher_educ[which(data2$p_educ==22)] <- 1
data2$higher_educ[which(data2$p_educ==23)] <- 1

glimpse(data2)

#возраст c элементами нормализации
age1 = as.character(data2$p_age)
age2 = lapply(age1, as.integer)
age3 = as.numeric(unlist(age2))
data2["age"]= (age3 - mean(age3)) / sqrt(var(age3))

glimpse(data2)

#продолжительность рабочей недели
dur1 = as.character(data2$pj6.2)
dur2 = lapply(dur1, as.integer)
dur3 = as.numeric(unlist(dur2))
data2["dur"] = (dur3 - mean(dur3)) / sqrt(var(dur3))

glimpse(data2)

#зарплата c элементами нормализации
sal1 = as.character(data2$pj13.2)
sal2 = lapply(sal1, as.integer)
sal3 = as.numeric(unlist(sal2))
data2["salary"] = (sal3 - mean(sal3)) / sqrt(var(sal3))

glimpse(data2)

# --------------------Данные подготовлены-------------------------------

data3 = select(data2, salary, age, dur, sex, higher_educ, city_status, wed1, wed2, wed3)
glimpse(data3)

model = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3)
vif(model) # vif для wed1, wed2 и wed3 почти в два раза больше чем у остальных регрессоров (около 2), но все равно допустимый, но попробуем их убрать и посмотреть на изменения Adjusted R-squared
summary(model) # Adjusted R-squared: 0.1718 

model1 = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status)
vif(model1) # vif теперь везде около 1, но Adjusted R-squared уменьшился где-то на 0.002, то есть на 0.2%. Хоть уменьшение и совсем небольшое, все равно оставим wed параметры для дальнейшего анализа.
summary(model1) # Adjusted R-squared:  0.1697

# ------------------------------Модель выбрана---------------------------
# Попробуем подобавлять степени (от 0.1 до 2 с шагом 0.1) и логарифмы вещественных параметров

#начала подберем лучшую степень для параметра age
modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^2))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1868 - вырос, оставим модель в таком виде

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.9))
vif(modela) # некоторые vif коэффициенты почти равны 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.8))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.7))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.6))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.5))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.4))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.3))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.2))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^1.1))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.9))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.8))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.7))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.6))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.5))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.4))
vif(modela) # некоторые vif коэффициенты почти равны 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3))
vif(modela)  # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1891 - вырос, оставим модель в таком виде

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.2))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.189 - не вырос

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.1))
vif(modela)  # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1889 - не вырос

# теперь подберем лучшую степень для параметра dur, с уже введенной лучшей степенью параметра age, а именно I(age^0.3)
modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^2))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1896 - вырос, оставим модель в таком виде

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.9))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1939 - вырос, оставим модель в таком виде

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.8))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1939 - не вырос

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.7))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.194 - вырос, оставим модель в таком виде

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.6))
vif(modela) # некоторые vif коэффициенты почти равны 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.5))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.4))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.3))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.2))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.1))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.9))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.8))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.7))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.6))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.5))
vif(modela) # некоторые vif коэффициенты превышают 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.4))
vif(modela) # некоторые vif коэффициенты почти равны 10

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.3))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1939 - не вырос

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.2))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1938 - не вырос

modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^0.1))
vif(modela) # vif коэффициенты не превышают 10
summary(modela) # Adjusted R-squared:  0.1937 - не вырос

######## в итоге остановимся на следующей модели
modela = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.7))
summary(modela) # Adjusted R-squared:  0.194

# теперь попробуем ввести логарифмы вещественных параметров (только для степеней, тк среди обычных значений есть отрицательные, что недопустимо для логарифма)
modelb = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.7) + log(I(dur^1.7)))
vif(modelb) # некоторые vif коэффициенты превышают 10

modelb = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.7) + log(I(age^0.3)))
vif(modelb) # некоторые vif коэффициенты превышают 10

modelb = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + I(age^0.3) + I(dur^1.7) + log(I(age^0.3)) + log(I(dur^1.7)))
vif(modelb) # некоторые vif коэффициенты превышают 10

# что если убрать квадраты и рассмотреть только добавленные логарифмы?
modelb = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + log(I(age^0.3)))
vif(modelb) # vif не высокий 
summary(modelb) # Adjusted R-squared: 0.1888

modelb = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + log(I(dur^1.7)))
vif(modelb) # vif не высокий 
summary(modelb) # Adjusted R-squared: 0.1715

modelb = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3 + log(I(dur^1.7)) + log(I(age^0.3)))
vif(modelb) # vif не высокий 
summary(modelb) # Adjusted R-squared: 0.1914 
# делаем вывод, что логарифмы не вносят в модель никаких толковых изменений, смысла брать их нет

#----------------Окончательно определились с моделью с Adjusted R-squared = 0.194 (не высокий, но такие уж данные), большая часть параметров значительна-------------------

model = lm(data = data3, salary ~ age + dur + sex + higher_educ + city_status + wed1 + wed2 + wed3)
summary(model) # верннемся к этой модели и сделаем вывод, какие индивиды получают большую зарплату
# коэффициенты:
# age = -0.06407
# dur = 0.128038
# sex = 0.487544
# higher_educ = 0.555539
# city_status = 0.335963
# wed1 = 0.055575
# wed2 = -0.003683
# wed3 = -0.097869
# делаем вывод, что большую зп получают в основном: люди чуть меньше среднего возраста, мужчины, с большей продолжительностью рабочей недели,
# с высшим образованием, живущие в городах. Семейное положение почти никак не связано с уровнем зарплаты.

#---------------не женатые мужчины с вышим образованием------------
dataA = subset(data3, wed1 == 0)
dataB = subset(dataA, higher_educ == 1)
models1 = lm(data = dataB, salary ~ age + dur + sex + city_status + I(age^0.3) + I(dur^1.7))
vif(models1) # vif нормальный
summary(models1) 
# Adjusted R-squared:  0.01704, для такой выборки хоть как-то значителен только sex, все остальные параметры никак не описывают данную выборку, большую за получают примерно те же самые категории людей, что и в целом
# Данные параметры очень плохо описывают данную выборку людей

#---------------городские жители состоящие в браке------------
dataA = subset(data3, wed1 == 1)
dataB = subset(dataA, city_status == 1)

models1 = lm(data = dataB, salary ~ age + dur + sex + higher_educ + I(age^0.3) + I(dur^1.7))
vif(models1) # vif нормальный
summary(models1) 
# Adjusted R-squared:  0.1798, незначительны параметры: I(dur^1.7), а слобо значимы dur и I(age^0.3). По сравнению с общими данными в этой выборке большую зп получают те же самые категории людей. (возраст, продолжительность рабочей недели
# и высшее образование сильно выше по значимости), то есть чаще молодые, больше работающие и более образованные.
# в этой выборке уже больше параметров имеют влияние
