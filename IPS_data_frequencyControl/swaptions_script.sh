#!/bin/bash

cfg_file="../config/gainestown_3D_16core16bank.cfg"

update_latency_and_run() {
    local latency_value=$1

    sed -i "s/^\([[:space:]]*latency[[:space:]]*=[[:space:]]*\)[0-9]\+/latency = $latency_value/" "$cfg_file"

    if grep -q "latency = $latency_value" "$cfg_file"; then
        echo "Latency parameter updated to $latency_value successfully."
    else
        echo "Failed to update latency parameter to $latency_value."
        exit 1
    fi

    python3 run.py
}

#latency_values=(15 45 75 105 135 165 195)
latency_values=(15 16 17 18 19 20 21 22)

for latency in "${latency_values[@]}"
do
    update_latency_and_run $latency
done
