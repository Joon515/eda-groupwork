// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(274);
    // Setup sub module instances
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscopep_TOP = new VerilatedScope{this, "TOP", "TOP", "<null>", 0, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top = new VerilatedScope{this, "async_fifo_top", "async_fifo_top", "async_fifo_top", -9, VerilatedScope::SCOPE_MODULE};
    __Vscopep_async_fifo_top__g_std_reg_mode = new VerilatedScope{this, "async_fifo_top.g_std_reg_mode", "g_std_reg_mode", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top__u_dual_port_ram = new VerilatedScope{this, "async_fifo_top.u_dual_port_ram", "u_dual_port_ram", "dual_port_ram", -9, VerilatedScope::SCOPE_MODULE};
    __Vscopep_async_fifo_top__u_read_pointer = new VerilatedScope{this, "async_fifo_top.u_read_pointer", "u_read_pointer", "rptr", -9, VerilatedScope::SCOPE_MODULE};
    __Vscopep_async_fifo_top__u_sync_r2w = new VerilatedScope{this, "async_fifo_top.u_sync_r2w", "u_sync_r2w", "sync_gray", -9, VerilatedScope::SCOPE_MODULE};
    __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst = new VerilatedScope{this, "async_fifo_top.u_sync_r2w.g_async_rst", "g_async_rst", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk1 = new VerilatedScope{this, "async_fifo_top.u_sync_r2w.g_async_rst.unnamedblk1", "unnamedblk1", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk2 = new VerilatedScope{this, "async_fifo_top.u_sync_r2w.g_async_rst.unnamedblk2", "unnamedblk2", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top__u_sync_w2r = new VerilatedScope{this, "async_fifo_top.u_sync_w2r", "u_sync_w2r", "sync_gray", -9, VerilatedScope::SCOPE_MODULE};
    __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst = new VerilatedScope{this, "async_fifo_top.u_sync_w2r.g_async_rst", "g_async_rst", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk1 = new VerilatedScope{this, "async_fifo_top.u_sync_w2r.g_async_rst.unnamedblk1", "unnamedblk1", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk2 = new VerilatedScope{this, "async_fifo_top.u_sync_w2r.g_async_rst.unnamedblk2", "unnamedblk2", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_async_fifo_top__u_write_pointer = new VerilatedScope{this, "async_fifo_top.u_write_pointer", "u_write_pointer", "wptr", -9, VerilatedScope::SCOPE_MODULE};
    // Set up scope hierarchy
    __Vhier.add(0, __Vscopep_async_fifo_top);
    __Vhier.add(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__g_std_reg_mode);
    __Vhier.add(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_dual_port_ram);
    __Vhier.add(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_read_pointer);
    __Vhier.add(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_sync_r2w);
    __Vhier.add(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_sync_w2r);
    __Vhier.add(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_write_pointer);
    __Vhier.add(__Vscopep_async_fifo_top__u_sync_r2w, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst);
    __Vhier.add(__Vscopep_async_fifo_top__u_sync_r2w__g_async_rst, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk1);
    __Vhier.add(__Vscopep_async_fifo_top__u_sync_r2w__g_async_rst, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk2);
    __Vhier.add(__Vscopep_async_fifo_top__u_sync_w2r, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst);
    __Vhier.add(__Vscopep_async_fifo_top__u_sync_w2r__g_async_rst, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk1);
    __Vhier.add(__Vscopep_async_fifo_top__u_sync_w2r__g_async_rst, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk2);
    // Setup export functions - final: 0
    // Setup export functions - final: 1
    // Setup public variables
    __Vscopep_TOP->varInsert("ralmost_empty", &(TOP.ralmost_empty), false, VLVT_UINT8, VLVD_OUT|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("rclk", &(TOP.rclk), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("rdata", &(TOP.rdata), false, VLVT_UINT16, VLVD_OUT|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,15,0);
    __Vscopep_TOP->varInsert("rempty", &(TOP.rempty), false, VLVT_UINT8, VLVD_OUT|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_TOP->varInsert("rinc", &(TOP.rinc), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("rrst", &(TOP.rrst), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("walmost_full", &(TOP.walmost_full), false, VLVT_UINT8, VLVD_OUT|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("wclk", &(TOP.wclk), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("wdata", &(TOP.wdata), false, VLVT_UINT16, VLVD_IN|VLVF_PUB_RW, 0, 1 ,15,0);
    __Vscopep_TOP->varInsert("wfull", &(TOP.wfull), false, VLVT_UINT8, VLVD_OUT|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("winc", &(TOP.winc), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("wrst", &(TOP.wrst), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("ADDR_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__ADDR_WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("ALMOST_EMPTY_EN", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__ALMOST_EMPTY_EN))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_BITVAR, 0, 0);
    __Vscopep_async_fifo_top->varInsert("ALMOST_EMPTY_VAL", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__ALMOST_EMPTY_VAL))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("ALMOST_FULL_EN", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__ALMOST_FULL_EN))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_BITVAR, 0, 0);
    __Vscopep_async_fifo_top->varInsert("ALMOST_FULL_VAL", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__ALMOST_FULL_VAL))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("DEPTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__DEPTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("FWFT_EN", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__FWFT_EN))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_BITVAR, 0, 0);
    __Vscopep_async_fifo_top->varInsert("MEM_DEPTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__MEM_DEPTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("OUT_REG_EN", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__OUT_REG_EN))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_BITVAR, 0, 0);
    __Vscopep_async_fifo_top->varInsert("PTR_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__PTR_WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("RST_POLARITY", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__RST_POLARITY))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("RST_TYPE", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__RST_TYPE))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,1,0);
    __Vscopep_async_fifo_top->varInsert("SYNC_STAGES", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__SYNC_STAGES))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top->varInsert("raddr", &(TOP.async_fifo_top__DOT__raddr), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,3,0);
    __Vscopep_async_fifo_top->varInsert("ralmost_empty", &(TOP.async_fifo_top__DOT__ralmost_empty), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("ram_rdata", &(TOP.async_fifo_top__DOT__ram_rdata), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,15,0);
    __Vscopep_async_fifo_top->varInsert("rclk", &(TOP.async_fifo_top__DOT__rclk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("rdata", &(TOP.async_fifo_top__DOT__rdata), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,15,0);
    __Vscopep_async_fifo_top->varInsert("rempty", &(TOP.async_fifo_top__DOT__rempty), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top->varInsert("rempty_raw", &(TOP.async_fifo_top__DOT__rempty_raw), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("rinc", &(TOP.async_fifo_top__DOT__rinc), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("rinc_internal", &(TOP.async_fifo_top__DOT__rinc_internal), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top->varInsert("rptr_gray", &(TOP.async_fifo_top__DOT__rptr_gray), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top->varInsert("rptr_gray_sync_w2", &(TOP.async_fifo_top__DOT__rptr_gray_sync_w2), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top->varInsert("rrst", &(TOP.async_fifo_top__DOT__rrst), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("rrst_internal", &(TOP.async_fifo_top__DOT__rrst_internal), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top->varInsert("rst_cond_r", &(TOP.async_fifo_top__DOT__rst_cond_r), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top->varInsert("waddr", &(TOP.async_fifo_top__DOT__waddr), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,3,0);
    __Vscopep_async_fifo_top->varInsert("walmost_full", &(TOP.async_fifo_top__DOT__walmost_full), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("wclk", &(TOP.async_fifo_top__DOT__wclk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("wdata", &(TOP.async_fifo_top__DOT__wdata), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,15,0);
    __Vscopep_async_fifo_top->varInsert("wfull", &(TOP.async_fifo_top__DOT__wfull), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("winc", &(TOP.async_fifo_top__DOT__winc), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("wptr_gray", &(TOP.async_fifo_top__DOT__wptr_gray), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top->varInsert("wptr_gray_sync_r2", &(TOP.async_fifo_top__DOT__wptr_gray_sync_r2), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top->varInsert("wrst", &(TOP.async_fifo_top__DOT__wrst), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top->varInsert("wrst_internal", &(TOP.async_fifo_top__DOT__wrst_internal), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__g_std_reg_mode->varInsert("rdata_stage1", &(TOP.async_fifo_top__DOT__g_std_reg_mode__DOT__rdata_stage1), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,15,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("DEPTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__DEPTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("mem", &(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__mem), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RW, 1, 1 ,0,15 ,15,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("raddr", &(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,3,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("rdata", &(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,15,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("waddr", &(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__waddr), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,3,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("wclk", &(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__wclk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("wdata", &(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__wdata), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,15,0);
    __Vscopep_async_fifo_top__u_dual_port_ram->varInsert("winc", &(TOP.async_fifo_top__DOT__u_dual_port_ram__DOT__winc), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("ADDR_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_read_pointer__DOT__ADDR_WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("ALMOST_EMPTY_EN", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_read_pointer__DOT__ALMOST_EMPTY_EN))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_BITVAR, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("ALMOST_EMPTY_VAL", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_read_pointer__DOT__ALMOST_EMPTY_VAL))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("FWFT_EN", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_read_pointer__DOT__FWFT_EN))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_BITVAR, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("PTR_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_read_pointer__DOT__PTR_WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("RST_POLARITY", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_read_pointer__DOT__RST_POLARITY))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("RST_TYPE", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_read_pointer__DOT__RST_TYPE))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,1,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("raddr", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__raddr), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,3,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("ralmost_empty", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__ralmost_empty), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rbin", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rbin), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rbin_next", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rclk", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rclk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rempty", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rempty), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rempty_val", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rempty_val), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rgray", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rgray), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rgray_next", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rinc", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rinc), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rrst", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rrst), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("rst_cond", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_read_pointer->varInsert("wgray_sync", &(TOP.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("RST_POLARITY", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__RST_POLARITY))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("RST_TYPE", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__RST_TYPE))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,1,0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("STAGES", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__STAGES))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("clk", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__clk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("din", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__din), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("dout", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__dout), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("rst", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__rst), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("rst_cond", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_sync_r2w->varInsert("sync_reg", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 1, 1 ,1,0 ,4,0);
    __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk1->varInsert("i", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk2->varInsert("i", &(TOP.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("RST_POLARITY", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__RST_POLARITY))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("RST_TYPE", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__RST_TYPE))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,1,0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("STAGES", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__STAGES))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("clk", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__clk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("din", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__din), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("dout", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__dout), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("rst", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__rst), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("rst_cond", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_sync_w2r->varInsert("sync_reg", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 1, 1 ,1,0 ,4,0);
    __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk1->varInsert("i", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk2->varInsert("i", &(TOP.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("ADDR_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_write_pointer__DOT__ADDR_WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("ALMOST_FULL_EN", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_write_pointer__DOT__ALMOST_FULL_EN))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_BITVAR, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("ALMOST_FULL_VAL", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_write_pointer__DOT__ALMOST_FULL_VAL))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("DEPTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_write_pointer__DOT__DEPTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("PTR_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_write_pointer__DOT__PTR_WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("RST_POLARITY", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_write_pointer__DOT__RST_POLARITY))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("RST_TYPE", const_cast<void*>(static_cast<const void*>(&(TOP.async_fifo_top__DOT__u_write_pointer__DOT__RST_TYPE))), true, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,1,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("rgray_sync", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("rst_cond", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("waddr", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__waddr), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,3,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("walmost_full", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__walmost_full), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wbin", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wbin), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wbin_next", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wclk", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wclk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wfull", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wfull), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wfull_val", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wfull_val), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wgray", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wgray), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wgray_next", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 1 ,4,0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("winc", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__winc), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_async_fifo_top__u_write_pointer->varInsert("wrst", &(TOP.async_fifo_top__DOT__u_write_pointer__DOT__wrst), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
}

Vtop__Syms::~Vtop__Syms() {
    // Tear down scope hierarchy
    __Vhier.remove(0, __Vscopep_async_fifo_top);
    __Vhier.remove(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__g_std_reg_mode);
    __Vhier.remove(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_dual_port_ram);
    __Vhier.remove(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_read_pointer);
    __Vhier.remove(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_sync_r2w);
    __Vhier.remove(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_sync_w2r);
    __Vhier.remove(__Vscopep_async_fifo_top, __Vscopep_async_fifo_top__u_write_pointer);
    __Vhier.remove(__Vscopep_async_fifo_top__u_sync_r2w, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst);
    __Vhier.remove(__Vscopep_async_fifo_top__u_sync_r2w__g_async_rst, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk1);
    __Vhier.remove(__Vscopep_async_fifo_top__u_sync_r2w__g_async_rst, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk2);
    __Vhier.remove(__Vscopep_async_fifo_top__u_sync_w2r, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst);
    __Vhier.remove(__Vscopep_async_fifo_top__u_sync_w2r__g_async_rst, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk1);
    __Vhier.remove(__Vscopep_async_fifo_top__u_sync_w2r__g_async_rst, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk2);
    // Clear keys from hierarchy map after values have been removed
    __Vhier.clear();
    // Tear down scopes
    VL_DO_CLEAR(delete __Vscopep_TOP, __Vscopep_TOP = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top, __Vscopep_async_fifo_top = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__g_std_reg_mode, __Vscopep_async_fifo_top__g_std_reg_mode = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_dual_port_ram, __Vscopep_async_fifo_top__u_dual_port_ram = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_read_pointer, __Vscopep_async_fifo_top__u_read_pointer = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_r2w, __Vscopep_async_fifo_top__u_sync_r2w = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk1, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk1 = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk2, __Vscopep_async_fifo_top__u_sync_r2w__g_async_rst__unnamedblk2 = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_w2r, __Vscopep_async_fifo_top__u_sync_w2r = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk1, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk1 = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk2, __Vscopep_async_fifo_top__u_sync_w2r__g_async_rst__unnamedblk2 = nullptr);
    VL_DO_CLEAR(delete __Vscopep_async_fifo_top__u_write_pointer, __Vscopep_async_fifo_top__u_write_pointer = nullptr);
    // Tear down sub module instances
}
