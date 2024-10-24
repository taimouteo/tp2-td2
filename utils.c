#include "utils.h"
#include <stdlib.h>

// Ejercicio 1.

int strLen(char* src) {
    int c = 0;  // Indice y contador de caracteres.
    while (src[c]!=0){ // Iterador
		c++;
	}
    return c;
}

char* strDup(char* src) {
    int longitudSrc = strLen(src);
	
    // Solicitamos memoria para el string duplicado.
    char* dupStr = (char*)malloc(sizeof(char)*(longitudSrc + 1));
	
    // Si el string es NULL, devuelve NULL.
    if(src==0) {
        dupStr = 0;
		return dupStr; 
	}

    // Copiamos el string en duplicado, caracter a caracter.
	for(int i = 0; i < longitudSrc; i++) {
        dupStr[i] = src[i];
	}
	
    // Agregamos el caracter nulo al final del nuevo string duplicado.
    dupStr[longitudSrc] = 0;
	
    return dupStr;
}

// Ejercicio 2.

struct node* findNodeInLevel(struct node** list, char character) {
    // Toma el puntero al nodo.
    struct node* puntero = *list;
    
    while(puntero!=0) {
        // Condición: si el nodo tiene el mismo caracter, lo devuelve.
        if(puntero->character==character) {
            return puntero;
        }
        // Continúa.
        puntero = puntero->next;
    }

    puntero = NULL;
    return puntero;
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
    // Iniciamos un nuevo nodo con sus valores en 0.
    struct node* nuevoNodo = (struct node*)malloc(sizeof(struct node));
    nuevoNodo -> character = character;
    nuevoNodo -> next = 0;
    nuevoNodo -> end = 0;
    nuevoNodo -> word = 0;
    nuevoNodo -> down = 0;

    // Toma el primer nodo de la lista (o NULL).
    struct node* actual = *list;
    
    // Si la lista está vacia o el primer nodo va después, agrega el nuevo nodo primero.
    if (actual == NULL || actual->character > character) {
        nuevoNodo -> next = actual;
        *list = nuevoNodo;
        return nuevoNodo;
    }

    // Busco la posición correcta del nuevo nodo y lo agrego.
    while (actual -> next != NULL && actual->next->character < character) {
        actual = actual -> next;
    }
    nuevoNodo->next = actual->next;
    actual->next = nuevoNodo;

    // Devuelvo un puntero al nodo agregado.
    return nuevoNodo; 
}

void deleteArrayOfWords(char** words, int wordsCount) {
    int i = 0;
    // Iteramos sobre todas las palabras.
    while(i<wordsCount) {
        // Liberamos la memoria de cada palabra.
        free(words[i]); 
        i++;
    }
    // Liberamos la memoria del arreglo entero.
    free(words); 
}

// Ejercicio 3: funciones principales. 

struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt -> first = 0;
    kt -> totalKeys = 0;
    kt -> totalWords = 0;
    return kt;
}

void keysPredictAddWord(struct keysPredict* kt, char* word) { 
	struct node** puntero = &(kt->first); // Puntero doble al primer nodo de la estructura.
	struct node* letra; // Puntero a la letra buscada.
	int nivel = 0; // Nivel/iterador de la palabra. Por cada letra agregada bajamos un nivel.
	
    // Itera sobre la palabra.
	while (nivel < strLen(word)) {
        if (*puntero == 0) { // Lista vacia.
            // Como no hay ningún caracter, agrego la palabra entera.
			for (int i=nivel; i < strLen(word); i++) {
				*puntero = addSortedNewNodeInLevel(&puntero, word[i]);
                kt->totalKeys++;
				puntero = &((*puntero)->down);
			}
            // Salida forzada.
			nivel = strLen(word)-1;
		} else {
            // Busco la letra en la lista.
			letra = findNodeinLevel(puntero, word[nivel]);
			// Si no está, la agrega.
            if (letra == 0) {
				letra = addSortedNewNodeInLevel(puntero, word[nivel]);
                kt->totalKeys++;
			}
            // Ya agregué la letra, bajo.
			puntero = &(letra->down);
		}
        // Si el indice/nivel es el último, la palabra termina.
		if (nivel==(strLen(word)-1)) {
			(*puntero) -> word = strDup(word);
			(*puntero) -> end = 1;
            kt->totalWords++;
		}
        // Aumento nivel.
		nivel++;
	} 
}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    // Chequea que los parametros no estén vacios.
    if (kt==0 || word==0 || *word==0){
        return;
    }

    int longitudWord = strLen(word);
    struct node* letra = kt->first; // Puntero al primer nodo de cada lista.

    // Ciclo que busca cada caracter (iteración) de la palabra en cada nivel. 
    for(int i=0; i<longitudWord; i++) {
        letra = findNodeInLevel(&letra, word[i]); // Letra apunta al nodo con la i-esima letra de word. 
        
        // Si la letra no está, la palabra tampoco.
        if(letra == 0) {
            return;
        }
        // Baja de nivel solo si la palabra sigue.
        if(word[i+1] != 0) {
            letra = letra -> down;
        }
    }
    // Condición: letra apuntando al último nodo de la palabra.
    if (letra!=0 && letra->end == 1){
        
        // Elimina la palabra 
        letra->end = 0;
        if (letra->word != 0){
            free(letra->word)
            letra->word = 0;
        }
        kt->totalWords --;
        kt->totalKeys = kt->totalKeys - longitudWord;
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
                
                palabras[i] = &palabra;

                i++;
            } 

            punteroSec = punteroSec -> down;
        }
        
        punteroInicial = punteroInicial -> next;

        punteroSec = punteroInicial;
        
    }

    return palabras;
}

int keysPredictCountWordAux(struct node* n) {

    // COMPLETAR
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {

    struct node* punteroInicial = kt -> first;

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

                palabras[i] = &palabra;

                i++;
            } 

            punteroSec = punteroSec -> down;
        }

        punteroInicial = punteroInicial -> next;

        punteroSec = punteroInicial;

    }

    return palabras;
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

