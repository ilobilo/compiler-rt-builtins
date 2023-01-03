project('compiler-rt-builtins', ['c', 'cpp'], default_options : ['c_std=c11', 'cpp_std=c++17'])

build_type = get_option('buildtype')

build_os = build_machine.system()
target_compiler = meson.get_compiler('cpp')

#########################
# Process Build Options #
#########################

force_32_bit = get_option('force_32_bit')
enable_pedantic_error = get_option('enable_pedantic_error')
enable_werror = get_option('enable_werror')
skip_atomic_builtins = get_option('compiler_rt_exclude_atomic_builtins')

#############################
# Initialize Compiler Flags #
#############################

if meson.is_cross_build()
	target_architecture = host_machine.cpu_family()
	# TODO: parse CPU for ARM -> cortex-m4, etc.
else
	target_architecture = build_machine.cpu_family()
	# CPU not currently needed - x86 or x86_64 handled correctly
endif

message('Building compiler-rt for target architecture: ' + target_architecture)

builtins_compiler_args = [
	'-fno-builtin',
	'-fvisibility=hidden',
	'-fomit-frame-pointer',
	'-ffreestanding',
	# These are to suppress warnings when building compiler_rt with pedantic enabled
	'-Wno-pedantic',
	'-Wno-undef',
	'-Wno-sign-conversion',
	'-Wno-double-promotion',
	'-Wno-float-equal',
	'-Wno-float-conversion',
	'-Wno-conversion',
	'-Wno-missing-noreturn',
	'-Wno-unused-parameter',
	'-Wno-format-nonliteral',
	'-Wno-unused-macros',
]

builtins_target_compiler_args = [
	builtins_compiler_args,
]

if force_32_bit == true
	builtins_target_compiler_args += ['-m32']
endif

###################
# Adjust Warnings #
###################

if target_compiler.has_argument('-Wno-builtin-declaration-mismatch')
	builtins_target_compiler_args += '-Wno-builtin-declaration-mismatch'
endif

if target_compiler.has_argument('-Wno-shift-sign-overflow')
	builtins_target_compiler_args += '-Wno-shift-sign-overflow'
endif

if target_compiler.has_argument('-Wno-shorten-64-to-32')
	builtins_target_compiler_args += '-Wno-shorten-64-to-32'
endif

if target_compiler.has_argument('-Wno-unreachable-code-break')
	builtins_target_compiler_args += '-Wno-unreachable-code-break'
endif

if target_compiler.has_argument('-Wno-conditional-uninitialized')
	builtins_target_compiler_args += '-Wno-conditional-uninitialized'
endif

if target_compiler.has_argument('-Wno-missing-variable-declarations')
	builtins_target_compiler_args += '-Wno-missing-variable-declarations'
endif

if target_compiler.has_argument('-Wno-reserved-id-macro')
	builtins_target_compiler_args += '-Wno-reserved-id-macro'
endif

if target_compiler.has_argument('-Wno-missing-prototypes') and target_compiler.get_id() != 'gcc'
	builtins_target_compiler_args += '-Wno-missing-prototypes'
endif

######################
# Builtin File Lists #
######################

