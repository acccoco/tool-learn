
unix 的 socket 相关练习

需要先下载作者整理的公共库

## 一些问题

### 如何使用tcpdump抓本地回环包？

```shell
sudo tcpdump -i lo port xxx
```

### 如何配置虚拟机的网络，使得可以访问外网，以及被主机访问？

- 设置网卡1：网络地址转换（NAT）。用来访问外网
- 设置网卡2：仅主机（Host-only）网络。用来被主机访问

### tcpdump 格式说明

- 标志：F（FIN），P（PUSH），R（RST）, .（没有标记）
- data-sequence：数据包中的数据顺序号
- ack：。。。
- win：窗口大小
- urgent：是否有紧急指针
- options：选项
- 注：tcpdump只在显示SYN时才显示完整的序号，对于其后的序号则显示他们相对于初始序号的偏移量。
