// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

void Vtop___024root___eval_triggers_vec__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vtop___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.rdata = vlSelfRef.async_fifo_top__DOT__rdata;
    vlSelfRef.async_fifo_top__DOT__wdata = vlSelfRef.wdata;
    vlSelfRef.async_fifo_top__DOT__rptr_gray = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray;
    vlSelfRef.async_fifo_top__DOT__wptr_gray = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray;
    vlSelfRef.async_fifo_top__DOT__rclk = vlSelfRef.rclk;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr 
        = (7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin));
    vlSelfRef.async_fifo_top__DOT__rempty_raw = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty;
    vlSelfRef.async_fifo_top__DOT__wfull = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull;
    vlSelfRef.async_fifo_top__DOT__wclk = vlSelfRef.wclk;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[1U];
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[1U];
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr 
        = (7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin));
    vlSelfRef.async_fifo_top__DOT__wrst = vlSelfRef.wrst;
    vlSelfRef.async_fifo_top__DOT__rrst = vlSelfRef.rrst;
    vlSelfRef.async_fifo_top__DOT__rinc = vlSelfRef.rinc;
    vlSelfRef.async_fifo_top__DOT__winc = vlSelfRef.winc;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wdata 
        = vlSelfRef.async_fifo_top__DOT__wdata;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__din 
        = vlSelfRef.async_fifo_top__DOT__rptr_gray;
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__din 
        = vlSelfRef.async_fifo_top__DOT__wptr_gray;
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__clk 
        = vlSelfRef.async_fifo_top__DOT__rclk;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rclk 
        = vlSelfRef.async_fifo_top__DOT__rclk;
    vlSelfRef.async_fifo_top__DOT__waddr = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr;
    vlSelfRef.async_fifo_top__DOT__rempty = vlSelfRef.async_fifo_top__DOT__rempty_raw;
    vlSelfRef.wfull = vlSelfRef.async_fifo_top__DOT__wfull;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__clk 
        = vlSelfRef.async_fifo_top__DOT__wclk;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wclk 
        = vlSelfRef.async_fifo_top__DOT__wclk;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wclk 
        = vlSelfRef.async_fifo_top__DOT__wclk;
    vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout;
    vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout;
    vlSelfRef.async_fifo_top__DOT__raddr = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr;
    vlSelfRef.async_fifo_top__DOT__wrst_internal = vlSelfRef.async_fifo_top__DOT__wrst;
    vlSelfRef.async_fifo_top__DOT__rrst_internal = vlSelfRef.async_fifo_top__DOT__rrst;
    vlSelfRef.async_fifo_top__DOT__rinc_internal = vlSelfRef.async_fifo_top__DOT__rinc;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__winc 
        = ((~ (IData)(vlSelfRef.async_fifo_top__DOT__wfull)) 
           & (IData)(vlSelfRef.async_fifo_top__DOT__winc));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__winc 
        = vlSelfRef.async_fifo_top__DOT__winc;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__waddr 
        = vlSelfRef.async_fifo_top__DOT__waddr;
    vlSelfRef.rempty = vlSelfRef.async_fifo_top__DOT__rempty;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync 
        = vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync 
        = vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr 
        = vlSelfRef.async_fifo_top__DOT__raddr;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst 
        = vlSelfRef.async_fifo_top__DOT__wrst_internal;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wrst 
        = vlSelfRef.async_fifo_top__DOT__wrst_internal;
    vlSelfRef.async_fifo_top__DOT__rst_cond_r = (1U 
                                                 & (~ (IData)(vlSelfRef.async_fifo_top__DOT__rrst_internal)));
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst 
        = vlSelfRef.async_fifo_top__DOT__rrst_internal;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rrst 
        = vlSelfRef.async_fifo_top__DOT__rrst_internal;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rinc 
        = vlSelfRef.async_fifo_top__DOT__rinc_internal;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin) 
                          + ((~ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull)) 
                             & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__winc))));
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata 
        = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem
        [vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr];
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst)));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wrst)));
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst)));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rrst)));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin) 
                          + ((~ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty)) 
                             & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rinc))));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next 
        = (VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next), 1U) 
           ^ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next));
    vlSelfRef.async_fifo_top__DOT__ram_rdata = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next 
        = (VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next), 1U) 
           ^ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull_val 
        = ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next) 
           == ((0x0000000cU & ((~ ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync) 
                                   >> 2U)) << 2U)) 
               | (3U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync))));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty_val 
        = ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next) 
           == (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync));
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vtop___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_triggers_vec__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wclk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_dual_port_ram__DOT__wclk__0))) 
                                                       << 0x0000000aU) 
                                                      | ((((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rst_cond__0))) 
                                                          << 9U) 
                                                         | (((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rclk) 
                                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rclk__0))) 
                                                            << 8U))) 
                                                     | (((((((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wclk) 
                                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__wclk__0))) 
                                                            << 3U) 
                                                           | (((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond) 
                                                               & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__rst_cond__0))) 
                                                              << 2U)) 
                                                          | ((((IData)(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond) 
                                                               & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond__0))) 
                                                              << 1U) 
                                                             | ((IData)(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__clk) 
                                                                & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__clk__0))))) 
                                                         << 4U) 
                                                        | (((((IData)(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond) 
                                                              & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond__0))) 
                                                             << 3U) 
                                                            | (((IData)(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__clk) 
                                                                & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__clk__0))) 
                                                               << 2U)) 
                                                           | ((((IData)(vlSelfRef.async_fifo_top__DOT__rst_cond_r) 
                                                                & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__rst_cond_r__0))) 
                                                               << 1U) 
                                                              | ((IData)(vlSelfRef.async_fifo_top__DOT__rclk) 
                                                                 & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__rclk__0)))))))));
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__rclk__0 
        = vlSelfRef.async_fifo_top__DOT__rclk;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__rst_cond_r__0 
        = vlSelfRef.async_fifo_top__DOT__rst_cond_r;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__clk__0 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond__0 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__clk__0 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond__0 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__rst_cond__0 
        = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__wclk__0 
        = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wclk;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rclk__0 
        = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rclk;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rst_cond__0 
        = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond;
    vlSelfRef.__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_dual_port_ram__DOT__wclk__0 
        = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wclk;
}

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __VdlyVal__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0;
    __VdlyVal__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0 = 0;
    CData/*2:0*/ __VdlyDim0__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0;
    __VdlyDim0__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0;
    __VdlySet__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0 = 0;
    // Body
    __VdlySet__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0 = 0U;
    if (vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__winc) {
        __VdlyVal__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0 
            = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wdata;
        __VdlyDim0__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0 
            = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__waddr;
        __VdlySet__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0 = 1U;
    }
    if (__VdlySet__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0) {
        vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[__VdlyDim0__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0] 
            = __VdlyVal__async_fifo_top__DOT__u_dual_port_ram__DOT__mem__v0;
    }
}

