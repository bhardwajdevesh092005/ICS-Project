<head>
  The Readme File
</head>
<h1>
  Multiple Linear Regression in C.
</h1>
<br>
The project uses structures in C to create a linear model.The variable of the type <b>struct MLR</b> stores the weights corresponding to the model. The get model function is created which returns the pointer to a variable model by initializing all weights to zer0. The data is read with the help of reading a comma seperated value(<b>csv</b>) file.
<br>
  I created two functions to count the number of data points and the number of features in the csv. You have to create two double type double pointers and allocate them memory as per needed. The data pointer must be allocated memory by such that it contains rows equal to the data points and columns equal to number of features <b> +1 </b>. The extra column will be allocated with all values 1 by the conver_to_tensor function which actually reads data from the csv file and stores it in the memory allocated to the data and label pointers by passing these data and label pointers created in the main function to the convert_to_tensor function. The bias is accommodated by keeping an extra weight in the model matrix of weights.
<hr>
```c
double** data;
<br>
data = (double**)malloc(sizeof(double*)*(data_points));
<br>
for(int i = 0;i&ltdata_points;i++)
<br>
{
<br>
  &nbsp&nbsp&nbsp&nbspdata[i] = (double*)malloc(sizeof(double)*(features+1));<br>
}
<br>
```
<hr>
