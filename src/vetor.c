#include <stdlib.h>
#include "vetor.h"

int *criarVetor(size_t tam) {
        int *vetor;

        vetor = malloc(sizeof(int) * tam);
        if (!vetor)
                vetor = NULL;

        return vetor;
}

void destruirVetor(int *vetor) {
        free(vetor);
}
