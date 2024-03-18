#include<stdio.h>
#include "mlr.h"
int main()
{
    char data_file[] = "linreg-data.csv";
    struct MLR *model = getModel(data_file);
    // Getting feature number and number of data points from the functions.
    int features = feature_cnt(data_file);
    int dat_pnts = data_points(data_file);
    //* Initializing data array and label array.
    double **data;
    data = (double **)malloc(sizeof(double *) * dat_pnts);
    for (int i = 0; i < dat_pnts; i++)
    {
        data[i] = (double *)malloc(sizeof(double) * (features + 1));
    }
    //* Label vector
    double **label;
    label = (double **)malloc(sizeof(double *) * (dat_pnts));
    for (int i = 0; i < dat_pnts; i++)
    {
        label[i] = (double *)malloc(sizeof(double) * 1);
    }
    // * Getting the ata loaded from the csv file.
    convert_to_tensor(data_file, data, label, features, dat_pnts);
    // * Standard scaling of the data
    standard_scale(data,dat_pnts,features);
    //* Train the model
    train_model(model, data, label, 1e-2, dat_pnts, features,9000,true,"RMSE.png");


    // Test the model
    // int test_features = feature_cnt("linreg-data-test.csv");
    // int test_dat_pnts = data_points("linreg-data-test.csv");
    // double **test_data;
    // test_data = (double **)malloc(sizeof(double *) * test_dat_pnts);
    // for (int i = 0; i < test_dat_pnts; i++)
    // {
    //     test_data[i] = (double *)malloc(sizeof(double) * (test_features + 1));
    // }
    // //* Label vector
    // double **test_label;
    // test_label = (double **)malloc(sizeof(double *) * (test_dat_pnts));
    // for (int i = 0; i < test_dat_pnts; i++)
    // {
    //     test_label[i] = (double *)malloc(sizeof(double) * 1);
    // }
    // convert_to_tensor("linreg-data-test.csv",test_data,test_label,test_features,test_dat_pnts);
    // double** pred = predict(model,test_data,test_dat_pnts,test_features);
    // printf("%lf",RMSE(test_label,pred,test_dat_pnts));
    free(data);
    free(label);
    free(model);
}