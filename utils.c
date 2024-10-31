#include "utils.h"
#include <stdlib.h>

// Ejercicio 1.

int strLen(char* src) {
    /*
    La funcion toma un iterador usado como indice, que aumenta por cada caracter en el string, y lo devuelve.
    */

    int i = 0;
    while(src[i]!=0) { 
		i++;
	}
    return i;
}

char* strDup(char* src) {
    /*
    Solicitamos la memoria correspondiente para el string, copiamos caracter a caracter, y agregamos el caracter nulo al final.
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
    Inicializa puntero, que toma el valor de lo que apunta list. Si es nulo, lo devuelve en 0, y si no, mueve el puntero hacia el nodo siguiente de la lista en cada 
    iteración del while hasta encontrar al nodo que tenga character. Si no lo encuentra devuelve 0 (puntero = último next). 
    */
	
	struct node* puntero = *list;
	
    if(puntero==0) {
		puntero = 0;
        return puntero;
    }
    
    while(puntero!=0) {
        // Si lo encontro, devuelve el puntero.
        if(puntero->character==character) {
            return puntero;
        }
        puntero = puntero->next; // Si no, se mueve al siguiente nodo.
    }

    return puntero; // En este punto, puntero es 0.
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
    /*
    Inicializa un nuevo nodo. Si el nuevo nodo va primero (lista vacia o lugar que le corresponde), lo agrega a la lista y retorna su puntero. Si no, va moviendo
    un puntero por la lista hasta encontrar la posición correcta (puntero->next->character < character). Cuando termina el ciclo while, puntero apunta al nodo
    anterior a character o al next del último nodo de la lista, entonces agregamos el nodo a la lista usando el puntero.
    */
    
    // Iniciamos nodo.
    struct node* nuevoNodo = (struct node*)malloc(sizeof(struct node));
    nuevoNodo->character = character;
    nuevoNodo->next = 0;
    nuevoNodo->end = 0;
    nuevoNodo->word = 0;
    nuevoNodo->down = 0;
    
    // El nuevo nodo va primero.
    if (*list == 0 || (*list)->character > character) {
        nuevoNodo -> next = *list;
		*list = nuevoNodo;
        return nuevoNodo;
    }
	
	struct node* puntero = *list;
    // Busco la posición correcta.
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
    Itera por cada elemento del array liberando la memoria de cada uno, y finalmente libera el array completo.
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
    Primero chequea que los parametros no esten vacios. Luego, inicializa 2 punteros: punteroLista apunta al primer nodo de la lista actual y punteroNodo apunta al nodo
    que estamos buscando en cada lista (word[i]). Si punteroNodo es 0, es decir, alguna letra de la palabra a agregar no está en la lista, agrega la letra, y las demás
    se agregaran tambien en cada iteracion, pues punteroNodo siempre sera 0. En cada iteracion punteroLista baja de nivel, y al terminar, punteroNodo apunta al último
    nodo de la palabra, para completar sus campos word y end.
	*/
	
	if(kt == 0 || word == 0 || *word == 0) {
		return;
	}
	
	struct node** punteroLista = &(kt->first);
	struct node* punteroNodo = 0;
	
	
	for(int i=0; word[i]!=0; i++) {
		// Busca el nodo con la i-esima letra en el nivel actual
		punteroNodo = findNodeInLevel(punteroLista, word[i]);
		
		// Si la letra no está, la agrega.
		if (punteroNodo == 0) {
			punteroNodo = addSortedNewNodeInLevel(punteroLista, word[i]);
			kt->totalKeys++;
		}
		
		// Baja al siguiente nivel.
		punteroLista = &(punteroNodo->down);
	}
	
	// punteroNodo apunta al ultimo nodo de la palabra.
	if (punteroNodo != 0 && punteroNodo->end == 0) {
		punteroNodo->end = 1;
		punteroNodo->word = strDup(word);
		kt->totalWords++;
	}
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {
	/*
	Inicializa un puntero al primer nodo de la lista. Si el i-esimo caracter de word no está en la estructura, la palabra no esta y devuelve 0. Si el caracter esta
    y el caracter no es el ultimo, el puntero baja a la siguiente lista. Al terminar el ciclo, el puntero esta en el ultimo nodo/caracter de la palabra y lo devuelve. 
    */
	
	struct node* puntero = kt->first;
	
	for(int i=0; i < strLen(word); i++) {
		puntero = findNodeInLevel(&puntero, word[i]); 
		
		if(puntero == 0) { // Si no esta, la palabra tampoco.
			puntero = 0;
			return puntero;
		} 
		
		if(word[i+1]!=0) { // Baja de nivel.
			puntero = puntero->down;
		}
	}
	
	return puntero;
}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    /*
    Verifica que los parametros no esten vacios. Inicializa un puntero al ultimo nodo de la palabra a eliminar. Si el puntero es 0, la palabra no esta y la funcion
    termina. Si el puntero es el final de una palabra (deberia serlo), pone end en 0, y libera la memoria del campo word, poniendolo en 0. 
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
	/* Funcion auxiliar recursiva. Toma un puntero. Si es nulo devuelve 0. Si el nodo es el ultima de una palabra, retorna la suma entre 1, y el llamado de la
    misma función con el nodo de abajo y el siguiente. Recursivamente llegará a donde el nodo de abajo y el siguiente sean 0 para cada una de las listas y de los
    nodos, y cuando llegue, el primer llamado retornara la suma de todos los llamados anteriores.  */
	
	if (n==0) { // Caso base: nodo vacio, no hay palabra
		return 0;
	} else {
		if (n->end==1) { // Encontre palabra.
			return 1 + keysPredictCountWordAux(n->down) + keysPredictCountWordAux(n->next);
		} else {
			return keysPredictCountWordAux(n->down) + keysPredictCountWordAux(n->next);
		}
	}
	
}

