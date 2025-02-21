// Copyright (c) Microsoft Corporation
// SPDX-License-Identifier: MIT

// clang -O2 -Werror -c divide_by_zero.c -o divide_by_zero_jit.o
//
// For bpf code: clang -target bpf -O2 -Werror -c divide_by_zero.c -o divide_by_zero.o
// this passes the checker

#include "bpf_helpers.h"

SEC("maps")
struct bpf_map_def test_map = {
    .type = BPF_MAP_TYPE_ARRAY, .key_size = sizeof(uint32_t), .value_size = sizeof(uint32_t), .max_entries = 1};

SEC("xdp")
uint32_t
divide_by_zero(xdp_md_t* ctx)
{
    uint32_t key = 0;
    uint32_t* value = bpf_map_lookup_elem(&test_map, &key);
    if (value) {
        return 100000 / *value;
    }
    return 0;
}
