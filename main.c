#include <stdio.h> 

#include <string.h> 

int main (int argc, char *argv[]) { 

char nombre[50]; 

printf("Ingrese el texto: "); 
fflush(stdin); 

fgets(nombre,50,stdin); 

 int len = strlen(nombre) - 1; 

if (nombre[len] == '\n') { 

nombre[len] = '\0'; 

} 

int num_palabras = 0; 

int max_longitud = 0; 

int min_longitud = 50; 

int longitud_actual_palabra = 0; 

for (int i = 0; i < len; i++) { 


    printf("%c\n", nombre[i]); 

    if (nombre[i] != ' ' && nombre[i] != '\0') { 

    longitud_actual_palabra++; 

  } else if (longitud_actual_palabra > 0) { 

num_palabras++; 


  if (longitud_actual_palabra > max_longitud) { 

 max_longitud = longitud_actual_palabra;  

}

if (longitud_actual_palabra < min_longitud) { 

min_longitud = longitud_actual_palabra; 

} 

longitud_actual_palabra = 0; 
} 

} 

 if (longitud_actual_palabra > 0) { 

num_palabras++; 

if (longitud_actual_palabra > max_longitud) { 

 max_longitud = longitud_actual_palabra; 

 } 


 if (longitud_actual_palabra < min_longitud) { 

 min_longitud = longitud_actual_palabra; 

    } 

  } 

 printf("\nNumero de palabras: %d\n", num_palabras); 

 printf("Caracteres de la palabra mas pequena: %d\n", min_longitud); 

 printf("Caracteres de la palabra mas grande: %d\n", max_longitud); 

 
return 0; 

}