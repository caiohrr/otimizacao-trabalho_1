//TODO:
//1.testar a modelagem para casos triviais
//2.implementar a logica para traduzir o resto do programa pro lp_solve

#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "rota.h"
#include "pacote.h"

void lerEntrada(int m, int k, int q, struct Rota *rotas, struct Pacote *pacotes) {

        
        // Ler as rotas e recursos de cada rota
        for (int i = 0; i < m; i++) {
                scanf("%d %d %d", &rotas[i].inicio, &rotas[i].fim, &rotas[i].capacidade);
                //printf("rota %d: ini: %d fim: %d capacidade: %d\n", i, rotas[i].inicio, rotas[i].fim, rotas[i].capacidade);
                for(int j = 0; j < k; j++) {
                        scanf("%d", &rotas[i].recursos[j]);
                        //printf("rota[%d],recurso[%d] = %d\n", i, j, rotas[i].recursos[j]);
                }
                //printf("Saiu 1o for\n");
        }
        
        // Ler os pacotes
        for (int i = 0; i < q; i++) {
                scanf("%d", &pacotes[i].custo);
                for (int j = 0; j < q; j++) {
                        scanf("%d", &pacotes[i].recursos[j]);
                }
                //printf("Saiu 2o for\n");
        }

}


int main() {

        int n_cidades, m_rotas, k_recursos, q_pacotes, p_ganho;
        scanf("%d %d %d %d %d", &n_cidades, &m_rotas, &k_recursos, &q_pacotes, &p_ganho);
        //printf("%d %d %d %d %d", n_cidades, m_rotas, k_recursos, q_pacotes, p_ganho);

        struct Rota rotas[m_rotas];
        struct Pacote pacotes[q_pacotes];

        for (int i = 0; i < m_rotas; i++) {
                rotas[i].recursos = criarVetor(k_recursos);
        }

        for (int i = 0; i < q_pacotes; i++) {
                pacotes[i].recursos = criarVetor(k_recursos);
        }

        lerEntrada(m_rotas, k_recursos, q_pacotes, rotas, pacotes);
        
        FILE *arquivo_saida = fopen("saida.lp", "w+");

        fprintf(arquivo_saida, "max:");
        fprintf(arquivo_saida, " %df0%d0%d", p_ganho, rotas[0].inicio, rotas[0].fim);
        if (m_rotas > 1) {
                for (int i = 1; i < m_rotas; i++) {
                        if (rotas[i].inicio == 1) {
                                fprintf(arquivo_saida, " + %df0%d0%d", p_ganho, rotas[i].inicio, rotas[i].fim);
                        }
                }
        }
        for (int i = 0; i < q_pacotes; i++) {
                fprintf(arquivo_saida, " - %dq0%d", pacotes[i].custo, i + 1);
        }
        fprintf(arquivo_saida, ";\n");

        fclose(arquivo_saida);

        for (int i = 0; i < m_rotas; i++) {
                free(rotas[i].recursos); 
        }

        for (int i = 0; i < q_pacotes; i++) {
                free(pacotes[i].recursos); 
        }

        return 0;
}
