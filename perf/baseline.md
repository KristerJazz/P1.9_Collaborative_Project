# Report of performace: Baseline

This file includes the profiling results of the project. 

|    Function        | Argon 108 | Argon 2916 |
|--------------------|-----------|------------|
| force()            | 72,68%    | |
| pbc()              | 20,12%    | |
| pbc@plt            | 4,91%     | |
| propagate_velocity | 1,23%     | |

The other functions are below 1%.

## Hotspots

### `force()`

* Sqrt operation: 18,48%
* Div operation: 11,07%
* `pbc@plt `: it is the unconditional jump to pbc

Other operations are below of 4%.

### `pbc()`

* Conditional jump: 12,72%
* SIMD memory MOV (SSE2): 11,80%
* Addition: 11,85%
* Compare floats (SSE2): 12,75%

Other operations are below of 4%.
 
### `propagate_velocity`

* Divisions: 78,88%

Other operations are below of 4%.