// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("../rtl_src/async_fifo_top.sv", 1, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtop___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtop___024root___eval_triggers_vec__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.rdata = vlSelfRef.async_fifo_top__DOT__rdata;
    vlSelfRef.async_fifo_top__DOT__wdata = vlSelfRef.wdata;
    vlSelfRef.async_fifo_top__DOT__walmost_full = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__walmost_full;
    vlSelfRef.async_fifo_top__DOT__ralmost_empty = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__ralmost_empty;
    vlSelfRef.async_fifo_top__DOT__rptr_gray = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray;
    vlSelfRef.async_fifo_top__DOT__wptr_gray = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr 
        = (7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin));
    vlSelfRef.async_fifo_top__DOT__rempty_raw = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty;
    vlSelfRef.async_fifo_top__DOT__rclk = vlSelfRef.rclk;
    vlSelfRef.async_fifo_top__DOT__wfull = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull;
    vlSelfRef.async_fifo_top__DOT__wclk = vlSelfRef.wclk;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr 
        = (7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin));
    vlSelfRef.async_fifo_top__DOT__wrst = vlSelfRef.wrst;
    vlSelfRef.async_fifo_top__DOT__rinc = vlSelfRef.rinc;
    vlSelfRef.async_fifo_top__DOT__rrst = vlSelfRef.rrst;
    vlSelfRef.async_fifo_top__DOT__winc = vlSelfRef.winc;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[1U];
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[1U];
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wdata 
        = vlSelfRef.async_fifo_top__DOT__wdata;
    vlSelfRef.walmost_full = vlSelfRef.async_fifo_top__DOT__walmost_full;
    vlSelfRef.ralmost_empty = vlSelfRef.async_fifo_top__DOT__ralmost_empty;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__din 
        = vlSelfRef.async_fifo_top__DOT__rptr_gray;
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__din 
        = vlSelfRef.async_fifo_top__DOT__wptr_gray;
    vlSelfRef.async_fifo_top__DOT__waddr = vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr;
    vlSelfRef.async_fifo_top__DOT__rempty = vlSelfRef.async_fifo_top__DOT__rempty_raw;
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__clk 
        = vlSelfRef.async_fifo_top__DOT__rclk;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rclk 
        = vlSelfRef.async_fifo_top__DOT__rclk;
    vlSelfRef.wfull = vlSelfRef.async_fifo_top__DOT__wfull;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__clk 
        = vlSelfRef.async_fifo_top__DOT__wclk;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wclk 
        = vlSelfRef.async_fifo_top__DOT__wclk;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wclk 
        = vlSelfRef.async_fifo_top__DOT__wclk;
    vlSelfRef.async_fifo_top__DOT__raddr = vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr;
    vlSelfRef.async_fifo_top__DOT__wrst_internal = vlSelfRef.async_fifo_top__DOT__wrst;
    vlSelfRef.async_fifo_top__DOT__rinc_internal = vlSelfRef.async_fifo_top__DOT__rinc;
    vlSelfRef.async_fifo_top__DOT__rrst_internal = vlSelfRef.async_fifo_top__DOT__rrst;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__winc 
        = ((~ (IData)(vlSelfRef.async_fifo_top__DOT__wfull)) 
           & (IData)(vlSelfRef.async_fifo_top__DOT__winc));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__winc 
        = vlSelfRef.async_fifo_top__DOT__winc;
    vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2 
        = vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout;
    vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2 
        = vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__waddr 
        = vlSelfRef.async_fifo_top__DOT__waddr;
    vlSelfRef.rempty = vlSelfRef.async_fifo_top__DOT__rempty;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr 
        = vlSelfRef.async_fifo_top__DOT__raddr;
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst 
        = vlSelfRef.async_fifo_top__DOT__wrst_internal;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wrst 
        = vlSelfRef.async_fifo_top__DOT__wrst_internal;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rinc 
        = vlSelfRef.async_fifo_top__DOT__rinc_internal;
    vlSelfRef.async_fifo_top__DOT__rst_cond_r = (1U 
                                                 & (~ (IData)(vlSelfRef.async_fifo_top__DOT__rrst_internal)));
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst 
        = vlSelfRef.async_fifo_top__DOT__rrst_internal;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rrst 
        = vlSelfRef.async_fifo_top__DOT__rrst_internal;
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin) 
                          + ((~ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull)) 
                             & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__winc))));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync 
        = vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync 
        = vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2;
    vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata 
        = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem
        [vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr];
    vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst)));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wrst)));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin) 
                          + ((~ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty)) 
                             & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rinc))));
    vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst)));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond 
        = (1U & (~ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rrst)));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next 
        = (VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next), 1U) 
           ^ (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync 
        = ((7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync)) 
           | (8U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync)));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i = 2U;
    while (VL_LTES_III(32, 0U, vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i)) {
        vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync 
            = (((~ ((IData)(1U) << (3U & vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i))) 
                & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync)) 
               | (0x0fU & ((1U & (((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync) 
                                   >> (3U & ((IData)(1U) 
                                             + vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i))) 
                                  ^ ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync) 
                                     >> (3U & vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i)))) 
                           << (3U & vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i))));
        vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i 
            = (vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i 
               - (IData)(1U));
    }
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync 
        = ((7U & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync)) 
           | (8U & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync)));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i = 2U;
    while (VL_LTES_III(32, 0U, vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i)) {
        vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync 
            = (((~ ((IData)(1U) << (3U & vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i))) 
                & (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync)) 
               | (0x0fU & ((1U & (((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync) 
                                   >> (3U & ((IData)(1U) 
                                             + vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i))) 
                                  ^ ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync) 
                                     >> (3U & vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i)))) 
                           << (3U & vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i))));
        vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i 
            = (vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i 
               - (IData)(1U));
    }
    vlSelfRef.async_fifo_top__DOT__ram_rdata = vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata;
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next 
        = (VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next), 1U) 
           ^ (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull_val 
        = ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next) 
           == ((0x0000000cU & ((~ ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync) 
                                   >> 2U)) << 2U)) 
               | (3U & (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync))));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__wcount 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin) 
                          - (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync)));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__rcount 
        = (0x0000000fU & ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync) 
                          - (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin)));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty_val 
        = ((IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next) 
           == (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync));
    vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__walmost_full_val 
        = (6U <= (IData)(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__wcount));
    vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__ralmost_empty_val 
        = (2U >= (IData)(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__rcount));
}

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtop___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtop___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge async_fifo_top.rclk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge async_fifo_top.rst_cond_r)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(posedge async_fifo_top.u_sync_r2w.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @(posedge async_fifo_top.u_sync_r2w.rst_cond)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @(posedge async_fifo_top.u_sync_w2r.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @(posedge async_fifo_top.u_sync_w2r.rst_cond)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 6 is active: @(posedge async_fifo_top.u_write_pointer.rst_cond)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 7U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 7 is active: @(posedge async_fifo_top.u_write_pointer.wclk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 8U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 8 is active: @(posedge async_fifo_top.u_read_pointer.rclk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 9U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 9 is active: @(posedge async_fifo_top.u_read_pointer.rst_cond)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 10 is active: @(posedge async_fifo_top.u_dual_port_ram.wclk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->wclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12278276179844817653ull);
    vlSelf->wrst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8223038449537001320ull);
    vlSelf->winc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16007895650452401314ull);
    vlSelf->wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12890271867161903902ull);
    vlSelf->wfull = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5864852463863308700ull);
    vlSelf->walmost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1561580491562988656ull);
    vlSelf->rclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12802990810940348356ull);
    vlSelf->rrst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7944061328447938208ull);
    vlSelf->rinc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3707185169570288080ull);
    vlSelf->rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10065165116613087284ull);
    vlSelf->rempty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13287137859590754213ull);
    vlSelf->ralmost_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8778799750629937607ull);
    vlSelf->async_fifo_top__DOT__wclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16812877558524127710ull);
    vlSelf->async_fifo_top__DOT__wrst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2384084257810622332ull);
    vlSelf->async_fifo_top__DOT__winc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3331318004353411249ull);
    vlSelf->async_fifo_top__DOT__wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9914738800132213078ull);
    vlSelf->async_fifo_top__DOT__wfull = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17986135321960635122ull);
    vlSelf->async_fifo_top__DOT__walmost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1982929663934821480ull);
    vlSelf->async_fifo_top__DOT__rclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15074860801278975214ull);
    vlSelf->async_fifo_top__DOT__rrst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10257900563775802412ull);
    vlSelf->async_fifo_top__DOT__rinc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14042605000471368511ull);
    vlSelf->async_fifo_top__DOT__rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6613753254576428931ull);
    vlSelf->async_fifo_top__DOT__rempty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12501303333833661714ull);
    vlSelf->async_fifo_top__DOT__ralmost_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9571123877245484758ull);
    vlSelf->async_fifo_top__DOT__wrst_internal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1760317402981458100ull);
    vlSelf->async_fifo_top__DOT__rrst_internal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2461472109296677692ull);
    vlSelf->async_fifo_top__DOT__rst_cond_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17833718914891655326ull);
    vlSelf->async_fifo_top__DOT__wptr_gray = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4913745089053382027ull);
    vlSelf->async_fifo_top__DOT__rptr_gray = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10492970134993014866ull);
    vlSelf->async_fifo_top__DOT__rptr_gray_sync_w2 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5248458549028985464ull);
    vlSelf->async_fifo_top__DOT__wptr_gray_sync_r2 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10001797989778344212ull);
    vlSelf->async_fifo_top__DOT__waddr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 2907359564356130297ull);
    vlSelf->async_fifo_top__DOT__raddr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10206627934347838097ull);
    vlSelf->async_fifo_top__DOT__rinc_internal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7185836590637765122ull);
    vlSelf->async_fifo_top__DOT__rempty_raw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3085533525134064739ull);
    vlSelf->async_fifo_top__DOT__ram_rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12326874831664296477ull);
    vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14653684378883864321ull);
    vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7819112493238439678ull);
    vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__din = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8362619265171917639ull);
    vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__dout = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7495756251000434164ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[__Vi0] = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11079977675207378519ull);
    }
    vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11577217301668613794ull);
    vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i = 0;
    vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8584370211205018442ull);
    vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3404161731113580214ull);
    vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__din = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16283387964365527597ull);
    vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__dout = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14105793841632721822ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[__Vi0] = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15220620453709799988ull);
    }
    vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11832120924559307442ull);
    vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i = 0;
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6782339954692117393ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wrst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8517364619729191273ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__winc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17133940687383561306ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1319912999036734091ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__waddr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17861497615370581064ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wgray = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17407014056604179372ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wfull = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17546922436562926477ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__walmost_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9302591660553262436ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wbin = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7132384648907871864ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wbin_next = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5211930558626041574ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wgray_next = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14190278208104883585ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__wfull_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16721591835639715659ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__rst_cond = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10378512860234993332ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__rbin_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 175455930263952669ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__wcount = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13722733968598684992ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__walmost_full_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15995578362915745503ull);
    vlSelf->async_fifo_top__DOT__u_write_pointer__DOT__g_almost_full__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7650973323375931935ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rrst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4397680270360883740ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rinc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13310474276802160936ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3998669145285028093ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__raddr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17644612342026274628ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rgray = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8774427142916064364ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rempty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10574613551598626645ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__ralmost_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3303384310517019180ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rbin = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1723618272422517899ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rbin_next = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10982543007613604815ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rgray_next = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9957705584301026622ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rempty_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4552872202859477792ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__rst_cond = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11346760778033652283ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__wbin_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13079710942572214772ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__rcount = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10600884939357499222ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__ralmost_empty_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13609242549006652158ull);
    vlSelf->async_fifo_top__DOT__u_read_pointer__DOT__g_almost_empty__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->async_fifo_top__DOT__u_dual_port_ram__DOT__wclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2306274132878331828ull);
    vlSelf->async_fifo_top__DOT__u_dual_port_ram__DOT__winc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2459873663680559750ull);
    vlSelf->async_fifo_top__DOT__u_dual_port_ram__DOT__waddr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9704679280826126584ull);
    vlSelf->async_fifo_top__DOT__u_dual_port_ram__DOT__wdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11703742115018426268ull);
    vlSelf->async_fifo_top__DOT__u_dual_port_ram__DOT__raddr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9388421617570928365ull);
    vlSelf->async_fifo_top__DOT__u_dual_port_ram__DOT__rdata = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5847785782645399678ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->async_fifo_top__DOT__u_dual_port_ram__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2220372520063786372ull);
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__rclk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__rst_cond_r__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__rst_cond__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__wclk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rclk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rst_cond__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__async_fifo_top__DOT__u_dual_port_ram__DOT__wclk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