generic_sources = files(
	'builtins/absvdi2.c',
	'builtins/absvsi2.c',
	'builtins/absvti2.c',
	'builtins/adddf3.c',
	'builtins/addsf3.c',
	'builtins/addtf3.c',
	'builtins/addvdi3.c',
	'builtins/addvsi3.c',
	'builtins/addvti3.c',
	'builtins/apple_versioning.c',
	'builtins/ashldi3.c',
	'builtins/ashlti3.c',
	'builtins/ashrdi3.c',
	'builtins/ashrti3.c',
	'builtins/clear_cache.c',
	'builtins/clzti2.c',
	'builtins/cmpdi2.c',
	'builtins/cmpti2.c',
	'builtins/comparedf2.c',
	'builtins/ctzdi2.c',
	'builtins/ctzsi2.c',
	'builtins/ctzti2.c',
	'builtins/divdc3.c',
	'builtins/divdf3.c',
	'builtins/divdi3.c',
	'builtins/divmoddi4.c',
	'builtins/divsc3.c',
	'builtins/divsf3.c',
	'builtins/divtc3.c',
	'builtins/divti3.c',
	'builtins/divtf3.c',
	'builtins/extendsfdf2.c',
	'builtins/extendhfsf2.c',
	'builtins/ffsdi2.c',
	'builtins/ffssi2.c',
	'builtins/ffsti2.c',
	'builtins/fixdfdi.c',
	'builtins/fixdfsi.c',
	'builtins/fixdfti.c',
	'builtins/fixsfdi.c',
	'builtins/fixsfsi.c',
	'builtins/fixsfti.c',
	'builtins/fixunsdfdi.c',
	'builtins/fixunsdfsi.c',
	'builtins/fixunsdfti.c',
	'builtins/fixunssfdi.c',
	'builtins/fixunssfsi.c',
	'builtins/fixunssfti.c',
	'builtins/floatsidf.c',
	'builtins/floatsisf.c',
	'builtins/floattidf.c',
	'builtins/floattisf.c',
	'builtins/floatunsidf.c',
	'builtins/floatunsisf.c',
	'builtins/floatuntidf.c',
	'builtins/floatuntisf.c',
	'builtins/int_util.c',
	'builtins/lshrdi3.c',
	'builtins/lshrti3.c',
	'builtins/moddi3.c',
	'builtins/modti3.c',
	'builtins/muldc3.c',
	'builtins/muldf3.c',
	'builtins/muldi3.c',
	'builtins/mulodi4.c',
	'builtins/mulosi4.c',
	'builtins/muloti4.c',
	'builtins/mulsc3.c',
	'builtins/mulsf3.c',
	'builtins/multi3.c',
	'builtins/multf3.c',
	'builtins/mulvdi3.c',
	'builtins/mulvsi3.c',
	'builtins/mulvti3.c',
	'builtins/negdf2.c',
	'builtins/negdi2.c',
	'builtins/negsf2.c',
	'builtins/negti2.c',
	'builtins/negvdi2.c',
	'builtins/negvsi2.c',
	'builtins/negvti2.c',
	# This file is used by Obj-C and won't build without clang
	#'builtins/os_version_check.c',
	'builtins/paritydi2.c',
	'builtins/paritysi2.c',
	'builtins/parityti2.c',
	'builtins/popcountdi2.c',
	'builtins/popcountsi2.c',
	'builtins/popcountti2.c',
	'builtins/powidf2.c',
	'builtins/powisf2.c',
	'builtins/powitf2.c',
	'builtins/subdf3.c',
	'builtins/subsf3.c',
	'builtins/subvdi3.c',
	'builtins/subvsi3.c',
	'builtins/subvti3.c',
	'builtins/subtf3.c',
	'builtins/trampoline_setup.c',
	'builtins/truncdfhf2.c',
	'builtins/truncdfsf2.c',
	'builtins/truncsfhf2.c',
	'builtins/ucmpdi2.c',
	'builtins/ucmpti2.c',
	'builtins/udivdi3.c',
	'builtins/udivmoddi4.c',
	'builtins/udivmodti4.c',
	'builtins/udivti3.c',
	'builtins/umoddi3.c',
	'builtins/umodti3.c',
)

generic_nonarm_sources = files(
	'builtins/bswapdi2.c',
	'builtins/bswapsi2.c',
	'builtins/clzdi2.c',
	'builtins/clzsi2.c',
	'builtins/comparesf2.c',
	'builtins/divmodsi4.c',
	'builtins/divsi3.c',
	'builtins/modsi3.c',
	'builtins/udivmodsi4.c',
	'builtins/udivsi3.c',
	'builtins/umodsi3.c',
)

generic_nonx86_64_sources = files(
	'builtins/floatdidf.c',
	'builtins/floatdisf.c',
	'builtins/floatundidf.c',
	'builtins/floatundisf.c',
)

generic_tf_sources = files(
	'builtins/comparetf2.c',
	'builtins/extenddftf2.c',
	'builtins/extendsftf2.c',
	'builtins/fixtfdi.c',
	'builtins/fixtfsi.c',
	'builtins/fixtfti.c',
	'builtins/fixunstfdi.c',
	'builtins/fixunstfsi.c',
	'builtins/fixunstfti.c',
	'builtins/floatditf.c',
	'builtins/floatsitf.c',
	'builtins/floattitf.c',
	'builtins/floatunditf.c',
	'builtins/floatunsitf.c',
	'builtins/floatuntitf.c',
	'builtins/multc3.c',
	'builtins/trunctfdf2.c',
	'builtins/trunctfsf2.c',
)

nonbaremetal_files = files(
	'builtins/emutls.c',
	'builtins/enable_execute_stack.c',
	'builtins/eprintf.c',
)

x86_files = files(
	'builtins/cpu_model.c',
	'builtins/divxc3.c',
	'builtins/fixxfdi.c',
	'builtins/fixxfti.c',
	'builtins/fixunsxfdi.c',
	'builtins/fixunsxfsi.c',
	'builtins/fixunsxfti.c',
	'builtins/floatdixf.c',
	'builtins/floattixf.c',
	'builtins/floatundixf.c',
	'builtins/floatuntixf.c',
	'builtins/mulxc3.c',
	'builtins/powixf2.c',
)

