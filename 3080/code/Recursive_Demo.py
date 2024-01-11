#!/usr/bin/env python
# coding: utf-8

# # Example 1

# 1. S(1) = 2 <Br>
# 2. S(n) = 2S(n-1) <br>

# In[11]:


## recursive algorithm:
def S_recur(n):
    if n == 1:
        return 2
    else:
        return 2*S_recur(n-1)


# In[10]:


for i in range(1,6):
    print("i: ", i, " = ", S_recur(i))


# In[18]:


## iterative algorithm:

def S_ite(n):
    if n == 1:
        return 2
    else:
        S = 2
        for i in range(2,n+1):
            S = 2*S
        return S


# In[17]:


for i in range(1,6):
    print("i: ", i, " = ", S_ite(i))


# ##############################

# # Example 2

# 1. F(1) = 1 <Br>
# 2. F(2) = 1 <br>
# 3. F(n) = F(n-2) + F(n-1) for n > 2<br>

# In[20]:


def F_recur(n):
    if n == 1 or n == 2:
        return 1
    else:
        return F_recur(n-2) + F_recur(n-1)


# In[25]:


for i in range(1,11):
    print("i: ", i, " = ", F_recur(i))


# In[28]:


## iterative algorithm:

def F_ite(n):
    if n == 1 or n == 2:
        return 1
    else:
        F1 = 1
        F2 = 1
        for i in range(3,n+1):
            Fn = F1 + F2
            F1 = F2
            F2 = Fn
        return Fn


# In[29]:


for i in range(1,11):
    print("i: ", i, " = ", F_ite(i))


# In[ ]:




