# Primeiro Trabalho Prático - CI1238 (Otimização)
Modelação e implementação do problema "transporte de carga com pacotes de recursos".

## Modo de uso
```bash
./transporte
```
A entrada (lida em *stdin*) inicia com 5 números *n*, *m*, *k*, *q* e *p* indicando a quantidade de cidades, rotas, recursos, e pacotes e o ganho por tonelada transportada, respectivamente. Em seguida temos *m* linhas, cada uma com os dados de uma rota. Cada rota é descrita com *k* + 3 números indicando as cidades *i* e *j* (extremos da rota), a capacidade e os valores dos recursos necessários *r<sub>i,j,t</sub>*, com *t* = 1, 2, . . . , *k*. Em seguida temos *q* linhas, cada uma com os dados de um pacote de recursos. Cada pacote é descrito com *k* + 1 números indicando o valor do pacote (*v<sub>u</sub>*) e as quantidades de cada recurso *s<sub>u,t</sub>*, com *t* = 1, 2, . . . , *k*.

