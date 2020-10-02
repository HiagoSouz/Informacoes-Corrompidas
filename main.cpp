//Hiago Rafael de Souza
//RA: 729218
//Engenharia de Computação

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstdio>


std::vector<long> compara(const std::string& pattern, const std::string& text)
{
    int seqR = pattern.length();
    int Cont = text.length();
    int vetor[256];
    int *armazena;
    std::vector<long> ruido;
    int a,b;


    for (a = 0; a < 256; ++a)
        vetor[a] = 0;
    for (b = 0; b < seqR; ++b)
        vetor[(int)pattern.at(b)] = b;


    armazena = (int *)malloc(seqR * sizeof(int));

    int h = seqR, aux = seqR-1;
    int i = seqR, j = aux;
    while (h >= 1){
        while (i >= h && j >= 1)
            if (pattern.at(i - 1) == pattern.at(j - 1))
                --i, --j;
            else
                i = seqR, j = --aux;
        armazena[--h] = aux;
    }

    aux = seqR;
    int c1, c2;
    while (aux <= Cont){
        i = seqR, j = aux;

        while (i >= 1 && pattern.at(i - 1) == text.at(j - 1))
            --i, --j;
        if (i < 1)
            ruido.push_back(j);
        if (i == seqR)
            aux += 1;
        else{
            c2 = seqR - armazena[i];
            c1  = seqR - vetor[(int)text.at(aux)];
            aux += (c2 > c1) ? c2 : c1;
        }
    }
    return ruido;
}

int main()
{
    char file_name[100],c;
    long tam,seq;
    FILE *entrada;
    std::string text;
    std::string pattern;
    std::vector<long> retorno;

    scanf("%s", file_name);
    entrada = fopen(file_name, "r");  //ABRE O ARQUIVO AQUI
    if (entrada == NULL){
        printf("\nARQUIVO NÃO ENCONTRADO!\n");
        exit(EXIT_FAILURE);
    }


    fscanf(entrada, "%ld %ld ", &seq, &tam);

    for (int i = 0; i < seq; i++){
        fscanf(entrada, "%c ", &c);
        text.append(1, c);
    }

    for (int i = 0; i < tam; i++){
        fscanf(entrada, "%c ", &c);
        pattern.append(1, c);
    }
    fclose(entrada);  //ENCERRA A LEITURA
    retorno = compara(pattern, text);  //chama a função
    for (unsigned int i = 0; i < retorno.size(); i++)
        std::cout << retorno.at(i) << '\n';


    return 0;
}