x86_64_files = files(
	'builtins/x86_64/floatdidf.c',
	'builtins/x86_64/floatdisf.c',
	'builtins/x86_64/floatdixf.c',
	'builtins/x86_64/floatundidf.S',
	'builtins/x86_64/floatundisf.S',
	'builtins/x86_64/floatundixf.S',
)

aarch64_files = files(
	'builtins/cpu_model.c',
	'builtins/aarch64/fp_mode.c'
)

arm_files = files(
	'builtins/arm/fp_mode.c',
	'builtins/arm/bswapdi2.S',
	'builtins/arm/bswapsi2.S',
	'builtins/arm/clzdi2.S',
	'builtins/arm/clzsi2.S',
	'builtins/arm/comparesf2.S',
	'builtins/arm/divmodsi4.S',
	'builtins/arm/divsi3.S',
	'builtins/arm/modsi3.S',
	'builtins/arm/sync_fetch_and_add_4.S',
	'builtins/arm/sync_fetch_and_add_8.S',
	'builtins/arm/sync_fetch_and_and_4.S',
	'builtins/arm/sync_fetch_and_and_8.S',
	'builtins/arm/sync_fetch_and_max_4.S',
	'builtins/arm/sync_fetch_and_max_8.S',
	'builtins/arm/sync_fetch_and_min_4.S',
	'builtins/arm/sync_fetch_and_min_8.S',
	'builtins/arm/sync_fetch_and_nand_4.S',
	'builtins/arm/sync_fetch_and_nand_8.S',
	'builtins/arm/sync_fetch_and_or_4.S',
	'builtins/arm/sync_fetch_and_or_8.S',
	'builtins/arm/sync_fetch_and_sub_4.S',
	'builtins/arm/sync_fetch_and_sub_8.S',
	'builtins/arm/sync_fetch_and_umax_4.S',
	'builtins/arm/sync_fetch_and_umax_8.S',
	'builtins/arm/sync_fetch_and_umin_4.S',
	'builtins/arm/sync_fetch_and_umin_8.S',
	'builtins/arm/sync_fetch_and_xor_4.S',
	'builtins/arm/sync_fetch_and_xor_8.S',
	'builtins/arm/udivmodsi4.S',
	'builtins/arm/udivsi3.S',
	'builtins/arm/umodsi3.S',
)

arm_thumb1_files = files(
	'builtins/arm/addsf3.S',
	'builtins/arm/divsi3.S',
	'builtins/arm/udivsi3.S',
	'builtins/arm/comparesf2.S',
	# Thumb1_JT
	'builtins/arm/switch16.S',
	'builtins/arm/switch32.S',
	'builtins/arm/switch8.S',
	'builtins/arm/switchu8.S',
	# Thumb1 ICache Sources
	'builtins/arm/sync_synchronize.S',
)

arm_vfp2_common_files = files(
	# SjLj EH Sources
	'builtins/arm/restore_vfp_d8_d15_regs.S',
	'builtins/arm/save_vfp_d8_d15_regs.S',
	# Thumb1_VFPv2_sources
	'builtins/arm/addsf3vfp.S',
	'builtins/arm/divsf3vfp.S',
	'builtins/arm/eqdf2vfp.S',
	'builtins/arm/eqsf2vfp.S',
	'builtins/arm/fixsfsivfp.S',
	'builtins/arm/fixunssfsivfp.S',
	'builtins/arm/floatsisfvfp.S',
	'builtins/arm/floatunssisfvfp.S',
	'builtins/arm/gedf2vfp.S',
	'builtins/arm/gesf2vfp.S',
	'builtins/arm/gtdf2vfp.S',
	'builtins/arm/gtsf2vfp.S',
	'builtins/arm/ledf2vfp.S',
	'builtins/arm/lesf2vfp.S',
	'builtins/arm/ltdf2vfp.S',
	'builtins/arm/ltsf2vfp.S',
	'builtins/arm/mulsf3vfp.S',
	'builtins/arm/nedf2vfp.S',
	'builtins/arm/negdf2vfp.S',
	'builtins/arm/negsf2vfp.S',
	'builtins/arm/nesf2vfp.S',
	'builtins/arm/subsf3vfp.S',
	'builtins/arm/unorddf2vfp.S',
	'builtins/arm/unordsf2vfp.S',
)

arm_vfp_double_precision_files = files(
	'builtins/arm/adddf3vfp.S',
	'builtins/arm/divdf3vfp.S',
	'builtins/arm/extendsfdf2vfp.S',
	'builtins/arm/fixdfsivfp.S',
	'builtins/arm/fixunsdfsivfp.S',
	'builtins/arm/floatunssidfvfp.S',
	'builtins/arm/floatsidfvfp.S',
	'builtins/arm/muldf3vfp.S',
	'builtins/arm/subdf3vfp.S',
	'builtins/arm/truncdfsf2vfp.S',
)

