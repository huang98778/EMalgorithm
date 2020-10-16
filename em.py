'''
Author: your name
Date: 2020-10-14 14:35:06
LastEditTime: 2020-10-14 14:43:20
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: /semlocalization/home/hy/Ecarx_ws/HY520/EMalgorithm/em.py
'''


import numpy as np
import matplotlib.pyplot as plt

dis_num = 100 
sample_num = 10000 
alphas = np.random.rand(dis_num) 
alphas /= np.sum(alphas)  
mus = np.random.rand(dis_num)
sigmas = np.random.rand(dis_num)**2 
samples = 1-(1-np.random.rand(sample_num))**0.5 
C_pi = (2*np.pi)**0.5

dis_val = np.zeros([sample_num,dis_num]) 
pij = np.zeros([sample_num,dis_num]) 
def calc_dis_val(sample,alpha,mu,sigma,c_pi):
    return alpha*np.exp(-(sample[:,np.newaxis]-mu)**2/(2*sigma))/(c_pi*sigma**0.5) 
def calc_pij(dis_v):  
    return dis_v / dis_v.sum(axis = 1)[:,np.newaxis]      
 
for i in range(1000):
    print(i)
    dis_val = calc_dis_val(samples,alphas,mus,sigmas,C_pi)
    pij = calc_pij(dis_val)  
    nj = pij.sum(axis = 0)
    alphas_before = alphas
    alphas = nj / sample_num
    mus = (pij*samples[:,np.newaxis]).sum(axis=0)/nj
    sigmas = (pij*(samples[:,np.newaxis] - mus)**2 ).sum(axis=0)/nj
    a = np.linalg.norm(alphas_before - alphas)
    print(a)
    if  a< 0.001:
        break

plt.rcParams['font.sans-serif']=['SimHei'] 
plt.rcParams['axes.unicode_minus']=False 
def get_dis_val(x,alpha,sigma,mu,c_pi):
    y = np.zeros([len(x)]) 
    for a,s,m in zip(alpha,sigma,mu):   
        y += a*np.exp(-(x-m)**2/(2*s))/(c_pi*s**0.5)   
    return y
def paint(alpha,sigma,mu,c_pi,samples):
    x = np.linspace(-1,2,500)
    y = get_dis_val(x,alpha,sigma,mu,c_pi) 
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.hist(samples,density = True,label = 'distribute') 
    ax.plot(x,y,label = "get prob")
    ax.legend(loc = 'best')
    plt.show()
paint(alphas,sigmas,mus,C_pi,samples)