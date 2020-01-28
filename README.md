Jose Saldaña Mercado 76424266G & Manuel Carmona Perez 17482989E

--Práctica final: Letras

El programa simulará parte del juego “Cifras y Letras”. En este caso solamente deberá generar la sección de Letras. Este juego consiste en dada una serie de letras escogidas de forma aleatoria, obtener la palabra existente en un diccionario formada a partir de ellas de mayor longitud o que tenga la mayor puntuación.

Por ejemplo dadas las siguientes letras:
O D Y R M E T
una de las mejores soluciones sería METRO.


--Para compilar juego:
make

--Para jugar:
./bin/Juego ./datos/diccionarioRAE.txt *A *B

*A <-- Numero de letras para jugar
*B <-- Tipo de juego, L (longitud) o P (puntuacion)

--Notas sobre la heurística:
Modo LONGITUD:
1)  Saca del diccionario las palabras de la longitud pasada por parametro
2)  Comprueba si alguna/s de ella/s se forma con las letras que han salido,
    de ser así, deja de buscar
3)  Si no ha encontrado, reduce en 1 la longitud de las palabras que busca y repite el proceso

Modo PUNTUACIÓN:
1)  Se recorre el diccionario completo
2)  Se comprueba si la palabra se forma con las letras que han salido,
    de ser así, se calcula su puntuación, si es mayor que la anterior, se borra
    el conjunto de soluciones y se actualiza puntuación máxima, que es igual, se añade


--NOTA SOBRE LA EFICIENCIA: Empezamos programando el juego haciendo combinaciones con las letras y lo hicimos funcionar pero la eficiencia era O(n!) y lo hemos modificado para que funcione trabajando con las palabras del diccionario
porque es O(n) y es mucho más eficiente
A continuación mostramos la base con la que hicimos funcionar el juego de la otra forma
do {
  if (diccionario.Esta(letrasParaJugar)){
    solucionesMaquina.push_back(letrasParaJugar);
  }
} while (next_permutation(letrasParaJugar.begin(), letrasParaJugar.end()));
