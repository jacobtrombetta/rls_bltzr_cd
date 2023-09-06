# multiexp [mtx]

## base [mtxb]
### digit_utility
### exponent_sequence_utility
### exponent_sequence
### generator_utility

## bitset_multiprod [mtxbmp]
### multiproduct
### test_operator
### value_cache_utility
### value_cache

## curve [mtxcrv]
The components inside the curve package are a generic implementation of multi-scalar multiplication/exponentiation that can be used on different curves.
### doubling_reduction
### multiexponentiation_cpu_driver
### multiproduct_bitset_operator
### multiproduct_solver
Base class where all the solvers inherit their interfaces from.
### multiproducts_combination
### naive_multiproduct_solver
Used for testing in the `multiexponentition_cpu_driver` component.

## curve21 [mtxc21]
The components inside the curve21 package are an implementation of multi-scalar multiplication/exponentiation that can be used on `curve25519`.
### multiexponentiation
### multiproduct_cpu_driver
### multiproduct_solver
### multiproduct
### pippenger_multiproduct_solver

## index
### clump2_descriptor_utility
### clump2_descriptor
### clump2_marker_utility
### index_table_utility
### index_table
### marker_transformation
### partition_marker_utility
### random_clump2
### reindex
### transpose

## multiproduct_gpu
### block_computation_descriptor
### completion
### computation_setup
### kernel
### multiproduct_computation_description
### multiproduct

## pippenger
### driver
### exponent_aggregates_computation
### exponent_aggregates
### multiexponentiation
### multiproduct_decomposition_gpu
### multiproduct_decomposition_kernel
### multiproduct_table
### test_driver

## pippenger_multiprod
### active_count
### active_offset
### clump_inputs
### clump_outputs
### driver
### multiproduct_params_computation
### multiproduct_params
### multiproduct
### partition_inputs
### product_table_normalization
### prune
### reduction_stats
### test_driver

## random [mtxrn]
The components inside the random package help generate random inputs, exponents, and products for testing multi-scalar multiplication/exponentiation.
### int_generation
Generates a span of uniformily distributed `uint64` values.
### random_multiexponentiation_descriptor
Description of exponent parameters used by the `random_multiexponentiation_generation` component.
### random_multiexponentiation_generation
Generates random inputs and exponents used to test multiexponentiation algorithm.
### random_multiproduct_descriptor
Description of product parameters used by `random_multiproduct_generation` component.
### random_multiproduct_generation
Generates a random index table of products used to test multiproduct algorithm.

## test [mtxtst]
The components inside the test package help with testing multi-scalar multiplication/exponentiation.
### add_ints
### compute_uint64_muladd
### curve21_arithmetic
### multiexponentiation
