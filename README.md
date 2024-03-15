The Readme File
# Multiple Linear Regression in C.
The project uses structures in C to create a linear model.The variable of the type **struct MLR** stores the weights corresponding to the model. The *get_model* function is created which returns the pointer to a variable model by initializing all weights to zer0. The data is read with the help of reading a comma seperated value(**csv**) file.<br> <font color = "red">The file must be such that the label or the actual values should be the last column of it.</font><br>
The number of features and data_points in read from the csv file and stored in the variables. For this, there are specified functions in the header file.<br>
```c
int features = feature_cnt("<file_name>");
int dat_points = data_points("<file_name>");
struct MLR* model = get_model("<file_name>");
```
I created two functions to count the number of data points and the number of features in the csv. You have to create two double type double pointers and allocate them memory as per needed. The data pointer must be allocated memory by such that it contains rows equal to the data points and columns equal to number of features **+1**.<br> <font color = "green">The extra column will be allocated with all values 1 by the conver_to_tensor function.</font> <br>It actually reads data from the csv file and stores it in the memory allocated to the data and label pointers by passing these data and label pointers created in the main function to the convert_to_tensor function. The bias is accommodated by keeping an extra weight in the model matrix of weights.
```c
double** data = (double**)malloc(sizeof(double*)*(data_points));
for(int i = 0;i<data_points;i++)
{
  data[i] = (double*)malloc(sizeof(double)*(features+1));
}
```
Similarly for label we have to create a column vector with the help of matrices and double pointers which will be done the following way.
```c
double** label = (double**)malloc(sizeof(double*)*data_points);
for(int i = 0;i<n;i++)
{
  // The label is a column vector hence each row of it will have only one element.
  label[i] = (double*)malloc(sizeof(double)*1);
}
```
Now we have to pass the *label* pointer the *data* pointer into the function ***convert_to_tensor*** as below:
```c
convert_to_tensor("<file_name as string>",data,label,features,data_points);
```
This reads the values from the csv and puts them i place in the memory allocted accordingly.
##### Now we are ready with the data and the initialized model and we are to train our data.
The train model uses the approach of *gradient descent* by taking the *squared_mean_error* as the *loss_function*.In order to train the model we call the train model function.
```c
bool graph = true;
train_model(model,data,label,learning_rate,data_points,features,<number of epochs in int>,graph,"<file name to store the graph with .png extension>");
```
The *graph* boolean is passed if one wants to create the graph to look for the decrease in *root_mean_squared_error* as the epochs pass.<br>
For graphing we use the *[pbPlots](https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.9.1)* library. The graph can be used to select learning rate and epochs.

In order to run the file we need to run the following commands in the terminal : 
```bash
gcc main.c pbPlots.c suppotLib.c
./a.exe
```
The graph looks like this:
![Graph](https://github.com/bhardwajdevesh092005/Multiple-Linear-Regression-in-C/blob/main/RMSE.png?raw=true)

# \-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\- THE END \-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-