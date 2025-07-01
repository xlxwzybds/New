import numpy as np
import matplotlib.pyplot as plt

core_freqs = ['1.0', '1.3', '1.6', '2.0', '2.3', '2.6', '3.0', '3.3', '3.6', '4.0']  # 核心频率
mem_core_labels = ['1.0', '0.9', '0.8', '0.7', '0.6', '0.5','0.4']  # 存储频率
data = np.array([
    [0.89, 1.07, 1.25, 1.35, 1.58, 1.70, 1.79, 1.93, 2.02, 2.13],  # Mem Freq=1.0
    [0.77, 0.88, 0.96, 1.03, 1.08, 1.13, 1.21, 1.22, 1.23, 1.24],  # Mem Freq=0.9
    [0.71, 0.78, 0.83, 0.91, 0.84, 0.82, 0.88, 0.89, 0.94, 1.00],  # Mem Freq=0.8
    [0.61, 0.65, 0.664, 0.64, 0.646, 0.68, 0.75, 0.78, 0.81, 0.86],  # Mem Freq=0.7
    [0.56, 0.57, 0.576, 0.58, 0.583, 0.586, 0.58, 0.61, 0.65, 0.71],  # Mem Freq=0.6
    [0.51, 0.52, 0.53, 0.54, 0.545, 0.55, 0.57, 0.576, 0.582, 0.61],  # Mem Freq=0.5
    [0.47, 0.45, 0.47, 0.51, 0.52, 0.52, 0.538, 0.546, 0.547, 0.548]   # Mem Freq=0.4
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
plt.savefig('IPSmodel_DataSample_Dedup.eps', format='eps')
plt.savefig('IPSmodel_DataSample_Dedup.svg', format='svg')

# 添加网格线
plt.grid(True, linestyle='--', alpha=0.7)

# 显示图形
plt.show()