char** keysPredictWordsArrayAux(struct node* n, char** prefixWords) {
	/*
    Función auxiliar recursiva. Recorre la estructura y en cada nodo que marca el final de una palabra, copia la palabra en el arreglo de strings prefixWords pasado
    por parametro. Luego llama a si misma recursivamente pasando el puntero a la lista de abajo como parametro y al siguiente nodo en la misma lista, construyendo una
    lista completa de todas las palabras en la estructura.
    */
	

	if (n==0) { // Si el nodo es nulo, devuelve el puntero actual de prefixWords
		return prefixWords;
	}
	if (n->end==1) { // Si el nodo marca el final de una palabra agrega una copia de la palabra al arreglo
		*prefixWords = strDup(n->word);
		prefixWords++;
	}
    // Llama recursivamente a la función para el nivel de abajo y actualiza prefixWords
	prefixWords = keysPredictWordsArrayAux(n->down, prefixWords);

    // Llama recursivamente a la función para el siguiente nodo en la lista next
	return keysPredictWordsArrayAux(n->next, prefixWords);
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
    /*
    Recorre la estructura hasta llegar a la última letra del prefijo. El puntero apunta a la lista abajo de esa letra. totalWords llama a keysPredictCountWordAux,
    que cuenta la cantidad de palabras. Asignamos memoria al arreglo de strings res, y hacemos un llamado a keysPredictWordsArrayAux, que crea un arreglo de todos
    los strings que hay a partir del puntero pasado por parametro, devolviendo el puntero al primer elemento.
    */
   
    struct node* puntero = kt->first;
    // Punteo apunta a la ultima letra del prefijo
    for(int i=0; partialWord[i]!=0; i++) {
        puntero = findNodeInLevel(&puntero, partialWord[i]);
        if(puntero==0) {
			*wordsCount = 0;
            return 0;
        }
		puntero = puntero->down;
    }

    *wordsCount = keysPredictCountWordAux(puntero);

    // Arreglo de strings.
    char** palabras = (char**)malloc(sizeof(char*)*(*wordsCount));
	keysPredictWordsArrayAux(puntero, palabras);
    return palabras;
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {
    /*
    Llama a la funcion keysPredictRunAux que dado un puntero, hace una lista de todas las palabras que se pueden armar con ese puntero, pero le pasa como parametro
    el primer nodo de la estructura kt, listando as� la estructura completa.
    */

    struct node* punteroInicial = kt->first;
    *wordsCount = keysPredictCountWordAux(punteroInicial);
	
	char** palabras = (char**)malloc(sizeof(char*)*(*wordsCount));
	keysPredictWordsArrayAux(punteroInicial, palabras);
    return palabras;
}

void keysPredictDeleteAux(struct node* n) {
	/*
	Funci�n auxiliar recursiva que toma un puntero, y en caso de ser no nulo, libera la memoria del nodo actual. Previamente,
	hace un llamado recursivo de la misma funci�n con los punteros a la lista del nivel m�s abajo y del nodo siguiente
	en la lista, liberando as� tambi�n su memoria. */
	
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
    La funci�n toma el puntero al primer nodo de la estructura y llama a la funci�n keysPredictDeleteAux que elimina cada
    nodo y palabra de la estructura usando recursi�n. Luego, vuelve a poner todos los valor de la estructura keysPredict
    en 0/NULL.
    */
    struct node* puntero = kt->first;
    keysPredictDeleteAux(puntero);
    free(kt);
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

