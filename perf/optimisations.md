# Report of performace: Baseline

This file includes the profiling results of the project. 

**Argon 108**

|    Function        | Opt-{1}   | Opt-{1,2} | Opt-{1,2,3} | No Optimised |
|--------------------|-----------|-----------|-------------|--------------|
| force()            | 62,74%    | 97,06%    | 93,53%      | 72,68%       |
| pbc()              | 28,64%    | --,--%    | --,--%      | 20,12%       |
| pbc@plt            | 6,09%     | --,--%    | --,--%      | 4,91%        |
| propagate_velocity | 1,55%     | 1,73%     | 3,83%%      | 1,23%        |

* `Opt-1`: Pure math optimisations
* `Opt-2`: Function inlining (`pbc`)
* `Opt-3`: Newton's third law

The other functions are below 1%.

For **Argon 2916**

Force(): 98,02%

## Walltime 

**Argon 108**

|    Function        | Opt-{1}     | Opt-{1,2}    | Opt-{1,2,3}  | No Optimised |
|--------------------|-------------|--------------|--------------|--------------|
| walltime           | 4,995590517 | 4,325905976  | 2,285692580  | 6,407873303  |

Speedup: 2.803

**Argon 2916**

|    Function        | Opt-{1,2,3}  | No Optimised |
|--------------------|--------------|--------------|
| walltime           | 88,83126558  | 296,5620224  |

Speedup: 3.338

> Time measured in seconds

## Hotspots

### `force()`

**Argon 108**

|    Function        | Opt-{1}   | Opt-{1,2} | Opt-{1,2,3} | No Optimised |
|--------------------|-----------|-----------|-------------|--------------|
| div()              | 13,90%    | 9,74%     | 10,46%      | 11,07%       |
| move()             | 11,04% (a)| < 4%      | < 4%        | < 4%         |

> There are a lot of multiplications which can be considered as
potential hotspots (Opt-{1,2})

> (a): accumulative

Other operations are below of 4%.

**Argon 2916**

The arithmetic operation became important:

* `subsd()`: 5,17% in `sys->rx[i] - sys->rx[j]`
* `addsd()`: 6,20% in `double rsq = POW2(rx) + POW2(ry) + POW2(rz);`
* `comisd`: 8,60% in `rsq < rcsq`

The inlined version of `pbc` introduces a `nop` within the while.

### `pbc()`

|    Function        | Opt-{1}   | No Opt    |
|--------------------|-----------|-----------|
| jump               | 10,55%    | 12,72%    |
| movapd             | 13,15%    | 11,80%    |
| add                | 14,55%    | 11,85%    |
| comisd             | 10,63%    | 12,75%    |
| repz               | --,--%    | --,--%    |

* Conditional jump: 12,72%
* SIMD memory MOV (SSE2): 11,80%
* Addition: 11,85%
* Compare floats (SSE2): 12,75%
* Repeat while zero: repz

Other operations are below of 4%.
 