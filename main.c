#include "pbPlots.h"
#include "supportLib.h"
#define MAXLEN 1000
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define string char*
// *Creating a structure for the model.
struct MLR
{
    int n_features;
    double **weights;   
};

// * Creating a function to return the model pointer.
struct MLR* getModel(string str)
{
    struct MLR* model = (struct MLR*)malloc(sizeof(struct MLR));
    model->n_features = feature_cnt(str);
    model->weights = (double**)malloc(sizeof(double*)*((model->n_features)+1));
    for(int i = 0;i<model->n_features+1;i++)
    {
        (model->weights)[i] = (double*)malloc(sizeof(double));
        model->weights[i][0] = 0;
    }
    
}

int data_points(char str[])
{
    FILE* line_cnt = fopen(str,"r");
    int l_cnt = 0;
    for(char c = getc(line_cnt);c!=EOF;c = getc(line_cnt))
    {
        if(c == '\n')
        {
            l_cnt++;
        }
    }
    return l_cnt-1;
}

int feature_cnt(char str[])
{
    // * counting the number of features, counting the number of comma seperated values in the first line of the file and return the number of comma seperated values - 1, as there is also a label.
    FILE* fp = fopen(str,"r");
    char str1[MAXLEN];
    fgets(str1,MAXLEN,fp);
    char* token = strtok(str1,",");
    int features = -1;
    while(token!=NULL)
    {
        features++;
        token = strtok(NULL,",");
    }
    return features;
}

void create_Map(double* x,double* y,int x_size,int y_size,char* str)
{
    RGBABitmapImageReference *imageref = CreateRGBABitmapImageReference();
	StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
    DrawScatterPlot(imageref,1000,1000,x,x_size,y,y_size,errorMessage);
    size_t length;
    double* pngData = ConvertToPNG(&length,imageref->image);
    WriteToFile(pngData,length,str);
}

void convert_to_tensor(char str[])
{
    // * Getting the data and labels ready and storing them in arrays of double values.

    // Getting feature number and number of data points from the functions.
    int features = feature_cnt(str);
    int dat_pnts = data_points(str);
    
    // Initializing data array and label array.
    double** data;
    data = (double**)malloc(sizeof(double*)*dat_pnts);
    for(int i = 0;i<dat_pnts;i++)
    {
        data[i] = (double*)malloc(sizeof(double)*(features+1));
    }
    // Label vector 
    double** label;
    label = (double**)malloc(sizeof(double*)*(dat_pnts));
    for(int i = 0;i<dat_pnts;i++)
    {
        label[i] = (double*)malloc(sizeof(double)*1);
    }

    // Extracting values from the csv file.
    FILE* file = fopen(str,"r");
    // Storing feature names
    char scan_str[MAXLEN];
    fgets(scan_str,MAXLEN,file);
    char feature_name[features][MAXLEN];
    char* token = strtok(scan_str,",");
    int i = 0;
    while(i<features)
    {
        strcpy(feature_name[i++],token);
        token = strtok(NULL,",");
    }

    // Extracting Data Values and storing them in data and label tensors.
    for(int i = 0;i<dat_pnts;i++)
    {
        fgets(scan_str,MAXLEN,file);
        data[i][0] = (double)(1.0);
        token = strtok(scan_str,",");
        for(int j = 1;j<=features;j++)
        {
            data[i][j] = (double)(atof(token));
            token = strtok(NULL,",");
        }
        label[i][0] = (double)(atof(token));
    }

}
int main()
{
    struct MLR* model = getModel("Book1.csv");
}