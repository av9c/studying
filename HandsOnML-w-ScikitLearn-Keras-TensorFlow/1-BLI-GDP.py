'''
if money makes people happy

0.1) download data from:
the Better Life Index data                          -> from the OECD’s website and 
stats about gross domestic product (GDP) per capita -> from the IMF’s website

0.2) u join the tables and sort by GDP per capita.
Table 1-1. Does money make people happier?
Country         GDP per capita (USD)    Life satisfaction
Hungary         12,240                  4.9
Korea           27,195                  5.8
France          37,675                  6.5
Australia       50,962                  7.3
United States   55,805                  7.2

1) plot the data for these countries
and we can see: life satisfaction goes up more or less linearly as the
country’s GDP per capita increases. 
So you decide to model life satisfaction as a "linear function" of GDP per capita. 
This step is called "model selection": you selected a linear model of life 
satisfaction with just one attribute, GDP per capita.

life_satisfaction = θ0 + θ1 × GDP_per_capita

This model ("linear function") has two model parameters, θ and θ . 
By tweaking these parameters, you can make your model represent any linear function.

2.1) Before you can "use your model", you "need to define the parameter values θ and θ". 
How can you know which values will make your model perform best? 

2.2) To answer this question, you "need to specify a performance measure". 
You can either define a "utility function" (or fitness function) that measures how good your model is, 
or you can define a "cost function" that measures how bad it is. 
For Linear Regression problems, people typically use a "cost function" that measures the
distance between the "linear model’s" predictions and the training examples; 
the objective is to minimize this distance.

2.3) This is where the Linear Regression algorithm comes in: you feed it your
training examples, and it finds the parameters that make the linear model fit best
to your data. This is called "training the model". In our case, the algorithm finds
that the optimal parameter values are θ0 = 4.85 and θ1 = 4.91 × 10^-5.
Now the model fits the training data as closely as possible (for a linear model).

3) You are finally ready to "run the model" to make predictions. 
For example, say you want to know how happy Cypriots are, and the 
OECD data does not have the answer. 
Fortunately, you can use your model to make a good prediction: you
look up Cyprus’s GDP per capita, find $22,587, and then apply your model and
find that life satisfaction is likely to be somewhere around 

4.85 + 22,587 × 4.91 × 10^-5 = 5.96.
'''

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sklearn.linear_model
# Load the data
oecd_bli = pd.read_csv("oecd_bli_2015.csv", thousands=',')
gdp_per_capita = pd.read_csv("gdp_per_capita.csv",thousands=',',delimiter='\t',
encoding='latin1', na_values="n/a")
# Prepare the data
country_stats = prepare_country_stats(oecd_bli, gdp_per_capita)
X = np.c_[country_stats["GDP per capita"]]
y = np.c_[country_stats["Life satisfaction"]]
# Visualize the data
country_stats.plot(kind='scatter', x="GDP per capita", y='Life satisfaction')
plt.show()
# Select a linear model
model = sklearn.linear_model.LinearRegression()
# Train the model
model.fit(X, y)
# Make a prediction for Cyprus
X_new = [[22587]] # Cyprus's GDP per capita
print(model.predict(X_new)) # outputs [[ 5.96242338]]







