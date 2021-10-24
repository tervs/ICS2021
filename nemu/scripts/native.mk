include $(NEMU_HOME)/scripts/git.mk
include $(NEMU_HOME)/scripts/build.mk
include $(NEMU_HOME)/tools/difftest.mk




compile_git:
	$(call git_commit, "compile")
$(BINARY): compile_git

export MPATH=/home/yu/ics2021/am-kernels/tests/cpu-tests/build##
#ALL = $(basename $(notdir $(shell find $(MPATH)/. -name "*-mtrace.txt")))##
#@$(shell touch $(CDPATH)/log-mtrace.txt)


# Some convenient rules


override ARGS ?= --log=$(BUILD_DIR)/nemu-log.txt
override ARGS += $(ARGS_DIFF)
override MTRACE =  --mtrace=$(MPATH)/nemu-log-mtrace.txt
#$(info new $(TEST))


# Command to execute NEMU
IMG ?=
NEMU_EXEC := $(BINARY) $(ARGS) $(MTRACE) $(IMG)

genmtrace:
	@$(shell if [ ! -e $(CDPATH)/nemu-log-mtrace.txt ];then touch $(CDPATH)/nemu-log-mtrace.txt; fi)

run-env: $(BINARY) $(DIFF_REF_SO)

run: run-env
		$(call genmtrace,"run")
		$(call git_commit, "run")
		$(NEMU_EXEC)

gdb: run-env
	$(call git_commit, "gdb")
	gdb -s $(BINARY) --args $(NEMU_EXEC)

clean-tools = $(dir $(shell find ./tools -name "Makefile"))
$(clean-tools):
	-@$(MAKE) -s -C $@ clean
clean-tools: $(clean-tools)
clean-all: clean distclean clean-tools


.PHONY: run gdb run-env clean-tools clean-all $(clean-tools) genmtrace
