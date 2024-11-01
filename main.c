#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void predictAndPrintAll(struct keysPredict* kt, char* partialWord ) {
    char** words;
    int wordsCount;
    words = keysPredictRun(kt, partialWord, &wordsCount);
    printf("Predicts: %s = ", partialWord);
    for(int i=0; i<wordsCount; i++) {
        printf("%s,", words[i]);
    }
    printf("\n");
    deleteArrayOfWords(words, wordsCount);
}

void findAndPrintAll(struct keysPredict* kt, char* word ) {
    struct node* result = keysPredictFind(kt, word);
    printf("Find: %s = %i\n", word, result==0);
}

int main() {
	// EJERCICIO 4
	
	// strLen
	char* a = "";
	char* b = "a";
	char* c = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	
	int aLen = strLen(a); // String vacio
	int bLen = strLen(b); // String de un caracter
	int cLen = strLen(c); // Todos los caracteres alfanumericos
	
	printf("El string \"%s\" mide %i\n", a, aLen);
	printf("El string \"%s\" mide %i\n", b, bLen);
	printf("El string \"%s\" mide %i\n", c, cLen);
	
	// strDup
	char* aDup = strDup(a); // String vacio
	char* bDup = strDup(b); // String de un caracter
	char* cDup = strDup(c); // Todos los caracteres alfanumerico
	
	printf("strDup(\"%s\") = \"%s\"\n", a, aDup);
	printf("strDup(\"%s\") = \"%s\"\n", b, bDup);
	printf("strDup(\"%s\") = \"%s\"\n", c, cDup);
	
	// keysPredict casos chicos.
	struct keysPredict* kt = keysPredictNew();
	
	// Armar un diccionar con las palabras “alfajor”, “canoa”, “rinoceronte”, “casa” y “rino”.
	keysPredictAddWord(kt, "alfajor");
	keysPredictAddWord(kt, "canoa");
	keysPredictAddWord(kt, "rinoceronte");
	keysPredictAddWord(kt, "casa");
	keysPredictAddWord(kt, "rino");
	
	keysPredictPrint(kt);
	
	// Borrar la palabra “canoa” y agregar la palabra “pato”.
	keysPredictRemoveWord(kt,"canoa");
	keysPredictAddWord(kt, "pato");
	keysPredictPrint(kt);
	
	// Predecir a partir “c”, “ca”, “casa” y “casas”.
	predictAndPrintAll(kt,"c");
	predictAndPrintAll(kt,"ca");
	predictAndPrintAll(kt,"casa");
	predictAndPrintAll(kt,"casas");
	
	keysPredictDelete(kt);
	
	// keysPredict casos grande.
	struct keysPredict* kw = keysPredictNew();
	
	//Agregar 100 palabras a un diccionario
	char* hundredWordsDict[] = {"gato", "perro", "cielo", "flor", "casa", "arbol", "camino", "cabeza", "corazon",
		"dedo", "luz", "fuego", "agua", "tierra", "aire", "sol", "luna", "estrella", "bosque", "rio",
		"nube", "lluvia", "trueno", "wacdwsd", "zanahorias", "oceano", "no", "hoja", "pluma", "lapiz",
		"mano", "pie", "ojos", "nariz", "boca", "diente", "oreja", "espada", "escudo", "puerta",
		"ventana", "pared", "techo", "suelo", "madera", "piedra", "metal", "acero", "oro", "plata",
		"artificial", "river", "vehiculo", "rueda", "escribania", "cuerda", "sonido", "musica", "ritmo", "nota",
		"arte", "pintura", "escultura", "danza", "cancion", "ciudad", "otorrinolaringologia", "pueblo", "calle", "parque",
		"verde", "rojo", "azul", "amarillo", "violeta", "naranja", "blanco", "negro", "gris", "rosa",
		"x", "oscuridad", "felicidad", "tristeza", "alegria", "risa", "llanto", "nieve", "invierno", "verano",
		"primavera", "tecnologia", "miedo", "valentia", "amor", "odio", "esperanza", "affbsfb", "amistad", "suerte"};
	
	for(int i = 0; i < 100; i++) {
		keysPredictAddWord(kw, hundredWordsDict[i]);
	}
	
	printf("Diccionario con 100 palabras:\n");
	keysPredictPrint(kw);
	
	// Borrar la mitad de las palabras del diccionario
	for(int i = 0; i < 50; i++) {
		keysPredictRemoveWord(kw, hundredWordsDict[i]);
	}
	
	int cantidadPalabras;
	printf("Borrar la mitad de las palabras.\n");
	char** newDict = keysPredictListAll(kw, &cantidadPalabras);
	printf("El diccionario ahora tiene %i palabras:\n", cantidadPalabras);
	for(int i = 0; i < cantidadPalabras; i++) {
		printf("%s, ", newDict[i]);
		if((i!=0 && (i%10)==0) || i == cantidadPalabras-1) {
			printf("\n");
		}
	}
	deleteArrayOfWords(newDict, cantidadPalabras);
	
	
	// Predecir todas las combinaciones posibles de prefijos de dos letras.
	predictAndPrintAll(kw,"am");
	predictAndPrintAll(kw,"fe");
	predictAndPrintAll(kw,"gz");
	predictAndPrintAll(kw,"ca");
	predictAndPrintAll(kw,"po");
	predictAndPrintAll(kw,"ve");
	predictAndPrintAll(kw,"es");
	predictAndPrintAll(kw,"ri");
	predictAndPrintAll(kw,"ro");
	
	keysPredictDelete(kw);
	
	return 0;
}
