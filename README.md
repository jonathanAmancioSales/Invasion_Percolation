# Percolação Invasiva 2D e 3D com Priority Heap

Neste repositório estou disponibilizando um trabalho que eu fiz sobre _Percolação Invasiva_ utilizando o algoritmo **Priority Heap** para a disciplina _Métodos Avançados de Algoritmos e Estruturas de Dados_.

[Aqui](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Relat%C3%B3rio%20-%20Percola%C3%A7%C3%A3o%20Invasiva%20%5BJonathan%20Sales%5D_2018.11.06.pdf) você pode ver um _relatório_ sobre esse trabalho, onde abordo um pouco da teoria da percolação invasiva e apresento os principais resultados obtidos.
Também apresento o algoritmo Priority Heap, que torna o algoritmo de percolação invasiva muito eficiente.
Por fim, apresento o código em C++ utilizado para gerar os resultados apresentados e as referências bibliográficas.

Um [exemplo](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Results%20(Images%2C%20movie)/M_1024_255138.pdf) de percolação invasiva sem aprisionamento em uma rede de 1024:
[![M_1024_255138_80fps.gif](https://raw.githubusercontent.com/jonathanAmancioSales/Invasion_Percolation/main/Results%20(Images%2C%20movie)/M_1024_255138.gif)](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Results%20(Images%2C%20movie)/M_1024_255138.gif)

Comparação visual entre os modelos de percolação invasiva sem e com aprisionamento para uma rede bimensional de lado L=400: [M_400_NTIP.pdf](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Results%20(Images%2C%20movie)/M_400_NTIP.pdf), [M_400_TIP.pdf](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Results%20(Images%2C%20movie)/M_400_TIP.pdf).

[![TIP_NTIP_400.png](https://raw.githubusercontent.com/jonathanAmancioSales/Invasion_Percolation/main/Results%20(Images%2C%20movie)/TIP_NTIP_400.png)](https://github.com/jonathanAmancioSales/Invasion_Percolation/tree/main/Results%20(Images%2C%20movie))


Um exemplo de percolação invasiva 3D:

[![3D](https://raw.githubusercontent.com/jonathanAmancioSales/Invasion_Percolation/main/Results%20(Images%2C%20movie)/3D.png)](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Results%20(Images%2C%20movie)/3D_3.png)

Um exemplo de percolação invasiva onde a fronteira é mostrada:

[![fronteira](https://raw.githubusercontent.com/jonathanAmancioSales/Invasion_Percolation/main/Results%20(Images%2C%20movie)/P_2001_201545_1535388302.png)](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Results%20(Images%2C%20movie)/P_2001_201545_1535388302.eps)

Pseudo código do algoritmo de percolação invasiva:
```
Algoritmo Invasion_Percolation:
1 inicio:
    2 Preencher a matriz aleatoriamente: r_i ∈ [0, 1];
    3 Definir invasores;
    4 Definir fronteira;
    5 enquanto o sistema não percolar faça:
        6 Invadir o menor sı́tio da fronteira;
        7 Atualizar fronteira;
    8 fim
9 fim
```

Neste [link](https://www.youtube.com/watch?v=yciAPJsy17Q), você pode ver um pequeno vídeo mostrando como funciona o algoritmo Priority Heap.
E [aqui](http://btv.melezinek.cz/binary-heap.html), você pode ver o funcionamento desse algoritmo de forma interativa.

[![melezinek](https://github.com/jonathanAmancioSales/Invasion_Percolation/blob/main/Results%20(Images%2C%20movie)/BSTinsert1.png)](http://btv.melezinek.cz/binary-heap.html)
