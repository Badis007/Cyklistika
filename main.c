/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Badis
 *
 * Created on 24. dubna 2020, 15:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SOUBOR "cyklistika.txt"
#define VELIKOST 200
#define ODDELOVAC ";\n"
#define VYSTUP "listina.txt"
/*
 * 
 */
int main(int argc, char** argv) {
    typedef struct{
       int cislo;
       char prijmeni[20];
       char jmeno[20];
       char narodnost[10];
       int rocnik;
       char klub[20];
       char cas[20];
    }CYKLISTI;
    CYKLISTI *cyklisti=NULL;
    
    char retezec [VELIKOST];
    int pocet=0;
    int pocetSloupcu;
    char *pch;
    int i;
    int index=0;
    int max=1958;
    int pocetCechu=0;
    int pocetSlovaku=0;
    int pocetJinych=0;

    FILE * pFile;
    
    if ((pFile = fopen(SOUBOR,"r")) == NULL){ 
        printf("Nebyl otevren vas soubor %s. \n",SOUBOR);
        return EXIT_FAILURE;
    }
    
    while(fgets(retezec,VELIKOST,pFile)!=NULL){
       if(pocet>0){
           cyklisti = (CYKLISTI*) realloc(cyklisti, pocet * sizeof(CYKLISTI));
           pocetSloupcu=1;
           pch = strtok(retezec,ODDELOVAC);
           while(pch!=NULL){
               switch(pocetSloupcu){
               case 1:
                    cyklisti[pocet-1].cislo=atoi(pch);
                    break;
                case 2:
                    strcpy(cyklisti[pocet-1].prijmeni,pch);
                    break;
                case 3:
                    strcpy(cyklisti[pocet-1].jmeno,pch);
                    break; 
                case 4:
                    strcpy(cyklisti[pocet-1].narodnost,pch);
                    break;
                case 5:
                    cyklisti[pocet-1].rocnik=atoi(pch);
                    break;
                case 6:
                    strcpy(cyklisti[pocet-1].klub,pch);
                    break;
                case 7:
                    strcpy(cyklisti[pocet-1].cas,pch);
                    break;
           }
           pch = strtok (NULL,ODDELOVAC);
           pocetSloupcu++;
          } 
       }
       pocet++;
    }
    
    if(fclose(pFile)==EOF){
        printf("Nebyl zavren vas soubor %s\n",SOUBOR);
    }
    
    printf("STARTOVNI LISTINA - OBR DRASAL\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("startovni cislo  |  prijmeni  |  jmeno  |  narodnost  |  rocnik  |               klub               |      cas      |\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    pocet--;
    
    for(i=0;i<pocet;i++){
        printf("%d %23s %9s %10s %12d %35s %15s\n",cyklisti[i].cislo, cyklisti[i].prijmeni, cyklisti[i].jmeno, cyklisti[i].narodnost, cyklisti[i].rocnik, cyklisti[i].klub, cyklisti[i].cas);
        if(cyklisti[i].rocnik==max){
            max=cyklisti[i].rocnik;
            index=i;
        }
        if(strcmp(cyklisti[i].narodnost,"CZE")==0){
            pocetCechu++;
        }
        else if(strcmp(cyklisti[i].narodnost,"SVK")==0){
            pocetSlovaku++;
        }
        else{
            pocetJinych++;
        }
    }
    
    printf("Celkovy pocet zavodniku je %d zavodniku.\n",pocet);
    printf("Nejstarsi zavodnik je %s %s narozen v roce %d je mu %d let.\n",cyklisti[index].jmeno,cyklisti[index].prijmeni,cyklisti[index].rocnik,2020-cyklisti[index].rocnik);
    printf("Zavodnici dle narodnosti: Cesi: %d\n",pocetCechu);
    printf("                          Slovaci: %d\n",pocetSlovaku);
    printf("                          Jine: %d\n",pocetJinych);
    
    if((pFile = fopen(VYSTUP,"w")) == NULL){
        printf("Nebyl otevren vas soubor %s.\n",VYSTUP);
        return EXIT_FAILURE;
    }
    
    fprintf(pFile,"<h1>VYSLEDKOVA LISTINA - OBR DRASAL</h1>");
    fprintf(pFile,"<table><tr>");
    fprintf(pFile,"<th>startovni cislo</th><th>prijmeni</th><th>jmeno</th><th>narodnost</th><th>rocnik</th><th>klub</th><th>cas</th>");
    for(i=0;i<pocet;i++){
        fprintf(pFile,"</tr><tr>");
        fprintf(pFile,"<td>%d</td> <td>%s</td> <td>%s</td> <td>%s</td> <td>%d</td> <td>%s</td> <td>%s</td>",cyklisti[i].cislo, cyklisti[i].prijmeni, cyklisti[i].jmeno, cyklisti[i].narodnost, cyklisti[i].rocnik, cyklisti[i].klub, cyklisti[i].cas);
        fprintf(pFile,"</tr>");
    }

    if(fclose(pFile)==EOF){
        printf("Nebyů zavren vas soubor %s.\n",VYSTUP);
    }else{
        printf("Byl vytvoren soubor %s.\n",VYSTUP);
    }
    
    return (EXIT_SUCCESS);
}

