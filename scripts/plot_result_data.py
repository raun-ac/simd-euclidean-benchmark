import json
import matplotlib.pyplot as plt


with open('build/results.json') as f:
    data = json.load(f)

sizes = []
scalar_times = []
simd_times = []


for bench in data['benchmarks']:
    name = bench['name']
    size = int(name.split('/')[1])
    time = bench['cpu_time']
    
    if 'BM_ScalarDistance' in name:
        sizes.append(size)
        scalar_times.append(time)
    elif 'BM_SIMDDistance' in name:
        simd_times.append(time)


speedups = [s / v for s, v in zip(scalar_times, simd_times)]


plt.figure(figsize=(10, 6))
plt.plot(sizes, speedups, marker='o', linestyle='-', color='b', linewidth=2, label='AVX-512 Speedup')


l1_boundary = (48 * 1024) / 8
l2_boundary = (512 * 1024) / 8
l3_boundary = (4096 * 1024) / 8

plt.axvline(x=l1_boundary, color='r', linestyle='--', label='L1 Cache Limit (48 KB)')
plt.axvline(x=l2_boundary, color='orange', linestyle='--', label='L2 Cache Limit (512 KB)')
plt.axvline(x=l3_boundary, color='g', linestyle='--', label='L3 Cache Limit (4 MB)')


plt.xscale('log', base=2)
plt.title('SIMD AVX-512 Performance vs. Memory Bottleneck (Von Neumann Wall)', fontsize=14)
plt.xlabel('Array Size N (Log Scale)', fontsize=12)
plt.ylabel('Effective Speedup (Multiplier)', fontsize=12)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend()
plt.tight_layout()


plt.savefig('memory_wall_graph.png', dpi=300)
print("Graph successfully saved as memory_wall_graph.png")