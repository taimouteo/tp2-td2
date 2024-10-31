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

    // Copia un caracter de src en dupStr por iteraciÃ³n.
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
	
    if(puntero==0) {
		puntero = 0;
        return puntero;
    }
    
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
    lugar de la lista. El ciclo while tiene una condiciÃ³n especial por si el nuevo nodo va en el ultimo lugar.
    */
    
    struct node* nuevoNodo = (struct node*)malloc(sizeof(struct node));
    nuevoNodo->character = character;
    nuevoNodo->next = 0;
    nuevoNodo->end = 0;
    nuevoNodo->word = 0;
    nuevoNodo->down = 0;
    
    // Lista vacia o nuevo nodo va primero.
    if (*list == 0 || (*list)->character > character) {
        nuevoNodo -> next = *list;
		*list = nuevoNodo;
        return nuevoNodo;
    }
	
	struct node* puntero = *list;
    // Mientras que haya un nodo siguiente y el nodo siguiente vaya después del nuevo nodo.
    while(puntero->next!=0 && puntero->next->character < character) {
		puntero = puntero->next;
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
	/*
    Inicializa un puntero doble al primer nodo de la lista y un entero que indica tanto el nivel, como la iteración
    sobre word. La función tiene un ciclo hasta que se llega al ultimo nivel. Siendo 0<=k<strLen(word), si el caracter
    no se encuentra en el nivel k, agrega la palabra entera desde la posición k, pues si no está¡ el primer caracter tampoco
    estaran los siguientes. Si el caracter se encuentra en k, el puntero baja hacia la lista siguiente, a menos que sea
    el último caracter, completando los campos word y end al finalizar el ciclo
	*/
	
	if(kt == 0 || word == 0 || *word == 0) {
		return;
	}
	
	struct node** punteroLista = &(kt->first);
	struct node* punteroNodo = 0;
	
	// Recorre cada letra de la palabra
	for(int i=0; word[i]!=0; i++) {
		// Busca el nodo con la letra actual en el nivel actual
		punteroNodo = findNodeInLevel(punteroLista, word[i]);
		
		// Si el nodo no existe, lo crea y lo agrega en orden
		if (punteroNodo == 0) {
			punteroNodo = addSortedNewNodeInLevel(punteroLista, word[i]);
			kt->totalKeys++;
		}
		
		// Baja al siguiente nivel (campo down), donde se buscará o agregará la siguiente letra
		punteroLista = &(punteroNodo->down);
	}
	
	// En el último nodo, añade la palabra y marca el nodo como final de palabra
	if (punteroNodo != 0 && punteroNodo->end == 0) {
		punteroNodo->end = 1;
		punteroNodo->word = strDup(word);
		kt->totalWords++;
	}
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {
	/*
	Inicializa un puntero al primer nodo de la lista. Busca el i-esimo caracter en la lista.
	Si el caracter no está, la palabra no esta y devuelve 0. Si el caracter está y el caracter
	no es el último, el puntero baja a la siguiente lista. Al terminar el ciclo, el puntero
	deberá estar en el último nodo/caracter de la palabra, y por lo tanto lo devuelve */
	
	struct node* puntero = kt->first;
	
	for(int i=0; i < strLen(word); i++) {
		puntero = findNodeInLevel(&puntero, word[i]); 
		
		if(puntero == 0) { // Si no está, la palabra tampoco.
			puntero = 0;
			return puntero;
		} 
		
		if(word[i+1]!=0) { // Baja de lista.
			puntero = puntero->down;
		}
	}
	
	return puntero;
}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    /*
    Inicializa un puntero al primer nodo de la lista. Busca cada caracter en su respectivo nivel. Si el caracter no
    está en la lista, la palabra tampoco y por lo tanto la función termina. Al llegar al nodo del último caracter,
    libera la memoria de la palabra y pone end en 0.
    */
    
    if (kt==0 || word==0 || *word==0){
        return;
    }

	struct node* puntero = keysPredictFind(kt, word);
	
	if (puntero==0) {
		return;
	}

    if (puntero->end == 1){
        // Elimina la palabra
        puntero->end = 0;
        if (puntero->word != 0){
            free(puntero->word);
            puntero->word = 0;
        }
        kt->totalWords--;
    }
}

