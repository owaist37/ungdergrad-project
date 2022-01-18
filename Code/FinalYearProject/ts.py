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
#p= ggplot(data,aes(x='x',y='y')) + geom_line(aes(color='class')) 
#p+ scale_color_manual(values = c('APCA'='red','PAA'='orange','TS'='blue')
					  #labels = c('APCA'='APCA','PAA'='PAA','TS'='TS'))
#print(p)
g1 = ggplot(data, aes(x='x',y='y',color='class')) + geom_line() + scale_color_discrete(h=0.3,l=0.7) #h,l,s
print(g1)