void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond) {
        vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray = 0U;
        vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin = 0U;
    } else {
        vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray 
            = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next;
        vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin 
            = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next;
    }
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull 
        = ((1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond))) 
           && (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull_val));
    vlSelfRef.async_fifo_top__DOT__wptr_gray = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray;
    vlSelfRef.async_fifo_top__DOT__wfull = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr 
        = (7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin) 
                          + ((~ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull)) 
                             & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__winc))));
    vlSelfRef.wfull = vlSelfRef.async_fifo_top__DOT__wfull;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__winc 
        = ((~ (IData)(vlSelfRef.async_fifo_top__DOT__wfull)) 
           & (IData)(vlSelfRef.async_fifo_top__DOT__winc));
    vlSelfRef.async_fifo_top__DOT__waddr = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next 
        = (VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next), 1U) 
           ^ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next));
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__waddr 
        = vlSelfRef.async_fifo_top__DOT__waddr;
}

void Vtop___024root___nba_sequent__TOP__2(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__2\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond) {
        vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray = 0U;
        vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin = 0U;
    } else {
        vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray 
            = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next;
        vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin 
            = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next;
    }
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty 
        = ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond) 
           || (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty_val));
    vlSelfRef.async_fifo_top__DOT__rptr_gray = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray;
    vlSelfRef.async_fifo_top__DOT__rempty_raw = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr 
        = (7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin) 
                          + ((~ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty)) 
                             & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rinc))));
    vlSelfRef.async_fifo_top__DOT__rempty = vlSelfRef.async_fifo_top__DOT__rempty_raw;
    vlSelfRef.async_fifo_top__DOT__raddr = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next 
        = (VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next), 1U) 
           ^ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next));
    vlSelfRef.rempty = vlSelfRef.async_fifo_top__DOT__rempty;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr 
        = vlSelfRef.async_fifo_top__DOT__raddr;
}

void Vtop___024root___nba_sequent__TOP__3(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__3\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.async_fifo_top__DOT__rst_cond_r) {
        vlSelfRef.async_fifo_top__DOT__rdata = 0U;
    } else if (vlSelfRef.async_fifo_top__DOT__rinc) {
        vlSelfRef.async_fifo_top__DOT__rdata = vlSelfRef.async_fifo_top__DOT__ram_rdata;
    }
    vlSelfRef.rdata = vlSelfRef.async_fifo_top__DOT__rdata;
}

