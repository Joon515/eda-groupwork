// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

// Parameter definitions for Vtop___024root
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__FWFT_EN;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__OUT_REG_EN;
constexpr CData/*1:0*/ Vtop___024root::async_fifo_top__DOT__RST_TYPE;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__RST_POLARITY;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__ALMOST_FULL_EN;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__ALMOST_EMPTY_EN;
constexpr CData/*1:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_r2w__DOT__RST_TYPE;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_r2w__DOT__RST_POLARITY;
constexpr CData/*1:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_w2r__DOT__RST_TYPE;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_w2r__DOT__RST_POLARITY;
constexpr CData/*1:0*/ Vtop___024root::async_fifo_top__DOT__u_write_pointer__DOT__RST_TYPE;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__u_write_pointer__DOT__RST_POLARITY;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__u_write_pointer__DOT__ALMOST_FULL_EN;
constexpr CData/*1:0*/ Vtop___024root::async_fifo_top__DOT__u_read_pointer__DOT__RST_TYPE;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__u_read_pointer__DOT__RST_POLARITY;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__u_read_pointer__DOT__ALMOST_EMPTY_EN;
constexpr CData/*0:0*/ Vtop___024root::async_fifo_top__DOT__u_read_pointer__DOT__FWFT_EN;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__DEPTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__SYNC_STAGES;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__ALMOST_FULL_VAL;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__ALMOST_EMPTY_VAL;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__PTR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__MEM_DEPTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_r2w__DOT__WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_r2w__DOT__STAGES;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_w2r__DOT__WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_sync_w2r__DOT__STAGES;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_write_pointer__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_write_pointer__DOT__DEPTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_write_pointer__DOT__ALMOST_FULL_VAL;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_write_pointer__DOT__PTR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_read_pointer__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_read_pointer__DOT__ALMOST_EMPTY_VAL;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_read_pointer__DOT__PTR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_dual_port_ram__DOT__WIDTH;
constexpr IData/*31:0*/ Vtop___024root::async_fifo_top__DOT__u_dual_port_ram__DOT__DEPTH;


void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf);

Vtop___024root::Vtop___024root(Vtop__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtop___024root___ctor_var_reset(this);
}

void Vtop___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtop___024root::~Vtop___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
