import os
import pandas as pd
import numpy as np
import matplotlib
from plotnine import *
from plotnine.data import *

#get current working directory
cwd = os.getcwd()
file = cwd+'/points.csv'

data=pd.read_csv(file)
theme_set(theme_538())
g1 = ggplot(data, aes(x='x',y='y',color='class')) + geom_line() + scale_fill_gradient('#E69F00', '#56B4E9')
print(g1)
