#include <stdio.h>
#include "common.h"
#include "ListDS.h"
#include "listDS_types.h"

int main (void){
ListData data[300];
int group [300];
for (int i = 0; i < 300; i++) {
    data[i].double_data = i*1.54;
    data[i].int_data = i;
    group[i]= i % 20;
}
    // printf(" data: \n");
    // for (int i=0;i<15;i++){
    //     printf(", %.2f",data[i]);
    // }

    // initialize List Data Structure
    ListData *lists;
    int *lists_ptr,*lists_size,temp_size,num_lists;
    num_lists = 20;
    temp_size = 5;
    CHECK_ERROR(init_LDS (num_lists,&lists,&lists_ptr,&lists_size,temp_size));
    for (int i=0;i<300;i++){
        LDS_insert(data[i],group[i],num_lists,temp_size,&lists,lists_ptr,lists_size);
    }
    CHECK_ERROR(LDS_print(num_lists,lists,lists_ptr,lists_size));

    free (lists);
    free (lists_size);
    free (lists_ptr);
    return 0; // success signal 
}