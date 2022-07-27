# riscv-isa-tests for BenRISC-V

RISC-V指令集兼容测试

forked: https://github.com/riscv-software-src/riscv-tests

编译方法:

    $ cd riscv-isa-tests
    $ autoconf
    $ export RISCV=$(pwd)
    $ ./configure --prefix=$RISCV/target
    $ make
    $ make install

编译完成之后，自动生成RTL仿真能读取的mem data文件.  
在target/share/riscv-tests/isa目录下面。

***.data 为仿真使用的mem data文件

目前只编译rv64ui，如果要测试如下指令集，需要修改isa/Makefile:   
rv64uf: RV64 user-level, integer and floating-point    
rv64si: RV64 supervisor-level, integer only      
rv64sv: RV64 supervisor-level, integer and vector    


修改_start入口，去掉reset_vector和异常相关的处理.   

fail和pass的判断：     

```
pass：
x3寄存器： 1
x26寄存器：0x55
x27寄存器：0x55

fail：
x3寄存器： 表示哪个test case出错
x26寄存器：0xbedbeef
x27寄存器：0xbedbeef
```
