#include <stdio.h>
#include "common.h"
#include "ListDS.h"

int main (void){
    // double data [] = {
    //     1, 2,
    //     0, 1,
    //     3, 2,
    //     4, 5,
    //     8, 9,
    //     2, 3,
    //     5, 6,
    //     10, 11,
    //     8, 8,
    //     7, 6,
    //     7, 7,
    //     7, 8,
    //     11, 10.00,
    //     15, 23.4234
    // };
double data[200];
for (int i = 0; i < 200; i++) {
    data[i] = (i % 2 != 0) ? i*1.54 : i % 20;
}
    // printf(" data: \n");
    // for (int i=0;i<15;i++){
    //     printf(", %.2f",data[i]);
    // }

    // initialize List Data Structure
    double *lists;
    int *lists_ptr,*lists_size,temp_size,num_lists;
    num_lists = 20;
    temp_size = 5;
    CHECK_ERROR(init_LDS (num_lists,&lists,&lists_ptr,&lists_size,temp_size));
    for (int i=0;i<100;i++){
        LDS_insert(data[2*i+1],(int)data[2*i],num_lists,temp_size,&lists,lists_ptr,lists_size);
    }
    CHECK_ERROR(LDS_print(num_lists,lists,lists_ptr,lists_size));

    free (lists);
    free (lists_size);
    free (lists_ptr);
    return 0; // success signal 
}