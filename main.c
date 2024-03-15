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
    train_model(model, data, label, 100, dat_pnts, features,100,true,"RMSE.png");
    double **pred = predict(model, data, dat_pnts, features);
    // printf("%lf",RMSE(label,pred,dat_pnts));
    // printf("Done with Training!!\n");
    free(data);
    free(label);
    free(model);
}