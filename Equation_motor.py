import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
dataset = pd.read_csv('B_R.csv')
ls = [i[0].split() for i in dataset.values]
for j in ls:
    j[0] = int(j[0])
    j[1] = float(j[1])
ls = np.array(ls)
x = ls[:, 1].reshape(-1,1)
y = ls[:, 0]
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(x, y)
y_pred = [int(k) for k in regressor.predict(x)]
slope = (regressor.coef_)[0]
Bias = regressor.intercept_
Equation = "PWM = ("+str(slope)+")Omega + "+str(Bias)
print(Equation)
v = 1
r = 1
Omega = v/r
pwm = round(slope*Omega + Bias)
# Slope = 35.947316451613446
# Bias = 6.7134362809290735
print("v =", v, ", r =", r, ", Omega =", Omega)
print("PWM =", pwm)
print(regressor.predict([[1]]))
plt.scatter(x, y_pred, color='red')
plt.plot(x, y_pred, color = 'blue')
plt.title('Motor Equation')
plt.xlabel('Omega')
plt.ylabel('PWM')
plt.grid(True)
plt.show()