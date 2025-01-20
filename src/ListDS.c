#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int init_LDS (int num_lists,double **lists2,int **lists_ptr2,int **lists_size2,int temp_size){
    if ( temp_size == 0 || num_lists == 0){
        fprintf(stderr,"! the temporary size or number of list is not defined.\n");
        return 1;
    }
    double *lists = (double *)malloc ((size_t)num_lists*(size_t)temp_size*sizeof(double));
    int *lists_ptr = (int *)calloc ((size_t)(num_lists+1),sizeof(int));
    int *lists_size = (int *) calloc ((size_t)num_lists,sizeof(int));
    if (lists == NULL || lists_ptr == NULL || lists_ptr == NULL ){
        fprintf(stderr,"! there is a problem in allocation memory\n");
        return 1;
    }
    for (int i=1;i<=num_lists;i++)
        lists_ptr[i]=temp_size*i;
    
    // pass arraies
    *lists2 =lists;
    *lists_ptr2 = lists_ptr;
    *lists_size2 = lists_size;
    return 0; //success signal
}
void LDS_reloc(int listID, int num_lists, double **lists_ptr, int *lists_ptr_array, int *lists_size, int temp_size) {
    // Extract the current `lists` array
    double *lists = *lists_ptr;

    // Calculate the new size for the `lists` array
    int newsize = lists_ptr_array[num_lists] + temp_size;

    // Safely reallocate memory for the `lists` array
    double *new_lists = (double *)realloc(lists, (size_t)newsize * sizeof(double));
    if (new_lists == NULL) {
        fprintf(stderr, "Reallocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Shift elements in the `lists` array to create space for the new list
    int start = lists_ptr_array[listID + 1];
    int end = lists_ptr_array[num_lists];

    // Move elements in reverse to avoid overwriting
    for (int i = end - 1; i >= start; i--) {
        new_lists[i + temp_size] = new_lists[i];
    }

    // Initialize the newly created space with 0
    for (int i = start; i < start + temp_size; i++) {
        new_lists[i] = 0;
    }

    // Update `lists_ptr_array` 
    for (int i = listID + 1; i <= num_lists; i++) {
        lists_ptr_array[i] += temp_size;
    }

    // Update the pointer to the reallocated memory
    *lists_ptr = new_lists;
}
int LDS_print(int num_lists,double *lists,int *lists_ptr,int *lists_size){
    if (lists == NULL || lists_ptr == NULL || lists_size == NULL){
        fprintf(stderr,"! NULL pointer pass to the function\n");
        return 1;
    }
    for (int i=0;i<num_lists;i++){
        printf("- List%d size(%d): ",i,lists_size[i]);
        for (int k=0;k<lists_size[i];k++)
        printf("%.2f ",lists[lists_ptr[i]+k]);
        printf("\n");
    }
    return 0; //success signal
}
void LDS_insert(double data, int listID, int num_lists, int temp_size, double **lists_ptr, int *lists_ptr_array, int *lists_size) {
    // Extract the current `lists` array
    double *lists = *lists_ptr;

    // Check if there's enough space; if not, reallocate
    int lsize = lists_ptr_array[listID + 1] - lists_ptr_array[listID];
    if (lsize <= lists_size[listID]) {
        #ifdef DEBUG
        printf("! Relocate list memory safely\n");
        #endif
        LDS_reloc(listID, num_lists, lists_ptr, lists_ptr_array, lists_size, temp_size);
        lists = *lists_ptr; // Update the local pointer after reallocation
    }

    // Insert the data
    lists[lists_ptr_array[listID] + lists_size[listID]] = data;
    lists_size[listID]++;
}