int keysPredictCountWordAux(struct node* n) {
	/* Función auxiliar recursiva que toma un puntero, y en caso de ser no nulo, devuelve 1 si el nodo representa el fin
	de una palabra, y hace un llamado recursivo de la función, con los punteros a la lista del nivel más abajo y del 
	nodo siguiente en la lista. */
	
	if (n==0) {
		return 0;
	} else {
		if (n->end==1) { // Encontró palabra.
			return 1 + keysPredictCountWordAux(n->down) + keysPredictCountWordAux(n->next);
		} else {
			return keysPredictCountWordAux(n->down) + keysPredictCountWordAux(n->next);
		}
	}
	
}

char** keysPredictWordsArrayAux(struct node* n, char** prefixWords) {
	/* Función auxiliar recursiva que toma un puntero, y en caso de ser no nulo y si el nodo representa el fin de una 
	palabra, agrega la palabra al arreglo de strings pasado por parÃ¡metro. Luego, hace un llamado recursivo de la 
	misma función con los punteros a la lista del nivel más abajo y del nodo siguiente en la lista. */
	
	if (n==0) {
		return prefixWords;
	}
	if (n->end==1) { // Encontró palabra
		*prefixWords = strDup(n->word);
		prefixWords++;
	}
	prefixWords = keysPredictWordsArrayAux(n->down, prefixWords);
	return keysPredictWordsArrayAux(n->next, prefixWords);
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
    /*
    El primer bloque recorre la estructura buscando la última letra del prefijo. Luego, puntero apunta al primer nodo
    de la lista abajo de esa letra. totalWords llama a keysPredictCountWordAux que cuenta la cantidad de palabras que
    hay en la estructura desde puntero y guarda su valor en wordsCount. Luego, asignamos memoria al arreglo de strings
    res, y guardamos la dirección de su primer elemento en una función auxiliar. Llamamos a keysPredictRunAux, el cual
    modifica res agregando las palabras que encuentra en la estructura, y retornamos el puntero res a la dirección de
    memoria donde empezo (guardada en aux).
    */
   
   // Primer bloque.
    struct node* puntero = kt->first;

    for(int i=0; partialWord[i]!=0; i++) {
        puntero = findNodeInLevel(&puntero, partialWord[i]);
        if(puntero==0) {
			*wordsCount = 0;
            return 0;
        }
		puntero = puntero->down;
    }

    // Contar palabras en la estructura
    *wordsCount = keysPredictCountWordAux(puntero);

    // Arreglo de strings.
    char** palabras = (char**)malloc(sizeof(char*)*(*wordsCount));
	keysPredictWordsArrayAux(puntero, palabras);
    return palabras;
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {
    /*
    Llama a la función keysPredictRunAux que dado un puntero, hace una lista de todas las palabras que se pueden armar
    con ese puntero, pero le pasa como parametro el primer nodo de la estructura kt, listando así la estructura completa.
    */

    struct node* punteroInicial = kt->first;
    *wordsCount = keysPredictCountWordAux(punteroInicial);
	
	char** palabras = (char**)malloc(sizeof(char*)*(*wordsCount));
	keysPredictWordsArrayAux(punteroInicial, palabras);
    return palabras;
}

void keysPredictDeleteAux(struct node* n) {
	/*
	Función auxiliar recursiva que toma un puntero, y en caso de ser no nulo, libera la memoria del nodo actual. Previamente,
	hace un llamado recursivo de la misma función con los punteros a la lista del nivel más abajo y del nodo siguiente
	en la lista, liberando así también su memoria. */
	
	if(n==0) {
		return;
	} else {
		if(n->end==1){
			free(n->word);
		}
		keysPredictDeleteAux(n->down);
		keysPredictDeleteAux(n->next);
		free(n);
	}
}

void keysPredictDelete(struct keysPredict* kt) {
    /*
    La función toma el puntero al primer nodo de la estructura y llama a la función keysPredictDeleteAux que elimina cada
    nodo y palabra de la estructura usando recursión. Luego, vuelve a poner todos los valor de la estructura keysPredict
    en 0/NULL.
    */
    struct node* puntero = kt->first;
    keysPredictDeleteAux(puntero);
    kt->first = 0;
    kt->totalKeys = 0;
    kt->totalWords = 0;
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

