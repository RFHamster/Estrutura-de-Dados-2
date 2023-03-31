#include <stdio.h>
int main()
{
    FILE *arq1, *arq2, *arq3;
    // leitura e escrita em arquivo no modo texto
    arq1 = fopen("texto1.c", "r");
    if (arq1 == NULL)
        printf("erro no arq1");
    arq2 = fopen("texto2.c", "w");
    if (arq2 == NULL)
        printf("erro no arq2");
    char c, d;
    while ((c = getc(arq1)) != EOF)
    {
        putc(c, arq2);
    }
    putc(EOF, arq2);
    fclose(arq1);
    fclose(arq2);
    // leitura e escrita em arquivo no modo binario, char=byte
    arq1 = fopen("texto1.c", "rb");
    if (arq1 == NULL)
        printf("erro no arq1");
    arq3 = fopen("texto3.txt", "wb");
    if (arq3 == NULL)
        printf("erro no arq3");
    while (!feof(arq1))
    {
        c = getc(arq1);
        putc(c, arq3);
        printf("%c", c);
    }
    fclose(arq1);
    fclose(arq3);
    // comparacao byte a byte dois arquivos binarios
    arq1 = fopen("texto1.c", "rb");
    if (arq1 == NULL)
        printf("erro no arq1");
    arq2 = fopen("texto2.txt", "rb");
    if (arq2 == NULL)
        printf("erro no arq2");
    while (!feof(arq1))
    {
        c = getc(arq1);
        d = getc(arq2);
        if (c != d)
            printf("%4d %4d %1d\n", c, d, (c == d));
    }
    fclose(arq1);
    fclose(arq2);
    // exemplo de escrita e leitura formatada em arquivo de texto
    int a, b;
    a = 10;
    arq1 = fopen("texto.c", "w");
    if (arq1 == NULL)
        printf("erro no arq1");
    fprintf(arq1, "%d", a);
    fclose(arq1);
    arq1 = fopen("texto.c", "r");
    if (arq1 == NULL)
        printf("erro no arq1");
    fscanf(arq1, "%d", &b);
    fclose(arq1);
    printf("%d %d", a, b);
    // exemplo de escrita e leitura binaria em arquivo binario
    a = 10;
    b = 5;
    arq1 = fopen("texto.c", "wb");
    if (arq1 == NULL)
        printf("erro no arq1");
    fwrite(&a, sizeof(int), 1, arq1);
    fclose(arq1);
    arq1 = fopen("texto.c", "rb");
    if (arq1 == NULL)
        printf("erro no arq1");
    fread(&b, sizeof(int), 1, arq1);
    fclose(arq1);
    printf("%d %d", a, b);
    return 0;
}