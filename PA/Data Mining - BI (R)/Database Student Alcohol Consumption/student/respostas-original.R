setwd(C:\Users\Ana Paula Gonzaga\Desktop\Database Student Alcohol Consumption\student')
rm(list=ls())

install.packages("data.table")
library(data.table)


d1=read.table("student-mat.csv",sep=";",header=TRUE)

d1<-as.data.table(d1)

#analise do número de faltas escolares por consumo semanal de bebidas alcoolicas
ind1<-d1[,.(media=mean(absences), mediana=quantile(absences,0.5), 
            moda=names(which.max(table(absences))),
              dp=sd(absences), var=var(absences)),
                by=.('uso_alcool'=Walc, 'sexo'=sex)]
setorder(ind1, uso_alcool)

#correlacao
with(d1,cor(absences,Walc))
with(d1,cor(absences,health))

#barplot
tab<-prop.table(table(d1$Walc,d1$sex),2)*100

bp<-barplot(tab, beside=TRUE, 
            legend.text =c('Very low','low','regular','high','very high'),
            col=c("darkblue","lightblue","gray","pink","red"),
            horiz = FALSE, ylim = c(0,60), ylab = "%",
            args.legend = list(x="topleft",cex=1,box.lty=0),
            main='Freq. relativa de uso de bebidas por sexo')


#boxplot: faltas escolares por freq. de consumo de bebidas
box<-boxplot(absences~Walc, d1, ylab="Nº faltas escolares", xlab='Consumo de bebidas')
