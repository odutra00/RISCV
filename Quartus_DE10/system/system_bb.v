
module system (
	clk_clk,
	flash_address,
	flash_chipselect,
	flash_clken,
	flash_write,
	flash_readdata,
	flash_writedata,
	flash_byteenable,
	flash_1_addr,
	flash_1_data,
	flash_1_stall,
	gpio_port,
	reset_reset_n,
	uart_rx,
	uart_tx,
	uart_clk_clk);	

	input		clk_clk;
	input	[13:0]	flash_address;
	input		flash_chipselect;
	input		flash_clken;
	input		flash_write;
	output	[31:0]	flash_readdata;
	input	[31:0]	flash_writedata;
	input	[3:0]	flash_byteenable;
	output	[31:0]	flash_1_addr;
	input	[31:0]	flash_1_data;
	output		flash_1_stall;
	inout	[31:0]	gpio_port;
	input		reset_reset_n;
	input		uart_rx;
	output		uart_tx;
	input		uart_clk_clk;
endmodule
