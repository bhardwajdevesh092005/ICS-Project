#include "pbPlots.h"
#include "supportLib.h"
#define MAXLEN 1000
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define string char *
// *Creating a structure for the model.
struct MLR
{
    int n_features;
    double **weights;
};
int feature_cnt(char str[])
{
    // * counting the number of features, counting the number of comma seperated values in the first line of the file and return the number of comma seperated values - 1, as there is also a label.
    FILE *fp = fopen(str, "r");
    char str1[MAXLEN];
    fgets(str1, MAXLEN, fp);
    char *token = strtok(str1, ",");
    int features = -1;
    while (token != NULL)
    {
        features++;
        token = strtok(NULL, ",");
    }
    free(fp);
    return features;
}
// * Creating a function to return the model pointer.
struct MLR *getModel(char *str)
{
    struct MLR *model = (struct MLR *)malloc(sizeof(struct MLR));
    int feat = feature_cnt(str);
    model->n_features = feat;
    model->weights = (double **)malloc(sizeof(double *) * ((model->n_features) + 1));
    for (int i = 0; i < model->n_features + 1; i++)
    {
        (model->weights)[i] = (double *)malloc(sizeof(double));
        model->weights[i][0] = 0;
    }
    return model;
}
void forward(struct MLR *model, double **data, int features, int dat_pnts, double **y_pred)
{
    for (int i = 0; i < dat_pnts; i++)
    {
        double y_hat_i = 0;
        for (int j = 0; j < features + 1; j++)
        {
            y_hat_i += (data[i][j]) * (model->weights[j][0]);
        }
        y_pred[i][0] = y_hat_i;
    }
}
void weight_update(struct MLR *model, double **data, double **label, int dat_pnts, int features, double alpha, double **y_pred)
{
    for (int i = 0; i < features + 1; i++)
    {
        double loss_sig = 0;
        for (int j = 0; j < dat_pnts; j++)
        {
            loss_sig = (y_pred[j][0] - label[j][0]) * data[j][i];
        }
        model->weights[i][0] = model->weights[i][0] - ((alpha) / dat_pnts) * (loss_sig);
    }
}
double **predict(struct MLR *model, double **data, int dat_pnts, int features)
{
    double **predictions = (double **)malloc(sizeof(double *) * dat_pnts);
    for (int i = 0; i < dat_pnts; i++)
    {
        predictions[i] = (double *)malloc(sizeof(double));
    }
    for (int i = 0; i < dat_pnts; i++)
    {
        double sum = 0;
        for (int j = 0; j < features + 1; j++)
        {
            sum += (model->weights[j][0] * data[i][j]);
        }
        predictions[i][0] = sum;
    }
    return predictions;
    free(predictions);
}
double RMSE(double **label, double **pred, int dat_pnts)
{
    double se = 0;
    for (int i = 0; i < dat_pnts; i++)
    {
        se += (pred[i][0] - label[i][0]) * (pred[i][0] - label[i][0]);
    }
    se = se / dat_pnts;
    return sqrt(se);
}
void create_Map(double *x, double *y, int x_size, int y_size, char *str)
{
    RGBABitmapImageReference *imageref = CreateRGBABitmapImageReference();
    StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
    DrawScatterPlot(imageref, 1000, 1000, x, x_size, y, y_size, errorMessage);
    size_t length;
    double *pngData = ConvertToPNG(&length, imageref->image);
    WriteToFile(pngData, length, str);
    free(imageref);
    free(errorMessage);
}
void train_model(struct MLR *model, double **data, double **label, double alpha, int dat_pnts, int features, int epochs, bool map_req, char* img_name)
{
    double **y_pred;
    y_pred = (double **)malloc(sizeof(double *) * dat_pnts);
    double *x = (double *)malloc(sizeof(double) * epochs);
    double *y = (double *)malloc(sizeof(double) * epochs);
    for (int i = 0; i < dat_pnts; i++)
    {
        y_pred[i] = (double *)malloc(sizeof(double));
    }
    double l = 100;
    for (int k = 0; k < epochs; k++)
    {
        forward(model, data, features, dat_pnts, y_pred);
        // *Update the weights
        weight_update(model, data, label, dat_pnts, features, alpha, y_pred);
        alpha = alpha + (1e-9);
        // Store the current RMSE in the x and y plot
        double **pred = predict(model, data, dat_pnts, features);
        x[k] = k;
        y[k] = RMSE(label, pred, dat_pnts);
        printf("Epoch: %d\t RMSE: %lf\n", k, y[k]);
    }
    if(map_req == true)
    {
        create_Map(x, y, epochs, epochs, img_name);
    }
    free(x);
    free(y);
    free(y_pred);
}

double mean(double **data, int features, int dat_pnts, int i)
{
    double sum = 0;
    for (int j = 0; j < dat_pnts; j++)
    {
        sum += data[j][i];
    }
    return sum / dat_pnts;
}

double stdev(double **data, int features, int dat_pnts, int i)
{
    double mu = mean(data, features, dat_pnts, i);
    double sq_sum = 0;
    for (int j = 0; j < dat_pnts; j++)
    {
        sq_sum += (data[j][i] - mu) * (data[j][i] - mu);
    }
    return sqrt(sq_sum / dat_pnts);
}

void standard_scale(double **data, int dat_pnts, int features)
{
    for (int i = 1; i < features + 1; i++)
    {
        double mu = mean(data, features, dat_pnts, i);
        double sigma = stdev(data, features, dat_pnts, i);
        for (int j = 0; j < dat_pnts; j++)
        {
            data[j][i] = (data[j][i] - mu) / sigma;
        }
    }
}

int data_points(char str[])
{
    FILE *line_cnt = fopen(str, "r");
    int l_cnt = 0;
    for (char c = getc(line_cnt); c != EOF; c = getc(line_cnt))
    {
        if (c == '\n')
        {
            l_cnt++;
        }
    }
    free(line_cnt);
    return l_cnt - 1;
}
void convert_to_tensor(char str[], double **data, double **label, int features, int dat_pnts)
{
    //* Getting the data and labels ready and storing them in arrays of double values.
    // Extracting values from the csv file.
    FILE *file = fopen(str, "r");
    // Storing feature names
    char scan_str[MAXLEN];
    fgets(scan_str, MAXLEN, file);
    
    // Extracting Data Values and storing them in data and label tensors.
    for (int i = 0; i < dat_pnts; i++)
    {
        fgets(scan_str, MAXLEN, file);
        data[i][0] = (double)(1.0);
        char *token = strtok(scan_str, ",");
        for (int j = 1; j <= features; j++)
        {
            data[i][j] = (double)(atof(token));
            token = strtok(NULL, ",");
        }
        label[i][0] = (double)(atof(token));
    }
    free(file);
}