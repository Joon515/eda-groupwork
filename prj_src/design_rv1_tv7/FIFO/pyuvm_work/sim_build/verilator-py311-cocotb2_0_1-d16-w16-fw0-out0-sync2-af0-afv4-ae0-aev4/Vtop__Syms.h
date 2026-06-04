// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTOP__SYMS_H_
#define VERILATED_VTOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtop.h"

// INCLUDE MODULE CLASSES
#include "Vtop___024root.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtop__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtop* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtop___024root                 TOP;

    // SCOPE NAMES
    VerilatedScope* __Vscopep_TOP;
    VerilatedScope* __Vscopep_async_fifo_top;
    VerilatedScope* __Vscopep_async_fifo_top__u_dual_port_ram;
    VerilatedScope* __Vscopep_async_fifo_top__u_read_pointer;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_r2w;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk1;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk2;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_w2r;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk1;
    VerilatedScope* __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk2;
    VerilatedScope* __Vscopep_async_fifo_top__u_write_pointer;

    // SCOPE HIERARCHY
    VerilatedHierarchy __Vhier;

    // CONSTRUCTORS
    Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp);
    ~Vtop__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
