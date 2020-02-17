# Report of performace: Baseline

This file includes the profiling results of the project. 

|    Function        | Argon 108 | Argon 2916 |
|--------------------|-----------|------------|
| force()            | 72,68%    | 65,24%     |
| pbc()              | 20,12%    | 24,42%     |
| pbc@plt            | 4,91%     | 9,57%      |
| propagate_velocity | 1,23%     | 0,09%      |

The other functions are below 1%.

## Walltime 

|    Function        | Argon 108   | Argon 2916  |
|--------------------|-------------|-------------|
| walltime           | 6,407873303 | 296,5620224 |

> Time measured in seconds

## Hotspots

### `force()`

|    Function        | Argon 108 | Argon 2916 |
|--------------------|-----------|------------|
| sqrt()             | 18,48%    | 42,76%     |
| div()              | 11,07%    | 2.13%      |
| pbc@plt            | 4,91%     | 9,57%      |
| comisd             | -,--%     | 7,45%      |

Other operations are below of 4%.

### `pbc()`

|    Function        | Argon 108 | Argon 2916 |
|--------------------|-----------|------------|
| jump               | 12,72%    | 19,33%     |
| movapd             | 11,80%    | 5,32%      |
| add                | 11,85%    | 7,91%      |
| comisd             | 12,75%    | 20,44%     |
| repz               | --,--%    | 22,27%     |

* Conditional jump: 12,72%
* SIMD memory MOV (SSE2): 11,80%
* Addition: 11,85%
* Compare floats (SSE2): 12,75%
* Repeat while zero: repz

Other operations are below of 4%.
 
### `propagate_velocity`

** For Argon 108 **

* Divisions: 78,88%

This becomes negligible when going to more particles.

Other operations are below of 4%.