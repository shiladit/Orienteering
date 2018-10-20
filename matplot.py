import matplotlib.pyplot as plt
import numpy as np


x = [10.5,8.7,7.3,8.2,10.2,7.4,9.7,11.7,11.2]
y =[14.4,17.7,18.8,19.9,22.1,24,23.8,20.3,14.1]
z =[10.5,18,18.3,16.5,15.4,14.9,16.3,16.4,15,16.1,15.7,13.2,14.3,14,11.4,8.3,7.9,11.4,11.2,10.1,11.7,10.2,9.7,10.1,7.4,8.2,8.7,8.9,5.6,4.9,7.3,11.2]
t =[14.4,15.9,13.3,9.3,11,13.2,13.3,17.8,17.9,19.6,20.6,20.1,15.3,5.1,6.7,5,9.8,12,17.6,18.7,20.3,22.1,23.8,26.4,24,19.9,17.7,13.6,11.1,18.9,18.8,14.1]


# y2 = [100-42.63, 100-42.85, 100-43.84, 100-42.40, 100-42.83, 100-42.09]
plt.figure(4)
plt.xlabel('Latitude')
plt.ylabel('Longitude')
plt.title('Tsiligirides Problem 1 TMAX = 85 (Sample size 32)')
# plt.annotate('Centre of gravity: 40.7703 , -73.9643');
plt.plot(z,t,color = 'r',linestyle= ' ', marker = 's', label = 'Rest of the Nodes')
plt.plot(x, y, linestyle='--', marker='s', color='b', label = 'Chosen Nodes')
plt.legend(loc='upper right')

plt.xlim([4,20])
plt.ylim([6,30])

plt.savefig("Tsiligirides_Problem_1_tmax_85.svg")
plt.show()
# plt.figure(2)

# plt.xlabel('Value of k (Number of Trees)')
# plt.ylabel('Validation Loss')
# plt.title('Validation Loss Vs Number of Trees')
# plt.plot(x, y2, 'o')
# #plt.axis('off')
# #plt.gca().set_position([0, 0, 1, 1])
# plt.savefig("test.svg")
