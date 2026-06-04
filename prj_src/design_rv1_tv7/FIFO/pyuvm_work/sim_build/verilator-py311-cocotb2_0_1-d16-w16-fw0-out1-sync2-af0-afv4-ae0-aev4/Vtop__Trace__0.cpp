// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    bufp->chgBit(oldp+0,(vlSelfRef.wclk));
    bufp->chgBit(oldp+1,(vlSelfRef.wrst));
    bufp->chgBit(oldp+2,(vlSelfRef.winc));
    bufp->chgSData(oldp+3,(vlSelfRef.wdata),16);
    bufp->chgBit(oldp+4,(vlSelfRef.wfull));
    bufp->chgBit(oldp+5,(vlSelfRef.rclk));
    bufp->chgBit(oldp+6,(vlSelfRef.rrst));
    bufp->chgBit(oldp+7,(vlSelfRef.rinc));
    bufp->chgSData(oldp+8,(vlSelfRef.rdata),16);
    bufp->chgBit(oldp+9,(vlSelfRef.rempty));
    bufp->chgBit(oldp+10,(vlSelfRef.async_fifo_top__DOT__wclk));
    bufp->chgBit(oldp+11,(vlSelfRef.async_fifo_top__DOT__wrst));
    bufp->chgBit(oldp+12,(vlSelfRef.async_fifo_top__DOT__winc));
    bufp->chgSData(oldp+13,(vlSelfRef.async_fifo_top__DOT__wdata),16);
    bufp->chgBit(oldp+14,(vlSelfRef.async_fifo_top__DOT__wfull));
    bufp->chgBit(oldp+15,(vlSelfRef.async_fifo_top__DOT__rclk));
    bufp->chgBit(oldp+16,(vlSelfRef.async_fifo_top__DOT__rrst));
    bufp->chgBit(oldp+17,(vlSelfRef.async_fifo_top__DOT__rinc));
    bufp->chgSData(oldp+18,(vlSelfRef.async_fifo_top__DOT__rdata),16);
    bufp->chgBit(oldp+19,(vlSelfRef.async_fifo_top__DOT__rempty));
    bufp->chgBit(oldp+20,(vlSelfRef.async_fifo_top__DOT__wrst_internal));
    bufp->chgBit(oldp+21,(vlSelfRef.async_fifo_top__DOT__rrst_internal));
    bufp->chgBit(oldp+22,(vlSelfRef.async_fifo_top__DOT__rst_cond_r));
    bufp->chgCData(oldp+23,(vlSelfRef.async_fifo_top__DOT__wptr_gray),5);
    bufp->chgCData(oldp+24,(vlSelfRef.async_fifo_top__DOT__rptr_gray),5);
    bufp->chgCData(oldp+25,(vlSelfRef.async_fifo_top__DOT__rptr_gray_sync_w2),5);
    bufp->chgCData(oldp+26,(vlSelfRef.async_fifo_top__DOT__wptr_gray_sync_r2),5);
    bufp->chgCData(oldp+27,(vlSelfRef.async_fifo_top__DOT__waddr),4);
    bufp->chgCData(oldp+28,(vlSelfRef.async_fifo_top__DOT__raddr),4);
    bufp->chgBit(oldp+29,(vlSelfRef.async_fifo_top__DOT__rinc_internal));
    bufp->chgBit(oldp+30,(vlSelfRef.async_fifo_top__DOT__rempty_raw));
    bufp->chgSData(oldp+31,(vlSelfRef.async_fifo_top__DOT__ram_rdata),16);
    bufp->chgSData(oldp+32,(vlSelfRef.async_fifo_top__DOT__g_std_reg_mode__DOT__rdata_stage1),16);
    bufp->chgBit(oldp+33,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wclk));
    bufp->chgBit(oldp+34,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__winc));
    bufp->chgCData(oldp+35,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__waddr),4);
    bufp->chgSData(oldp+36,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__wdata),16);
    bufp->chgCData(oldp+37,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__raddr),4);
    bufp->chgSData(oldp+38,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__rdata),16);
    bufp->chgSData(oldp+39,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[0]),16);
    bufp->chgSData(oldp+40,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[1]),16);
    bufp->chgSData(oldp+41,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[2]),16);
    bufp->chgSData(oldp+42,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[3]),16);
    bufp->chgSData(oldp+43,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[4]),16);
    bufp->chgSData(oldp+44,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[5]),16);
    bufp->chgSData(oldp+45,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[6]),16);
    bufp->chgSData(oldp+46,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[7]),16);
    bufp->chgSData(oldp+47,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[8]),16);
    bufp->chgSData(oldp+48,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[9]),16);
    bufp->chgSData(oldp+49,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[10]),16);
    bufp->chgSData(oldp+50,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[11]),16);
    bufp->chgSData(oldp+51,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[12]),16);
    bufp->chgSData(oldp+52,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[13]),16);
    bufp->chgSData(oldp+53,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[14]),16);
    bufp->chgSData(oldp+54,(vlSelfRef.async_fifo_top__DOT__u_dual_port_ram__DOT__mem[15]),16);
    bufp->chgBit(oldp+55,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rclk));
    bufp->chgBit(oldp+56,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rrst));
    bufp->chgBit(oldp+57,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rinc));
    bufp->chgCData(oldp+58,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__wgray_sync),5);
    bufp->chgCData(oldp+59,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__raddr),4);
    bufp->chgCData(oldp+60,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray),5);
    bufp->chgBit(oldp+61,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty));
    bufp->chgCData(oldp+62,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin),5);
    bufp->chgCData(oldp+63,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rbin_next),5);
    bufp->chgCData(oldp+64,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rgray_next),5);
    bufp->chgBit(oldp+65,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rempty_val));
    bufp->chgBit(oldp+66,(vlSelfRef.async_fifo_top__DOT__u_read_pointer__DOT__rst_cond));
    bufp->chgBit(oldp+67,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__clk));
    bufp->chgBit(oldp+68,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst));
    bufp->chgCData(oldp+69,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__din),5);
    bufp->chgCData(oldp+70,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__dout),5);
    bufp->chgCData(oldp+71,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[1]),5);
    bufp->chgCData(oldp+72,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__sync_reg[0]),5);
    bufp->chgBit(oldp+73,(vlSelfRef.async_fifo_top__DOT__u_sync_r2w__DOT__rst_cond));
    bufp->chgBit(oldp+74,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__clk));
    bufp->chgBit(oldp+75,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst));
    bufp->chgCData(oldp+76,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__din),5);
    bufp->chgCData(oldp+77,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__dout),5);
    bufp->chgCData(oldp+78,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[1]),5);
    bufp->chgCData(oldp+79,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__sync_reg[0]),5);
    bufp->chgBit(oldp+80,(vlSelfRef.async_fifo_top__DOT__u_sync_w2r__DOT__rst_cond));
    bufp->chgBit(oldp+81,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wclk));
    bufp->chgBit(oldp+82,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wrst));
    bufp->chgBit(oldp+83,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__winc));
    bufp->chgCData(oldp+84,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rgray_sync),5);
    bufp->chgCData(oldp+85,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__waddr),4);
    bufp->chgCData(oldp+86,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray),5);
    bufp->chgBit(oldp+87,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull));
    bufp->chgCData(oldp+88,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin),5);
    bufp->chgCData(oldp+89,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wbin_next),5);
    bufp->chgCData(oldp+90,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wgray_next),5);
    bufp->chgBit(oldp+91,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__wfull_val));
    bufp->chgBit(oldp+92,(vlSelfRef.async_fifo_top__DOT__u_write_pointer__DOT__rst_cond));
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