arm_eabi_files = files(
	'builtins/arm/aeabi_cdcmp.S',
	'builtins/arm/aeabi_cdcmpeq_check_nan.c',
	'builtins/arm/aeabi_cfcmp.S',
	'builtins/arm/aeabi_cfcmpeq_check_nan.c',
	'builtins/arm/aeabi_dcmp.S',
	'builtins/arm/aeabi_div0.c',
	'builtins/arm/aeabi_drsub.c',
	'builtins/arm/aeabi_fcmp.S',
	'builtins/arm/aeabi_frsub.c',
	'builtins/arm/aeabi_idivmod.S',
	'builtins/arm/aeabi_ldivmod.S',
	'builtins/arm/aeabi_memcmp.S',
	'builtins/arm/aeabi_memcpy.S',
	'builtins/arm/aeabi_memmove.S',
	'builtins/arm/aeabi_memset.S',
	'builtins/arm/aeabi_uidivmod.S',
	'builtins/arm/aeabi_uldivmod.S',
)

arm_file_group = [
	arm_files,
	arm_eabi_files,
	arm_thumb1_files,
]

thumb1_file_group = [
	arm_eabi_files,
	arm_thumb1_files,
]

atomic_files = files(
	'builtins/atomic.c'
)

apple_atomic_files = files(
	'builtins/atomic_flag_clear.c',
	'builtins/atomic_flag_clear_explicit.c',
	'builtins/atomic_flag_test_and_set.c',
	'builtins/atomic_flag_test_and_set_explicit.c',
	'builtins/atomic_signal_fence.c',
	'builtins/atomic_thread_fence.c',
)

gcc_unwind_files = files(
	'builtins/gcc_personality_v0.c',
)

compiler_rt_target_files = [
	generic_sources,
]

################################
# Select Files by Architecture #
################################

if meson.is_cross_build() == false
	compiler_rt_target_files += nonbaremetal_files

	if host_machine.system() == 'darwin' and target_compiler.get_id() != 'gcc'
		compiler_rt_target_files += apple_atomic_files
	endif
endif

if not skip_atomic_builtins
	compiler_rt_target_files += atomic_files
endif

if target_architecture == 'arm'
	compiler_rt_target_files += [
		arm_file_group,
		generic_nonx86_64_sources
	]

	arm_fp_setting = target_compiler.get_define('__ARM_FP')
	arm_version = target_compiler.get_define('__ARM_ARCH')

	# Single precision (aka 32 bit support) is true when bit 2 is set (0bx1xx)
	if arm_fp_setting == '4' or arm_fp_setting == '12' or arm_fp_setting == '14'
		message('Enabling single-precision ARM VFP Builtins')
		if(arm_version.to_int() < 7)
			# VFPv2 files are only needed for ARMv5 and ARMv6
			compiler_rt_target_files += arm_vfp2_common_files
		endif
	endif

	# Double precision (aka 64 bit support) is true when bit 3 is set (0b1xxx)
	if arm_fp_setting == '8' or arm_fp_setting == '12' or arm_fp_setting == '14'
		message('Enabling double-precision ARM VFP Builtins')
		compiler_rt_target_files + arm_vfp_double_precision_files
	endif

elif target_architecture == 'aarch64' or target_architecture == 'arm64'
	compiler_rt_target_files += [
		aarch64_files,
		generic_tf_sources,
		generic_nonx86_64_sources,
		generic_nonarm_sources
	]
elif target_architecture == 'x86'
	compiler_rt_target_files += [
		x86_files,
		generic_nonx86_64_sources,
		generic_nonarm_sources
	]
elif target_architecture == 'x86_64'
	compiler_rt_target_files += [
		x86_files,
		x86_64_files,
		generic_nonarm_sources
	]
else
	assert(0, 'Unsupported architecture: ' + target_architecture)
endif

##############
# Dependency #
##############

args = [builtins_target_compiler_args, '-D__ELF__']

compiler_rt_builtins_lib = static_library('compiler_rt_builtins',
    sources : compiler_rt_target_files,
    include_directories : 'include',
	c_args : args,
	cpp_args : args
)

compiler_rt_builtins_dep = declare_dependency(link_with : compiler_rt_builtins_lib)

# To use your own assert.h for cpu_model.c
compiler_rt_builtins_src_dep = declare_dependency(sources : compiler_rt_target_files, compile_args : args)

if meson.version().version_compare('>=0.54.0')
    meson.override_dependency('compiler_rt_builtins', compiler_rt_builtins_dep)
    meson.override_dependency('compiler_rt_builtins_src', compiler_rt_builtins_src_dep)
endif