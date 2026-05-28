	component system is
		port (
			clk_clk          : in    std_logic                     := 'X';             -- clk
			flash_address    : in    std_logic_vector(13 downto 0) := (others => 'X'); -- address
			flash_chipselect : in    std_logic                     := 'X';             -- chipselect
			flash_clken      : in    std_logic                     := 'X';             -- clken
			flash_write      : in    std_logic                     := 'X';             -- write
			flash_readdata   : out   std_logic_vector(31 downto 0);                    -- readdata
			flash_writedata  : in    std_logic_vector(31 downto 0) := (others => 'X'); -- writedata
			flash_byteenable : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- byteenable
			flash_1_addr     : out   std_logic_vector(31 downto 0);                    -- addr
			flash_1_data     : in    std_logic_vector(31 downto 0) := (others => 'X'); -- data
			flash_1_stall    : out   std_logic;                                        -- stall
			gpio_port        : inout std_logic_vector(31 downto 0) := (others => 'X'); -- port
			reset_reset_n    : in    std_logic                     := 'X';             -- reset_n
			uart_rx          : in    std_logic                     := 'X';             -- rx
			uart_tx          : out   std_logic;                                        -- tx
			uart_clk_clk     : in    std_logic                     := 'X'              -- clk
		);
	end component system;

	u0 : component system
		port map (
			clk_clk          => CONNECTED_TO_clk_clk,          --      clk.clk
			flash_address    => CONNECTED_TO_flash_address,    --    flash.address
			flash_chipselect => CONNECTED_TO_flash_chipselect, --         .chipselect
			flash_clken      => CONNECTED_TO_flash_clken,      --         .clken
			flash_write      => CONNECTED_TO_flash_write,      --         .write
			flash_readdata   => CONNECTED_TO_flash_readdata,   --         .readdata
			flash_writedata  => CONNECTED_TO_flash_writedata,  --         .writedata
			flash_byteenable => CONNECTED_TO_flash_byteenable, --         .byteenable
			flash_1_addr     => CONNECTED_TO_flash_1_addr,     --  flash_1.addr
			flash_1_data     => CONNECTED_TO_flash_1_data,     --         .data
			flash_1_stall    => CONNECTED_TO_flash_1_stall,    --         .stall
			gpio_port        => CONNECTED_TO_gpio_port,        --     gpio.port
			reset_reset_n    => CONNECTED_TO_reset_reset_n,    --    reset.reset_n
			uart_rx          => CONNECTED_TO_uart_rx,          --     uart.rx
			uart_tx          => CONNECTED_TO_uart_tx,          --         .tx
			uart_clk_clk     => CONNECTED_TO_uart_clk_clk      -- uart_clk.clk
		);

