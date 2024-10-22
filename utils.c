#include "utils.h"
#include <stdlib.h>

int strLen(char* src) {
    int c = 0;  // Indice y contador de caracteres.
    while (src[c]!=0){ // Iterador
		c++;
	}
    return c;
}

char* strDup(char* src) {
    
    int longitudSrc = strLen(src);
	
    // Solicitamos la memoria para el string duplicado.
    char* dupStr = (char*)malloc(sizeof(char)*(longitudSrc*2)+1);
	
    // Si el string es NULL, devuelve NULL.
    if(src == NULL) {
		return NULL; 
	}

    // Asignamos cada caracter del string a sus dos apariciones en el duplicado.
	for(int i = 0; i < longitudSrc; i++) {
        dupStr[i] = src[i];
        dupStr[i+longitudSrc] = src[i];
	}
	
    // Agregamos el caracter nulo al final del string.
    dupStr[longitudSrc*2] = 0;
	
    return dupStr;
}

// Auxiliar functions

struct node* findNodeInLevel(struct node** list, char character) {
    struct node* puntero = *list;
    while(puntero->next != 0) {
        puntero = puntero->next;
        if(puntero->character==character) {
            return puntero;
        }
    }
    puntero = NULL;
    return puntero;
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
    struct node* nuevoNodo = (struct node*)malloc(sizeof(struct node));
    nuevoNodo -> character = character;
    nuevoNodo -> next = 0;
    nuevoNodo -> end = 0;
    nuevoNodo -> word = 0;
    nuevoNodo -> down = 0;

    struct node* actual = *list; // Toma el primer nodo de la lista (o NULL).
    
    // Si la lista está vacia o el primer nodo va después, agrega el nuevo nodo primero.
    if (actual == NULL || actual->character > character) {
        nuevoNodo -> next = actual;
        *list = nuevoNodo;
        return nuevoNodo;
    }

    // Busco la posición correcta del nuevo nodo y lo agrego.
    while (actual -> next != NULL && (*(actual->next)).character < character) {
        actual = actual -> next;
    }
    nuevoNodo->next = actual->next;
    actual->next = nuevoNodo;

    return nuevoNodo; // Devuelvo un puntero al nodo agregado.
}

void deleteArrayOfWords(char** words, int wordsCount) {

    if (words == NULL){
        return;
    }
    for(int i=0; i < wordsCount; i++){
        free(words[i]); // Liberamos la memoria de cada string
    }
    free(words); // Liberamos la memoria del arreglo de punteros
}

void addEntireWord(struct node* pointer, char* palabra) {
    for(int i=0; i < strLen(palabra); i++) {
            addSortedNewNodeInLevel(&pointer, palabra[i]);
            if (i==(strLen(palabra)-1)) {
                pointer -> word = palabra;
                pointer -> end = 1;
            }
            pointer = pointer -> down;
        }
}

char sacoPrimeraLetra(char* palabra) {
    char* res = (char*)malloc(sizeof(char));
    while (i < strLen(palabra))
    {
        res[i] = palabra[i+1];
    }
    
    return res
}

// Keys Predict

struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt -> first = 0;
    kt -> totalKeys = 0;
    kt -> totalWords = 0;
    return kt;
}

void keysPredictAddWord(struct keysPredict* kt, char* word) { 
	struct node* puntero = kt->first;
	struct node* letra;
	int nivel = 0;
	
	while (nivel<strLen(word)){
		if (puntero==0){
			for (int i=nivel; i<strLen(word); i++) {
				addSortedNewNodeInLevel(&puntero, word[i]);
				puntero = puntero -> down;
			}
			nivel = strLen(word)-1;
		}
		else {
			letra = findNodeinLevel(&puntero, word[nivel]);
			if (letra==0) {
				letra = addSortedNewNodeInLevel(&puntero, word[nivel]);
				puntero = letra->down;
			}
			else {
				puntero = letra->down
			}
		}
		if (nivel==(strLen(word)-1)) {
			puntero -> word = word;
			puntero -> end = 1;
		}

		nivel++;
	} 
}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    if (kt == NULL || word==NULL || *word== '\0'){
        return
    }
    int longitud = strLen(word);
    struct node* letra = kt->first;
    for(int i=0; i<longitud != NULL;i++){
        letra = findNodeInLevel(&letra, word[i]);
        if(letra == NULL){
            return;
        }
        if (word[i+1] != NULL){
            letra = letra -> down;
        }
    }
    if (letra !=NULL && letra->end == 1){
        letra->end = 0;
        if (letra->word != NULL){
            free(letra->word)
            letra->word = NULL;
        }
        kt->totalWords --;
    }   
    
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {

    int i = 0;

    struct node* puntero = kt -> first;

    while (i < strLen(word))
    {
        puntero = findNodeInLevel(puntero, word[i]);

        if (puntero == NULL) 
        {
            return 0;
        } 
        
        else
        {
            puntero = puntero -> down;
            i++;
        }
    }

    return puntero;
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {

    struct node* punteroInicial = keysPredictFind(kt, partialWord) -> down;

    struct node* punteroSec = punteroInicial;
    
    char** palabras = (char**)malloc(sizeof(char) * (*wordsCount));
    
    int i = 0;

    while (punteroSec -> next != 0) 
    {

        while (punteroSec -> down != 0) 
        {   
            if (punteroSec -> end != 0) 
            {   
                struct node* palabra = puntero -> word;
                
                palabras[i] = palabra;

                i++;
            } 

            punteroSec = punteroSec -> down;
        }
        
        punteroSec = punteroInicial -> next;
        
    }

    
    return palabras;
}

int keysPredictCountWordAux(struct node* n) {

    // COMPLETAR
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {

    // COMPLETAR

    return 0;
}

void keysPredictDelete(struct keysPredict* kt) {

    // COMPLETAR

}

void keysPredictPrint(struct keysPredict* kt) {
    printf("--- Predict --- Keys: %i Words: %i\n", kt->totalKeys, kt->totalWords);
    keysPredictPrintAux(kt->first, 0);
    printf("---\n");
}

void keysPredictPrintAux(struct node* n, int level) {
    if(!n) return;
    struct node* current = n;
    while(current) {
        for(int i=0; i<level;i++) printf(" |   ");
        if(current->end) {
            printf("[%c]\n",current->character);
        } else  {
            printf(" %c \n",current->character);
        }
        keysPredictPrintAux(current->down, level+1);
        current = current->next;
    }
}

