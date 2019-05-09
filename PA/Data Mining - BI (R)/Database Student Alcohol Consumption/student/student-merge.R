d1=read.table("student-mat.csv",sep=";",header=TRUE)

d2=read.table("student-por.csv",sep=";",header=TRUE)


d3=merge(d1,d2,by=c("school","sex","age","address","famsize","Pstatus","Medu","Fedu","Mjob","Fjob","reason","nursery","internet"))

print(nrow(d3)) # 382 students


total <- rbind(d1,d2)   juntar as 2

total[,"Alc"]<-c(Alc)   adicionar a coluna Alc

Alc<-total[,((Walc*2)+(Dalc*5))/7]   conta do Alc
format(round(Alc<-total[,((Walc*2)+(Dalc*5))/7]), nsmall=2)

round(x, digits=2)




d3=merge(d1,d2,by=c(V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V20,V22))






> total<-as.data.table(total)
> indtotal<-total[,.(Media=mean(absences), Mediana=quantile(absences,0.5),Moda=names(which.max(table(absences))), DP=sd(absences), Var=var(absences)), by=.('uso_alcool'=Walc, 'sexo'=sex)]
> setorder(indtotal, uso_alcool)
> View(indtotal)