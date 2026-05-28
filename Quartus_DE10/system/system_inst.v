	system u0 (
		.clk_clk          (<connected-to-clk_clk>),          //      clk.clk
		.flash_address    (<connected-to-flash_address>),    //    flash.address
		.flash_chipselect (<connected-to-flash_chipselect>), //         .chipselect
		.flash_clken      (<connected-to-flash_clken>),      //         .clken
		.flash_write      (<connected-to-flash_write>),      //         .write
		.flash_readdata   (<connected-to-flash_readdata>),   //         .readdata
		.flash_writedata  (<connected-to-flash_writedata>),  //         .writedata
		.flash_byteenable (<connected-to-flash_byteenable>), //         .byteenable
		.flash_1_addr     (<connected-to-flash_1_addr>),     //  flash_1.addr
		.flash_1_data     (<connected-to-flash_1_data>),     //         .data
		.flash_1_stall    (<connected-to-flash_1_stall>),    //         .stall
		.gpio_port        (<connected-to-gpio_port>),        //     gpio.port
		.reset_reset_n    (<connected-to-reset_reset_n>),    //    reset.reset_n
		.uart_rx          (<connected-to-uart_rx>),          //     uart.rx
		.uart_tx          (<connected-to-uart_tx>),          //         .tx
		.uart_clk_clk     (<connected-to-uart_clk_clk>)      // uart_clk.clk
	);