void Vtop___024root___nba_sequent__TOP__4(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__4\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v0;
    __VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v0 = 0;
    CData/*3:0*/ __VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v1;
    __VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v1 = 0;
    CData/*3:0*/ __VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2;
    __VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2 = 0;
    CData/*0:0*/ __VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2;
    __VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2 = 0;
    // Body
    if (vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond) {
        vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i = 0U;
        while (VL_GTS_III(32, 2U, vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i)) {
            __VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v0 
                = (1U & vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i);
            vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_r2w__DOT__sync_reg.enqueue(0U, (IData)(__VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v0));
            vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i 
                = ((IData)(1U) + vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i);
        }
    } else {
        __VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v1 
            = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__din;
        vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_r2w__DOT__sync_reg.enqueue(__VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v1, 0U);
        vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i = 1U;
        while (VL_GTS_III(32, 2U, vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i)) {
            __VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2 
                = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg
                [(1U & (vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i 
                        - (IData)(1U)))];
            __VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2 
                = (1U & vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i);
            vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_r2w__DOT__sync_reg.enqueue(__VdlyVal__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2, (IData)(__VdlyDim0__async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg__v2));
            vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i 
                = ((IData)(1U) + vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i);
        }
    }
    vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_r2w__DOT__sync_reg.commit(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg);
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[1U];
    vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync 
        = vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2;
}

void Vtop___024root___nba_sequent__TOP__5(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__5\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v0;
    __VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v0 = 0;
    CData/*3:0*/ __VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v1;
    __VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v1 = 0;
    CData/*3:0*/ __VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2;
    __VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2 = 0;
    CData/*0:0*/ __VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2;
    __VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2 = 0;
    // Body
    if (vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond) {
        vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i = 0U;
        while (VL_GTS_III(32, 2U, vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i)) {
            __VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v0 
                = (1U & vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i);
            vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_w2r__DOT__sync_reg.enqueue(0U, (IData)(__VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v0));
            vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i 
                = ((IData)(1U) + vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i);
        }
    } else {
        __VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v1 
            = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__din;
        vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_w2r__DOT__sync_reg.enqueue(__VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v1, 0U);
        vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i = 1U;
        while (VL_GTS_III(32, 2U, vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i)) {
            __VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2 
                = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg
                [(1U & (vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i 
                        - (IData)(1U)))];
            __VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2 
                = (1U & vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i);
            vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_w2r__DOT__sync_reg.enqueue(__VdlyVal__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2, (IData)(__VdlyDim0__async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg__v2));
            vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i 
                = ((IData)(1U) + vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i);
        }
    }
    vlSelfRef.__VdlyCommitQueueasync_fifo_top__DOT__u_sync_w2r__DOT__sync_reg.commit(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg);
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[1U];
    vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync 
        = vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2;
}

void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata 
        = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem
        [vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr];
    vlSelfRef.async_fifo_top__DOT__ram_rdata = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata;
}

void Vtop___024root___nba_sequent__TOP__6(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__6\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__din 
        = vlSelfRef.async_fifo_top__DOT__rptr_gray;
}

void Vtop___024root___nba_comb__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull_val 
        = ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next) 
           == ((0x0000000cU & ((~ ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync) 
                                   >> 2U)) << 2U)) 
               | (3U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync))));
}

void Vtop___024root___nba_sequent__TOP__7(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__7\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__din 
        = vlSelfRef.async_fifo_top__DOT__wptr_gray;
}

void Vtop___024root___nba_comb__TOP__2(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__2\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty_val 
        = ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next) 
           == (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync));
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x0000000000000400ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((0x00000000000000c0ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((0x0000000000000300ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((0x000000000000000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((0x0000000000000030ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((0x0000000000000700ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((0x0000000000000300ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__6(vlSelf);
    }
    if ((0x00000000000000ccULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__1(vlSelf);
    }
    if ((0x00000000000000c0ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__7(vlSelf);
    }
    if ((0x0000000000000330ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__2(vlSelf);
    }
}

void Vtop___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtop___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vtop___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtop___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        Vtop___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("../rtl_src/async_fifo_top.sv", 1, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vtop___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("../rtl_src/async_fifo_top.sv", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("../rtl_src/async_fifo_top.sv", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vtop___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtop___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.wclk & 0xfeU)))) {
        Verilated::overWidthError("wclk");
    }
    if (VL_UNLIKELY(((vlSelfRef.wrst & 0xfeU)))) {
        Verilated::overWidthError("wrst");
    }
    if (VL_UNLIKELY(((vlSelfRef.winc & 0xfeU)))) {
        Verilated::overWidthError("winc");
    }
    if (VL_UNLIKELY(((vlSelfRef.rclk & 0xfeU)))) {
        Verilated::overWidthError("rclk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rrst & 0xfeU)))) {
        Verilated::overWidthError("rrst");
    }
    if (VL_UNLIKELY(((vlSelfRef.rinc & 0xfeU)))) {
        Verilated::overWidthError("rinc");
    }
}
#endif  // VL_DEBUG
