from email import message
import sys
import math
from tabnanny import check
import matplotlib.pyplot as plt

n = int(sys.argv[1])
dlina = 100
array = [[0 for j in range(n)] for i in range(n)]

i = 1
while i<=n:
    j=1
    while j<=n:
        array[i-1][n-j] = int(sys.argv[n*i-j + 2])
        j=j+1
    i=i+1

str_message = ""
i = n*n+2
while i<len(sys.argv):
    str_message += sys.argv[i]+' '
    i+=1
#print(array)

coord = [[0 for j in range(2)] for i in range(n)]

def push_coord():
    i = 0
    for i in range(n):
        x = dlina * math.cos(2 * math.pi * i / n)
        y = dlina *  math.sin(2 * math.pi * i / n)
        coord[i] = (x,y)

push_coord()

#print(coord)

def print_orient_graph():
    size = dlina*1.3
    plt.figure(figsize=(6.5, 6))
    plt.xlim([-size, size])
    plt.ylim([-size, size])
    arrowprops = {
        'arrowstyle': '<|-',
        'mutation_scale': 15,
        'connectionstyle':'arc3, rad=0.04'
    }
    plt.text(-size, size, str_message)
    i = 0
    for i in range(n):
        alp=0.07
        plt.text(coord[i][0]-dlina*0.025, coord[i][1]-dlina*0.025, i+1)
        ax=plt.gca()
        j=0
        for j in range(n):
            k = 1-alp
            if array[i][j]!=0:
                xy1 = (coord[i][0]*k, coord[i][1]*k)
                xy2 = (coord[j][0]*k, coord[j][1]*k)
                if(i!=j):
                    x, y = ((n/2-0.25*n)*xy1[0]+(n/2+0.2*n)*xy2[0])/n, ((n/2-0.2*n)*xy1[1]+(n/2+0.2*n)*xy2[1])/n
                    if(coord[j][0]>=0):
                        y+=dlina*0.05
                    else:#if(coord[i][0]<0):
                        y-=dlina*0.05
                    if(coord[j][1]>0):
                        x-=dlina*0.05
                    else:#if(coord[i][1]<0):
                        x+=dlina*0.05
                    plt.text(x-dlina*0.025, y-dlina*0.025, array[i][j], weight='black', color='blue')
                    plt.annotate(' ', xy=xy1, xytext=xy2, arrowprops=arrowprops)
                else:
                    val1 = 1+alp
                    x, y = coord[i][0]*val1, coord[i][1]*val1
                    circle = plt.Circle((x, y), dlina*2*alp, color='k', fill=False)
                    ax.add_patch(circle)

                    val1 += alp
                    plt.text(coord[i][0]*val1-dlina*0.025, coord[i][1]*val1-dlina*0.025, array[i][j], weight='black', color='red')

                    val1 = 1+3*alp
                    x, y = coord[i][0]*val1, coord[i][1]*val1
                    plt.annotate(' ', xy=(x,y), xytext=(x,y), arrowprops=arrowprops)
        circle = plt.Circle(coord[i], dlina*alp, color='lightblue', fill=True)
        ax.add_patch(circle)
    #plt.axes().set_aspect(1)
    plt.axis('off')
    plt.grid()
    plt.show()


def print_non_orient_graph():
    size = dlina*1.3
    plt.figure(figsize=(6.5, 6))
    plt.xlim([-size, size])
    plt.ylim([-size, size])
    arrowprops = {
        'arrowstyle': '-',
        'mutation_scale': 15,
        'connectionstyle':'arc3, rad=0'
    }
    plt.text(-size, size, str_message)
    i = 0
    for i in range(n):
        alp=0.07
        plt.text(coord[i][0]-dlina*0.025, coord[i][1]-dlina*0.025, i+1)
        ax=plt.gca()
        j=i
        for j in range(n):
            k = 1-alp
            if array[i][j]!=0 and i<=j:
                xy1 = (coord[i][0]*k, coord[i][1]*k)
                xy2 = (coord[j][0]*k, coord[j][1]*k)
                if(i!=j):
                    x, y = ((n/2-0.25*n)*xy1[0]+(n/2+0.2*n)*xy2[0])/n, ((n/2-0.2*n)*xy1[1]+(n/2+0.2*n)*xy2[1])/n
                    if(coord[j][0]>=0):
                        y+=dlina*0.05
                    else:#if(coord[i][0]<0):
                        y-=dlina*0.05
                    if(coord[j][1]>0):
                        x-=dlina*0.05
                    else:#if(coord[i][1]<0):
                        x+=dlina*0.05
                    plt.annotate(' ', xy=xy1, xytext=xy2, arrowprops=arrowprops)
                    plt.text(x-dlina*0.025, y-dlina*0.025, array[i][j], weight='black', color='blue')
                else:
                    val1 = 1+alp
                    x, y = coord[i][0]*val1, coord[i][1]*val1
                    circle = plt.Circle((x, y), dlina*2*alp, color='k', fill=False)
                    ax.add_patch(circle)

                    val1 += alp
                    plt.text(coord[i][0]*val1-dlina*0.025, coord[i][1]*val1-dlina*0.025, array[i][j], weight='black', color='red')

                    val1 = 1+3*alp
                    x, y = coord[i][0]*val1, coord[i][1]*val1
                    plt.annotate(' ', xy=(x,y), xytext=(x,y), arrowprops=arrowprops)
        circle = plt.Circle(coord[i], dlina*alp, color='lightblue', fill=True)
        ax.add_patch(circle)
    #plt.axes().set_aspect(1)
    plt.axis('off')
    plt.grid()
    plt.show()


check_orient = True
i = 0
for i in range(n):
    j = i
    for j in range(n):
        if array[i][j] == array[j][i]:
            check_orient = check_orient and True
        else:
            check_orient = check_orient and False

#print(check_orient)
if check_orient==True:
    print_non_orient_graph()
else:
    print_orient_graph()