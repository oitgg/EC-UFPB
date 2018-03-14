rm(list=ls())

install.packages("data.table")
library(data.table)


d1=read.table("student-mat.csv",sep=";",header=TRUE)

d1<-as.data.table(d1)

#analise do número de faltas escolares por consumo semanal de bebidas alcoolicas
ind1<-total[,.(Media=mean(absences), Mediana=quantile(absences,0.5), 
            Moda=names(which.max(table(absences))),
              DP=sd(absences), Var=var(absences)),
                by=.('uso_alcool'=Alc, 'sexo'=sex)]
setorder(ind1, uso_alcool)

#correlacao
with(total,cor(absences,Alc))
with(total,cor(absences,health))

#barplot
tab<-prop.table(table(total$Alc,total$sex),2)*100

bp<-barplot(tab, beside=TRUE, 
            legend.text =c('Muito Baixo','Baixo','Regular','Alto','Muito Alto'),
            col=c("darkblue","lightblue","gray","pink","red"),
            horiz = FALSE, ylim = c(0,60), ylab = "%",
            args.legend = list(x="topleft",cex=1,box.lty=0),
            main='Frequência entre uso de bebidas alcoólicas e sexo')


#boxplot: faltas escolares por frequência de consumo de bebidas
box<-boxplot(absences~Alc, total, ylab="Número de faltas escolares", xlab='Consumo de bebidas alcoólicas')