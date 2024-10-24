#include "utils.h"
#include <stdlib.h>

// Ejercicio 1.

int strLen(char* src) {
    /*
    La función toma un iterador usado como indice, que aumenta por cada caracter en el string, y lo devuelve.
    */

    int i = 0;
    while (src[i]!=0){ 
		i++;
	}
    return i;
}

char* strDup(char* src) {
    /*
    Solicitamos la memoria correspondiente para el string, copiamos caracter a caracter, y agregamos el caracter nulo
    al final.
    */
    
    int longitudSrc = strLen(src);
    char* dupStr = (char*)malloc(sizeof(char)*(longitudSrc + 1)); // Solicitamos memoria
	
    // Si el string es nulo, devuelve 0.
    if(src==0) {
        dupStr = 0;
		return dupStr; 
	}

    // Copia un caracter de src en dupStr por iteración.
	for(int i = 0; i < longitudSrc; i++) {
        dupStr[i] = src[i];
	}
	
    dupStr[longitudSrc] = 0; // Agrega el caracter nulo al final del nuevo string.
	
    return dupStr;
}

// Ejercicio 2.

struct node* findNodeInLevel(struct node** list, char character) {
    /*
    Implementamos un ciclo que mueve el puntero hacia el nodo siguiente en la lista. Si encuentra el que busca lo
    devuelve, y si no, devuelve 0 (nulo). 
    */
    
    struct node* puntero = *list;
    
    while(puntero!=0) {
        // Si lo encontró, devuelve el puntero.
        if(puntero->character==character) {
            return puntero;
        }
        puntero = puntero->next; // Si no, se mueve al siguiente nodo.
    }

    return puntero; // En este punto, puntero es 0.
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
    /*
    Inicializa un nuevo nodo solo con el valor character y un puntero que itera sobre la lista. Si el nuevo nodo va
    primero (lista vacía o lugar que le corresponde), lo agrega a la lista y retorna su puntero. Si no, busca un nodo
    previo a el que quiero agregar, cuyo siguiente nodo (next) vaya luego del nuevo nodo e inserta el nuevo nodo en ese
    lugar de la lista. El ciclo while tiene una condición especial por si el nuevo nodo va en el ultimo lugar.
    */
    
    struct node* nuevoNodo = (struct node*)malloc(sizeof(struct node));
    nuevoNodo -> character = character;
    nuevoNodo -> next = 0;
    nuevoNodo -> end = 0;
    nuevoNodo -> word = 0;
    nuevoNodo -> down = 0;

    struct node* puntero = *list;
    
    // Lista vacia o nuevo nodo va primero.
    if (puntero == 0 || puntero->character > character) {
        nuevoNodo -> next = puntero;
        *list = nuevoNodo;
        return nuevoNodo;
    }

    // Mientras que haya un nodo siguiente y el nodo siguiente vaya después del nuevo nodo.
    while (puntero -> next != 0 && puntero->next->character < character) {
        puntero = puntero -> next;
    }

    // Agrego el nodo.
    nuevoNodo->next = puntero->next;
    puntero->next = nuevoNodo;
    return nuevoNodo; 
}

void deleteArrayOfWords(char** words, int wordsCount) {
    /*
    Primero itera sobre el arreglo y libera la memoria de cada uno de sus elementos, y luego libera el arreglo entero.
    */

    for(int i=0; i<wordsCount; i++) {
        free(words[i]); // Cada elemento.
    }
    
    free(words); // Arreglo entero.
}

// Ejercicio 3. 

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
        kt->totalWords--;
        kt->totalKeys = kt->totalKeys - longitudWord;
    }   
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {
    struct node* puntero = kt->first; // Toma el primer elemento de la lista.

    // Ciclo: iteración por cada caracter de la palabra.
    for(int i=0; i < strLen(word); i++) {
        // Busco la i-esima letra en el nivel actual.
        puntero = findNodeInLevel(&puntero, word[i]); 
        // Si no está, devuelve el puntero en 0.
        if(puntero == 0) {
            puntero = 0;
            return puntero;
        } 
        // A menos que esté en el último nivel, baja.
        if(i!=strLen(word)-1) {
            puntero = puntero->down;
        }
    }
    // Si es el final de la palabra, retorna puntero. En este punto, la condición if no es necesaria
    // pero la agregamos para comprobar que no halla errores.
    if(puntero->end==1) {
        return puntero;
    }
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

