import numpy as np
import matplotlib.pyplot as plt

core_freqs = ['1.0', '1.3', '1.6', '2.0', '2.3', '2.6', '3.0', '3.3', '3.6', '4.0']  # 核心频率
mem_core_labels = ['1.0', '0.9', '0.8', '0.7', '0.6', '0.5','0.4']  # 存储频率
data = np.array([
    [1.36, 1.76, 2.16, 2.67, 3.05, 3.45, 3.92, 4.26, 4.64, 5.14],  # Mem Freq=1.0
    [1.35, 1.74, 2.13, 2.61, 2.98, 3.32, 3.87, 4.25, 4.57, 5.04],  # Mem Freq=0.9
    [1.34, 1.72, 2.09, 2.56, 2.91, 3.23, 3.70, 4.04, 4.37, 4.74],  # Mem Freq=0.8
    [1.32, 1.68, 2.00, 2.43, 2.84, 3.13, 3.55, 3.81, 4.13, 4.50],  # Mem Freq=0.7
    [1.30, 1.63, 1.94, 2.34, 2.74, 3.05, 3.44, 3.69, 3.89, 4.27],  # Mem Freq=0.6
    [1.28, 1.60, 1.88, 2.24, 2.63, 2.96, 3.35, 3.53, 3.79, 4.07],   # Mem Freq=0.5
    [1.26, 1.57, 1.85, 2.17, 2.53, 2.88, 3.25, 3.43, 3.67, 3.84]   # Mem Freq=0.4
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
plt.savefig('IPSmodel_DataSample_Blackscholes.eps', format='eps')
plt.savefig('IPSmodel_DataSample_Blackscholes.svg', format='svg')

# 添加网格线
plt.grid(True, linestyle='--', alpha=0.7)

# 显示图形
plt.show()
