#include "utils.h"
// EJERCICIO 1
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
    char* dupStr = (char*)malloc(sizeof(char)*(longitudStr*2)+1);
	
    // Si el string es NULL, devovelmos NULL.
    if(src == NULL) {
		return NULL; 
	}

    // Asignamos cada caracter del string a sus dos apariciones en el duplicado.
	for(int i = 0; i < longitudStr; i++) {
        dupStr[i] = src[i];
        dupStr[i+longitudStr] = src[i];
	}
	
    // Agregamos el caracter nulo al final del string.
    dupStr[longitudStr*2] = 0;
	
    return dupStr;
}


// Auxiliar functions

struct node* findNodeInLevel(struct node** list, char character) {

    struct node* puntero = list[0] -> first;

    // Cambié orden de == char, -> next, return

    while(puntero -> next != 0) {
        
        puntero = puntero -> next;

        if(puntero -> character == character) {
            return puntero;
        } 
    }
    
    puntero = puntero -> NULL;

    return puntero;
    
/*
    struct node* puntero = list[0] -> first;
    struct node* punteroInicial = list[0] -> first;

    int i = 0;





    while (i < list.totalKeys) {
            
        if (puntero -> next != character || puntero -> next != 0) {

            if (puntero -> down == 1) {
                punteroInicial = &puntero;
                puntero = puntero -> down;
                i++;
            }

            if(puntero -> down == 0) {
                
                puntero = puntero -> next;
                i++;
            }
            
        }

        if (puntero -> next = character) {
            
            puntero = puntero -> next;
            return puntero;
        }

        if (puntero -> next = 0) {
            
            puntero = &punteroInicial;
            i++;
        }
        
    }

    puntero -> NULL;
    
    return puntero;

*/
}


struct node* addSortedNewNodeInLevel(struct node** list, char character) {
    
    // Creo el nuevo nodo y seteo sus valores en 0 (menos char).
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode -> character = character;
    newNode -> next = 0;
    newNode -> end = 0;
    newNode -> word = 0;
    newNode -> down = 0;

    // Caso 1: la lista está vacia.
    if((list -> first) == 0) {
        list -> first = &newNode;
    }
    else {
        struct node* anteX;
        struct node* x = list -> first;
        while ((x -> character) <= character) {
            // Caso 2: la lista tiene un solo caracter previo al del nuevo nodo.
            if ((x -> next) ==0) {
                x -> next = &newNode
            }
        }
    }
}

void deleteArrayOfWords(char** words, int wordsCount) {

    if (words==NULL){
        return;
    }
    for(int i=0; i<wordsCount; i++){
        free(words[i]); // Liberamos la memoria de cada string
    }
    free(words); // Liberamos la memoria del arreglo de punteros
}



// Keys Predict

struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt->first = 0;
    kt->totalKeys = 0;
    kt->totalWords = 0;
    return kt;
}

void keysPredictAddWord(struct keysPredict* kt, char* word) {

    // COMPLETAR

}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {

    // COMPLETAR
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {

    // COMPLETAR

    return 0;
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {

    // COMPLETAR

    return 0;
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

