#ifndef LISTDS_H
#define LISTDS_H
    int init_LDS (int num_lists,double **lists2,int **lists_ptr2,int **lists_size2,int temp_size);
    int LDS_print(int num_lists,double *lists,int *lists_ptr,int *lists_size);
    void LDS_insert(double data, int listID, int num_lists, int temp_size, double **lists_ptr, int *lists_ptr_array, int *lists_size);
#endif