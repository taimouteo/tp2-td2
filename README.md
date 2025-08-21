El objetivo de este trabajo practico es implementar una estructura de datos que nos permita recorrer un diccionario de palabras de forma eficiente y con esto implementar funciones para predecir un conjunto posible de palabras en base a un prefijo.

A partir de las siguientes estructuras se define una keysPredict:

<img width="521" height="123" alt="image" src="https://github.com/user-attachments/assets/a2226630-31c2-4fed-95fd-ab05f74237cb" />

La estructura keysPredict, contiene un puntero a una lista de listas de nodos de tipo node. Cada nodo representa una letra indicada por el campo character. El campo next apunta a la siguiente letra dentro del mismo nivel, mientras que el campo down permite llegar a la siguiente lista de letras en un nivel inferior.
Los campos end y word est an relacionados, ya que indican la palabra completa formada por los nodos desde el primero al ́ultimo. El campo end indica que ese nodo es nodo final de una palabra,
mientras que word es un puntero a la palabra almacenada para ese nodo.
Dentro de la estructura principal, además del puntero first, existen dos campos más. El campo totalKeys indica la cantidad total de letras dentro de la estructura, mientras que totalWords corresponde a la cantidad total de palabras almacenadas.
A continuación se ilustra un ejemplo de la estructura:

<img width="643" height="305" alt="image" src="https://github.com/user-attachments/assets/00341f9a-bf6d-49b0-a751-30281a7a2caf" />

En el ejemplo se puede observar como el primer nivel de la estructura est ́a compuesto por las letras 'a', 'b', 'c', 'l' y 'p'. Estas siempre son almacenadas en orden alfabetico dentro de la lista. Luego los punteros down van apuntando a las siguientes listas, algunas pueden tener un solo elemento como la que parte del primer nodo con una 'a', o pueden tener más elementos, como el siguiente puntero. Esta primera parte del la estructura logra almacenar las palabras 'ala' y 'ale'. Siendo la  ́ultima letra la ́unica diferente.
Incluso, es posible tener palabras almacenadas en un nodo intermedio, como es el caso de la palabra 'lo', que un nodo m as abajo construye la palabra 'los'.
