import os
import numpy as np

from keras.models import Sequential
from keras.layers import Dense
import matplotlib.pyplot as plt
import tensorflow.compat.v1 as tf

tf.logging.set_verbosity(tf.logging.ERROR)
np.random.seed(1337)
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
os.environ["CUDA_VISIBLE_DEVICES"] = "3"
X = np.linspace(-1, 1, 200)
np.random.shuffle(X)
Y = 0.5 * X + 2 + np.random.normal(0, 0.05, (200,))
plt.scatter(X, Y)
plt.show()

X_train, Y_train = X[:160], Y[:160]
X_test, Y_test = X[160:], Y[160:]

model = Sequential()
model.add(Dense(units=1, input_dim=1))
# model.add(Dense(output_dim=1))
model.compile(loss='mse', optimizer='sgd')
for step in range(301):
    cost = model.train_on_batch(X_train, Y_train)
    if step % 100 == 0:
        print(f'train cost: {cost:.4f}')

cost = model.evaluate(X_test, Y_test, batch_size=40)
print(f'test cost: {cost:.4f}')
W, b = model.layers[0].get_weights()
print(f'W={W}, b={b}')
Y_pred = model.predict(X_test)
plt.scatter(X_test, Y_test)
plt.plot(X_test, Y_pred)
plt.show()
