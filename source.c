#include <stdio.h>
#include <stdlib.h>  
#include <pthread.h>
#include <string.h>
#define NUM_THREADS 421
#define MAX_INPUT 100

int a[20][20];
int b[20][20];
int c_per_matrix[20][20];
int c_per_row[20][20];
int c_per_element[20][20];

struct matrixData{
    int rowA;
    int columnA;
    int rowB;
    int columnB;
};

struct rowData{
    int currentRowA;
    int rowB;
    int columnB;
};
struct elementData{
    int currentRow;
    int currentColumn;
    int columnA;
};


void printMatrixToFile(int row, int col, char* str, char* filename, FILE* fp){
    // FILE* fp;
    // if(strcmp(str, "matrix") == 0){
    //     strcat(filename, "_per_matrix.txt");
    // }else if(strcmp(str, "row") == 0){
    //     strcat(filename, "_per_row.txt");
    // }else if(strcmp(str, "element") == 0){
    //     strcat(filename, "_per_element.txt");
    // }else{
    //     printf("Invalid string");
    //     return;
    // }
    // fp = fopen(filename, "w");
    fprintf(fp, "row=%d col=%d\n", row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fprintf(fp, "%d ", c_per_matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
}

void* calculateByMatrix(void* arg){
    struct matrixData* data = (struct matrixData*)arg;

    for (int i = 0; i < data->rowA; i++)
    {
        for (int j = 0; j < data->columnB; j++)
        {
            c_per_matrix[i][j] = 0;
            for (int k = 0; k < data->columnA; k++)
            {
                c_per_matrix[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void* calculatorByRow(void* arg){
    struct rowData* data = (struct rowData*)arg;

    for (int j = 0; j < data->columnB; j++)
    {
        c_per_row[data->currentRowA][j] = 0;
        for (int k = 0; k < data->rowB; k++)
        {
            c_per_row[data->currentRowA][j] += a[data->currentRowA][k] * b[k][j];
        }
        
    }
}

void* calculateByElement(void* args){
    struct elementData* data = (struct elementData*) args;
    c_per_element[data->currentRow][data->currentColumn] = 0;
    for (int i = 0; i < data->columnA; i++)
    {
        c_per_element[data->currentRow][data->currentColumn] += a[data->currentRow][i] *  b[i][data->currentColumn];
    }
    
}

void getNumberOfRowsAndColumns(char* input, int* row, int* column){
    char* token = strtok(input, " =");
    // char** tokenized = malloc(MAX_INPUT * sizeof(char*));
    char* tokenized[4];
    int it = 0;
    // gets the row and column of matrix A
    while(token != NULL){
        if(it == 4)
            break;
        tokenized[it++] = token;
        token = strtok(NULL, " =");
    }

    *row = atoi(tokenized[1]);
    *column = atoi(tokenized[3]);
}

void populateMatrix(FILE* fp, int rows, int columns, int a[][20]){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            // fscanf(fp, "%d", &a[i][j]);
            fscanf(fp, "%d", &a[i][j]);
        }
        
    }
    
}

void method1(int rowA, int columnA, int rowB, int columnB, char* output){
    pthread_t thread;
    struct matrixData data = {rowA, columnA,rowB, columnB};
    struct matrixData* dataPointer = &data;
    // multiplication by one thread
    pthread_create(&thread, NULL, calculateByMatrix, (void * ) &data);
    pthread_join(thread, NULL);
    char* temp = (char *)malloc(MAX_INPUT * sizeof(char));
    strcpy(temp, output);
    strcat(temp, "_per_matrix.txt");
    FILE* fp = fopen(temp, "w");
    fprintf(fp, "Method: A thread per matrix\n");
    printMatrixToFile(rowA, columnB, "matrix", output, fp);
    fclose(fp);
}

void method2(int rowA, int columnA, int rowB, int columnB, char* output){
    pthread_t thread[rowA];
    int currentThread = 0;
    // multiplication by row
    for (int i = 0; i < rowA; i++)
    {
        struct rowData data = {i, rowB, columnB};
        pthread_create(&thread[currentThread++], NULL, calculatorByRow, (void * ) &data);
    }
    for (int i = 0; i < rowA; i++)
    {
        pthread_join(thread[i], NULL);
    }
    char* temp = (char *)malloc(MAX_INPUT * sizeof(char));
    strcpy(temp, output);
    strcat(temp, "_per_row.txt");
    FILE* fp = fopen(temp, "w");
    fprintf(fp, "Method: A thread per row\n");
    printMatrixToFile(rowA, columnB, "row", output, fp);
    fclose(fp);
}

void method3(int rowA, int columnA, int rowB, int columnB, char* output){
    pthread_t thread[rowA * columnB];
    int currentThread = 0;
    // multiplication by element
    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < columnB; j++)
        {
            struct elementData data = {i, j, columnB};
            pthread_create(&thread[currentThread++], NULL, calculateByElement, (void *) &data);
        }
    }
    for (int i = 0; i < currentThread; i++)
    {
        pthread_join(thread[i], NULL);
    }
    char* temp = (char *)malloc(MAX_INPUT * sizeof(char));
    strcpy(temp, output);
    strcat(temp, "_per_element.txt");
    FILE* fp = fopen(temp, "w");
    fprintf(fp, "Method: A thread per element\n");
    printMatrixToFile(rowA, columnB, "element", output, fp);   
    fclose(fp);
}



int main(int argc, char* argv[]){
    pthread_t thread[NUM_THREADS];
    char* input1 = (char *)malloc(MAX_INPUT * sizeof(char));
    char* input2 = (char *)malloc(MAX_INPUT * sizeof(char));
    char* output = (char *)malloc(MAX_INPUT * sizeof(char));
    strcpy(input1, "a");
    strcpy(input2, "b");
    strcpy(output, "c");
    if(argc == 4){
        strcpy(input1, argv[1]);
        strcpy(input2, argv[2]);
        strcpy(output, argv[3]);
    }
    strcat(input1, ".txt");
    strcat(input2, ".txt");
    FILE* fileA = fopen(input1, "r");
    FILE* fileB = fopen(input2, "r");

    if(fileA == NULL || fileB == NULL){
        printf("File not found %s %s", input1, input2);
        return 0;
    }
    char input[MAX_INPUT];
    int rowA = 0, columnA = 0, rowB = 0, columnB = 0, currentThread = 0;

    // parses first line of input to get the row and column
    fgets(input, MAX_INPUT, fileA);
    getNumberOfRowsAndColumns(input, &rowA, &columnA);
    fgets(input, MAX_INPUT, fileB);
    getNumberOfRowsAndColumns(input, &rowB, &columnB);

    // populate matrix
    populateMatrix(fileA, rowA, columnA, a);
    populateMatrix(fileB, rowB, columnB, b);
    fclose(fileA);
    fclose(fileB);
    
    method1(rowA, columnA, rowB, columnB, output);
    method2(rowA, columnA, rowB, columnB, output);
    method3(rowA, columnA, rowB, columnB, output);
}