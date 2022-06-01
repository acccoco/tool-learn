这是协程的实践


说明：
- setjmp(jmp_buf)，第一次执行返回0；由longjmp跳转过来会返回非0
- longjmp(jmp_buf, val)，跳转到setjmp的地方，并且将val传递过去作为setjpm的返回值
     如果val是0，那么setjmp会返回1
- jmp_buf里面的内容本来是寄存器的值，但是被glib加密了，所以需要解密
- 在使用协程时，为了不出现意想不到的情况，协程函数应该使用单独的栈
- 创建一个协程的时候，需要自定义pc，esp，ebp这三个值。其中，通过esp分配新的栈
- 设计协程的一个问题是：如何才能够将参数传递给协程函数。要知道，协程函数使用的是新的栈
并不知道函数调用方式，不太方便直接往栈里面写东西。可以利用全局变量来传递参数。
- 参考文章
  - https://blog.csdn.net/dog250/article/details/89742140
  - https://www.cnblogs.com/adinosaur/p/5889014.html
