#include<stdio.h>
#include <stdlib.h>
#include <time.h>
void NhapMaTran(int **a, int dong, int cot)
{
    int i, j;
    for (i = 0; i < dong; i++)
        for (j = 0; j < cot; j++)
        {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
}

void XuatMaTran(int **a, int dong, int cot)
{
    int i, j;
    for (i = 0; i < dong; i++)
    {
        for (j = 0; j < cot; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
}

void RandomMaTran(int **a, int dong, int cot)
{
	srand(time(NULL));
    int i, j;
    for (i = 0; i < dong; i++)
        for (j = 0; j < cot; j++)
        {
        	a[i][j]=rand()%256;
        }
}
void sapXepMang(int *a, int sizeOfArray){
    int tg, i, j;
    
    for(i = 0; i < sizeOfArray - 1; i++){
        for(j = i + 1; j < sizeOfArray; j++){
            if(a[i] > a[j]){
                // Hoan vi 2 so a[i] va a[j]
                tg = a[i];
                a[i] = a[j];
                a[j] = tg;        
            }
        }
    }
}
void sapXepMaTran(int **kernel, int sizeOfKernel, int **output, int a, int b){
	int *p;
	p = (int *)malloc(sizeOfKernel * sizeOfKernel * sizeof(int ));
	int i, j;
	int x=0;
	for(i=0; i<sizeOfKernel; i++){
		for(j=0; j<sizeOfKernel; j++){
			*(p + x) = kernel[i][j];
			printf("%d	", *(p + x));
			++x;
		}
	}
	printf("\n");
	sapXepMang(p, sizeOfKernel*sizeOfKernel);
	for(i=0; i<sizeOfKernel*sizeOfKernel; i++){
			printf("%d	", *(p + i ));	
	}
	output[a][b] = *(p+(sizeOfKernel*sizeOfKernel-1)/2);
	printf("\n");
	free(p);
}
void MedianFilter(int **a, int dong, int cot, int sizeOfKernel, int **output){
	int **kernel = NULL;
	int i, j;
	kernel = (int **)malloc(sizeOfKernel * sizeof(int *));
	for (i = 0; i < sizeOfKernel; i++)
	{
    	kernel[i] = (int *)malloc(sizeOfKernel * sizeof(int));
	}
	int x, y;
	for (i = 0; i < dong; i++){
        for (j = 0; j < cot; j++)
        {
        	for(x = 0; x<sizeOfKernel; x++){ //offset tat ca gia tri cua ma tran kernel = 0
				for(y = 0; y<sizeOfKernel; y++){
					kernel[x][y]=0;
				}
			}
			for(x = 0; x<sizeOfKernel; x++){ //offset tat ca gia tri cua ma tran kernel = 0
				for(y = 0; y<sizeOfKernel; y++){
					if(((x+i-(int)(sizeOfKernel/2))<0)||((y+j-(int)(sizeOfKernel/2))<0)){
						kernel[x][y]=0;
					}
					else if(((x+i-(int)(sizeOfKernel/2))>=dong)||((y+j-(int)(sizeOfKernel/2))>=cot)){
						kernel[x][y]=0;
					}
					else
						kernel[x][y]=a[x+i-(int)(sizeOfKernel/2)][y+j-(int)(sizeOfKernel/2)];
				}
			}
			XuatMaTran(kernel, sizeOfKernel, sizeOfKernel);
			sapXepMaTran(kernel, sizeOfKernel, output, i, j);
        }
	}
	
	// gi?i phóng t?ng hàng
    for (i = 0; i < sizeOfKernel; i++)
    {
        free(kernel[i]);
    }
    // giai phong con tr? qu?n lý các dòng
    free(kernel);
	}
int main(){
	int **a = NULL, **output = NULL, dong, cot;
	int i;
    printf("Nhap vao so dong = ");
    scanf("%d", &dong);
    printf("Nhap vao so cot = ");
    scanf("%d", &cot);
	a = (int **)malloc(dong * sizeof(int *));
	for (i = 0; i < dong; i++)
	{
    	a[i] = (int *)malloc(cot * sizeof(int));
	}
	output = (int **)malloc(dong * sizeof(int *));
	for (i = 0; i < dong; i++)
	{
    	output[i] = (int *)malloc(cot * sizeof(int));
	}
	RandomMaTran(a, dong, cot);
	XuatMaTran(a, dong, cot);
	MedianFilter(a, dong, cot, 3, output);
	printf("Anh Sau Khi Loc: \n");
	XuatMaTran(output, dong, cot);
	    // gi?i phóng t?ng hàng
    for (i = 0; i < dong; i++)
    {
        free(a[i]);
    }
    // giai phong con tr? qu?n lý các dòng
    free(a);
    	    // gi?i phóng t?ng hàng
    for (i = 0; i < dong; i++)
    {
        free(output[i]);
    }
    // giai phong con tr? qu?n lý các dòng
    free(output);
    return 0;
}