# -*- Makefile -*-
include ../Rules.mk

LD_LIBRARY_PATH=$(LIB_PATH)
export LD_LIBRARY_PATH

PERF_SAMPLE=argon_108.inp
PYTHON_EXE=$(ROOT_DIR)/ljmd.py

default: check

clean:
	rm -f *.xyz *.dat $(PERF_PATH)/*.data $(PERF_RESULT) $(PERF_PATH)/perfstat.txt

check: check_python

check_python: $(PYTHON_EXE) $(wildcard ../tests/python_tests/*.py)
	$(MAKE) -C $(LIB_PATH) clean
	$(MAKE) -C $(ROOT_DIR) 
	$(EXECUTER) $(NUM_PROC) python3 $(PYTHON_EXE) argon_108.inp
	head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> a.dat
	head -10 $(REFERENCE_PATH)/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> b.dat
	cmp a.dat b.dat || exit 1
	rm -f a.dat b.dat
	$(EXECUTER) $(NUM_PROC) python3 $(PYTHON_EXE) argon_2916.inp
	head -10 argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> a.dat
	head -10 $(REFERENCE_PATH)/argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> b.dat
	cmp a.dat b.dat || exit 1
	rm -f a.dat b.dat
	$(MAKE) -C $(LIB_PATH) clean

check_exe: $(EXE)
	$(MAKE) -C $(LIB_PATH) clean
	$(MAKE) -C $(ROOT_DIR)
	$(EXECUTER) $(NUM_PROC) $(EXE) < argon_108.inp
	head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> a.dat
	head -10 $(REFERENCE_PATH)/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> b.dat
	cmp a.dat b.dat || exit 1
	rm -f a.dat b.dat
	$(EXECUTER) $(NUM_PROC) $(EXE) < argon_2916.inp
	head -10 argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> a.dat
	head -10 $(REFERENCE_PATH)/argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> b.dat
	cmp a.dat b.dat || exit 1
	rm -f a.dat b.dat
	$(MAKE) -C $(LIB_PATH) clean

check_morse: $(EXE)
	$(MAKE) -C $(LIB_PATH) clean
	$(MAKE) -C $(ROOT_DIR) WITH_MORSE=1
	$(EXECUTER) $(NUM_PROC) $(EXE) < argon_108.inp
	head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> a.dat
	head -10 $(REFERENCE_PATH)/morse/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> b.dat
	cmp a.dat b.dat || exit 1
	rm -f a.dat b.dat
	$(EXECUTER) $(NUM_PROC) $(EXE) < argon_2916.inp
	head -10 argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> a.dat
	head -10 $(REFERENCE_PATH)/morse/argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> b.dat
	cmp a.dat b.dat || exit 1
	rm -f a.dat b.dat
	$(MAKE) -C $(LIB_PATH) clean

perf: $(EXE) $(PERF_RESULT)

$(PERF): $(EXE)
	perf record -o $(PERF) -T -B $(EXE) < $(PERF_SAMPLE)
	perf stat -o $(PERF_PATH)/perfstat.txt $(EXE) < $(PERF_SAMPLE) 

$(PERF_RESULT): $(PERF)
	perf report -i $(PERF)
