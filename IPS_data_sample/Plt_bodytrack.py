import numpy as np
import matplotlib.pyplot as plt

core_freqs = ['1.0', '1.3', '1.6', '2.0', '2.3', '2.6', '3.0', '3.3', '3.6', '4.0']  # 核心频率
mem_core_labels = ['1.0', '0.9', '0.8', '0.7', '0.6', '0.5','0.4']  # 存储频率
data = np.array([
   [1.144 ,1.378 ,1.584 ,1.852 ,2.    ,2.114 ,2.222 ,2.357 ,2.432 ,2.548],
   [0.962 ,1.14  ,1.29  ,1.504 ,1.608 ,1.699 ,1.818 ,1.886 ,1.935 ,2.216],
   [0.806 ,0.909 ,0.988 ,1.099 ,1.15  ,1.182 ,1.205 ,1.231 ,1.254 ,1.282],
   [0.704 ,0.802 ,0.865 ,0.966 ,0.996 ,1.02  ,1.045 ,1.071 ,1.088 ,1.117],
   [0.637 ,0.703 ,0.744 ,0.769 ,0.793 ,0.818 ,0.857 ,0.871 ,0.882 ,0.915],
   [0.63, 0.67, 0.74, 0.76, 0.78, 0.81, 0.82, 0.83, 0.85, 0.85],  # Mem Freq=0.5
   [0.57, 0.61, 0.67, 0.69, 0.71, 0.74, 0.75, 0.76, 0.78, 0.78]   # Mem Freq=0.4
])

markers = ['o', 's', '^', 'D', '*', 'v', 'P']

# 创建折线图
#plt.figure(figsize=(12, 8))  # 设置图形大小
plt.figure(figsize=(12, 6))  # 设置图形大小
for i in range(len(mem_core_labels)):
    plt.plot(core_freqs, data[i], marker=markers[i], label=f'{mem_core_labels[i]} GHz')
    #plt.plot(core_freqs, data[i], marker='o', label=f'{mem_core_labels[i]} GHz')

# 添加标题和标签
plt.title('Impact of Core Frequency on IPS at Different Memory Frequencies', fontsize=16)
plt.xlabel('Core Frequency(GHz)', fontsize=16)
plt.ylabel(r'$\text{IPS} \, (10^{10})$', fontsize=16)
plt.ylim(0, 5.5)

# 调大横纵坐标的数字
plt.tick_params(axis='both', labelsize=16)
plt.legend(title='Memory Frequency', loc='upper left', fontsize=14, title_fontsize=15)

# 添加图例
plt.legend(title='Memory Frequency', loc='upper left',fontsize=14)
plt.savefig('IPSmodel_DataSample_Bodytrack.eps', format='eps')
plt.savefig('IPSmodel_DataSample_Bodytrack.svg', format='svg')

# 添加网格线
plt.grid(True, linestyle='--', alpha=0.7)

# 显示图形
plt.show()
