`ifndef FIFO_SEQ_ITEM_SV
`define FIFO_SEQ_ITEM_SV

class fifo_seq_item #(parameter int WIDTH = 16) extends uvm_sequence_item;

    // 随机化控制变量
    rand logic [WIDTH-1:0] data;       // 写入的数据 / 读出的数据
    rand bit               is_write;   // 1: 写操作; 0: 读操作
    rand int unsigned      delay;      // 两次操作之间的空闲时钟周期数

    // 约束条件
    constraint c_delay {
        delay inside {[0:10]};        // 限制随机延迟在 0 到 10 个周期之间
    }

    constraint c_delay_dist {
        delay dist { 0 := 70, [1:3] := 20, [4:10] := 10 }; // 70% 概率连续不间断读写
    }

    // UVM 域自动化宏
    `uvm_object_param_utils_begin(fifo_seq_item #(WIDTH))
        `uvm_field_int(data,     UVM_DEFAULT)
        `uvm_field_int(is_write, UVM_DEFAULT)
        `uvm_field_int(delay,    UVM_DEFAULT)
    `uvm_object_utils_end

    // 构造函数
    function new(string name = "fifo_seq_item");
        super.new(name);
    endfunction : new

    // 方便打印的辅助函数
    function string convert2string();
        return $sformatf("is_write=%0b data=16'h%4h delay=%0d", is_write, data, delay);
    endfunction : convert2string

endclass : fifo_seq_item

`endif // FIFO_SEQ_ITEM_SV