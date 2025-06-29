import re
import os

file_config = open('../config/base.cfg')
for line in file_config:
    if line.startswith('mapping'):
        line_words = re.split('=|#|\s', line)
        line_words = list(filter(None, line_words))
        benchmark_name = line_words[1]
file_config.close()

if benchmark_name is not None:
    with open('./system_sim_state_3D/mapping_name.txt', 'w') as f_out:
        f_out.write(benchmark_name + '\n')
else:
    print("Warning: benchmark_name not found in config!")
