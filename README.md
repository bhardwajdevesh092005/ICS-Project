The Readme File
# Multiple Linear Regression in C.
The project uses structures in C to create a linear model.The variable of the type **struct MLR** stores the weights corresponding to the model. The get model function is created which returns the pointer to a variable model by initializing all weights to zer0. The data is read with the help of reading a comma seperated value(**csv**) file.<br>
I created two functions to count the number of data points and the number of features in the csv. You have to create two double type double pointers and allocate them memory as per needed. The data pointer must be allocated memory by such that it contains rows equal to the data points and columns equal to number of features **+1**. <font color = "green">The extra column will be allocated with all values 1 by the conver_to_tensor function.</font> It actually reads data from the csv file and stores it in the memory allocated to the data and label pointers by passing these data and label pointers created in the main function to the convert_to_tensor function. The bias is accommodated by keeping an extra weight in the model matrix of weights.
```c
double** data = (double**)malloc(sizeof(double*)*(data_points));
for(int i = 0;i<data_points;i++)
{
  data[i] = (double*)malloc(sizeof(double)*(features+1));
}
```
