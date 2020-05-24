Your first task is to use
California census data to build a model of housing prices in the state. This data
includes metrics such as the population, median income, and median housing
price for each block group in California. Block groups are the smallest
geographical unit for which the US Census Bureau publishes sample data (a
block group typically has a population of 600 to 3,000 people). We will call
them “districts” for short.
Your model should learn from this data and be able to predict the median
housing price in any district, given all the other metrics.


## First, you need to frame the problem: 

 ### is it 
 * supervised, 
 * unsupervised, or
 * Reinforcement Learning?    
 
> answer: it is clearly a typical supervised learning task, 
> since you are given labeled training examples 
> (each instance comes with the expected output, i.e., the district’s median housing price).        
 
 ### is it 
 * a classification task, 
 * a regression task, or
 * something else? 

> answer: it is also a typical regression task, since you are asked to predict a value. 
> More specifically, this is a *multiple regression problem*, since the system will 
> use multiple features to make a prediction (it will use the district’s population, 
> the median income, etc.). 
> It is also a *univariate regression problem*, since we are only trying to predict 
> a single value for each district. 
> If we were trying to predict multiple values per district, it would be a *multivariate 
> regression problem*. 

 ### should you use 
 * batch learning or 
 * online learning techniques?

> answer: there is no continuous flow of data coming into the system, there is 
> no particular need to adjust to changing data rapidly, and the data is small 
> enough to fit in memory, so plain batch learning should do just fine.

## Select a Performance Measure

A typical performance
measure for regression problems is the Root Mean Square Error (RMSE). It
gives an idea of how much error the system typically makes in its predictions,
with a higher weight for large errors.

**Root Mean Square Error (RMSE)**

----- formulae ------

#### NOTATIONS
This equation introduces several very common Machine Learning notations
that we will use throughout this book:
* `m` is the number of instances in the dataset you are measuring the RMSE on.
  * for example, if you are evaluating the RMSE on a validation set of 2,000 districts, then m = 2,000.

* `x(i)` is a vector of all the feature values (excluding the label) of the i
instance in the dataset, and y is its label (the desired output value
for that instance).
  * For example, if the first district in the dataset is located at
    longitude –118.29°, latitude 33.91°, and it has 1,416
    inhabitants with a median income of $38,372, and the
    median house value is $156,400 (ignoring the other
    features for now), then:

  x
(1) =
⎛
⎜⎜⎜⎜
⎝
−118.29
33.91
1,416
38,372
⎞
⎟⎟⎟⎟
⎠
and:
y
(1) = 156,400

  
  
