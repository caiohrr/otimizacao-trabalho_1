//1.testar a modelagem para casos triviais

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "rota.h"
#include "pacote.h"

void lerEntrada(int m, int k, int q, struct Rota *rotas, struct Pacote *pacotes) {

        // Ler as rotas e recursos de cada rota
        for (int i = 0; i < m; i++) {
                scanf("%d %d %d", &rotas[i].inicio, &rotas[i].fim, &rotas[i].capacidade);
                for(int j = 0; j < k; j++) {
                        scanf("%d", &rotas[i].recursos[j]);
                }
        }
        
        // Ler os pacotes
        for (int i = 0; i < q; i++) {
                scanf("%d", &pacotes[i].custo);
                for (int j = 0; j < k; j++) {
                        scanf("%d", &pacotes[i].recursos[j]);
                }
        }

}


//int main(int argc, char **argv) {
int main() {

        int n_cidades, m_rotas, k_recursos, q_pacotes, p_ganho;
        scanf("%d %d %d %d %d", &n_cidades, &m_rotas, &k_recursos, &q_pacotes, &p_ganho);
        if (n_cidades == 0 || m_rotas == 0 || k_recursos == 0 || q_pacotes == 0) {
                fprintf(stderr, "Erro: entrada invalida\n");
                return EXIT_FAILURE;
        }

        struct Rota rotas[m_rotas];
        struct Pacote pacotes[q_pacotes];

        for (int i = 0; i < m_rotas; i++) {
                rotas[i].recursos = criarVetor(k_recursos);
        }

        for (int i = 0; i < q_pacotes; i++) {
                pacotes[i].recursos = criarVetor(k_recursos);
        }

        lerEntrada(m_rotas, k_recursos, q_pacotes, rotas, pacotes);


        FILE *stream_saida = stdout;

        fprintf(stream_saida, "max:");
        fprintf(stream_saida, " %df0%d0%d", p_ganho, rotas[0].inicio, rotas[0].fim);
        if (m_rotas > 1) {
                for (int i = 1; i < m_rotas; i++) {
                        if (rotas[i].inicio == 1) {
                                fprintf(stream_saida, " + %df0%d0%d", p_ganho, rotas[i].inicio, rotas[i].fim);
                        }
                }
        }

        for (int i = 0; i < q_pacotes; i++) {
                fprintf(stream_saida, " - %dq%d", pacotes[i].custo, i + 1);
        }
        fprintf(stream_saida, " + 0;\n");

        for (int i = 0; i < k_recursos; i++) {
                fprintf(stream_saida, "%dy0%d0%d", rotas[0].recursos[i], rotas[0].inicio, rotas[0].fim);
                fprintf(stream_saida, " + %dz0%d0%d", rotas[0].recursos[i], rotas[0].inicio, rotas[0].fim);
                for (int j = 1; j < m_rotas; j++) {
                        fprintf(stream_saida, " + %dy0%d0%d", rotas[j].recursos[i], rotas[j].inicio, rotas[j].fim);
                        fprintf(stream_saida, " + %dz0%d0%d", rotas[j].recursos[i], rotas[j].inicio, rotas[j].fim);

                }
                fprintf(stream_saida, " <= %dq1", pacotes[0].recursos[i]);
                for (int k = 1; k < q_pacotes; k++) {
                        fprintf(stream_saida, " + %dq%d", pacotes[k].recursos[i], k + 1);

                }
                fprintf(stream_saida, " + 0;\n");
        }
        fprintf(stream_saida, "\n");

        for (int i = 0; i < m_rotas; i++) {
                fprintf(stream_saida, "f0%d0%d <= %d;\n", rotas[i].inicio, rotas[i].fim, rotas[i].capacidade);
                fprintf(stream_saida, "f0%d0%d >= -%d;\n", rotas[i].inicio, rotas[i].fim, rotas[i].capacidade);
        }
        fprintf(stream_saida, "\n");

        for (int i = 0; i < m_rotas; i++) {
                fprintf(stream_saida, "y0%d0%d <= %d;\n", rotas[i].inicio, rotas[i].fim, rotas[i].capacidade);
                fprintf(stream_saida, "y0%d0%d >= 0;\n", rotas[i].inicio, rotas[i].fim);
                fprintf(stream_saida, "z0%d0%d <= %d;\n", rotas[i].inicio, rotas[i].fim, rotas[i].capacidade);
                fprintf(stream_saida, "z0%d0%d >= 0;\n\n", rotas[i].inicio, rotas[i].fim);
        }


        int flag_soma_inicio, flag_soma_fim;
        flag_soma_inicio = flag_soma_fim = 0;
        // Comeca em i = 1 pois nada entra na primeira cidade (quando i = 0)
        // termina em n_cidades - 1 pois a ultima cidade tambem nao e relevante
        for (int i = 1; i < n_cidades - 1; i++) {

                for (int j = 0; j < m_rotas; j++) {
                        if (rotas[j].fim == i + 1) {
                                if (flag_soma_fim == 0) {
                                        fprintf(stream_saida, "f0%d0%d", rotas[j].inicio, rotas[j].fim);
                                        flag_soma_fim = 1;
                                } else {
                                        fprintf(stream_saida, " + f0%d0%d", rotas[j].inicio, rotas[j].fim);
                                }
                        }
                }

                fprintf(stream_saida, " + 0 = + 0");
                for (int j = 0; j < m_rotas; j++) {
                        if (rotas[j].inicio == i + 1) {
                                if (flag_soma_inicio == 0) {
                                        fprintf(stream_saida, " + f0%d0%d", rotas[j].inicio, rotas[j].fim);
                                        flag_soma_inicio = 1;
                                } else {
                                        fprintf(stream_saida, " + f0%d0%d", rotas[j].inicio, rotas[j].fim);
                                }
                        }
                }
                flag_soma_inicio = flag_soma_fim = 0;
                fprintf(stream_saida, ";\n");
        }

        fprintf(stream_saida, "\n");

        for (int i = 0; i < m_rotas; i++) {
                int ini, fim;
                ini = rotas[i].inicio;
                fim = rotas[i].fim;
                fprintf(stream_saida, "f0%d0%d = y0%d0%d - z0%d0%d;\n", ini, fim, ini, fim, ini, fim);
        }

        fprintf(stream_saida, "\n");

        for(int i = 0; i < q_pacotes; i++) {
                fprintf(stream_saida, "q%d >= 0;\n", i+1);
        }

        //fclose(arquivo_saida);

        for (int i = 0; i < m_rotas; i++) {
                free(rotas[i].recursos); 
        }

        for (int i = 0; i < q_pacotes; i++) {
                free(pacotes[i].recursos); 
        }

        return 0;
}
