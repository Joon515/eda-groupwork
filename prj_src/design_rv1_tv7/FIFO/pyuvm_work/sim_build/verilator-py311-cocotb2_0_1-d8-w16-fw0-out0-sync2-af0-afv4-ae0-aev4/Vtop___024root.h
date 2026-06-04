// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(wclk,0,0);
        VL_IN8(wrst,0,0);
        VL_IN8(rclk,0,0);
        VL_IN8(rrst,0,0);
        VL_IN8(winc,0,0);
        VL_OUT8(wfull,0,0);
        VL_OUT8(walmost_full,0,0);
        VL_IN8(rinc,0,0);
        VL_OUT8(rempty,0,0);
        VL_OUT8(ralmost_empty,0,0);
        CData/*0:0*/ async_fifo_top__DOT__wclk;
        CData/*0:0*/ async_fifo_top__DOT__wrst;
        CData/*0:0*/ async_fifo_top__DOT__winc;
        CData/*0:0*/ async_fifo_top__DOT__wfull;
        CData/*0:0*/ async_fifo_top__DOT__walmost_full;
        CData/*0:0*/ async_fifo_top__DOT__rclk;
        CData/*0:0*/ async_fifo_top__DOT__rrst;
        CData/*0:0*/ async_fifo_top__DOT__rinc;
        CData/*0:0*/ async_fifo_top__DOT__rempty;
        CData/*0:0*/ async_fifo_top__DOT__ralmost_empty;
        CData/*0:0*/ async_fifo_top__DOT__wrst_internal;
        CData/*0:0*/ async_fifo_top__DOT__rrst_internal;
        CData/*0:0*/ async_fifo_top__DOT__rst_cond_r;
        CData/*3:0*/ async_fifo_top__DOT__wptr_gray;
        CData/*3:0*/ async_fifo_top__DOT__rptr_gray;
        CData/*3:0*/ async_fifo_top__DOT__rptr_gray_sync_w2;
        CData/*3:0*/ async_fifo_top__DOT__wptr_gray_sync_r2;
        CData/*2:0*/ async_fifo_top__DOT__waddr;
        CData/*2:0*/ async_fifo_top__DOT__raddr;
        CData/*0:0*/ async_fifo_top__DOT__rinc_internal;
        CData/*0:0*/ async_fifo_top__DOT__rempty_raw;
        CData/*0:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__clk;
        CData/*0:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__rst;
        CData/*3:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__din;
        CData/*3:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__dout;
        CData/*0:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond;
        CData/*0:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__clk;
        CData/*0:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__rst;
        CData/*3:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__din;
        CData/*3:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__dout;
        CData/*0:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond;
        CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wclk;
        CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wrst;
        CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__winc;
        CData/*3:0*/ async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync;
        CData/*2:0*/ async_fifo_top__DOT__u_write_pointer__DOT__waddr;
        CData/*3:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wgray;
        CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wfull;
        CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__walmost_full;
        CData/*3:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wbin;
        CData/*3:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wbin_next;
        CData/*3:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wgray_next;
        CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__wfull_val;
        CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__rst_cond;
        CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rclk;
        CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rrst;
        CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rinc;
        CData/*3:0*/ async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync;
        CData/*2:0*/ async_fifo_top__DOT__u_read_pointer__DOT__raddr;
        CData/*3:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rgray;
        CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rempty;
        CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__ralmost_empty;
        CData/*3:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rbin;
        CData/*3:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rbin_next;
    };
    struct {
        CData/*3:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rgray_next;
        CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rempty_val;
        CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__rst_cond;
        CData/*0:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__wclk;
        CData/*0:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__winc;
        CData/*2:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__waddr;
        CData/*2:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__raddr;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __VicoPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__rclk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__rst_cond_r__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__rst_cond__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_write_pointer__DOT__wclk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rclk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_read_pointer__DOT__rst_cond__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__async_fifo_top__DOT__u_dual_port_ram__DOT__wclk__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        VL_IN16(wdata,15,0);
        VL_OUT16(rdata,15,0);
        SData/*15:0*/ async_fifo_top__DOT__wdata;
        SData/*15:0*/ async_fifo_top__DOT__rdata;
        SData/*15:0*/ async_fifo_top__DOT__ram_rdata;
        SData/*15:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__wdata;
        SData/*15:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__rdata;
        IData/*31:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk1__DOT__i;
        IData/*31:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__g_async_rst__DOT__unnamedblk2__DOT__i;
        IData/*31:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk1__DOT__i;
        IData/*31:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__g_async_rst__DOT__unnamedblk2__DOT__i;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<CData/*3:0*/, 2> async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg;
        VlUnpacked<CData/*3:0*/, 2> async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg;
        VlUnpacked<SData/*15:0*/, 8> async_fifo_top__DOT__u_dual_port_ram__DOT__mem;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    VlNBACommitQueue<VlUnpacked<CData/*3:0*/, 2>, false, CData/*3:0*/, 1> __VdlyCommitQueueasync_fifo_top__DOT__u_sync_r2w__DOT__sync_reg;
    VlNBACommitQueue<VlUnpacked<CData/*3:0*/, 2>, false, CData/*3:0*/, 1> __VdlyCommitQueueasync_fifo_top__DOT__u_sync_w2r__DOT__sync_reg;

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr CData/*0:0*/ async_fifo_top__DOT__FWFT_EN = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__OUT_REG_EN = 0U;
    static constexpr CData/*1:0*/ async_fifo_top__DOT__RST_TYPE = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__RST_POLARITY = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__ALMOST_FULL_EN = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__ALMOST_EMPTY_EN = 0U;
    static constexpr CData/*1:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__RST_TYPE = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__RST_POLARITY = 0U;
    static constexpr CData/*1:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__RST_TYPE = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__RST_POLARITY = 0U;
    static constexpr CData/*1:0*/ async_fifo_top__DOT__u_write_pointer__DOT__RST_TYPE = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__RST_POLARITY = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__u_write_pointer__DOT__ALMOST_FULL_EN = 0U;
    static constexpr CData/*1:0*/ async_fifo_top__DOT__u_read_pointer__DOT__RST_TYPE = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__RST_POLARITY = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__ALMOST_EMPTY_EN = 0U;
    static constexpr CData/*0:0*/ async_fifo_top__DOT__u_read_pointer__DOT__FWFT_EN = 0U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__DEPTH = 8U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__SYNC_STAGES = 2U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__ALMOST_FULL_VAL = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__ALMOST_EMPTY_VAL = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__ADDR_WIDTH = 3U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__PTR_WIDTH = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__MEM_DEPTH = 8U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__WIDTH = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_sync_r2w__DOT__STAGES = 2U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__WIDTH = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_sync_w2r__DOT__STAGES = 2U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_write_pointer__DOT__ADDR_WIDTH = 3U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_write_pointer__DOT__DEPTH = 8U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_write_pointer__DOT__ALMOST_FULL_VAL = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_write_pointer__DOT__PTR_WIDTH = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_read_pointer__DOT__ADDR_WIDTH = 3U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_read_pointer__DOT__ALMOST_EMPTY_VAL = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_read_pointer__DOT__PTR_WIDTH = 4U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ async_fifo_top__DOT__u_dual_port_ram__DOT__DEPTH = 8U;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* namep);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
