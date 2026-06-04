// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    VL_TRACE_PUSH_PREFIX(tracep, "$rootio", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+0,0,"wclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+1,0,"wrst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+2,0,"winc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+3,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_DECL_BIT(tracep,c+4,0,"wfull",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+5,0,"walmost_full",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+6,0,"rclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+7,0,"rrst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+8,0,"rinc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+9,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_DECL_BIT(tracep,c+10,0,"rempty",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+11,0,"ralmost_empty",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "async_fifo_top", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+96,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+97,0,"WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+98,0,"FWFT_EN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT);
    VL_TRACE_DECL_BIT(tracep,c+98,0,"OUT_REG_EN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT);
    VL_TRACE_DECL_BUS(tracep,c+99,0,"RST_TYPE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 1,0);
    VL_TRACE_DECL_BIT(tracep,c+100,0,"RST_POLARITY",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+101,0,"SYNC_STAGES",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+102,0,"ALMOST_FULL_EN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT);
    VL_TRACE_DECL_BUS(tracep,c+101,0,"ALMOST_FULL_VAL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+102,0,"ALMOST_EMPTY_EN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT);
    VL_TRACE_DECL_BUS(tracep,c+101,0,"ALMOST_EMPTY_VAL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+12,0,"wclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+13,0,"wrst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+14,0,"winc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+15,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_DECL_BIT(tracep,c+16,0,"wfull",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+17,0,"walmost_full",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+18,0,"rclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+19,0,"rrst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+20,0,"rinc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+21,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_DECL_BIT(tracep,c+22,0,"rempty",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+23,0,"ralmost_empty",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+103,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+104,0,"PTR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+96,0,"MEM_DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+24,0,"wrst_internal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+25,0,"rrst_internal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+26,0,"rst_cond_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+27,0,"wptr_gray",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+28,0,"rptr_gray",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+29,0,"rptr_gray_sync_w2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+30,0,"wptr_gray_sync_r2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+31,0,"waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+32,0,"raddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BIT(tracep,c+33,0,"rinc_internal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+34,0,"rempty_raw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+35,0,"ram_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_PUSH_PREFIX(tracep, "u_dual_port_ram", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+97,0,"WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+96,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+36,0,"wclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+37,0,"winc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+38,0,"waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+39,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_DECL_BUS(tracep,c+40,0,"raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+41,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_PUSH_PREFIX(tracep, "mem", VerilatedTracePrefixType::ARRAY_UNPACKED, 0, 7);
    for (int i = 0; i < 8; ++i) {
        VL_TRACE_DECL_BUS_ARRAY(tracep,c+42+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, (i + 0), 15,0);
    }
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "u_read_pointer", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+103,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+99,0,"RST_TYPE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 1,0);
    VL_TRACE_DECL_BIT(tracep,c+100,0,"RST_POLARITY",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+102,0,"ALMOST_EMPTY_EN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT);
    VL_TRACE_DECL_BUS(tracep,c+101,0,"ALMOST_EMPTY_VAL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+98,0,"FWFT_EN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT);
    VL_TRACE_DECL_BIT(tracep,c+50,0,"rclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+51,0,"rrst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+52,0,"rinc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+53,0,"wgray_sync",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+54,0,"raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+55,0,"rgray",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BIT(tracep,c+56,0,"rempty",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+57,0,"ralmost_empty",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+104,0,"PTR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+58,0,"rbin",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+59,0,"rbin_next",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+60,0,"rgray_next",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BIT(tracep,c+61,0,"rempty_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+62,0,"rst_cond",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_PUSH_PREFIX(tracep, "g_almost_empty", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+63,0,"wbin_sync",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+64,0,"rcount",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BIT(tracep,c+65,0,"ralmost_empty_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "u_sync_r2w", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+104,0,"WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+101,0,"STAGES",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+99,0,"RST_TYPE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 1,0);
    VL_TRACE_DECL_BIT(tracep,c+100,0,"RST_POLARITY",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+66,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+67,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+68,0,"din",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+69,0,"dout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_PUSH_PREFIX(tracep, "sync_reg", VerilatedTracePrefixType::ARRAY_UNPACKED, 1, 0);
    for (int i = 0; i < 2; ++i) {
        VL_TRACE_DECL_BUS_ARRAY(tracep,c+70+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, (1 - i), 3,0);
    }
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_DECL_BIT(tracep,c+72,0,"rst_cond",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "u_sync_w2r", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+104,0,"WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+101,0,"STAGES",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+99,0,"RST_TYPE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 1,0);
    VL_TRACE_DECL_BIT(tracep,c+100,0,"RST_POLARITY",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+73,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+74,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+75,0,"din",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+76,0,"dout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_PUSH_PREFIX(tracep, "sync_reg", VerilatedTracePrefixType::ARRAY_UNPACKED, 1, 0);
    for (int i = 0; i < 2; ++i) {
        VL_TRACE_DECL_BUS_ARRAY(tracep,c+77+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, (1 - i), 3,0);
    }
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_DECL_BIT(tracep,c+79,0,"rst_cond",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "u_write_pointer", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+103,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+96,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+99,0,"RST_TYPE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 1,0);
    VL_TRACE_DECL_BIT(tracep,c+100,0,"RST_POLARITY",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+102,0,"ALMOST_FULL_EN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT);
    VL_TRACE_DECL_BUS(tracep,c+101,0,"ALMOST_FULL_VAL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+80,0,"wclk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+81,0,"wrst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+82,0,"winc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+83,0,"rgray_sync",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+84,0,"waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+85,0,"wgray",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BIT(tracep,c+86,0,"wfull",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+87,0,"walmost_full",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+104,0,"PTR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+88,0,"wbin",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+89,0,"wbin_next",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+90,0,"wgray_next",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BIT(tracep,c+91,0,"wfull_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+92,0,"rst_cond",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_PUSH_PREFIX(tracep, "g_almost_full", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+93,0,"rbin_sync",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+94,0,"wcount",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BIT(tracep,c+95,0,"walmost_full_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_POP_PREFIX(tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtop___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vtop___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtop___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+96,(8U),32);
    bufp->fullIData(oldp+97,(0x00000010U),32);
    bufp->fullBit(oldp+98,(0U));
    bufp->fullCData(oldp+99,(0U),2);
    bufp->fullBit(oldp+100,(0U));
    bufp->fullIData(oldp+101,(2U),32);
    bufp->fullBit(oldp+102,(1U));
    bufp->fullIData(oldp+103,(3U),32);
    bufp->fullIData(oldp+104,(4U),32);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+0,(vlSelfRef.wclk));
    bufp->fullBit(oldp+1,(vlSelfRef.wrst));
    bufp->fullBit(oldp+2,(vlSelfRef.winc));
    bufp->fullSData(oldp+3,(vlSelfRef.wdata),16);
    bufp->fullBit(oldp+4,(vlSelfRef.wfull));
    bufp->fullBit(oldp+5,(vlSelfRef.walmost_full));
    bufp->fullBit(oldp+6,(vlSelfRef.rclk));
    bufp->fullBit(oldp+7,(vlSelfRef.rrst));
    bufp->fullBit(oldp+8,(vlSelfRef.rinc));
    bufp->fullSData(oldp+9,(vlSelfRef.rdata),16);
    bufp->fullBit(oldp+10,(vlSelfRef.rempty));
    bufp->fullBit(oldp+11,(vlSelfRef.ralmost_empty));
    bufp->fullBit(oldp+12,(vlSelfRef.async_fifo_top__DOT__wclk));
    bufp->fullBit(oldp+13,(vlSelfRef.async_fifo_top__DOT__wrst));
    bufp->fullBit(oldp+14,(vlSelfRef.async_fifo_top__DOT__winc));
    bufp->fullSData(oldp+15,(vlSelfRef.async_fifo_top__DOT__wdata),16);
    bufp->fullBit(oldp+16,(vlSelfRef.async_fifo_top__DOT__wfull));
    bufp->fullBit(oldp+17,(vlSelfRef.async_fifo_top__DOT__walmost_full));
    bufp->fullBit(oldp+18,(vlSelfRef.async_fifo_top__DOT__rclk));
    bufp->fullBit(oldp+19,(vlSelfRef.async_fifo_top__DOT__rrst));
    bufp->fullBit(oldp+20,(vlSelfRef.async_fifo_top__DOT__rinc));
    bufp->fullSData(oldp+21,(vlSelfRef.async_fifo_top__DOT__rdata),16);
    bufp->fullBit(oldp+22,(vlSelfRef.async_fifo_top__DOT__rempty));
    bufp->fullBit(oldp+23,(vlSelfRef.async_fifo_top__DOT__ralmost_empty));
    bufp->fullBit(oldp+24,(vlSelfRef.async_fifo_top__DOT__wrst_internal));
    bufp->fullBit(oldp+25,(vlSelfRef.async_fifo_top__DOT__rrst_internal));
    bufp->fullBit(oldp+26,(vlSelfRef.async_fifo_top__DOT__rst_cond_r));
    bufp->fullCData(oldp+27,(vlSelfRef.async_fifo_top__DOT__wptr_gray),4);
    bufp->fullCData(oldp+28,(vlSelfRef.async_fifo_top__DOT__rptr_gray),4);
    bufp->fullCData(oldp+29,(vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2),4);
    bufp->fullCData(oldp+30,(vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2),4);
    bufp->fullCData(oldp+31,(vlSelfRef.async_fifo_top__DOT__waddr),3);
    bufp->fullCData(oldp+32,(vlSelfRef.async_fifo_top__DOT__raddr),3);
    bufp->fullBit(oldp+33,(vlSelfRef.async_fifo_top__DOT__rinc_internal));
    bufp->fullBit(oldp+34,(vlSelfRef.async_fifo_top__DOT__rempty_raw));
    bufp->fullSData(oldp+35,(vlSelfRef.async_fifo_top__DOT__ram_rdata),16);
    bufp->fullBit(oldp+36,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wclk));
    bufp->fullBit(oldp+37,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__winc));
    bufp->fullCData(oldp+38,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__waddr),3);
    bufp->fullSData(oldp+39,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wdata),16);
    bufp->fullCData(oldp+40,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr),3);
    bufp->fullSData(oldp+41,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata),16);
    bufp->fullSData(oldp+42,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[0]),16);
    bufp->fullSData(oldp+43,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[1]),16);
    bufp->fullSData(oldp+44,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[2]),16);
    bufp->fullSData(oldp+45,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[3]),16);
    bufp->fullSData(oldp+46,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[4]),16);
    bufp->fullSData(oldp+47,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[5]),16);
    bufp->fullSData(oldp+48,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[6]),16);
    bufp->fullSData(oldp+49,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[7]),16);
    bufp->fullBit(oldp+50,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rclk));
    bufp->fullBit(oldp+51,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rrst));
    bufp->fullBit(oldp+52,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rinc));
    bufp->fullCData(oldp+53,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync),4);
    bufp->fullCData(oldp+54,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr),3);
    bufp->fullCData(oldp+55,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray),4);
    bufp->fullBit(oldp+56,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty));
    bufp->fullBit(oldp+57,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__ralmost_empty));
    bufp->fullCData(oldp+58,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin),4);
    bufp->fullCData(oldp+59,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next),4);
    bufp->fullCData(oldp+60,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next),4);
    bufp->fullBit(oldp+61,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty_val));
    bufp->fullBit(oldp+62,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond));
    bufp->fullCData(oldp+63,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync),4);
    bufp->fullCData(oldp+64,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__rcount),4);
    bufp->fullBit(oldp+65,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__ralmost_empty_val));
    bufp->fullBit(oldp+66,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__clk));
    bufp->fullBit(oldp+67,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst));
    bufp->fullCData(oldp+68,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__din),4);
    bufp->fullCData(oldp+69,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout),4);
    bufp->fullCData(oldp+70,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[1]),4);
    bufp->fullCData(oldp+71,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[0]),4);
    bufp->fullBit(oldp+72,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond));
    bufp->fullBit(oldp+73,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__clk));
    bufp->fullBit(oldp+74,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst));
    bufp->fullCData(oldp+75,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__din),4);
    bufp->fullCData(oldp+76,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout),4);
    bufp->fullCData(oldp+77,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[1]),4);
    bufp->fullCData(oldp+78,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[0]),4);
    bufp->fullBit(oldp+79,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond));
    bufp->fullBit(oldp+80,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wclk));
    bufp->fullBit(oldp+81,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wrst));
    bufp->fullBit(oldp+82,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__winc));
    bufp->fullCData(oldp+83,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync),4);
    bufp->fullCData(oldp+84,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr),3);
    bufp->fullCData(oldp+85,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray),4);
    bufp->fullBit(oldp+86,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull));
    bufp->fullBit(oldp+87,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__walmost_full));
    bufp->fullCData(oldp+88,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin),4);
    bufp->fullCData(oldp+89,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next),4);
    bufp->fullCData(oldp+90,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next),4);
    bufp->fullBit(oldp+91,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull_val));
    bufp->fullBit(oldp+92,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond));
    bufp->fullCData(oldp+93,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync),4);
    bufp->fullCData(oldp+94,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__wcount),4);
    bufp->fullBit(oldp+95,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__walmost_full_val));
}
